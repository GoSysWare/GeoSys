#include "plpin.h"

PLPin::PLPin() {
  hasVariable = false;
  hasInputLink = false;
}
PLPin::~PLPin() {}

PLPin::PLPin(const PLPin &pin) {
  type = pin.type;
  name = pin.name;
  value = pin.value;
  hasVariable = false;
  hasInputLink = false;
}

QString PLPin::getStrValue() {
  v_type t = value.t();
  switch (t) {
    case v_type::T_BOOL:
    case v_type::T_INT32:
    case v_type::T_UINT32:
    case v_type::T_INT64:
    case v_type::T_UINT64:
    case v_type::T_FLOAT32:
    case v_type::T_FLOAT64:
    case v_type::T_TIME:
    case v_type::T_STRING:
    case v_type::T_BYTES:
    case v_type::T_ANY:
      return QString::fromStdString(value.v().ShortDebugString());
    case v_type::T_IMAGE:
    case v_type::T_LIDAR:
    case v_type::T_SONAR:
    case v_type::T_FILE:
      return QString::fromStdString(" Len: " +
                                    std::to_string(value.v().ByteSizeLong()));
    default:
      return QString::fromStdString(value.v().ShortDebugString());
  }
}

QString PLPin::getStrPureValue() {
  v_type t = value.t();
  switch (t) {
    case v_type::T_BOOL:
      return QString::fromStdString(std::to_string(value.v().b()));
    case v_type::T_INT32:
      return QString::fromStdString(std::to_string(value.v().i()));
    case v_type::T_UINT32:
      return QString::fromStdString(std::to_string(value.v().ui()));
    case v_type::T_INT64:
      return QString::fromStdString(std::to_string(value.v().ll()));
    case v_type::T_UINT64:
      return QString::fromStdString(std::to_string(value.v().ull()));
    case v_type::T_FLOAT32:
      return QString::fromStdString(std::to_string(value.v().f()));
    case v_type::T_FLOAT64:
      return QString::fromStdString(std::to_string(value.v().d()));
    case v_type::T_TIME:
      return QString::fromStdString(std::to_string(value.v().tm()));
    case v_type::T_STRING:
      return QString::fromStdString(value.v().str());
    case v_type::T_BYTES:
      return QString::fromStdString(value.v().str());
    case v_type::T_ANY:
    case v_type::T_IMAGE:
    case v_type::T_LIDAR:
    case v_type::T_SONAR:
    case v_type::T_FILE:
    default:
      return QString::fromStdString("");
  }
}
