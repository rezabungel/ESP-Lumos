#include "web/api/common/RequestBodyContext.h"

#include <cstdlib>
#include <cstring>
#include <limits>
#include <new>

RequestBodyContext::RequestBodyContext(size_t totalSize)
    : totalSize(totalSize),
      receivedSize(0),
      status(totalSize == 0 ? Status::Complete : Status::Receiving)
{
    getBuffer()[0] = '\0';
}

RequestBodyContext *RequestBodyContext::create(
    size_t maxSize,
    size_t totalSize)
{
    const size_t maxValue = std::numeric_limits<size_t>::max();

    if (totalSize > maxSize ||
        sizeof(RequestBodyContext) >= maxValue ||
        totalSize > maxValue - sizeof(RequestBodyContext) - 1)
    {
        return nullptr;
    }

    const size_t bufferSize = totalSize + 1;
    const size_t allocationSize = sizeof(RequestBodyContext) + bufferSize;

    void *memory = malloc(allocationSize);

    if (memory == nullptr)
    {
        return nullptr;
    }

    return new (memory) RequestBodyContext(totalSize);
}

bool RequestBodyContext::append(
    const uint8_t *data,
    size_t len,
    size_t index,
    size_t total)
{
    if (status != Status::Receiving)
    {
        return false;
    }

    if ((len > 0 && data == nullptr) ||
        total != totalSize ||
        index != receivedSize ||
        index > totalSize ||
        len > totalSize - index)
    {
        status = Status::Invalid;
        return false;
    }

    if (len > 0)
    {
        memcpy(getBuffer() + receivedSize, data, len);
        receivedSize += len;
    }

    getBuffer()[receivedSize] = '\0';

    if (receivedSize == totalSize)
    {
        status = Status::Complete;
    }

    return true;
}

RequestBodyContext::Status RequestBodyContext::getStatus() const
{
    return status;
}

const char *RequestBodyContext::data() const
{
    return status == Status::Complete ? getBuffer() : nullptr;
}

size_t RequestBodyContext::size() const
{
    return receivedSize;
}

char *RequestBodyContext::getBuffer()
{
    return reinterpret_cast<char *>(this + 1);
}

const char *RequestBodyContext::getBuffer() const
{
    return reinterpret_cast<const char *>(this + 1);
}
