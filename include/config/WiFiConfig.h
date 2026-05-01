#pragma once
#ifndef _WIFI_CONFIG_H_
#define _WIFI_CONFIG_H_

#ifndef WIFI_SSID
  #error "WIFI_SSID not defined! Please define it in build_flags."
#endif

#ifndef WIFI_PASS
  #error "WIFI_PASS not defined! Please define it in build_flags."
#endif

#endif // _WIFI_CONFIG_H_
