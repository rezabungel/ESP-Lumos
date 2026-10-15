#include "LightElement.h"

LightElement::LightElement(const char *id, const char *name) : id(id), name(name)
{
}

const char *LightElement::getId() const
{
    return id;
}

const char *LightElement::getName() const
{
    return name;
}

LightElement *LightElement::findElementByPointer(const LightElement *searchEl)
{
    if (searchEl == nullptr)
    {
        return nullptr;
    }

    return this == searchEl ? this : nullptr;
}

LightElement *LightElement::findElementById(const char *searchId)
{
    if (searchId == nullptr)
    {
        return nullptr;
    }

    return strcmp(getId(), searchId) == 0 ? this : nullptr;
}
