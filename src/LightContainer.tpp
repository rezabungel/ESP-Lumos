template <uint8_t MAX_ELEMENTS>
LightContainer<MAX_ELEMENTS>::LightContainer() : elementCount(0)
{
}

template <uint8_t MAX_ELEMENTS>
bool LightContainer<MAX_ELEMENTS>::addElement(LightElement *el)
{
    if (!el || elementCount >= MAX_ELEMENTS)
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
