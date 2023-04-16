

#ifdef _MSC_VER
#pragma warning(disable : 4786)
#define WIN32_LEAN_AND_MEAN
#include <windows.h>
#endif

#include <dlfcn.h>

#include "ddk.h"
#include "ioss.h"

DRIVER_LIST g_drivers;
extern IOSS::DevicesCfg g_devices_cfg;

#ifndef _WIN32
#define LoadLibrary(name, flag) dlopen(name, flag)
#define HINSTANCE void *
#define GetProcAddress(handle, name) dlsym(handle, name)
#define FARPROC void *
#define FreeLibrary(handle) dlclose(handle)
#endif

#ifdef _WIN32
#define DLL_SUFFIX ".dll"
#else
#define DLL_SUFFIX ".so"
#endif


template<class T>
T* dlsym_ptr(void* handle, char const* name) {
  return static_cast<T*>( dlsym( handle, name ) );
}

bool _load_module(driver_t &driver) {
  HINSTANCE h;

  driver.flags &= ~DRIVER_FLAG_LOADED;
  int real_flag = RTLD_LAZY|RTLD_GLOBAL;
  h = LoadLibrary(driver.dllname.c_str(), real_flag);

  if (!h) {
    std::cout << "dlopen " << dlerror() << std::endl;
    driver.dllname += DLL_SUFFIX;
    h = LoadLibrary(driver.dllname.c_str(), real_flag);
  }

  if (!h) {
    return false;
  }

  driver.plugin_handle = (void *)h;
  driver.flags |= DRIVER_FLAG_LOADED;

  //将dll导出函数指针赋给DRIVER_INFO   driver中
  (FARPROC &)driver.load =
      GetProcAddress(h, "load"); //得到设备驱动dll导出函数load()的指针
  (FARPROC &)driver.unload = GetProcAddress(h, "unload");
  (FARPROC &)driver.start_device = GetProcAddress(h, "start_device");
  (FARPROC &)driver.stop_device = GetProcAddress(h, "stop_device");
  (FARPROC &)driver.address_translate = GetProcAddress(h, "address_translate");
  (FARPROC &)driver.update_value = GetProcAddress(h, "update_value");
  (FARPROC &)driver.write_value = GetProcAddress(h, "write_value");



  return true;
}

driver_t *get_driver(std::string key) {
  device_t *dev;
  dev = io_open_device(key);
  if (!dev) {
    return 0;
  }
  return dev->drv;
}

std::vector<driver_t *> io_get_drivers()
{
 DRIVER_LIST::iterator p;
  std::vector<driver_t *> drv_list;
  p = g_drivers.begin();
  while (p != g_drivers.end()) {
    drv_list.push_back(&(*p));
    p++;
  }
  return std::move(drv_list);
}


driver_t *io_load_driver(std::string vendor_name, std::string driver_name) {
  DRIVER_LIST::iterator it;
  driver_t driver;
  std::string infofile;

  for (auto i = 0; i < g_devices_cfg.vendors().size(); i++) {
    if (g_devices_cfg.vendors(i).name() == vendor_name) {
      IOSS::VendorsCfg v = g_devices_cfg.vendors(i);
      for (auto j = 0; j < v.drivers().size(); j++) {
        if (v.drivers(j).name() == driver_name) {
          driver.dllname = v.drivers(j).dllname();
        }
      }
    }
  }

  for (it = g_drivers.begin(); it != g_drivers.end(); it++) {
    if (it->dllname == driver.dllname) {
      return &(*it);
    }
  }

  if (_load_module(driver)) {
    if (driver.load) {
      driver.load(&driver);
    }
  }

  it = g_drivers.insert(g_drivers.end(), driver);
  if (it == g_drivers.end()) {
    io_unload_driver(&driver);
    return 0;
  }

  return &(*it);
}

bool io_unload_driver(driver_t *driver) {
  DRIVER_LIST::iterator it;

  for (it = g_drivers.begin(); it != g_drivers.end(); it++) {
    if (&(*it) == driver) {
      break;
    }
  }
  if (it == g_drivers.end()) {
    return false;
  }

  if (driver->device_count) {
    return false;
  }

  if (driver->unload) {
    if (!driver->unload()) {
      return false;
    }
  }
  if (driver->plugin_handle) {
    FreeLibrary((HINSTANCE)driver->plugin_handle);
  }

  g_drivers.erase(it);
  return true;
}
