#ifndef ioss_h
#define ioss_h
#include "ddk.h"

bool ioss_init();
void ioss_uninit();


driver_t * io_load_driver(vendor_t v,device_type_t t);
bool io_load_driver(driver_t * dirver);

device_t * io_create_device(driver_t * dirver,std::string device_name);
bool io_delete_device(device_t *);
bool io_start_device(device_t *);
bool io_stop_device(device_t *);

device_t * io_open_device(std::string device_name);
std::vector<device_t> io_get_devices();




#endif