#include <unity.h>

#include <cstdlib>
#include <cstring>
#include <limits>

#include "web/api/common/RequestBodyContext.h"

// Releases memory allocated by RequestBodyContext::create().
class RequestBodyContextGuard
{
public:
    explicit RequestBodyContextGuard(RequestBodyContext *context)
        : context(context)
    {
    }

    ~RequestBodyContextGuard()
    {
        free(context);
    }

    RequestBodyContext *get() const
    {
        return context;
    }

private:
    RequestBodyContext *context;
};

void test_create_valid_context()
{
    RequestBodyContextGuard guard(RequestBodyContext::create(100, 29));

    TEST_ASSERT_NOT_NULL(guard.get());
    TEST_ASSERT_EQUAL(
        RequestBodyContext::Status::Receiving,
        guard.get()->getStatus());
    TEST_ASSERT_EQUAL_UINT32(0, guard.get()->size());
    TEST_ASSERT_NULL(guard.get()->data());
}

void test_create_rejects_oversized_body()
{
    RequestBodyContextGuard guard(RequestBodyContext::create(10, 11));

    TEST_ASSERT_NULL(guard.get());
}

void test_create_rejects_allocation_size_overflow()
{
    const size_t maxValue = std::numeric_limits<size_t>::max();

    RequestBodyContextGuard guard(
        RequestBodyContext::create(maxValue, maxValue));

    TEST_ASSERT_NULL(guard.get());
}

void test_create_completes_empty_body()
{
    RequestBodyContextGuard guard(RequestBodyContext::create(0, 0));

    TEST_ASSERT_NOT_NULL(guard.get());

    TEST_ASSERT_EQUAL(
        RequestBodyContext::Status::Complete,
        guard.get()->getStatus());
    TEST_ASSERT_EQUAL_UINT32(0, guard.get()->size());
    TEST_ASSERT_NOT_NULL(guard.get()->data());
    TEST_ASSERT_EQUAL_STRING("", guard.get()->data());
}

void test_append_single_chunk()
{
    const char body[] = "{\"r\":255,\"g\":0,\"b\":0}";

    RequestBodyContextGuard guard(
        RequestBodyContext::create(sizeof(body) - 1, sizeof(body) - 1));

    TEST_ASSERT_NOT_NULL(guard.get());

    const bool result = guard.get()->append(
        reinterpret_cast<const uint8_t *>(body),
        sizeof(body) - 1,
        0,
        sizeof(body) - 1);

    TEST_ASSERT_TRUE(result);
    TEST_ASSERT_EQUAL(
        RequestBodyContext::Status::Complete,
        guard.get()->getStatus());
    TEST_ASSERT_EQUAL_UINT32(sizeof(body) - 1, guard.get()->size());
    TEST_ASSERT_NOT_NULL(guard.get()->data());
    TEST_ASSERT_EQUAL_STRING(body, guard.get()->data());
}

void test_append_multiple_chunks()
{
    const char firstChunk[] = "{\"r\":255,";
    const char secondChunk[] = "\"g\":0,";
    const char thirdChunk[] = "\"b\":0}";

    const char expectedBody[] = "{\"r\":255,\"g\":0,\"b\":0}";

    const size_t totalSize = sizeof(expectedBody) - 1;

    RequestBodyContextGuard guard(
        RequestBodyContext::create(totalSize, totalSize));

    TEST_ASSERT_NOT_NULL(guard.get());

    // First chunk.
    TEST_ASSERT_TRUE(guard.get()->append(
        reinterpret_cast<const uint8_t *>(firstChunk),
        sizeof(firstChunk) - 1,
        0,
        totalSize));

    TEST_ASSERT_EQUAL(
        RequestBodyContext::Status::Receiving,
        guard.get()->getStatus());
    TEST_ASSERT_EQUAL_UINT32(sizeof(firstChunk) - 1, guard.get()->size());
    TEST_ASSERT_NULL(guard.get()->data());

    // Second chunk.
    TEST_ASSERT_TRUE(guard.get()->append(
        reinterpret_cast<const uint8_t *>(secondChunk),
        sizeof(secondChunk) - 1,
        sizeof(firstChunk) - 1,
        totalSize));

    TEST_ASSERT_EQUAL(
        RequestBodyContext::Status::Receiving,
        guard.get()->getStatus());
    TEST_ASSERT_EQUAL_UINT32(
        sizeof(firstChunk) + sizeof(secondChunk) - 2,
        guard.get()->size());
    TEST_ASSERT_NULL(guard.get()->data());

    // Third chunk.
    TEST_ASSERT_TRUE(guard.get()->append(
        reinterpret_cast<const uint8_t *>(thirdChunk),
        sizeof(thirdChunk) - 1,
        sizeof(firstChunk) + sizeof(secondChunk) - 2,
        totalSize));

    TEST_ASSERT_EQUAL(
        RequestBodyContext::Status::Complete,
        guard.get()->getStatus());
    TEST_ASSERT_EQUAL_UINT32(totalSize, guard.get()->size());
    TEST_ASSERT_NOT_NULL(guard.get()->data());
    TEST_ASSERT_EQUAL_STRING(expectedBody, guard.get()->data());
}

void test_append_accepts_null_data_with_zero_length()
{
    RequestBodyContextGuard guard(RequestBodyContext::create(10, 10));

    TEST_ASSERT_NOT_NULL(guard.get());

    const bool result = guard.get()->append(
        nullptr,
        0,
        0,
        10);

    TEST_ASSERT_TRUE(result);
    TEST_ASSERT_EQUAL(
        RequestBodyContext::Status::Receiving,
        guard.get()->getStatus());
    TEST_ASSERT_EQUAL_UINT32(0, guard.get()->size());
    TEST_ASSERT_NULL(guard.get()->data());
}

void test_append_rejects_wrong_index()
{
    RequestBodyContextGuard guard(RequestBodyContext::create(10, 10));

    TEST_ASSERT_NOT_NULL(guard.get());

    const uint8_t chunk[] = {'a', 'b', 'c'};

    const bool result = guard.get()->append(
        chunk,
        sizeof(chunk),
        1,
        10);

    TEST_ASSERT_FALSE(result);
    TEST_ASSERT_EQUAL(
        RequestBodyContext::Status::Invalid,
        guard.get()->getStatus());
    TEST_ASSERT_EQUAL_UINT32(0, guard.get()->size());
    TEST_ASSERT_NULL(guard.get()->data());
}

void test_append_rejects_wrong_total()
{
    RequestBodyContextGuard guard(RequestBodyContext::create(10, 10));

    TEST_ASSERT_NOT_NULL(guard.get());

    const uint8_t chunk[] = {'a', 'b', 'c'};

    const bool result = guard.get()->append(
        chunk,
        sizeof(chunk),
        0,
        9);

    TEST_ASSERT_FALSE(result);
    TEST_ASSERT_EQUAL(
        RequestBodyContext::Status::Invalid,
        guard.get()->getStatus());
    TEST_ASSERT_EQUAL_UINT32(0, guard.get()->size());
    TEST_ASSERT_NULL(guard.get()->data());
}

void test_append_rejects_chunk_out_of_bounds()
{
    RequestBodyContextGuard guard(RequestBodyContext::create(10, 10));

    TEST_ASSERT_NOT_NULL(guard.get());

    const uint8_t chunk[] = {'a', 'b', 'c'};

    const bool result = guard.get()->append(
        chunk,
        sizeof(chunk),
        0,
        10);

    TEST_ASSERT_TRUE(result);
    TEST_ASSERT_EQUAL(
        RequestBodyContext::Status::Receiving,
        guard.get()->getStatus());
    TEST_ASSERT_EQUAL_UINT32(3, guard.get()->size());
    TEST_ASSERT_NULL(guard.get()->data());

    // 3 bytes have already been received. The next chunk must not
    // exceed the total body size of 10 bytes.
    const uint8_t nextChunk[] = {'d', 'e', 'f', 'g', 'h', 'i', 'j', 'k'};

    const bool nextResult = guard.get()->append(
        nextChunk,
        sizeof(nextChunk),
        3,
        10);

    TEST_ASSERT_FALSE(nextResult);
    TEST_ASSERT_EQUAL(
        RequestBodyContext::Status::Invalid,
        guard.get()->getStatus());
    TEST_ASSERT_EQUAL_UINT32(3, guard.get()->size());
    TEST_ASSERT_NULL(guard.get()->data());
}

void test_append_rejects_null_data_with_nonzero_length()
{
    RequestBodyContextGuard guard(RequestBodyContext::create(10, 10));

    TEST_ASSERT_NOT_NULL(guard.get());

    const bool result = guard.get()->append(
        nullptr,
        1,
        0,
        10);

    TEST_ASSERT_FALSE(result);
    TEST_ASSERT_EQUAL(
        RequestBodyContext::Status::Invalid,
        guard.get()->getStatus());
    TEST_ASSERT_EQUAL_UINT32(0, guard.get()->size());
    TEST_ASSERT_NULL(guard.get()->data());
}

void test_append_rejects_data_after_complete()
{
    const uint8_t body[] = {'a', 'b', 'c'};

    RequestBodyContextGuard guard(
        RequestBodyContext::create(sizeof(body), sizeof(body)));

    TEST_ASSERT_NOT_NULL(guard.get());

    TEST_ASSERT_TRUE(guard.get()->append(
        body,
        sizeof(body),
        0,
        sizeof(body)));

    TEST_ASSERT_EQUAL(
        RequestBodyContext::Status::Complete,
        guard.get()->getStatus());
    TEST_ASSERT_EQUAL_UINT32(sizeof(body), guard.get()->size());
    TEST_ASSERT_EQUAL_UINT8_ARRAY(
        body,
        reinterpret_cast<const uint8_t *>(guard.get()->data()),
        sizeof(body));

    const uint8_t extraData[] = {'d'};

    const bool result = guard.get()->append(
        extraData,
        sizeof(extraData),
        sizeof(body),
        sizeof(body));

    TEST_ASSERT_FALSE(result);

    // The status must remain Complete.
    TEST_ASSERT_EQUAL(
        RequestBodyContext::Status::Complete,
        guard.get()->getStatus());
    TEST_ASSERT_EQUAL_UINT32(sizeof(body), guard.get()->size());
    TEST_ASSERT_EQUAL_UINT8_ARRAY(
        body,
        reinterpret_cast<const uint8_t *>(guard.get()->data()),
        sizeof(body));
}

void test_append_rejects_data_after_empty_body_completed()
{
    RequestBodyContextGuard guard(RequestBodyContext::create(0, 0));

    TEST_ASSERT_NOT_NULL(guard.get());

    TEST_ASSERT_EQUAL(
        RequestBodyContext::Status::Complete,
        guard.get()->getStatus());
    TEST_ASSERT_EQUAL_UINT32(0, guard.get()->size());
    TEST_ASSERT_NOT_NULL(guard.get()->data());
    TEST_ASSERT_EQUAL_STRING("", guard.get()->data());

    const bool result = guard.get()->append(nullptr, 0, 0, 0);

    TEST_ASSERT_FALSE(result);

    TEST_ASSERT_EQUAL(
        RequestBodyContext::Status::Complete,
        guard.get()->getStatus());
    TEST_ASSERT_EQUAL_UINT32(0, guard.get()->size());
    TEST_ASSERT_NOT_NULL(guard.get()->data());
    TEST_ASSERT_EQUAL_STRING("", guard.get()->data());
}

void run_request_body_context_tests()
{
    RUN_TEST(test_create_valid_context);
    RUN_TEST(test_create_rejects_oversized_body);
    RUN_TEST(test_create_rejects_allocation_size_overflow);
    RUN_TEST(test_create_completes_empty_body);

    RUN_TEST(test_append_single_chunk);
    RUN_TEST(test_append_multiple_chunks);
    RUN_TEST(test_append_accepts_null_data_with_zero_length);

    RUN_TEST(test_append_rejects_wrong_index);
    RUN_TEST(test_append_rejects_wrong_total);
    RUN_TEST(test_append_rejects_chunk_out_of_bounds);
    RUN_TEST(test_append_rejects_null_data_with_nonzero_length);

    RUN_TEST(test_append_rejects_data_after_complete);
    RUN_TEST(test_append_rejects_data_after_empty_body_completed);
}
