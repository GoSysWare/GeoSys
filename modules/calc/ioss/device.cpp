

#include "ioss.h"

DEVICE_LIST g_devices;

device_t *io_create_device(driver_t *driver, std::string device_name) {
  device_t *dev;
  std::pair<DEVICE_LIST::iterator, bool> pr;
  dev = new device_t;
  if (!dev) {
    return 0;
  }
  dev->name = device_name;
  dev->drv = driver;
  if (driver) {
    driver->device_count++;
  }
  pr = g_devices.insert(DEVICE_LIST::value_type(device_name, dev));
  return dev;
}

bool io_delete_device(device_t *dev) {
  driver_t *driver;
  DEVICE_LIST::iterator it;

  it = g_devices.find(dev->name);
  driver = dev->drv;
  g_devices.erase(it);
  delete dev;

  if (driver) {
    driver->device_count--;
    if (!driver->device_count) {
      io_unload_driver(driver);
    }
  }

  return true;
}
std::vector<device_t *> io_get_devices() {

  DEVICE_LIST::iterator p;
  std::vector<device_t *> dev_list;
  p = g_devices.begin();
  while (p != g_devices.end()) {
    dev_list.push_back(p->second);
    p++;
  }
  return std::move(dev_list);
}
device_t *io_get_devices(std::string dev_name) {

  DEVICE_LIST::iterator p;
  std::vector<device_t *> dev_list;
  p = g_devices.begin();
  while (p != g_devices.end()) {
    if (p->first == dev_name) {
      return p->second;
    }
    p++;
  }
  return 0;
}

device_t *io_open_device(std::string device_name) {
  DEVICE_LIST::iterator it;
  it = g_devices.find(device_name);
  if (it == g_devices.end()) {
    return 0;
  }
  return it->second;
}
bool io_start_device(device_t *dev) {
  bool ret;

  if (!(dev->drv->flags & DRIVER_FLAG_LOADED)) {
    dev->error = DRIVER_NOT_LOADED;
    ret = false;
  } else {
    if (!dev->drv->start_device) {
      ret = true;
    } else {
      ret = dev->drv->start_device(dev);
      if (!ret) {
        dev->error = DEVICE_NOT_STARTED;
      }
    }
  }

  if (!ret) {
    dev->flags &= ~DF_Active;
  } else {
    dev->flags |= DF_Active;
    dev->error = 0;
  }

  if (ret) {

  } else {
  }

  return ret;
}
bool io_stop_device(device_t *dev) {
  if (!(dev->flags & DF_Active)) {
    return true;
  }
  if (dev->drv) {
    if (dev->drv->stop_device) {
      if (!dev->drv->stop_device(dev)) {
        dev->flags &= ~DF_Active;
        return false;
      }
    }
  }
  dev->flags &= ~DF_Active;

  return true;
}