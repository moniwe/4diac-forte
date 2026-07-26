/*************************************************************************
 *** FORTE Library Element
 ***
 *** This file was generated using the 4DIAC FORTE Export Filter 3.0.0.202512231800!
 ***
 *** Name: Wago459
 *** Description: Service Interface Function Block Type
 *** Version:
 ***     3.0: 2025-04-14/Patrick Aigner -  - changed package
 ***     1.1: 2024-09-22/Monika Wenger -  -
 ***     1.0: 2018-12-05/Jose Cabral -  -
 *************************************************************************/

#pragma once

#include "WagoSlaveBase.h"

namespace forte::eclipse4diac::io::wago {
  class FORTE_Wago459 final : public WagoSlaveBase {
      DECLARE_FIRMWARE_FB(FORTE_Wago459)

    protected:
      INIT_HANDLES(0, 0, 4, 0)

    private:
      static const TEventID scmEventMAPOID = 0;
      static const TEventID scmEventINDID = 1;
      static const TEventID scmEventMAPID = 0;

      void readInputData(TEventID paEIID) override;
      void writeOutputData(TEventID paEIID) override;
      void setInitialValues() override;

    public:
      FORTE_Wago459(StringId paInstanceNameId, CFBContainer &paContainer);

      CIEC_BOOL var_QI;
      CIEC_STRING var_AnalogInput_1;
      CIEC_STRING var_AnalogInput_2;
      CIEC_STRING var_AnalogInput_3;
      CIEC_STRING var_AnalogInput_4;

      CIEC_BOOL var_QO;
      CIEC_WSTRING var_STATUS;

      CEventConnection conn_MAPO;
      CEventConnection conn_IND;

      CDataConnection *conn_QI;
      CDataConnection *conn_AnalogInput_1;
      CDataConnection *conn_AnalogInput_2;
      CDataConnection *conn_AnalogInput_3;
      CDataConnection *conn_AnalogInput_4;

      COutDataConnection<CIEC_BOOL> conn_QO;
      COutDataConnection<CIEC_WSTRING> conn_STATUS;

      CIEC_ANY *getDI(size_t) override;
      CIEC_ANY *getDO(size_t) override;
      forte::ISocketPin *getSocketPinUnchecked(size_t) override;
      forte::IPlugPin *getPlugPinUnchecked(size_t) override;
      CEventConnection *getEOConUnchecked(TPortId) override;
      CDataConnection **getDIConUnchecked(TPortId) override;
      CDataConnection *getDOConUnchecked(TPortId) override;

      void evt_MAP(const CIEC_BOOL &paQI, const CIEC_STRING &paAnalogInput_1, const CIEC_STRING &paAnalogInput_2, const CIEC_STRING &paAnalogInput_3, const CIEC_STRING &paAnalogInput_4, CAnyBitOutputParameter<CIEC_BOOL> paQO, COutputParameter<CIEC_WSTRING> paSTATUS) {
        COutputGuard guard_QO(paQO);
        COutputGuard guard_STATUS(paSTATUS);
        var_QI = paQI;
        var_AnalogInput_1 = paAnalogInput_1;
        var_AnalogInput_2 = paAnalogInput_2;
        var_AnalogInput_3 = paAnalogInput_3;
        var_AnalogInput_4 = paAnalogInput_4;
        executeEvent(scmEventMAPID, nullptr);
        *paQO = var_QO;
        *paSTATUS = var_STATUS;
      }

      void operator()(const CIEC_BOOL &paQI, const CIEC_STRING &paAnalogInput_1, const CIEC_STRING &paAnalogInput_2, const CIEC_STRING &paAnalogInput_3, const CIEC_STRING &paAnalogInput_4, CAnyBitOutputParameter<CIEC_BOOL> paQO, COutputParameter<CIEC_WSTRING> paSTATUS) {
        evt_MAP(std::forward<const CIEC_BOOL &>(paQI), std::forward<const CIEC_STRING &>(paAnalogInput_1), std::forward<const CIEC_STRING &>(paAnalogInput_2), std::forward<const CIEC_STRING &>(paAnalogInput_3), std::forward<const CIEC_STRING &>(paAnalogInput_4), std::forward<CAnyBitOutputParameter<CIEC_BOOL>>(paQO), std::forward<COutputParameter<CIEC_WSTRING>>(paSTATUS));
      }
  };
}

