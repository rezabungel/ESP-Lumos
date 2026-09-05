#pragma once
#ifndef _JSON_BUILDER_CONFIG_H_
#define _JSON_BUILDER_CONFIG_H_

#ifndef JSON_BUILDER_BUFFER_SIZE
  #error "JSON_BUILDER_BUFFER_SIZE not defined! Please define it in build_flags."
#endif

#ifndef JSON_BUILDER_MAX_DEPTH
  #error "JSON_BUILDER_MAX_DEPTH not defined! Please define it in build_flags."
#endif

// JSON_BUILDER_MAX_DEPTH is the maximum number of simultaneously
// open JSON objects and arrays.
//
// It is calculated by counting the maximum number of unmatched '{'
// and '[' at any point in the JSON structure.
//
// Current JSON structure:
// House(Object)
//   -> children(Array)
//      -> Room(Object)
//         -> children(Array)
//            -> LightGroup(Object)
//               -> children(Array)
//                  -> Strip(Object)
//                     -> state(Object)
//
// Maximum depth = 8:
// Object -> Array -> Object -> Array -> Object -> Array -> Object -> Object

#if (JSON_BUILDER_BUFFER_SIZE < 2) || (JSON_BUILDER_BUFFER_SIZE > 65535)
  #error "JSON_BUILDER_BUFFER_SIZE must be in range [2, 65535]."
#endif

#if (JSON_BUILDER_MAX_DEPTH < 1) || (JSON_BUILDER_MAX_DEPTH > 255)
  #error "JSON_BUILDER_MAX_DEPTH must be in range [1, 255]."
#endif

#endif // _JSON_BUILDER_CONFIG_H_
