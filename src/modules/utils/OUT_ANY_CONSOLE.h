/*******************************************************************************
 * Copyright (c) 2011 - 2014 AIT, ACIN, Profactor GmbH
 *               2023 Martin Erich Jobst
 * This program and the accompanying materials are made available under the
 * terms of the Eclipse Public License 2.0 which is available at
 * http://www.eclipse.org/legal/epl-2.0.
 *
 * SPDX-License-Identifier: EPL-2.0
 *
 * Contributors:
 *   Thomas Strasser, Monika Wenger, Matthias Plasch
 *   - initial API and implementation and/or initial documentation
 *   Martin Jobst
 *     - refactor for ANY variant
 *******************************************************************************/

#pragma once

#include "funcbloc.h"
#include "forte_bool.h"
#include "forte_string.h"
#include "forte_any_variant.h"
#include "iec61131_functions.h"
#include "forte_array_common.h"
#include "forte_array.h"
#include "forte_array_fixed.h"
#include "forte_array_variable.h"


class FORTE_OUT_ANY_CONSOLE: public CFunctionBlock {
  DECLARE_FIRMWARE_FB(FORTE_OUT_ANY_CONSOLE)

private:
  static const CStringDictionary::TStringId scm_anDataInputNames[];
  static const CStringDictionary::TStringId scm_anDataInputTypeIds[];
  
  static const CStringDictionary::TStringId scm_anDataOutputNames[];
  static const CStringDictionary::TStringId scm_anDataOutputTypeIds[];
  
  static const TEventID scm_nEventREQID = 0;
  
  static const TDataIOID scm_anEIWith[];
  static const TForteInt16 scm_anEIWithIndexes[];
  static const CStringDictionary::TStringId scm_anEventInputNames[];
  
  static const TEventID scm_nEventCNFID = 0;
  
  static const TDataIOID scm_anEOWith[]; 
  static const TForteInt16 scm_anEOWithIndexes[];
  static const CStringDictionary::TStringId scm_anEventOutputNames[];
  

  static const SFBInterfaceSpec scm_stFBInterfaceSpec;

  void executeEvent(TEventID pa_nEIID);

  void readInputData(TEventID pa_nEIID) override;
  void writeOutputData(TEventID pa_nEIID) override;

public:
  FORTE_OUT_ANY_CONSOLE(const CStringDictionary::TStringId pa_nInstanceNameId, CResource *pa_poSrcRes);

  CIEC_BOOL var_QI;
  CIEC_STRING var_LABEL;
  CIEC_ANY_VARIANT var_IN;
  CIEC_BOOL var_QO;
  
  CIEC_BOOL var_conn_QO;
  CEventConnection conn_CNF;
  CDataConnection *conn_QI;
  CDataConnection *conn_LABEL;
  CDataConnection *conn_IN;
  CDataConnection conn_QO;
  
  CIEC_ANY *getDI(size_t) override;
  CIEC_ANY *getDO(size_t) override;
  CEventConnection *getEOConUnchecked(TPortId) override;
  CDataConnection **getDIConUnchecked(TPortId) override;
  CDataConnection *getDOConUnchecked(TPortId) override;
  
  void evt_REQ(const CIEC_BOOL &pa_QI, const CIEC_STRING &pa_LABEL, const CIEC_ANY &pa_IN, CIEC_BOOL &pa_QO) {
    var_QI = pa_QI;
    var_LABEL = pa_LABEL;
    var_IN = pa_IN;
    receiveInputEvent(scm_nEventREQID, nullptr);
    pa_QO = var_QO;
  }
  
  void operator()(const CIEC_BOOL &pa_QI, const CIEC_STRING &pa_LABEL, const CIEC_ANY &pa_IN, CIEC_BOOL &pa_QO) {
    evt_REQ(pa_QI, pa_LABEL, pa_IN, pa_QO);
  }
  
};



