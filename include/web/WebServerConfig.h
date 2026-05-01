#pragma once
#ifndef _WEB_SERVER_CONFIG_H_
#define _WEB_SERVER_CONFIG_H_

#ifndef WEB_SERVER_PORT
  #error "WEB_SERVER_PORT not defined! Please define it in build_flags."
#endif

#if (WEB_SERVER_PORT < 1) || (WEB_SERVER_PORT > 65535)
  #error "WEB_SERVER_PORT must be in range [1, 65535]."
#endif

#endif // _WEB_SERVER_CONFIG_H_
