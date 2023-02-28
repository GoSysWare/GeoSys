
#include "ioss.h"

IOSS::DevicesInfo g_devices_info;

extern DEVICE_LIST g_devices;

bool ioss_init() {
  apollo::cyber::common::GetProtoFromFile("device_info.conf", &g_devices_info);
  io_pnp_devices();
  return true;
}
void ioss_uninit() { io_pnp_stop_devices(); }

bool io_pnp_devices() {

  for (auto i = 0; i < g_devices_info.vendors().size(); i++) {
    IOSS::Vendors v = g_devices_info.vendors(i);
    for (auto j = 0; j < v.drivers().size(); j++) {
      IOSS::Driver drv_cfg = v.drivers(j);
      if (drv_cfg.devices().size() > 0) {
        driver_t *driver = io_load_driver(v.name(), drv_cfg.name());
        if (!driver) {
          // to do
        }
        for (auto m = 0; m < drv_cfg.devices().size(); m++) {
          IOSS::Device dev_cfg = drv_cfg.devices(m);
          device_t *device = io_create_device(driver, dev_cfg.name());
          if (!device) {
            // to do
          }
          bool b = io_start_device(device);
          if (!b) {
            // to do
          }
        }
      }
    }
  }
  return true;
}


bool io_pnp_stop_devices() {
  device_t *dev;
  DEVICE_LIST::iterator it;

  for (it = g_devices.begin(); it != g_devices.end();) {
    dev = it->second;
    if (io_stop_device(dev)) {
      it++;
      io_delete_device(dev);
    }
  }
  if (g_devices.size()) {
    // to do
  }
  return true;
}
bool io_update_tag(std::string tag, std::string device_name, vam_t new_value) {
  device_t *dev;
  dev = io_get_devices(device_name);
  if (!dev) {
    return false;
  }

  if (!dev->drv) {
    return false;
  }

  if (!dev->drv->update_value) {
    return false;
  }

  if (dev->drv->update_value) {
    dev->drv->update_value(tag, new_value);
  }

  return true;
}

bool io_write_device(std::string tag, std::string device_name,
                     vam_t new_value) {
  bool ret = false;

  device_t *dev;
  dev = io_get_devices(device_name);
  if (!dev) {
    return false;
  }

  if (!dev->drv) {
    return false;
  }

  if (!dev->drv->write_value) {
    return false;
  }

  if (dev->drv->write_value) {
    ret = dev->drv->write_value(tag, new_value);
  }

  return ret;
}
