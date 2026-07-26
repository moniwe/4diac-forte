/*************************************************************************
 *** FORTE Library Element
 ***
 *** This file was generated using the 4DIAC FORTE Export Filter 3.0.0.202512231800!
 ***
 *** Name: Wago1405_6
 *** Description: Service Interface Function Block Type
 *** Version:
 ***     3.0: 2025-04-14/Patrick Aigner -  - changed package
 ***     1.1: 2024-09-22/Monika Wenger -  -
 ***     1.0: 2018-12-05/Jose Cabral -  -
 *************************************************************************/

#pragma once

#include "WagoSlaveBase.h"

namespace forte::eclipse4diac::io::wago {

  class FORTE_Wago1405_6 final : public WagoSlaveBase {
      DECLARE_FIRMWARE_FB(FORTE_Wago1405_6)

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
      FORTE_Wago1405_6(StringId paInstanceNameId, CFBContainer &paContainer);

      CIEC_BOOL var_QI;
      CIEC_STRING var_DigitalInput_1;
      CIEC_STRING var_DigitalInput_2;
      CIEC_STRING var_DigitalInput_3;
      CIEC_STRING var_DigitalInput_4;
      CIEC_STRING var_DigitalInput_5;
      CIEC_STRING var_DigitalInput_6;
      CIEC_STRING var_DigitalInput_7;
      CIEC_STRING var_DigitalInput_8;
      CIEC_STRING var_DigitalInput_9;
      CIEC_STRING var_DigitalInput_10;
      CIEC_STRING var_DigitalInput_11;
      CIEC_STRING var_DigitalInput_12;
      CIEC_STRING var_DigitalInput_13;
      CIEC_STRING var_DigitalInput_14;
      CIEC_STRING var_DigitalInput_15;
      CIEC_STRING var_DigitalInput_16;

      CIEC_BOOL var_QO;
      CIEC_WSTRING var_STATUS;

      CEventConnection conn_MAPO;
      CEventConnection conn_IND;

      CDataConnection *conn_QI;
      CDataConnection *conn_DigitalInput_1;
      CDataConnection *conn_DigitalInput_2;
      CDataConnection *conn_DigitalInput_3;
      CDataConnection *conn_DigitalInput_4;
      CDataConnection *conn_DigitalInput_5;
      CDataConnection *conn_DigitalInput_6;
      CDataConnection *conn_DigitalInput_7;
      CDataConnection *conn_DigitalInput_8;
      CDataConnection *conn_DigitalInput_9;
      CDataConnection *conn_DigitalInput_10;
      CDataConnection *conn_DigitalInput_11;
      CDataConnection *conn_DigitalInput_12;
      CDataConnection *conn_DigitalInput_13;
      CDataConnection *conn_DigitalInput_14;
      CDataConnection *conn_DigitalInput_15;
      CDataConnection *conn_DigitalInput_16;

      COutDataConnection<CIEC_BOOL> conn_QO;
      COutDataConnection<CIEC_WSTRING> conn_STATUS;

      CIEC_ANY *getDI(size_t) override;
      CIEC_ANY *getDO(size_t) override;
      forte::ISocketPin *getSocketPinUnchecked(size_t) override;
      forte::IPlugPin *getPlugPinUnchecked(size_t) override;
      CEventConnection *getEOConUnchecked(TPortId) override;
      CDataConnection **getDIConUnchecked(TPortId) override;
      CDataConnection *getDOConUnchecked(TPortId) override;

      void evt_MAP(const CIEC_BOOL &paQI, const CIEC_STRING &paDigitalInput_1, const CIEC_STRING &paDigitalInput_2, const CIEC_STRING &paDigitalInput_3, const CIEC_STRING &paDigitalInput_4, const CIEC_STRING &paDigitalInput_5, const CIEC_STRING &paDigitalInput_6, const CIEC_STRING &paDigitalInput_7, const CIEC_STRING &paDigitalInput_8, const CIEC_STRING &paDigitalInput_9, const CIEC_STRING &paDigitalInput_10, const CIEC_STRING &paDigitalInput_11, const CIEC_STRING &paDigitalInput_12, const CIEC_STRING &paDigitalInput_13, const CIEC_STRING &paDigitalInput_14, const CIEC_STRING &paDigitalInput_15, const CIEC_STRING &paDigitalInput_16, CAnyBitOutputParameter<CIEC_BOOL> paQO, COutputParameter<CIEC_WSTRING> paSTATUS) {
        COutputGuard guard_QO(paQO);
        COutputGuard guard_STATUS(paSTATUS);
        var_QI = paQI;
        var_DigitalInput_1 = paDigitalInput_1;
        var_DigitalInput_2 = paDigitalInput_2;
        var_DigitalInput_3 = paDigitalInput_3;
        var_DigitalInput_4 = paDigitalInput_4;
        var_DigitalInput_5 = paDigitalInput_5;
        var_DigitalInput_6 = paDigitalInput_6;
        var_DigitalInput_7 = paDigitalInput_7;
        var_DigitalInput_8 = paDigitalInput_8;
        var_DigitalInput_9 = paDigitalInput_9;
        var_DigitalInput_10 = paDigitalInput_10;
        var_DigitalInput_11 = paDigitalInput_11;
        var_DigitalInput_12 = paDigitalInput_12;
        var_DigitalInput_13 = paDigitalInput_13;
        var_DigitalInput_14 = paDigitalInput_14;
        var_DigitalInput_15 = paDigitalInput_15;
        var_DigitalInput_16 = paDigitalInput_16;
        executeEvent(scmEventMAPID, nullptr);
        *paQO = var_QO;
        *paSTATUS = var_STATUS;
      }

      void operator()(const CIEC_BOOL &paQI, const CIEC_STRING &paDigitalInput_1, const CIEC_STRING &paDigitalInput_2, const CIEC_STRING &paDigitalInput_3, const CIEC_STRING &paDigitalInput_4, const CIEC_STRING &paDigitalInput_5, const CIEC_STRING &paDigitalInput_6, const CIEC_STRING &paDigitalInput_7, const CIEC_STRING &paDigitalInput_8, const CIEC_STRING &paDigitalInput_9, const CIEC_STRING &paDigitalInput_10, const CIEC_STRING &paDigitalInput_11, const CIEC_STRING &paDigitalInput_12, const CIEC_STRING &paDigitalInput_13, const CIEC_STRING &paDigitalInput_14, const CIEC_STRING &paDigitalInput_15, const CIEC_STRING &paDigitalInput_16, CAnyBitOutputParameter<CIEC_BOOL> paQO, COutputParameter<CIEC_WSTRING> paSTATUS) {
        evt_MAP(std::forward<const CIEC_BOOL &>(paQI), std::forward<const CIEC_STRING &>(paDigitalInput_1), std::forward<const CIEC_STRING &>(paDigitalInput_2), std::forward<const CIEC_STRING &>(paDigitalInput_3), std::forward<const CIEC_STRING &>(paDigitalInput_4), std::forward<const CIEC_STRING &>(paDigitalInput_5), std::forward<const CIEC_STRING &>(paDigitalInput_6), std::forward<const CIEC_STRING &>(paDigitalInput_7), std::forward<const CIEC_STRING &>(paDigitalInput_8), std::forward<const CIEC_STRING &>(paDigitalInput_9), std::forward<const CIEC_STRING &>(paDigitalInput_10), std::forward<const CIEC_STRING &>(paDigitalInput_11), std::forward<const CIEC_STRING &>(paDigitalInput_12), std::forward<const CIEC_STRING &>(paDigitalInput_13), std::forward<const CIEC_STRING &>(paDigitalInput_14), std::forward<const CIEC_STRING &>(paDigitalInput_15), std::forward<const CIEC_STRING &>(paDigitalInput_16), std::forward<CAnyBitOutputParameter<CIEC_BOOL>>(paQO), std::forward<COutputParameter<CIEC_WSTRING>>(paSTATUS));
      }
  };
}
