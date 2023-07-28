/*******************************************************************************
 * Copyright (c) 2012 - 2023 AIT, Davor Cihlar
 * This program and the accompanying materials are made available under the
 * terms of the Eclipse Public License 2.0 which is available at
 * http://www.eclipse.org/legal/epl-2.0.
 *
 * SPDX-License-Identifier: EPL-2.0
 *
 * Contributors:
 *   Filip Andren - initial API and implementation and/or initial documentation
 *   Davor Cihlar - multiple FBs sharing a single Modbus connection
 *******************************************************************************/
#include "modbusclientconnection.h"
#include "devlog.h"
#include "modbuspoll.h"
#include <forte_thread.h>
#include <unistd.h> // for sleep
// for open and disabling DTR
#include <termios.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>

using namespace modbus_connection_event;

/*************************************
 * CModbusClientConnection class
 *************************************/

CModbusClientConnection::CModbusClientConnection(CModbusHandler* pa_modbusHandler) :
    CModbusConnection(pa_modbusHandler), m_pModbusConnEvent(nullptr), m_nSlaveId(0xFF){
}

CModbusClientConnection::~CModbusClientConnection() {
  if (m_bConnected){
    disconnect();
  }
  for (auto itRunner : m_lstPollList) {
    delete itRunner;
  }
  if (m_pModbusConnEvent != nullptr){
    delete m_pModbusConnEvent;
  }
}

int CModbusClientConnection::readData(CModbusIOBlock* pa_pIOBlock, void* pa_pData, unsigned int pa_nMaxDataSize){
  const unsigned int size = std::min(pa_nMaxDataSize, pa_pIOBlock->getReadSize());
  memcpy(pa_pData, pa_pIOBlock->getCache(), size);
  return (int)size;
}

void CModbusClientConnection::writeDataRange(EModbusFunction pa_eFunction, unsigned int pa_nStartAddress, unsigned int pa_nNrAddresses, const void *pa_pData){
  CCriticalRegion criticalRegion(m_oModbusLock);
  if (!m_bConnected) {
    // TODO: error
    return;
  }
  switch (pa_eFunction) {
    case eCoil:
      modbus_write_bits(m_pModbusConn, pa_nStartAddress, pa_nNrAddresses, (const uint8_t*)pa_pData);
      break;
    case eHoldingRegister:
      modbus_write_registers(m_pModbusConn, pa_nStartAddress, pa_nNrAddresses, (const uint16_t*)pa_pData);
      break;
    default:
      // TODO: error
      break;
  }
}

int CModbusClientConnection::connect(){
  CModbusConnection::connect();

  if(m_nSlaveId != 0xFF){
    modbus_set_slave(m_pModbusConn, m_nSlaveId);
  }

  m_pModbusConnEvent = new CModbusConnectionEvent(1000, getFlowControl(), getDevice());
  m_pModbusConnEvent->activate();

  this->start();

  return 0;
}

void CModbusClientConnection::disconnect(){
  this->end();
  if (m_bConnected){
    modbus_close(m_pModbusConn);
    m_bConnected = false;
  }
  CModbusConnection::disconnect();
}

void CModbusClientConnection::addNewPoll(long pa_nPollInterval, CModbusIOBlock* pa_pIOBlock){
  CModbusPoll *newPoll = nullptr;

  for (auto it : m_lstPollList) {
    if(it->getUpdateInterval() == pa_nPollInterval){
      newPoll = it;
      break;
    }
  }
  if(newPoll == nullptr){
    newPoll = new CModbusPoll(m_pModbusHandler, pa_nPollInterval);
    m_lstPollList.push_back(newPoll);
  }

  newPoll->addPollBlock(pa_pIOBlock);
}

void CModbusClientConnection::setSlaveId(unsigned int pa_nSlaveId){
  m_nSlaveId = pa_nSlaveId;
}

void CModbusClientConnection::run(){

  while(isAlive()){
    if(m_bConnected){
      tryPolling();
    }
    else{
      tryConnect();
    }

    CThread::sleepThread(1);
  }
}

void CModbusClientConnection::tryPolling(){
  unsigned int nrErrors = 0, nrPolls = 0;

  for (size_t index = 0; index < m_lstPollList.size(); ++index) {
    auto itPoll = m_lstPollList[index];

    if(itPoll->readyToExecute()){
      CCriticalRegion criticalRegion(m_oModbusLock);

      int nrVals = itPoll->executeEvent(m_pModbusConn, 0);

      if(nrVals < 0){
        DEVLOG_ERROR("Error reading input status :: %s\n", modbus_strerror(errno));
        itPoll->deactivate();

        nrErrors++;
      }
      ++nrPolls;
    }
  }

  if((nrErrors == nrPolls) && nrPolls && !m_lstPollList.empty()){
    DEVLOG_WARNING("Too many errors on Modbus, reconnecting\n");
    CCriticalRegion criticalRegion(m_oModbusLock);
    modbus_close(m_pModbusConn); // in any case it is worth trying to close the socket
    m_bConnected = false;
    m_pModbusConnEvent = new CModbusConnectionEvent(1000, getFlowControl(), getDevice());
    m_pModbusConnEvent->activate();
  }
}

void CModbusClientConnection::tryConnect(){
  if(m_pModbusConnEvent != nullptr){
    if(m_pModbusConnEvent->readyToExecute()){
      CCriticalRegion criticalRegion(m_oModbusLock);
      if(m_pModbusConnEvent->executeEvent(m_pModbusConn, nullptr) < 0) {
        DEVLOG_ERROR("Connection to Modbus server failed: %s\n", modbus_strerror(errno));
      } else {
        DEVLOG_INFO("Connection to Modbus server succeded\n");

        delete m_pModbusConnEvent;
        m_pModbusConnEvent = nullptr;

        m_bConnected = true;

        // Start polling
        for (auto itPoll : m_lstPollList) {
          itPoll->activate();
        }
      }
    }
  }
}

/*************************************
 * CModbusConnectionEvent class
 *************************************/
CModbusConnectionEvent::CModbusConnectionEvent(long pa_nReconnectInterval, EModbusFlowControl pa_enFlowControl, const char *pa_acDevice) :
    CModbusTimedEvent((TForteUInt32)pa_nReconnectInterval), m_enFlowControl(pa_enFlowControl){
  strcpy(m_acDevice, pa_acDevice);
}

int CModbusConnectionEvent::executeEvent(modbus_t *pa_pModbusConn, void *pa_pRetVal){
  (void)pa_pRetVal; // avoid warning

  restartTimer();

  switch (m_enFlowControl) {
    case eFlowArduino: {
      int fd = open(m_acDevice, O_RDWR);
      if (fd >= 0) {
        termios tty;
        tcgetattr(fd, &tty);
        if (tty.c_cflag & (HUPCL | CRTSCTS)) {
          tty.c_cflag &= ~(HUPCL | CRTSCTS);
          if (!tcsetattr(fd, TCSANOW, &tty)) {
            DEVLOG_INFO("Hardware flow control for Modbus RTU disabled\n");
            // Disabling DTR is not perfect and it will be toggled by this open for disabling it.
            // Therefore, wait for Arduino to boot only if flags weren't previously set.
            sleep(2);
          } else {
            DEVLOG_ERROR("Failed disabling flow control for Modbus RTU\n");
            return -1;
          }
        } else {
          DEVLOG_INFO("Hardware flow control for Modbus RTU was already disabled\n");
        }
        close(fd);
      }
      break;
    }
    default:
      // ignore
      break;
  };

  int retVal = modbus_connect(pa_pModbusConn);

  if (retVal >= 0) {
    switch (m_enFlowControl) {
      case eFlowLongDelay:
        sleep(3);
        // fall through
      case eFlowDelay:
        sleep(2);
        break;
      default:
        // ignore
        break;
    }
  }

  return retVal;
}

