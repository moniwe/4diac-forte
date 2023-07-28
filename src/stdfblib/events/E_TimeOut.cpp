/*******************************************************************************
 * Copyright (c) 2013 fortiss GmbH
 * This program and the accompanying materials are made available under the
 * terms of the Eclipse Public License 2.0 which is available at
 * http://www.eclipse.org/legal/epl-2.0.
 *
 * SPDX-License-Identifier: EPL-2.0
 *
 * Contributors:
 *   Alois Zoitl - initial API and implementation and/or initial documentation
 *******************************************************************************/

#include "E_TimeOut.h"
#ifdef FORTE_ENABLE_GENERATED_SOURCE_CPP
#include "E_TimeOut_gen.cpp"
#endif

#include "criticalregion.h"
#include "resource.h"

DEFINE_FIRMWARE_FB(FORTE_E_TimeOut, g_nStringIdE_TimeOut)

const TForteInt16 FORTE_E_TimeOut::scm_anEOWithIndexes[] = { -1 };
const SAdapterInstanceDef FORTE_E_TimeOut::scm_astAdapterInstances[] = { { g_nStringIdATimeOut, g_nStringIdTimeOutSocket, false } };

const SFBInterfaceSpec FORTE_E_TimeOut::scm_stFBInterfaceSpec = { 0, nullptr, nullptr, nullptr, 0, nullptr, nullptr, nullptr, 0, nullptr, nullptr, 0, nullptr, nullptr, 1, scm_astAdapterInstances };

void FORTE_E_TimeOut::executeEvent(TEventID pa_nEIID){
  if(cg_nExternalEventID == pa_nEIID){
    mActive = false;
    sendAdapterEvent(scm_nTimeOutSocketAdpNum, FORTE_ATimeOut::scm_nEventTimeOutID);
  }
  else if(var_TimeOutSocket().evt_START() == pa_nEIID){
    if(!mActive){
      setEventChainExecutor(mInvokingExecEnv);  // delay notification should be execute in the same thread on as from where it has been triggered.
      getTimer().registerTimedFB(&mTimeListEntry, var_TimeOutSocket().var_DT());
      mActive = true;
    }
  }
  else if(var_TimeOutSocket().evt_STOP() == pa_nEIID){
    if(mActive){
      getTimer().unregisterTimedFB(this);
      mActive = false;
    }
  }
}

EMGMResponse FORTE_E_TimeOut::changeFBExecutionState(EMGMCommandType pa_unCommand){
  EMGMResponse eRetVal = CFunctionBlock::changeFBExecutionState(pa_unCommand);
  if((EMGMResponse::Ready == eRetVal) && ((EMGMCommandType::Stop == pa_unCommand) || (EMGMCommandType::Kill == pa_unCommand))){
    if(mActive){
      getTimer().unregisterTimedFB(this);
      mActive = false;
    }
  }
  return eRetVal;
}
