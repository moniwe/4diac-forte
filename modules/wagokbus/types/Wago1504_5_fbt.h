/*************************************************************************
 *** FORTE Library Element
 ***
 *** This file was generated using the 4DIAC FORTE Export Filter 3.0.0.202512231800!
 ***
 *** Name: Wago1504_5
 *** Description: Service Interface Function Block Type
 *** Version:
 ***     3.0: 2025-04-14/Patrick Aigner -  - changed package
 ***     1.1: 2024-09-22/Monika Wenger -  -
 ***     1.0: 2018-12-05/Jose Cabral -  -
 *************************************************************************/

#pragma once

#include "WagoSlaveBase.h"

namespace forte::eclipse4diac::io::wago {
  class FORTE_Wago1504_5 final : public WagoSlaveBase {
      DECLARE_FIRMWARE_FB(FORTE_Wago1504_5)

    protected:
      INIT_HANDLES(16, 0, 0, 0)

    private:
      static const TEventID scmEventMAPOID = 0;
      static const TEventID scmEventINDID = 1;
      static const TEventID scmEventMAPID = 0;

      void readInputData(TEventID paEIID) override;
      void writeOutputData(TEventID paEIID) override;
      void setInitialValues() override;

    public:
      FORTE_Wago1504_5(StringId paInstanceNameId, CFBContainer &paContainer);

      CIEC_BOOL var_QI;
      CIEC_STRING var_DigitalOutput_1;
      CIEC_STRING var_DigitalOutput_2;
      CIEC_STRING var_DigitalOutput_3;
      CIEC_STRING var_DigitalOutput_4;
      CIEC_STRING var_DigitalOutput_5;
      CIEC_STRING var_DigitalOutput_6;
      CIEC_STRING var_DigitalOutput_7;
      CIEC_STRING var_DigitalOutput_8;
      CIEC_STRING var_DigitalOutput_9;
      CIEC_STRING var_DigitalOutput_10;
      CIEC_STRING var_DigitalOutput_11;
      CIEC_STRING var_DigitalOutput_12;
      CIEC_STRING var_DigitalOutput_13;
      CIEC_STRING var_DigitalOutput_14;
      CIEC_STRING var_DigitalOutput_15;
      CIEC_STRING var_DigitalOutput_16;

      CIEC_BOOL var_QO;
      CIEC_WSTRING var_STATUS;

      CEventConnection conn_MAPO;
      CEventConnection conn_IND;

      CDataConnection *conn_QI;
      CDataConnection *conn_DigitalOutput_1;
      CDataConnection *conn_DigitalOutput_2;
      CDataConnection *conn_DigitalOutput_3;
      CDataConnection *conn_DigitalOutput_4;
      CDataConnection *conn_DigitalOutput_5;
      CDataConnection *conn_DigitalOutput_6;
      CDataConnection *conn_DigitalOutput_7;
      CDataConnection *conn_DigitalOutput_8;
      CDataConnection *conn_DigitalOutput_9;
      CDataConnection *conn_DigitalOutput_10;
      CDataConnection *conn_DigitalOutput_11;
      CDataConnection *conn_DigitalOutput_12;
      CDataConnection *conn_DigitalOutput_13;
      CDataConnection *conn_DigitalOutput_14;
      CDataConnection *conn_DigitalOutput_15;
      CDataConnection *conn_DigitalOutput_16;

      COutDataConnection<CIEC_BOOL> conn_QO;
      COutDataConnection<CIEC_WSTRING> conn_STATUS;

      CIEC_ANY *getDI(size_t) override;
      CIEC_ANY *getDO(size_t) override;
      forte::ISocketPin *getSocketPinUnchecked(size_t) override;
      forte::IPlugPin *getPlugPinUnchecked(size_t) override;
      CEventConnection *getEOConUnchecked(TPortId) override;
      CDataConnection **getDIConUnchecked(TPortId) override;
      CDataConnection *getDOConUnchecked(TPortId) override;

      void evt_MAP(const CIEC_BOOL &paQI, const CIEC_STRING &paDigitalOutput_1, const CIEC_STRING &paDigitalOutput_2, const CIEC_STRING &paDigitalOutput_3, const CIEC_STRING &paDigitalOutput_4, const CIEC_STRING &paDigitalOutput_5, const CIEC_STRING &paDigitalOutput_6, const CIEC_STRING &paDigitalOutput_7, const CIEC_STRING &paDigitalOutput_8, const CIEC_STRING &paDigitalOutput_9, const CIEC_STRING &paDigitalOutput_10, const CIEC_STRING &paDigitalOutput_11, const CIEC_STRING &paDigitalOutput_12, const CIEC_STRING &paDigitalOutput_13, const CIEC_STRING &paDigitalOutput_14, const CIEC_STRING &paDigitalOutput_15, const CIEC_STRING &paDigitalOutput_16, CAnyBitOutputParameter<CIEC_BOOL> paQO, COutputParameter<CIEC_WSTRING> paSTATUS) {
        COutputGuard guard_QO(paQO);
        COutputGuard guard_STATUS(paSTATUS);
        var_QI = paQI;
        var_DigitalOutput_1 = paDigitalOutput_1;
        var_DigitalOutput_2 = paDigitalOutput_2;
        var_DigitalOutput_3 = paDigitalOutput_3;
        var_DigitalOutput_4 = paDigitalOutput_4;
        var_DigitalOutput_5 = paDigitalOutput_5;
        var_DigitalOutput_6 = paDigitalOutput_6;
        var_DigitalOutput_7 = paDigitalOutput_7;
        var_DigitalOutput_8 = paDigitalOutput_8;
        var_DigitalOutput_9 = paDigitalOutput_9;
        var_DigitalOutput_10 = paDigitalOutput_10;
        var_DigitalOutput_11 = paDigitalOutput_11;
        var_DigitalOutput_12 = paDigitalOutput_12;
        var_DigitalOutput_13 = paDigitalOutput_13;
        var_DigitalOutput_14 = paDigitalOutput_14;
        var_DigitalOutput_15 = paDigitalOutput_15;
        var_DigitalOutput_16 = paDigitalOutput_16;
        executeEvent(scmEventMAPID, nullptr);
        *paQO = var_QO;
        *paSTATUS = var_STATUS;
      }

      void operator()(const CIEC_BOOL &paQI, const CIEC_STRING &paDigitalOutput_1, const CIEC_STRING &paDigitalOutput_2, const CIEC_STRING &paDigitalOutput_3, const CIEC_STRING &paDigitalOutput_4, const CIEC_STRING &paDigitalOutput_5, const CIEC_STRING &paDigitalOutput_6, const CIEC_STRING &paDigitalOutput_7, const CIEC_STRING &paDigitalOutput_8, const CIEC_STRING &paDigitalOutput_9, const CIEC_STRING &paDigitalOutput_10, const CIEC_STRING &paDigitalOutput_11, const CIEC_STRING &paDigitalOutput_12, const CIEC_STRING &paDigitalOutput_13, const CIEC_STRING &paDigitalOutput_14, const CIEC_STRING &paDigitalOutput_15, const CIEC_STRING &paDigitalOutput_16, CAnyBitOutputParameter<CIEC_BOOL> paQO, COutputParameter<CIEC_WSTRING> paSTATUS) {
        evt_MAP(std::forward<const CIEC_BOOL &>(paQI), std::forward<const CIEC_STRING &>(paDigitalOutput_1), std::forward<const CIEC_STRING &>(paDigitalOutput_2), std::forward<const CIEC_STRING &>(paDigitalOutput_3), std::forward<const CIEC_STRING &>(paDigitalOutput_4), std::forward<const CIEC_STRING &>(paDigitalOutput_5), std::forward<const CIEC_STRING &>(paDigitalOutput_6), std::forward<const CIEC_STRING &>(paDigitalOutput_7), std::forward<const CIEC_STRING &>(paDigitalOutput_8), std::forward<const CIEC_STRING &>(paDigitalOutput_9), std::forward<const CIEC_STRING &>(paDigitalOutput_10), std::forward<const CIEC_STRING &>(paDigitalOutput_11), std::forward<const CIEC_STRING &>(paDigitalOutput_12), std::forward<const CIEC_STRING &>(paDigitalOutput_13), std::forward<const CIEC_STRING &>(paDigitalOutput_14), std::forward<const CIEC_STRING &>(paDigitalOutput_15), std::forward<const CIEC_STRING &>(paDigitalOutput_16), std::forward<CAnyBitOutputParameter<CIEC_BOOL>>(paQO), std::forward<COutputParameter<CIEC_WSTRING>>(paSTATUS));
      }
  };
}

