#ifndef ioss_ddk_h
#define ioss_ddk_h

#include<string>
#include<functional>
#include "modules/calc/include/k_evdata.h"

#define DRIVER_FLAG_LOADED	(0x1<<0) 
#define DRIVER_NOT_LOADED	(-1) 
#define DEVICE_NOT_STARTED	(-2) 


#define DF_Active		(0x1 << 0)
#define DF_Deleted	(0x1 << 1)

struct DriverInfo;

typedef struct DeviceInfo {
  struct DriverInfo * drv;
  std::string name;
  std::string address;
  std::string parameter;
  unsigned int flags;
  int error;

} device_t;


using IO_LOAD_PROC = std::function<bool(DriverInfo *)>;
using IO_UNLOAD_PROC = std::function<bool()>;
using IO_START_DEVICE_PROC = std::function<bool(device_t *)>;
using IO_STOP_DEVICE_PROC = std::function<bool(device_t *)>;
using IO_ADRESS_TRANSLATE_PROC = std::function<bool(std::string)>;
using IO_UPDATE_VALUE_PROC = std::function<void(std::string, vam_t )>;
using IO_WRITE_VALUE_PROC = std::function<bool(std::string, vam_t )>;

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
  std::string description;
  std::string parameter;
  std::string dllname;
  uint64_t version;
  uint32_t flags;
} driver_t;


bool load(driver_t * dirver);
bool unload();
bool start_device(device_t * device);
bool stop_device(device_t * device);
bool address_translate(std::string tag_name);
bool update_value(std::string tag_name, vam_t new_value);
bool write_value(std::string tag_name, vam_t vaule);


#endif
