/*************************************************************************
 * Copyright (c) 2016, 2025 fortiss GmbH, Monika Wenger
 * This program and the accompanying materials are made available under the
 * terms of the Eclipse Public License 2.0 which is available at
 * http://www.eclipse.org/legal/epl-2.0.
 *
 * SPDX-License-Identifier: EPL-2.0
 *************************************************************************/

#pragma once

#include "forte/io/configFB/io_slave_multi.h"
#include "WagoBusAdapter_adp.h"
#include "forte/datatypes/forte_bool.h"
#include "forte/datatypes/forte_string.h"
#include "forte/datatypes/forte_wstring.h"

#define INIT_HANDLES(noOfBoolInputs, noOfBoolOutputs, noOfAnalogInputs, noOfAnalogOutputs)                             \
  void initHandles() override {                                                                                        \
    initHandlesBase(noOfBoolInputs, noOfBoolOutputs, noOfAnalogInputs, noOfAnalogOutputs);                             \
  };

using namespace forte::literals;

namespace forte::eclipse4diac::io::wago {

	class WagoSlaveBase : public forte::io::IOConfigFBMultiSlave {

	  public:
	    forte::CPlugPin<FORTE_WagoBusAdapter_Plug> var_BusAdapterOut;
	    forte::CSocketPin<FORTE_WagoBusAdapter_Socket> var_BusAdapterIn;

	  protected:
	    WagoSlaveBase(int paType,
                      CFBContainer &paContainer,
                      const SFBInterfaceSpec &paInterfaceSpec,
                      const forte::StringId paInstanceNameId);
        ~WagoSlaveBase() override = default;

        void initHandlesBase(size_t paNumberOfBoolInputs,
	                         size_t paNumberOfBoolOutputs,
	                         size_t paNumberOfAnalogInputs,
	                         size_t paNumberOfAnalogOutputs);
	    void initHandles() override = 0;
	    void initWagoHandle(int paDIIndex,
	                        int paIOIndex,
	                        CIEC_ANY::EDataTypeID paType,
	                        forte::io::IOMapper::Direction paDirection);

	  private:
	    static const TForteUInt8 scmSlaveConfigurationIO[];
	    static const TForteUInt8 scmSlaveConfigurationIONum;
	};

}
