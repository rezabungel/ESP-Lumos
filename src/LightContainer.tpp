template <uint8_t MAX_ELEMENTS>
LightContainer<MAX_ELEMENTS>::LightContainer(const char *name) : name(name), elementCount(0)
{
}

template <uint8_t MAX_ELEMENTS>
const char *LightContainer<MAX_ELEMENTS>::getName() const
{
    return name;
}

template <uint8_t MAX_ELEMENTS>
LightElement *LightContainer<MAX_ELEMENTS>::findElementByPointer(LightElement *searchEl) const
{
    for (uint8_t i = 0; i < elementCount; ++i)
    {
        if (elements[i] == searchEl)
        {
            return elements[i];
        }
    }
    return nullptr;
}

template <uint8_t MAX_ELEMENTS>
LightElement *LightContainer<MAX_ELEMENTS>::findElementByName(const char *searchName) const
{
    for (uint8_t i = 0; i < elementCount; ++i)
    {
        if (strcmp(elements[i]->getName(), searchName) == 0)
        {
            return elements[i];
        }
    }
    return nullptr;
}

template <uint8_t MAX_ELEMENTS>
bool LightContainer<MAX_ELEMENTS>::addElement(LightElement *el)
{
    if (!el || findElementByPointer(el) || findElementByName(el->getName()) || elementCount >= MAX_ELEMENTS)
    {
        return false;
    }

    elements[elementCount++] = el;
    return true;
}

template <uint8_t MAX_ELEMENTS>
void LightContainer<MAX_ELEMENTS>::setColor(uint8_t r, uint8_t g, uint8_t b)
{
    for (uint8_t i = 0; i < elementCount; ++i)
    {
        elements[i]->setColor(r, g, b);
    }
}

template <uint8_t MAX_ELEMENTS>
void LightContainer<MAX_ELEMENTS>::clear()
{
    for (uint8_t i = 0; i < elementCount; ++i)
    {
        elements[i]->clear();
    }
}

template <uint8_t MAX_ELEMENTS>
void LightContainer<MAX_ELEMENTS>::setAnimation(Animation *anim)
{
    for (uint8_t i = 0; i < elementCount; ++i)
    {
        elements[i]->setAnimation(anim);
    }
}

template <uint8_t MAX_ELEMENTS>
LightElement *LightContainer<MAX_ELEMENTS>::getElement(uint8_t index) const
{
    if (index >= elementCount)
    {
        return nullptr;
    }

    return elements[index];
}

template <uint8_t MAX_ELEMENTS>
uint8_t LightContainer<MAX_ELEMENTS>::getElementCount() const
{
    return elementCount;
}
