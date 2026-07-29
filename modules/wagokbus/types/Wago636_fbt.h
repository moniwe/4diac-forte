/*************************************************************************
 *** FORTE Library Element
 ***
 *** This file was generated using the 4DIAC FORTE Export Filter 3.0.0.202512231800!
 ***
 *** Name: Wago636
 *** Description: Wago 750-636 DC-Drive-Controller 24V 5A
 *** Version:
 ***     3.0: 2026-07-20/Monika Wenger -  - change package
 ***     1.0: 2025-05-05/Monika Wenger -  -
 *************************************************************************/

#pragma once

#include "WagoSlaveBase.h"

namespace forte::eclipse4diac::io::wago {

  class FORTE_Wago636 final : public WagoSlaveBase {
      DECLARE_FIRMWARE_FB(FORTE_Wago636)

    private:
      static const TEventID scmEventMAPOID = 0;
      static const TEventID scmEventINDID = 1;
      static const TEventID scmEventMAPID = 0;

      void readInputData(TEventID paEIID) override;
      void writeOutputData(TEventID paEIID) override;
      void setInitialValues() override;

    protected:
        void initHandlesBase(size_t paNumberOfBoolInputs,
                             size_t paNumberOfBoolOutputs,
                             size_t paNumberOfAnalogInputs,
                             size_t paNumberOfAnalogOutputs);
        INIT_HANDLES(7, 7, 1, 1)

    public:
      FORTE_Wago636(StringId paInstanceNameId, CFBContainer &paContainer);

      CIEC_BOOL var_QI;
      CIEC_STRING var_Busy;
      CIEC_STRING var_LimitSwitchN;
      CIEC_STRING var_LimitSwitchP;
      CIEC_STRING var_PresetInput;
      CIEC_STRING var_OptimizeOnZInput;
      CIEC_STRING var_OnTarget;
      CIEC_STRING var_ReferenceOk;
      CIEC_STRING var_CurrentPosition;
      CIEC_STRING var_TargetPosition;
      CIEC_STRING var_MotorN;
      CIEC_STRING var_MotorP;
      CIEC_STRING var_Positioning;
      CIEC_STRING var_OptimizeOn;
      CIEC_STRING var_Preset;
      CIEC_STRING var_PresetInputEnable;
      CIEC_STRING var_QuitErrors;

      CIEC_BOOL var_QO;
      CIEC_WSTRING var_STATUS;

      CEventConnection conn_MAPO;
      CEventConnection conn_IND;

      CDataConnection *conn_QI;
      CDataConnection *conn_Busy;
      CDataConnection *conn_LimitSwitchN;
      CDataConnection *conn_LimitSwitchP;
      CDataConnection *conn_PresetInput;
      CDataConnection *conn_OptimizeOnZInput;
      CDataConnection *conn_OnTarget;
      CDataConnection *conn_ReferenceOk;
      CDataConnection *conn_CurrentPosition;
      CDataConnection *conn_TargetPosition;
      CDataConnection *conn_MotorN;
      CDataConnection *conn_MotorP;
      CDataConnection *conn_Positioning;
      CDataConnection *conn_OptimizeOn;
      CDataConnection *conn_Preset;
      CDataConnection *conn_PresetInputEnable;
      CDataConnection *conn_QuitErrors;

      COutDataConnection<CIEC_BOOL> conn_QO;
      COutDataConnection<CIEC_WSTRING> conn_STATUS;

      CIEC_ANY *getDI(size_t) override;
      CIEC_ANY *getDO(size_t) override;
      forte::ISocketPin *getSocketPinUnchecked(size_t) override;
      forte::IPlugPin *getPlugPinUnchecked(size_t) override;
      CEventConnection *getEOConUnchecked(TPortId) override;
      CDataConnection **getDIConUnchecked(TPortId) override;
      CDataConnection *getDOConUnchecked(TPortId) override;

      void evt_MAP(const CIEC_BOOL &paQI, const CIEC_STRING &paBusy, const CIEC_STRING &paLimitSwitchN, const CIEC_STRING &paLimitSwitchP, const CIEC_STRING &paPresetInput, const CIEC_STRING &paOptimizeOnZInput, const CIEC_STRING &paOnTarget, const CIEC_STRING &paReferenceOk, const CIEC_STRING &paCurrentPosition, const CIEC_STRING &paTargetPosition, const CIEC_STRING &paMotorN, const CIEC_STRING &paMotorP, const CIEC_STRING &paPositioning, const CIEC_STRING &paOptimizeOn, const CIEC_STRING &paPreset, const CIEC_STRING &paPresetInputEnable, const CIEC_STRING &paQuitErrors, CAnyBitOutputParameter<CIEC_BOOL> paQO, COutputParameter<CIEC_WSTRING> paSTATUS) {
        COutputGuard guard_QO(paQO);
        COutputGuard guard_STATUS(paSTATUS);
        var_QI = paQI;
        var_Busy = paBusy;
        var_LimitSwitchN = paLimitSwitchN;
        var_LimitSwitchP = paLimitSwitchP;
        var_PresetInput = paPresetInput;
        var_OptimizeOnZInput = paOptimizeOnZInput;
        var_OnTarget = paOnTarget;
        var_ReferenceOk = paReferenceOk;
        var_CurrentPosition = paCurrentPosition;
        var_TargetPosition = paTargetPosition;
        var_MotorN = paMotorN;
        var_MotorP = paMotorP;
        var_Positioning = paPositioning;
        var_OptimizeOn = paOptimizeOn;
        var_Preset = paPreset;
        var_PresetInputEnable = paPresetInputEnable;
        var_QuitErrors = paQuitErrors;
        executeEvent(scmEventMAPID, nullptr);
        *paQO = var_QO;
        *paSTATUS = var_STATUS;
      }

      void operator()(const CIEC_BOOL &paQI, const CIEC_STRING &paBusy, const CIEC_STRING &paLimitSwitchN, const CIEC_STRING &paLimitSwitchP, const CIEC_STRING &paPresetInput, const CIEC_STRING &paOptimizeOnZInput, const CIEC_STRING &paOnTarget, const CIEC_STRING &paReferenceOk, const CIEC_STRING &paCurrentPosition, const CIEC_STRING &paTargetPosition, const CIEC_STRING &paMotorN, const CIEC_STRING &paMotorP, const CIEC_STRING &paPositioning, const CIEC_STRING &paOptimizeOn, const CIEC_STRING &paPreset, const CIEC_STRING &paPresetInputEnable, const CIEC_STRING &paQuitErrors, CAnyBitOutputParameter<CIEC_BOOL> paQO, COutputParameter<CIEC_WSTRING> paSTATUS) {
        evt_MAP(std::forward<const CIEC_BOOL &>(paQI), std::forward<const CIEC_STRING &>(paBusy), std::forward<const CIEC_STRING &>(paLimitSwitchN), std::forward<const CIEC_STRING &>(paLimitSwitchP), std::forward<const CIEC_STRING &>(paPresetInput), std::forward<const CIEC_STRING &>(paOptimizeOnZInput), std::forward<const CIEC_STRING &>(paOnTarget), std::forward<const CIEC_STRING &>(paReferenceOk), std::forward<const CIEC_STRING &>(paCurrentPosition), std::forward<const CIEC_STRING &>(paTargetPosition), std::forward<const CIEC_STRING &>(paMotorN), std::forward<const CIEC_STRING &>(paMotorP), std::forward<const CIEC_STRING &>(paPositioning), std::forward<const CIEC_STRING &>(paOptimizeOn), std::forward<const CIEC_STRING &>(paPreset), std::forward<const CIEC_STRING &>(paPresetInputEnable), std::forward<const CIEC_STRING &>(paQuitErrors), std::forward<CAnyBitOutputParameter<CIEC_BOOL>>(paQO), std::forward<COutputParameter<CIEC_WSTRING>>(paSTATUS));
      }
  };
}

