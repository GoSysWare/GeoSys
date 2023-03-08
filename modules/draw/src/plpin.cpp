#include "plpin.h"

PLPin::PLPin()
{
    hasVariable = false;
    hasInputLink = false;
}
PLPin::~PLPin()
{

}

PLPin::PLPin(const PLPin &pin)
{
    type = pin.type;
    name = pin.name;
    value = pin.value;
    hasVariable = false;
    hasInputLink = false;
}

QString PLPin::getStrValue()
{
 v_type t = value.v().t();

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
    return QString::fromStdString(value.v().ShortDebugString());
    break;
  case v_type::T_BYTES:
  case v_type::T_IMAGE:
  case v_type::T_LIDAR:
  case v_type::T_SONAR:
  case v_type::T_FILE:
    return QString::fromStdString("t: " + v_type_Name(value.v().t()) + " Len: " + std::to_string(value.v().ByteSizeLong()));
    break;
  default:
    return QString::fromStdString(value.v().ShortDebugString());
  }
}
