#ifndef ioss_ddk_h
#define ioss_ddk_h

#include "modules/calc/include/k_evdata.h"
#include <functional>
#include <string>

#define DRIVER_FLAG_LOADED (0x1 << 0)
#define DRIVER_NOT_LOADED (-1)
#define DEVICE_NOT_STARTED (-2)

#define DF_Active (0x1 << 0)
#define DF_Deleted (0x1 << 1)

struct DriverInfo;

typedef struct DeviceInfo {
  struct DriverInfo *drv{0};
  std::string name;
  std::string address;
  std::string parameter;
  unsigned int flags{0};
  int error{0};

} device_t;

// using IO_LOAD_PROC = std::function<bool(DriverInfo *)>;
// using IO_UNLOAD_PROC = std::function<bool()>;
// using IO_START_DEVICE_PROC = std::function<bool(device_t *)>;
// using IO_STOP_DEVICE_PROC = std::function<bool(device_t *)>;
// using IO_ADRESS_TRANSLATE_PROC = std::function<bool(std::string)>;
// using IO_UPDATE_VALUE_PROC = std::function<void(std::string, vam_t)>;
// using IO_WRITE_VALUE_PROC = std::function<bool(std::string, vam_t)>;

typedef bool (*IO_LOAD_PROC)(struct DriverInfo *driver);
typedef bool (*IO_UNLOAD_PROC)();
typedef bool (*IO_START_DEVICE_PROC)(device_t *dev);
typedef bool (*IO_STOP_DEVICE_PROC)(device_t *dev);
typedef bool (*IO_ADDRESS_TRANSLATE_PROC)(std::string tte);
typedef void (*IO_UPDATE_VALUE_PROC)(std::string tag_name, vam_t v);
typedef bool (*IO_WRITE_VALUE_PROC)(std::string tag_name, vam_t v);

typedef struct DriverInfo {
  void *plugin_handle{0};
  IO_LOAD_PROC load{0};
  IO_UNLOAD_PROC unload{0};
  IO_START_DEVICE_PROC start_device{0};
  IO_STOP_DEVICE_PROC stop_device{0};
  IO_ADDRESS_TRANSLATE_PROC address_translate{0};
  IO_UPDATE_VALUE_PROC update_value{0};
  IO_WRITE_VALUE_PROC write_value{0};
  uint32_t device_count{0};
  std::string description;
  std::string parameter;
  std::string dllname;
  uint64_t version{0};
  uint32_t flags{0};
} driver_t;

extern "C"{
bool load(driver_t *dirver);
bool unload();
bool start_device(device_t *device);
bool stop_device(device_t *device);
bool address_translate(std::string tag_name);
bool update_value(std::string tag_name, vam_t value);
bool write_value(std::string tag_name, vam_t vaule);
}

#endif
