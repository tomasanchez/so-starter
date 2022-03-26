/**
 * @file buffer.c
 * @author Tomás Sánchez <tosanchez@frba.utn.edu.ar>
 * @brief Buffer class implementation
 * @version 0.1
 * @date 03-26-2022
 *
 * @copyright Copyright (c) 2022
 *
 */
#include <stdlib.h>

#include "buffer.h"

// ============================================================================================================
//                               ***** Public Functions *****
// ============================================================================================================

buffer_t *buffer_create(size_t size)
{
	// A new buffer instace
	buffer_t *buffer = malloc(sizeof(buffer_t));
	buffer->size = size;
	buffer->stream = malloc(buffer->size);
	return buffer;
}

void buffer_destroy(buffer_t *buffer_instance)
{
	free(buffer_instance->stream);
	free(buffer_instance);
}
