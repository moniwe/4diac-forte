/*************************************************************************
 *** FORTE Library Element
 ***
 *** This file was generated using the 4DIAC FORTE Export Filter 3.0.0.202512231800!
 ***
 *** Name: WagoMaster
 *** Description: Service Interface Function Block Type
 *** Version:
 ***     3.0: 2025-04-14/Patrick Aigner -  - changed package
 ***     1.0: 2018-12-05/Jose Cabral -  -
 *************************************************************************/

#pragma once

#include "WagoBusAdapter_adp.h"
#include "forte/io/configFB/io_master_multi.h"

namespace forte::eclipse4diac::io::wago {
  class FORTE_WagoMaster final : public ::forte::io::IOConfigFBMultiMaster {
      DECLARE_FIRMWARE_FB(FORTE_WagoMaster)

    private:
      static const TEventID scmEventINITOID = 0;
      static const TEventID scmEventINDID = 1;
      static const TEventID scmEventINITID = 0;
      static const int scmBusAdapterOutAdpNum = 0;

      void readInputData(TEventID paEIID) override;
      void writeOutputData(TEventID paEIID) override;
      void setInitialValues() override;

      ::forte::io::IODeviceController *createDeviceController(CDeviceExecution &paDeviceExecution) override;
      void setConfig() override;

    public:
      FORTE_WagoMaster(const StringId paInstanceNameId, CFBContainer &paContainer);
      ~FORTE_WagoMaster() override = default;

      CIEC_BOOL var_QI;
      CIEC_UINT var_UpdateInterval;

      CIEC_BOOL var_QO;
      CIEC_WSTRING var_STATUS;

      CPlugPin<FORTE_WagoBusAdapter_Plug> var_BusAdapterOut;

      CEventConnection conn_INITO;
      CEventConnection conn_IND;

      CDataConnection *conn_QI;
      CDataConnection *conn_UpdateInterval;

      COutDataConnection<CIEC_BOOL> conn_QO;
      COutDataConnection<CIEC_WSTRING> conn_STATUS;

      CIEC_ANY *getDI(size_t) override;
      CIEC_ANY *getDO(size_t) override;
      IPlugPin *getPlugPinUnchecked(size_t) override;
      CEventConnection *getEOConUnchecked(TPortId) override;
      CDataConnection **getDIConUnchecked(TPortId) override;
      CDataConnection *getDOConUnchecked(TPortId) override;

      void evt_INIT(const CIEC_BOOL &paQI, const CIEC_UINT &paUpdateInterval, CAnyBitOutputParameter<CIEC_BOOL> paQO, COutputParameter<CIEC_WSTRING> paSTATUS) {
        COutputGuard guard_QO(paQO);
        COutputGuard guard_STATUS(paSTATUS);
        var_QI = paQI;
        var_UpdateInterval = paUpdateInterval;
        executeEvent(scmEventINITID, nullptr);
        *paQO = var_QO;
        *paSTATUS = var_STATUS;
      }

      void operator()(const CIEC_BOOL &paQI, const CIEC_UINT &paUpdateInterval, CAnyBitOutputParameter<CIEC_BOOL> paQO, COutputParameter<CIEC_WSTRING> paSTATUS) {
        evt_INIT(std::forward<const CIEC_BOOL &>(paQI), std::forward<const CIEC_UINT &>(paUpdateInterval), std::forward<CAnyBitOutputParameter<CIEC_BOOL>>(paQO), std::forward<COutputParameter<CIEC_WSTRING>>(paSTATUS));
      }
  };
}

