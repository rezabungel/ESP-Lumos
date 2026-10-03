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
