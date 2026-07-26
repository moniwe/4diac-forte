/*************************************************************************
 *** FORTE Library Element
 ***
 *** This file was generated using the 4DIAC FORTE Export Filter 3.0.0.202512231800!
 ***
 *** Name: WriteRegCom
 *** Description: Write register communication
 *** Version:
 ***     3.0: 2026-07-21/Monika Wenger -  -
 *************************************************************************/

#include "forte/eclipse4diac/io/wago/WriteRegCom_dtp.h"

#include "forte/iec61131_functions.h"
#include "forte/datatypes/forte_array_common.h"
#include "forte/datatypes/forte_array.h"
#include "forte/datatypes/forte_array_fixed.h"
#include "forte/datatypes/forte_array_variable.h"

using namespace std::literals;
using namespace forte::literals;

namespace forte::eclipse4diac::io::wago {
  namespace {
    constexpr std::string_view TypeHash ="v1:SHA3-512:el0-8uZAK1Hqt1-CrxfZTkDMEezLYwJSpamd_hfzu5nglQAyNb6-1mJ5zU9_kGuZ-SRoFu65Wr1P15Q9sZ-XlQ=="sv;
  }

  DEFINE_FIRMWARE_DATATYPE(WriteRegCom, "eclipse4diac::io::wago::WriteRegCom"_STRID, TypeHash);

  const StringId CIEC_WriteRegCom::scmElementNames[] = {"RegNr"_STRID, "REG_D0"_STRID, "REG_D1"_STRID};

  CIEC_WriteRegCom::CIEC_WriteRegCom() :
      CIEC_STRUCT(),
      var_RegNr(0_USINT),
      var_REG_D0(0_BYTE),
      var_REG_D1(0_BYTE) {
  }

  CIEC_WriteRegCom::CIEC_WriteRegCom(const CIEC_USINT &paRegNr, const CIEC_BYTE &paREG_D0, const CIEC_BYTE &paREG_D1) :
      CIEC_STRUCT(),
      var_RegNr(paRegNr),
      var_REG_D0(paREG_D0),
      var_REG_D1(paREG_D1) {
  }

  StringId CIEC_WriteRegCom::getStructTypeNameID() const {
    return "eclipse4diac::io::wago::WriteRegCom"_STRID;
  }

  void CIEC_WriteRegCom::setValue(const CIEC_ANY &paValue) {
    if (paValue.getDataTypeID() == e_STRUCT) {
      auto &otherStruct = static_cast<const CIEC_STRUCT &>(paValue);
      if ("eclipse4diac::io::wago::WriteRegCom"_STRID == otherStruct.getStructTypeNameID()) {
        operator=(static_cast<const CIEC_WriteRegCom &>(paValue));
      }
    }
  }

  CIEC_ANY *CIEC_WriteRegCom::getMember(const size_t paIndex) {
    switch(paIndex) {
      case 0: return &var_RegNr;
      case 1: return &var_REG_D0;
      case 2: return &var_REG_D1;
    }
    return nullptr;
  }

  const CIEC_ANY *CIEC_WriteRegCom::getMember(const size_t paIndex) const {
    switch(paIndex) {
      case 0: return &var_RegNr;
      case 1: return &var_REG_D0;
      case 2: return &var_REG_D1;
    }
    return nullptr;
  }

}