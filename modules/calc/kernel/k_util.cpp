#include <stdio.h>
#include <stdlib.h>

#include "modules/calc/include/k_config.h"
#include "modules/calc/include/k_datatype.h"
#include "modules/calc/include/k_util.h"
#include <sys/time.h>

#include <iostream>
#include <sstream>
#include <random>
#include <climits>
#include <algorithm>
#include <functional>

#ifdef _WIN32

#endif

#ifdef _LINUX
#include <arpa/inet.h>
#include <ifaddrs.h>
#include <netdb.h>
#include <sys/types.h>
#include <unistd.h>

#include <climits>
#include <cstdlib>

int k_getpid()
{
	return getpid();
}
std::string k_getpidstr()
{
	return std::to_string(k_getpid());
}


std::string k_hostname() {
  char host_name[1024];
  gethostname(host_name, sizeof(host_name));
  return std::string(host_name);
}

std::string k_hostip(){
  std::string host_ip = "127.0.0.1";

  // if we have exported a non-loopback CYBER_IP, we will use it firstly,
  // otherwise, we try to find first non-loopback ipv4 addr.
  const char* ip_env = getenv("CYBER_IP");
  if (ip_env != nullptr) {
    // maybe we need to verify ip_env
    std::string ip_env_str(ip_env);
    std::string starts = ip_env_str.substr(0, 3);
    if (starts != "127") {
      host_ip = ip_env_str;
      return host_ip;
    }
  }

  ifaddrs* ifaddr = nullptr;
  if (getifaddrs(&ifaddr) != 0) {
    return std::string();
  }
  for (ifaddrs* ifa = ifaddr; ifa; ifa = ifa->ifa_next) {
    if (ifa->ifa_addr == nullptr) {
      continue;
    }
    int family = ifa->ifa_addr->sa_family;
    if (family != AF_INET) {
      continue;
    }
    char addr[NI_MAXHOST] = {0};
    if (getnameinfo(ifa->ifa_addr, sizeof(sockaddr_in), addr, NI_MAXHOST, NULL,
                    0, NI_NUMERICHOST) != 0) {
      continue;
    }
    std::string tmp_ip(addr);
    std::string starts = tmp_ip.substr(0, 3);
    if (starts != "127") {
      host_ip = tmp_ip;
      break;
    }
  }
  freeifaddrs(ifaddr);
  return host_ip;
}
unsigned char random_char() {
    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_int_distribution<> dis(0, 255);
    return static_cast<unsigned char>(dis(gen));
}

std::string generate_hex(const unsigned int len) {
    std::stringstream ss;
    for (unsigned int i = 0; i < len; i++) {
        auto rc = random_char();
        std::stringstream hexstream;
        hexstream << std::hex << int(rc);
        auto hex = hexstream.str();
        ss << (hex.length() < 2 ? '0' + hex : hex);
    }
    return ss.str();
}

std::string gen_uuid() {
    return generate_hex(4) + "-" + generate_hex(2) + "-" + generate_hex(2) + "-" + generate_hex(2) + "-" +
        generate_hex(6);
}

#endif


