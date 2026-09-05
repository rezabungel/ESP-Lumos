#include "json/JsonBuilder.h"

JsonBuilder::JsonBuilder() : position(0), level(0)
{
    buffer[0] = '\0';
}

bool JsonBuilder::beginObject()
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

    contexts[level].contextType = Context::ContextType::Object;
    contexts[level].hasElements = false;

    ++level;

    return true;
}

bool JsonBuilder::beginObject(const char *name)
{
    if (!add(name))
    {
        return false;
    }

    return beginObject();
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

    if (!append('}'))
    {
        return false;
    }

    --level;

    return true;
}

bool JsonBuilder::beginArray()
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

    contexts[level].contextType = Context::ContextType::Array;
    contexts[level].hasElements = false;

    ++level;

    return true;
}

bool JsonBuilder::beginArray(const char *name)
{
    if (!add(name))
    {
        return false;
    }

    return beginArray();
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

bool JsonBuilder::add(const char *name)
{
    if (level == 0)
    {
        return false;
    }

    Context &context = contexts[level - 1];

    if (context.contextType != Context::ContextType::Object)
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

    if (!append('"') || !append(name) || !append('"') || !append(':'))
    {
        return false;
    }

    context.hasElements = true;

    return true;
}

bool JsonBuilder::add(const char *name, const char *value)
{
    if (!add(name))
    {
        return false;
    }

    if (!append('"') || !append(value) || !append('"'))
    {
        return false;
    }

    return true;
}

const char *JsonBuilder::data() const
{
    return buffer;
}

uint16_t JsonBuilder::size() const
{
    return position;
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
