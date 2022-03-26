/**
 * @file buffer.c
 * @author Tomás Sánchez <tosanchez@frba.utn.edu.ar>
 * @brief Buffer class unit tests
 * @version 0.1
 * @date 03-26-2022
 *
 * @copyright Copyright (c) 2022
 *
 */

#include "buffer.h"
#include "ctest.h"

CTEST(buffer, when_bufferIsCreated_then_hasSpecifiedSize)
{
	size_t size = 10;
	buffer_t *buffer = buffer_create(size);

	if (buffer == NULL)
		ASSERT_FAIL();

	ASSERT_EQUAL(size, buffer->size);
	buffer_destroy(buffer);
}

CTEST(buffer, when_bufferIsDestroyed_then_isFreed)
{
	size_t size = 1;
	buffer_t *buffer = buffer_create(size);
	buffer_destroy(buffer);
	ASSERT_NOT_EQUAL(size, buffer->size);
}
