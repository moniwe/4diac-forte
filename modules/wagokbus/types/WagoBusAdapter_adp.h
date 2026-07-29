/*************************************************************************
 *** FORTE Library Element
 ***
 *** This file was generated using the 4DIAC FORTE Export Filter 3.0.0.202512231800!
 ***
 *** Name: WagoBusAdapter
 *** Description:
 *** Version:
 ***     3.0: 2025-04-14/Patrick Aigner -  - changed package
 ***     1.0: 2018-12-05/Jose Cabral -  -
 *************************************************************************/

#pragma once

#include "forte/io/configFB/io_adapter_multi.h"
#include "forte/datatypes/forte_bool.h"
#include "forte/datatypes/forte_uint.h"

namespace forte::eclipse4diac::io::wago {
  class FORTE_WagoBusAdapter : public ::forte::io::IOConfigFBMultiAdapter {
      DECLARE_ADAPTER_TYPE(FORTE_WagoBusAdapter)

      protected:
        void setInitialValues() override;

      public:
      CIEC_BOOL var_QO;

      CIEC_BOOL var_QI;
      CIEC_UINT var_MasterId;
      CIEC_UINT var_Index;

      TEventID evt_INITO() {
        return getParentAdapterListEventID() + scmEventINITOID;
      }

      TEventID evt_INIT() {
        return getParentAdapterListEventID() + scmEventINITID;
      }

      CIEC_ANY *getDeviceConfigPin(int) override {
        return nullptr;
      }

      ~FORTE_WagoBusAdapter() override = default;

    protected:
      FORTE_WagoBusAdapter(CFBContainer &paContainer,
                    const SFBInterfaceSpec &paInterfaceSpec,
                    const StringId paInstanceNameId,
                    TForteUInt8 paParentAdapterlistID);
  };

  class FORTE_WagoBusAdapter_Plug final : public FORTE_WagoBusAdapter {
    public:
      FORTE_WagoBusAdapter_Plug(StringId paInstanceNameId,
                          CFBContainer &paContainer,
                          TForteUInt8 paParentAdapterlistID);
      ~FORTE_WagoBusAdapter_Plug() override = default;

      CEventConnection conn_INITO;

      CDataConnection *conn_QI;
      CDataConnection *conn_MasterId;
      CDataConnection *conn_Index;

      COutDataConnection<CIEC_BOOL> conn_QO;

    private:
      void readInputData(TEventID paEIID) override;
      void writeOutputData(TEventID paEIID) override;
      CIEC_ANY *getDI(size_t) override;
      CIEC_ANY *getDO(size_t) override;
      CEventConnection *getEOConUnchecked(TPortId) override;
      CDataConnection **getDIConUnchecked(TPortId) override;
      CDataConnection *getDOConUnchecked(TPortId) override;
  };

  class FORTE_WagoBusAdapter_Socket final : public FORTE_WagoBusAdapter {
    public:
      FORTE_WagoBusAdapter_Socket(StringId paInstanceNameId,
                          CFBContainer &paContainer,
                          TForteUInt8 paParentAdapterlistID);
      ~FORTE_WagoBusAdapter_Socket() override = default;

      CEventConnection conn_INIT;

      CDataConnection *conn_QO;

      COutDataConnection<CIEC_BOOL> conn_QI;
      COutDataConnection<CIEC_UINT> conn_MasterId;
      COutDataConnection<CIEC_UINT> conn_Index;

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
