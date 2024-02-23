/*******************************************************************************
 * Copyright (c) 2017 - 2018 fortiss GmbH
 * This program and the accompanying materials are made available under the
 * terms of the Eclipse Public License 2.0 which is available at
 * http://www.eclipse.org/legal/epl-2.0.
 *
 * SPDX-License-Identifier: EPL-2.0
 *
 * Contributors:
 *   Johannes Messmer - initial API and implementation and/or initial documentation
 *   Jose Cabral - Cleaning of namespaces
 *******************************************************************************/

#ifndef SRC_CORE_IO_DEVICE_IO_CONTROLLER_MULTI_H_
#define SRC_CORE_IO_DEVICE_IO_CONTROLLER_MULTI_H_

#include "io_controller.h"
#include <io/mapper/io_handle.h>

namespace forte {
  namespace core {
    namespace io {

      class IOConfigFBMultiSlave;

      /*! @brief Abstract Device Controller for modular devices
       *
       * The IODeviceMultiController extends the abstract #IODeviceController.
       * It integrates additional functionality for modular devices.
       * The controller should be used with the #IOConfigFBMulti configuration fbs.
       */
      class IODeviceMultiController : public IODeviceController {
          friend class IOConfigFBMultiSlave;

        public:

          class HandleDescriptor : public IODeviceController::HandleDescriptor {
            public:
              int mSlaveIndex;

              HandleDescriptor(std::string const &paId, IOMapper::Direction paDirection, int paSlaveIndex) :
                  IODeviceController::HandleDescriptor(paId, paDirection), mSlaveIndex(paSlaveIndex) {
              }
          };

          /*! @brief Adds a handle for a slave
           *
           * The controller should read and write the given handle.
           * It should keep a list of handles and delete the provided handle in case the #dropSlaveHandles method is called.
           *
           * @param paIndex Index/Position of the modular slave
           * @param paHandle IOHandle object which should be updated by the controller.
           */
          virtual void addSlaveHandle(int paIndex, IOHandle* paHandle) = 0;

          /*! @brief Drop all handles of a specific slave
           *
           * The method should delete all handles of the indexed slave.
           * All handles which were added by the #addSlaveHandle method should be deleted.
           *
           * @param paIndex Index/Position of the modular slave
           */
          virtual void dropSlaveHandles(int paIndex) = 0;

        protected:
          explicit IODeviceMultiController(CDeviceExecution& paDeviceExecution);

          void addHandle(IODeviceController::HandleDescriptor &paHandleDescriptor) override;

<<<<<<< Upstream, based on eclipse/develop
          IOHandle* createIOHandle(IODeviceController::HandleDescriptor &paHandleDescriptor) override = 0;

=======
>>>>>>> 78ecaa2 Upgraded RevPi elements to latest IO and FB interface
        private:

          /*! @brief Checks if a slave exists at the given index
           *
           * @param paIndex Index/Position of the modular slave
           * @return True in case a slave was found at the given position
           */
          virtual bool isSlaveAvailable(int paIndex) = 0;

          /*! @brief Checks if the slave type matches the configured type
           *
           * @param paIndex Index/Position of the modular slave
           * @param paType Type identifier which describes the modular slave
           * @return True in case the slave at the index has the given type
           */
          virtual bool checkSlaveType(int paIndex, int paType) = 0;

      };

    } //namespace IO
  } //namepsace core
} //namespace forte

#endif /* SRC_CORE_IO_DEVICE_IO_CONTROLLER_MULTI_H_ */
