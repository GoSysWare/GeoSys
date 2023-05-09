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
 v_type t = value.t();
  std::string val;
  
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
    val = value.v().ShortDebugString();
    return QString::fromStdString(val);
    break;
  case v_type::T_IMAGE:
  case v_type::T_LIDAR:
  case v_type::T_SONAR:
  case v_type::T_FILE:
    return QString::fromStdString(" Len: " + std::to_string(value.v().ByteSizeLong()));
    break;
  default:
    return QString::fromStdString(value.v().ShortDebugString());
  }
}
