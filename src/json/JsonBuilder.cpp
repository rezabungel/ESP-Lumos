#include "json/JsonBuilder.h"

JsonBuilder::JsonBuilder() : position(0), level(0)
{
    buffer[0] = '\0';
}

bool JsonBuilder::beginObject()
{
    if (!canOpenUnnamedContainer())
    {
        return false;
    }

    return openObject();
}

bool JsonBuilder::beginObject(const char *name)
{
    if (!add(name))
    {
        return false;
    }

    return openObject();
}

bool JsonBuilder::endObject()
{
    if (level == 0)
    {
        return false;
    }

    if (contexts[level - 1].contextType != Context::ContextType::Object)
    {
        return false;
    }

    if (contexts[level - 1].expectingValue)
    {
        return false;
    }

    if (!append('}'))
    {
        return false;
    }

    --level;

    return true;
}

bool JsonBuilder::beginArray()
{
    if (!canOpenUnnamedContainer())
    {
        return false;
    }

    return openArray();
}

bool JsonBuilder::beginArray(const char *name)
{
    if (!add(name))
    {
        return false;
    }

    return openArray();
}

bool JsonBuilder::endArray()
{
    if (level == 0)
    {
        return false;
    }

    if (contexts[level - 1].contextType != Context::ContextType::Array)
    {
        return false;
    }

    if (!append(']'))
    {
        return false;
    }

    --level;

    return true;
}

bool JsonBuilder::add(const char *valueOrName)
{
    if (level == 0)
    {
        return false;
    }

    Context &context = contexts[level - 1];

    if (context.contextType == Context::ContextType::Object)
    {
        if (context.expectingValue)
        {
            return false;
        }

        if (context.hasElements)
        {
            if (!append(','))
            {
                return false;
            }
        }

        if (!append('"') || !append(valueOrName) || !append('"') || !append(':'))
        {
            return false;
        }

        context.hasElements = true;
        context.expectingValue = true;

        return true;
    }

    return prepareArrayElement() && append('"') && append(valueOrName) && append('"');
}

bool JsonBuilder::add(const char *name, const char *value)
{
    if (level == 0 ||
        contexts[level - 1].contextType != Context::ContextType::Object)
    {
        return false;
    }

    if (!add(name))
    {
        return false;
    }

    if (!append('"') || !append(value) || !append('"'))
    {
        return false;
    }

    contexts[level - 1].expectingValue = false;

    return true;
}

bool JsonBuilder::add(const char *name, bool value)
{
    if (level == 0 ||
        contexts[level - 1].contextType != Context::ContextType::Object)
    {
        return false;
    }

    if (!add(name))
    {
        return false;
    }

    if (!append(value ? "true" : "false"))
    {
        return false;
    }

    contexts[level - 1].expectingValue = false;

    return true;
}

bool JsonBuilder::add(const char *name, uint8_t value)
{
    if (level == 0 ||
        contexts[level - 1].contextType != Context::ContextType::Object)
    {
        return false;
    }

    if (!add(name))
    {
        return false;
    }

    char number[4];
    snprintf(number, sizeof(number), "%u", value);

    if (!append(number))
    {
        return false;
    }

    contexts[level - 1].expectingValue = false;

    return true;
}

bool JsonBuilder::add(const char *name, uint16_t value)
{
    if (level == 0 ||
        contexts[level - 1].contextType != Context::ContextType::Object)
    {
        return false;
    }

    if (!add(name))
    {
        return false;
    }

    char number[6];
    snprintf(number, sizeof(number), "%u", value);

    if (!append(number))
    {
        return false;
    }

    contexts[level - 1].expectingValue = false;

    return true;
}

bool JsonBuilder::add(bool value)
{
    if (level == 0 ||
        contexts[level - 1].contextType != Context::ContextType::Array)
    {
        return false;
    }

    if (!prepareArrayElement())
    {
        return false;
    }

    return append(value ? "true" : "false");
}

bool JsonBuilder::add(uint8_t value)
{
    if (level == 0 ||
        contexts[level - 1].contextType != Context::ContextType::Array)
    {
        return false;
    }

    if (!prepareArrayElement())
    {
        return false;
    }

    char number[4];
    snprintf(number, sizeof(number), "%u", value);

    return append(number);
}

bool JsonBuilder::add(uint16_t value)
{
    if (level == 0 ||
        contexts[level - 1].contextType != Context::ContextType::Array)
    {
        return false;
    }

    if (!prepareArrayElement())
    {
        return false;
    }

    char number[6];
    snprintf(number, sizeof(number), "%u", value);

    return append(number);
}

const char *JsonBuilder::data() const
{
    return buffer;
}

uint16_t JsonBuilder::size() const
{
    return position;
}

bool JsonBuilder::canOpenUnnamedContainer() const
{
    if (level == 0)
    {
        return true;
    }

    const Context &context = contexts[level - 1];

    if (context.contextType == Context::ContextType::Array)
    {
        return true;
    }

    return context.expectingValue;
}

bool JsonBuilder::openObject()
{
    if (level >= JSON_BUILDER_MAX_DEPTH)
    {
        return false;
    }

    if (!prepareArrayElement())
    {
        return false;
    }

    if (!append('{'))
    {
        return false;
    }

    if (level > 0 &&
        contexts[level - 1].contextType == Context::ContextType::Object &&
        contexts[level - 1].expectingValue)
    {
        contexts[level - 1].expectingValue = false;
    }

    contexts[level].contextType = Context::ContextType::Object;
    contexts[level].hasElements = false;
    contexts[level].expectingValue = false;

    ++level;

    return true;
}

bool JsonBuilder::openArray()
{
    if (level >= JSON_BUILDER_MAX_DEPTH)
    {
        return false;
    }

    if (!prepareArrayElement())
    {
        return false;
    }

    if (!append('['))
    {
        return false;
    }

    if (level > 0 &&
        contexts[level - 1].contextType == Context::ContextType::Object &&
        contexts[level - 1].expectingValue)
    {
        contexts[level - 1].expectingValue = false;
    }

    contexts[level].contextType = Context::ContextType::Array;
    contexts[level].hasElements = false;
    contexts[level].expectingValue = false;

    ++level;

    return true;
}

bool JsonBuilder::prepareArrayElement()
{
    if (level == 0)
    {
        return true;
    }

    Context &parent = contexts[level - 1];

    if (parent.contextType != Context::ContextType::Array)
    {
        return true;
    }

    if (parent.hasElements)
    {
        if (!append(','))
        {
            return false;
        }
    }

    parent.hasElements = true;

    return true;
}

bool JsonBuilder::append(char value)
{
    if (position + 1 >= JSON_BUILDER_BUFFER_SIZE)
    {
        return false;
    }

    buffer[position] = value;
    position++;
    buffer[position] = '\0';

    return true;
}

bool JsonBuilder::append(const char *value)
{
    const uint16_t length = strlen(value);
    if (position + length >= JSON_BUILDER_BUFFER_SIZE)
    {
        return false;
    }

    memcpy(&buffer[position], value, length);
    position += length;
    buffer[position] = '\0';

    return true;
}
