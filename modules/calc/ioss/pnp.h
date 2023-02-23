#ifndef ioss_pnp_h
#define ioss_pnp_h
#include "ddk.h"

bool pnp_init();
bool pnp_uninit();
bool io_pnp_devices();

device_t *io_pnp_device(std::string device_name,bool validate);

#endif