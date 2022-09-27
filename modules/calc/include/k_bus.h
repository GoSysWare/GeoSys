#ifndef k_bus_h
#define k_bus_h

#include "cyber/cyber.h"

#include "modules/calc/proto/cmd.pb.h"
#include "modules/calc/proto/snapshot.pb.h"
#include "k_project.h"

int bus_init(std::shared_ptr<apollo::cyber::Node> & node);
int bus_uninit();

#endif