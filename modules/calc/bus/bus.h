#ifndef k_service_h
#define k_service_h


int rbus_init(std::shared_ptr<apollo::cyber::Node> & node);
int rbus_uninit();
#endif