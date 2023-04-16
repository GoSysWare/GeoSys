#ifndef ioss_h
#define ioss_h
#include <list>

#include "cyber/cyber.h"
#include "ddk.h"
#include "modules/calc/proto/device.pb.h"

bool ioss_init();
void ioss_uninit();

bool io_pnp_devices();
bool io_pnp_stop_devices();


driver_t *io_load_driver(std::string vendor_name, std::string driver_name);

bool io_unload_driver(driver_t *driver);

device_t *io_create_device(driver_t *driver, std::string device_name);

bool io_delete_device(device_t *dev);

std::vector<device_t *> io_get_devices();
std::vector<driver_t *> io_get_drivers();

device_t *io_get_devices(std::string dev_name);

device_t *io_open_device(std::string device_name);

bool io_start_device(device_t *dev);

bool io_stop_device(device_t *dev);

bool io_update_tag(std::string device_name, std::string tag, vam_t value);
bool io_write_device(std::string device_name, std::string tag, vam_t value);

typedef std::list<driver_t> DRIVER_LIST;
extern DRIVER_LIST g_drivers;

typedef std::map<std::string, device_t *> DEVICE_LIST;
extern DEVICE_LIST g_devices;

#endif