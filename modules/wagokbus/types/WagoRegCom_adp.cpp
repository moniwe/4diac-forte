/*************************************************************************
 *** FORTE Library Element
 ***
 *** This file was generated using the 4DIAC FORTE Export Filter 3.0.0.202512231800!
 ***
 *** Name: WagoRegCom
 *** Description: Register communication for Wago modules
 *** Version:
 ***     3.0: 2026-07-21/Monika Wenger -  -
 *************************************************************************/

#include "WagoRegCom_adp.h"

#include "forte/iec61131_functions.h"
#include "forte/datatypes/forte_array_common.h"
#include "forte/datatypes/forte_array.h"
#include "forte/datatypes/forte_array_fixed.h"
#include "forte/datatypes/forte_array_variable.h"

using namespace std::literals;
using namespace forte::literals;

namespace forte::eclipse4diac::io::wago {
  namespace {
    constexpr std::string_view TypeHash ="v1:SHA3-512:ve2dY_xv8S2qPLv8JmRYsQqjAJBEms1gdCcGQcFb8EC0Y20PhHvViqY4FREi1YOJHc_26cN23KmJAtq4Bo5VaA=="sv;

    const auto cEventInputNames = std::array{"CNF"_STRID, "Finished"_STRID};
    const auto cEventOutputNames = std::array{"Read"_STRID, "Write"_STRID, "Complete"_STRID};
    const auto cDataInputNames = std::array{"Counter"_STRID, "rREG_D0"_STRID, "rREG_D1"_STRID};
    const auto cDataOutputNames = std::array{"RegNr"_STRID, "wREG_D0"_STRID, "wREG_D1"_STRID};

    const SFBInterfaceSpec cFBInterfaceSpecSocket = {
        .mEINames = cEventInputNames,
        .mEITypeNames = {},
        .mEONames = cEventOutputNames,
        .mEOTypeNames = {},
        .mDINames = cDataInputNames,
        .mDONames = cDataOutputNames,
        .mDIONames = {},
        .mSocketNames = {},
        .mPlugNames = {},
    };

    const SFBInterfaceSpec cFBInterfaceSpecPlug = {
        .mEINames = cEventOutputNames,
        .mEITypeNames = {},
        .mEONames = cEventInputNames,
        .mEOTypeNames = {},
        .mDINames = cDataOutputNames,
        .mDONames = cDataInputNames,
        .mDIONames = {},
        .mSocketNames = {},
        .mPlugNames = {},
    };
  }

  DEFINE_ADAPTER_TYPE(FORTE_WagoRegCom, "eclipse4diac::io::wago::WagoRegCom"_STRID, TypeHash)


  FORTE_WagoRegCom::FORTE_WagoRegCom(CFBContainer &paContainer,
                               const SFBInterfaceSpec &paInterfaceSpec,
                               const StringId paInstanceNameId,
                               TForteUInt8 paParentAdapterlistID) :
      CAdapter(paContainer, paInterfaceSpec, paInstanceNameId, paParentAdapterlistID),
      var_Counter(0_USINT),
      var_rREG_D0(0_BYTE),
      var_rREG_D1(0_BYTE),
      var_RegNr(0_USINT),
      var_wREG_D0(0_BYTE),
      var_wREG_D1(0_BYTE) {
  }

  void FORTE_WagoRegCom::setInitialValues() {
    forte::CAdapter::setInitialValues();
    var_Counter = 0_USINT;
    var_rREG_D0 = 0_BYTE;
    var_rREG_D1 = 0_BYTE;
    var_RegNr = 0_USINT;
    var_wREG_D0 = 0_BYTE;
    var_wREG_D1 = 0_BYTE;
  }


  FORTE_WagoRegCom_Plug::FORTE_WagoRegCom_Plug(StringId paInstanceNameId,
                                           CFBContainer &paContainer,
                                           TForteUInt8 paParentAdapterlistID) :
      FORTE_WagoRegCom(paContainer, cFBInterfaceSpecPlug, paInstanceNameId, paParentAdapterlistID),
      conn_CNF(*this, 0),
      conn_Finished(*this, 1),
      conn_RegNr(nullptr),
      conn_wREG_D0(nullptr),
      conn_wREG_D1(nullptr),
      conn_Counter(*this, 0, var_Counter),
      conn_rREG_D0(*this, 1, var_rREG_D0),
      conn_rREG_D1(*this, 2, var_rREG_D1) {
  }

  void FORTE_WagoRegCom_Plug::readInputData(const TEventID paEIID) {
    switch(paEIID) {
      case scmEventReadID: {
        readData(3, var_RegNr, conn_RegNr);
        if(auto peer = static_cast<FORTE_WagoRegCom_Socket *>(getPeer()); peer) {
          peer->var_RegNr = var_RegNr;
        }
        break;
      }
      case scmEventWriteID: {
        readData(4, var_wREG_D0, conn_wREG_D0);
        readData(3, var_RegNr, conn_RegNr);
        readData(5, var_wREG_D1, conn_wREG_D1);
        if(auto peer = static_cast<FORTE_WagoRegCom_Socket *>(getPeer()); peer) {
          peer->var_wREG_D0 = var_wREG_D0;
          peer->var_RegNr = var_RegNr;
          peer->var_wREG_D1 = var_wREG_D1;
        }
        break;
      }
      default:
        break;
    }
  }

  void FORTE_WagoRegCom_Plug::writeOutputData(const TEventID paEIID) {
    switch(paEIID) {
      case scmEventCNFID: {
        writeData(0, var_Counter, conn_Counter);
        writeData(1, var_rREG_D0, conn_rREG_D0);
        writeData(2, var_rREG_D1, conn_rREG_D1);
        break;
      }
      default:
        break;
    }
  }
  CIEC_ANY *FORTE_WagoRegCom_Plug::getDI(const size_t paIndex) {
    switch(paIndex) {
      case 0: return &var_RegNr;
      case 1: return &var_wREG_D0;
      case 2: return &var_wREG_D1;
    }
    return nullptr;
  }

  CIEC_ANY *FORTE_WagoRegCom_Plug::getDO(const size_t paIndex) {
    switch(paIndex) {
      case 0: return &var_Counter;
      case 1: return &var_rREG_D0;
      case 2: return &var_rREG_D1;
    }
    return nullptr;
  }

  CEventConnection *FORTE_WagoRegCom_Plug::getEOConUnchecked(const TPortId paIndex) {
    switch(paIndex) {
      case 0: return &conn_CNF;
      case 1: return &conn_Finished;
    }
    return nullptr;
  }

  CDataConnection **FORTE_WagoRegCom_Plug::getDIConUnchecked(const TPortId paIndex) {
    switch(paIndex) {
      case 0: return &conn_RegNr;
      case 1: return &conn_wREG_D0;
      case 2: return &conn_wREG_D1;
    }
    return nullptr;
  }

  CDataConnection *FORTE_WagoRegCom_Plug::getDOConUnchecked(const TPortId paIndex) {
    switch(paIndex) {
      case 0: return &conn_Counter;
      case 1: return &conn_rREG_D0;
      case 2: return &conn_rREG_D1;
    }
    return nullptr;
  }


  FORTE_WagoRegCom_Socket::FORTE_WagoRegCom_Socket(StringId paInstanceNameId,
                                           CFBContainer &paContainer,
                                           TForteUInt8 paParentAdapterlistID) :
      FORTE_WagoRegCom(paContainer, cFBInterfaceSpecSocket, paInstanceNameId, paParentAdapterlistID),
      conn_Read(*this, 0),
      conn_Write(*this, 1),
      conn_Complete(*this, 2),
      conn_Counter(nullptr),
      conn_rREG_D0(nullptr),
      conn_rREG_D1(nullptr),
      conn_RegNr(*this, 0, var_RegNr),
      conn_wREG_D0(*this, 1, var_wREG_D0),
      conn_wREG_D1(*this, 2, var_wREG_D1) {
  }

  void FORTE_WagoRegCom_Socket::readInputData(const TEventID paEIID) {
    switch(paEIID) {
      case scmEventCNFID: {
        readData(0, var_Counter, conn_Counter);
        readData(1, var_rREG_D0, conn_rREG_D0);
        readData(2, var_rREG_D1, conn_rREG_D1);
        if(auto peer = static_cast<FORTE_WagoRegCom_Plug *>(getPeer()); peer) {
          peer->var_Counter = var_Counter;
          peer->var_rREG_D0 = var_rREG_D0;
          peer->var_rREG_D1 = var_rREG_D1;
        }
        break;
      }
      default:
        break;
    }
  }

  void FORTE_WagoRegCom_Socket::writeOutputData(const TEventID paEIID) {
    switch(paEIID) {
      case scmEventReadID: {
        writeData(3, var_RegNr, conn_RegNr);
        break;
      }
      case scmEventWriteID: {
        writeData(4, var_wREG_D0, conn_wREG_D0);
        writeData(3, var_RegNr, conn_RegNr);
        writeData(5, var_wREG_D1, conn_wREG_D1);
        break;
      }
      default:
        break;
    }
  }
  CIEC_ANY *FORTE_WagoRegCom_Socket::getDI(const size_t paIndex) {
    switch(paIndex) {
      case 0: return &var_Counter;
      case 1: return &var_rREG_D0;
      case 2: return &var_rREG_D1;
    }
    return nullptr;
  }

  CIEC_ANY *FORTE_WagoRegCom_Socket::getDO(const size_t paIndex) {
    switch(paIndex) {
      case 0: return &var_RegNr;
      case 1: return &var_wREG_D0;
      case 2: return &var_wREG_D1;
    }
    return nullptr;
  }

  CEventConnection *FORTE_WagoRegCom_Socket::getEOConUnchecked(const TPortId paIndex) {
    switch(paIndex) {
      case 0: return &conn_Read;
      case 1: return &conn_Write;
      case 2: return &conn_Complete;
    }
    return nullptr;
  }

  CDataConnection **FORTE_WagoRegCom_Socket::getDIConUnchecked(const TPortId paIndex) {
    switch(paIndex) {
      case 0: return &conn_Counter;
      case 1: return &conn_rREG_D0;
      case 2: return &conn_rREG_D1;
    }
    return nullptr;
  }

  CDataConnection *FORTE_WagoRegCom_Socket::getDOConUnchecked(const TPortId paIndex) {
    switch(paIndex) {
      case 0: return &conn_RegNr;
      case 1: return &conn_wREG_D0;
      case 2: return &conn_wREG_D1;
    }
    return nullptr;
  }

}
