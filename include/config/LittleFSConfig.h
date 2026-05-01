/*
 * LITTLEFS_SHOULD_FORMAT - build flag controlling LittleFS initialization:
 *
 * 0 = mount filesystem without formatting.
 * 1 = format filesystem on startup.
 *     After formatting, upload files to FS and set this flag back to 0.
 *
 * This flag must be defined in build_flags (e.g. -DLITTLEFS_SHOULD_FORMAT=0 or 1).
 */

#pragma once
#ifndef _LITTLEFS_CONFIG_H_
#define _LITTLEFS_CONFIG_H_

#ifndef LITTLEFS_SHOULD_FORMAT
  #error "LITTLEFS_SHOULD_FORMAT not defined! Please define it in build_flags (0 or 1)."
#elif (LITTLEFS_SHOULD_FORMAT != 0) && (LITTLEFS_SHOULD_FORMAT != 1)
  #error "LITTLEFS_SHOULD_FORMAT must be 0 or 1."
#endif

#endif // _LITTLEFS_CONFIG_H_
