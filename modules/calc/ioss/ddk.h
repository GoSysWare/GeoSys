#ifndef ioss_ddk_h
#define ioss_ddk_h
#include "k_evdata.h"

typedef struct Vendor {
  std::string name;
  std::string desc;
} vendor_t;

typedef struct DeviceType {
  std::string name;
  std::string desc;
} device_type_t;

typedef struct DeviceInfo {

  std::string name;
  vendor_t vendor;
  device_type_t type;
  std::string parameter;
  std::string address;
  unsigned int flags;
  int error;

} device_t;

struct driver_t;

using IO_LOAD_PROC = std::function<bool(driver_t *)>;
using IO_UNLOAD_PROC = std::function<bool()>;
using IO_START_DEVICE_PROC = std::function<bool(device_t *)>;
using IO_STOP_DEVICE_PROC = std::function<bool(device_t *)>;
using IO_ADRESS_TRANSLATE_PROC = std::function<void(std::string)>;
using IO_UPDATE_VALUE_PROC = std::function<void(std::string, vam_t *)>;
using IO_WRITE_VALUE_PROC = std::function<void(std::string, vam_t *)>;

typedef struct DriverInfo {
  void *plugin_handle;
  IO_LOAD_PROC load;
  IO_UNLOAD_PROC unload;
  IO_START_DEVICE_PROC start_device;
  IO_STOP_DEVICE_PROC stop_device;
  IO_ADRESS_TRANSLATE_PROC address_translate;
  IO_UPDATE_VALUE_PROC update_value;
  IO_WRITE_VALUE_PROC write_value;
  uint32_t device_count;
  vendor_t vendor;
  device_type_t type;
  std::string desc;
  std::string parameter;
  std::string dllname;
  uint64_t version;
  uint32_t flags;
} driver_t;


bool load(driver_t * dirver);
bool unload();
bool start_device(device_t * device);
bool stop_device(device_t * device);
bool address_translate(std::string ev_name);
bool update_value(std::string ev_name, vam_t *new_value);
bool write_value(std::string ev_name, vam_t *vaule);


#endif
