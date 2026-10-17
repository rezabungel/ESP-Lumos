#include "LightElement.h"

LightElement::LightElement(const char *id, const char *name) : id(id), name(name)
{
}

const LightElement *LightElement::getParent() const
{
    return parent;
}

LightElement *LightElement::getParent()
{
    return const_cast<LightElement *>(
        static_cast<const LightElement *>(this)->getParent());
}

const char *LightElement::getId() const
{
    return id;
}

const char *LightElement::getName() const
{
    return name;
}

const LightElement *LightElement::getRoot() const
{
    const LightElement *root = this;

    while (root->parent != nullptr)
    {
        root = root->parent;
    }

    return root;
}

LightElement *LightElement::getRoot()
{
    return const_cast<LightElement *>(
        static_cast<const LightElement *>(this)->getRoot());
}

LightElement *LightElement::findElementByPointer(const LightElement *searchEl)
{
    if (searchEl == nullptr)
    {
        return nullptr;
    }

    return this == searchEl ? this : nullptr;
}

const LightElement *LightElement::findElementById(const char *searchId) const
{
    if (searchId == nullptr)
    {
        return nullptr;
    }

    return strcmp(getId(), searchId) == 0 ? this : nullptr;
}

LightElement *LightElement::findElementById(const char *searchId)
{
    return const_cast<LightElement *>(
        static_cast<const LightElement *>(this)->findElementById(searchId));
}

LightElement *LightElement::getElement(uint8_t index) const
{
    return nullptr;
}

uint8_t LightElement::getElementCount() const
{
    return 0;
}

void LightElement::setParent(LightElement *parent)
{
    this->parent = parent;
}
