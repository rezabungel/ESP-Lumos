#pragma once
#ifndef _REQUEST_BODY_CONTEXT_H_
#define _REQUEST_BODY_CONTEXT_H_

#include <cstddef>
#include <cstdint>

class RequestBodyContext
{
public:
    enum class Status
    {
        Receiving,
        Complete,
        Invalid
    };

    static RequestBodyContext *create(size_t maxSize, size_t totalSize);

    bool append(
        const uint8_t *data,
        size_t len,
        size_t index,
        size_t total);

    Status getStatus() const;

    const char *data() const;

    size_t size() const;

private:
    explicit RequestBodyContext(size_t totalSize);

    char *getBuffer();
    const char *getBuffer() const;

    size_t totalSize;
    size_t receivedSize;

    Status status;
};

#endif // _REQUEST_BODY_CONTEXT_H_
