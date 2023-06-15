
#include "ioss.h"

IOSS::DevicesCfg g_devices_cfg;

bool ioss_init() {
  // apollo::cyber::common::GetProtoFromFile("device_info.conf",
  // &g_devices_cfg);
  apollo::cyber::common::GetProtoFromFile(
      "/home/shuimujie/Works/GeoSys/modules/calc/ioss/device_info.conf",
      &g_devices_cfg);

  std::cout << g_devices_cfg.DebugString() << std::endl;
  io_pnp_devices();
  return true;
}
void ioss_uninit() { io_pnp_stop_devices(); }

bool io_pnp_devices() {

  for (auto i = 0; i < g_devices_cfg.vendors().size(); i++) {
    IOSS::VendorsCfg v = g_devices_cfg.vendors(i);
    for (auto j = 0; j < v.drivers().size(); j++) {
      IOSS::DriverCfg drv_cfg = v.drivers(j);
      if (drv_cfg.devices().size() > 0) {
        driver_t *driver = io_load_driver(v.name(), drv_cfg.name());
        if (!driver) {
          // to do
        }
        for (auto m = 0; m < drv_cfg.devices().size(); m++) {
          IOSS::DeviceCfg dev_cfg = drv_cfg.devices(m);
          device_t *device = io_create_device(driver, dev_cfg.name());
          if (!device) {
            // to do
          }
          device->address = dev_cfg.address();
          device->parameter = dev_cfg.parameter();

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
bool io_update_tag(std::string device_name, std::string tag, vam_t value) {
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
    dev->drv->update_value(dev, tag, value);
  }

  return true;
}

bool io_install_event_handler(std::string device_name, std::string event_name, IO_EVENT_HANDLER handler) {
  device_t *dev;
  dev = io_get_devices(device_name);
  if (!dev) {
    return false;
  }

  if (!dev->drv) {
    return false;
  }

  if (!dev->drv->event_hanlder) {
    return false;
  }

  if (dev->drv->event_hanlder) {
    dev->drv->event_hanlder(dev, event_name, handler);
  }

  return true;
}

bool io_write_device(std::string device_name, std::string tag, vam_t value) {
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
    ret = dev->drv->write_value(dev, tag, value);
  }

  return ret;
}
