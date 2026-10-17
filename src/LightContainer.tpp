template <uint8_t MAX_ELEMENTS>
LightContainer<MAX_ELEMENTS>::LightContainer(const char *id, const char *name) : LightElement(id, name), elementCount(0)
{
}

template <uint8_t MAX_ELEMENTS>
bool LightContainer<MAX_ELEMENTS>::toJson(JsonBuilder &json) const
{
    if (!json.beginObject())
    {
        return false;
    }

    if (!json.add("id", getId()))
    {
        return false;
    }

    if (!json.add("name", getName()))
    {
        return false;
    }

    if (!json.add("type", lightElementTypeToString(getType())))
    {
        return false;
    }

    if (!json.beginArray("children"))
    {
        return false;
    }

    for (uint8_t i = 0; i < elementCount; ++i)
    {
        if (!elements[i]->toJson(json))
        {
            return false;
        }
    }

    if (!json.endArray())
    {
        return false;
    }

    return json.endObject();
}

template <uint8_t MAX_ELEMENTS>
void LightContainer<MAX_ELEMENTS>::setLightState(const LightState &lightState)
{
    for (uint8_t i = 0; i < elementCount; ++i)
    {
        elements[i]->setLightState(lightState);
    }
}

template <uint8_t MAX_ELEMENTS>
void LightContainer<MAX_ELEMENTS>::on()
{
    for (uint8_t i = 0; i < elementCount; ++i)
    {
        elements[i]->on();
    }
}

template <uint8_t MAX_ELEMENTS>
void LightContainer<MAX_ELEMENTS>::off()
{
    for (uint8_t i = 0; i < elementCount; ++i)
    {
        elements[i]->off();
    }
}

template <uint8_t MAX_ELEMENTS>
void LightContainer<MAX_ELEMENTS>::setColor(const Color &color)
{
    for (uint8_t i = 0; i < elementCount; ++i)
    {
        elements[i]->setColor(color);
    }
}

template <uint8_t MAX_ELEMENTS>
void LightContainer<MAX_ELEMENTS>::setBrightness(uint8_t brightness)
{
    for (uint8_t i = 0; i < elementCount; ++i)
    {
        elements[i]->setBrightness(brightness);
    }
}

template <uint8_t MAX_ELEMENTS>
void LightContainer<MAX_ELEMENTS>::setAnimationState(const AnimationState &animationState)
{
    for (uint8_t i = 0; i < elementCount; ++i)
    {
        elements[i]->setAnimationState(animationState);
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

template <uint8_t MAX_ELEMENTS>
LightElement *LightContainer<MAX_ELEMENTS>::findElementByPointer(const LightElement *searchEl)
{
    if (searchEl == nullptr)
    {
        return nullptr;
    }

    if (this == searchEl)
    {
        return this;
    }

    for (uint8_t i = 0; i < elementCount; ++i)
    {
        LightElement *found = elements[i]->findElementByPointer(searchEl);

        if (found != nullptr)
        {
            return found;
        }
    }

    return nullptr;
}

template <uint8_t MAX_ELEMENTS>
const LightElement *LightContainer<MAX_ELEMENTS>::findElementById(const char *searchId) const
{
    if (searchId == nullptr)
    {
        return nullptr;
    }

    if (strcmp(getId(), searchId) == 0)
    {
        return this;
    }

    for (uint8_t i = 0; i < elementCount; ++i)
    {
        const LightElement *found =
            static_cast<const LightElement *>(elements[i])->findElementById(searchId);

        if (found != nullptr)
        {
            return found;
        }
    }

    return nullptr;
}

template <uint8_t MAX_ELEMENTS>
LightElement *LightContainer<MAX_ELEMENTS>::findElementById(const char *searchId)
{
    return const_cast<LightElement *>(
        static_cast<const LightContainer<MAX_ELEMENTS> *>(this)->findElementById(searchId));
}

template <uint8_t MAX_ELEMENTS>
bool LightContainer<MAX_ELEMENTS>::addElement(LightElement *el)
{
    if (!el || el->getParent() || el->getType() == LightElementType::House || elementCount >= MAX_ELEMENTS)
    {
        return false;
    }

    const LightElement *root = getRoot();
    if (!hasUniqueIds(root, el))
    {
        return false;
    }

    el->setParent(this);
    elements[elementCount++] = el;
    return true;
}

template <uint8_t MAX_ELEMENTS>
bool LightContainer<MAX_ELEMENTS>::hasUniqueIds(const LightElement *root, const LightElement *el) const
{
    if (!root || !el)
    {
        return false;
    }

    if (root->findElementById(el->getId()))
    {
        return false;
    }

    if (el->getType() != LightElementType::Strip)
    {
        for (uint8_t i = 0; i < el->getElementCount(); ++i)
        {
            bool uniqueId = hasUniqueIds(root, el->getElement(i));

            if (!uniqueId)
            {
                return false;
            }
        }
    }

    return true;
}
