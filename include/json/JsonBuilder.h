#pragma once
#ifndef _JSON_BUILDER_H_
#define _JSON_BUILDER_H_

#include <cstdint>
#include <cstring>
#include <cstdio>
#include "config/JsonBuilderConfig.h"

class JsonBuilder
{
public:
    JsonBuilder();

    bool beginObject();
    bool beginObject(const char *name);

    bool endObject();

    bool beginArray();
    bool beginArray(const char *name);

    bool endArray();

    // Object property / Array string element
    bool add(const char *valueOrName);

    // Object properties
    bool add(const char *name, const char *value);
    bool add(const char *name, bool value);
    bool add(const char *name, uint8_t value);
    bool add(const char *name, uint16_t value);

    // Array elements
    bool add(bool value);
    bool add(uint8_t value);
    bool add(uint16_t value);

    const char *data() const;
    uint16_t size() const;

private:
    struct Context
    {
        enum class ContextType : uint8_t
        {
            Object,
            Array
        };

        ContextType contextType;
        bool hasElements;
        bool expectingValue;
    };

    char buffer[JSON_BUILDER_BUFFER_SIZE];
    uint16_t position;

    Context contexts[JSON_BUILDER_MAX_DEPTH];
    uint8_t level;

    bool canOpenUnnamedContainer() const;

    bool openObject();
    bool openArray();

    bool prepareArrayElement();

    bool append(char value);
    bool append(const char *value);
};

#endif // _JSON_BUILDER_H_
