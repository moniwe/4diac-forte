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

#pragma once

#include "forte/adapter.h"
#include "forte/datatypes/forte_byte.h"
#include "forte/datatypes/forte_usint.h"

namespace forte::eclipse4diac::io::wago {
  class FORTE_WagoRegCom : public forte::CAdapter {
      DECLARE_ADAPTER_TYPE(FORTE_WagoRegCom)

    private:
      public:
        static const TEventID scmEventReadID = 0;
        static const TEventID scmEventWriteID = 1;
        static const TEventID scmEventCompleteID = 2;

      private:
      public:
        static const TEventID scmEventCNFID = 0;
        static const TEventID scmEventFinishedID = 1;

      private:

      void setInitialValues() override;
    public:
      CIEC_USINT var_Counter;
      CIEC_BYTE var_rREG_D0;
      CIEC_BYTE var_rREG_D1;

      CIEC_USINT var_RegNr;
      CIEC_BYTE var_wREG_D0;
      CIEC_BYTE var_wREG_D1;

      TEventID evt_CNF() {
        return getParentAdapterListEventID() + scmEventCNFID;
      }

      TEventID evt_Finished() {
        return getParentAdapterListEventID() + scmEventFinishedID;
      }

      TEventID evt_Read() {
        return getParentAdapterListEventID() + scmEventReadID;
      }

      TEventID evt_Write() {
        return getParentAdapterListEventID() + scmEventWriteID;
      }

      TEventID evt_Complete() {
        return getParentAdapterListEventID() + scmEventCompleteID;
      }

      ~FORTE_WagoRegCom() override = default;

    protected:
      FORTE_WagoRegCom(CFBContainer &paContainer,
                    const SFBInterfaceSpec &paInterfaceSpec,
                    const StringId paInstanceNameId,
                    TForteUInt8 paParentAdapterlistID);
  };

  class FORTE_WagoRegCom_Plug final : public FORTE_WagoRegCom {
    public:
      FORTE_WagoRegCom_Plug(StringId paInstanceNameId,
                          CFBContainer &paContainer,
                          TForteUInt8 paParentAdapterlistID);
      ~FORTE_WagoRegCom_Plug() override = default;

      CEventConnection conn_CNF;
      CEventConnection conn_Finished;

      CDataConnection *conn_RegNr;
      CDataConnection *conn_wREG_D0;
      CDataConnection *conn_wREG_D1;

      COutDataConnection<CIEC_USINT> conn_Counter;
      COutDataConnection<CIEC_BYTE> conn_rREG_D0;
      COutDataConnection<CIEC_BYTE> conn_rREG_D1;

    private:
      void readInputData(TEventID paEIID) override;
      void writeOutputData(TEventID paEIID) override;
      CIEC_ANY *getDI(size_t) override;
      CIEC_ANY *getDO(size_t) override;
      CEventConnection *getEOConUnchecked(TPortId) override;
      CDataConnection **getDIConUnchecked(TPortId) override;
      CDataConnection *getDOConUnchecked(TPortId) override;
  };

  class FORTE_WagoRegCom_Socket final : public FORTE_WagoRegCom {
    public:
      FORTE_WagoRegCom_Socket(StringId paInstanceNameId,
                          CFBContainer &paContainer,
                          TForteUInt8 paParentAdapterlistID);
      ~FORTE_WagoRegCom_Socket() override = default;

      CEventConnection conn_Read;
      CEventConnection conn_Write;
      CEventConnection conn_Complete;

      CDataConnection *conn_Counter;
      CDataConnection *conn_rREG_D0;
      CDataConnection *conn_rREG_D1;

      COutDataConnection<CIEC_USINT> conn_RegNr;
      COutDataConnection<CIEC_BYTE> conn_wREG_D0;
      COutDataConnection<CIEC_BYTE> conn_wREG_D1;

    private:
      void readInputData(TEventID paEIID) override;
      void writeOutputData(TEventID paEIID) override;
      CIEC_ANY *getDI(size_t) override;
      CIEC_ANY *getDO(size_t) override;
      CEventConnection *getEOConUnchecked(TPortId) override;
      CDataConnection **getDIConUnchecked(TPortId) override;
      CDataConnection *getDOConUnchecked(TPortId) override;
  };
}
