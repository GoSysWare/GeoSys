#include "plevdata.h"
PLEVData::PLEVData() {
  initValue.set_t(v_type::T_NONE);
  value.set_t(v_type::T_NONE);
}

PLEVData::PLEVData(const PLEVData &ev) {
  id = ev.id;
  idLog = ev.idLog;
  name = ev.name;
  desc = ev.desc;
  refIn = ev.refIn;
  refOut = ev.refOut;
  initValue = ev.initValue;
  value = ev.value;
  isSelected = ev.isSelected;
  type = ev.type;
}
PLEVData::~PLEVData() {}

QString PLEVData::getStrValue() {
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
    return QString::fromStdString(value.v().ShortDebugString());
    break;
  case v_type::T_BYTES:
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

QString PLEVData::getStrInitValue() {
  v_type t = initValue.t();

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
    return QString::fromStdString( " Len: " + std::to_string(value.v().ByteSizeLong()));
    break;
  default:
    return QString::fromStdString(value.v().ShortDebugString());
  }
}