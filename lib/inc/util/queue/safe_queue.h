#pragma once

#include <pthread.h>
#include <commons/collections/queue.h>

// 

// 	/**
// 	* @NAME: queue_push
// 	* @DESC: Agrega un elemento al final de la cola
// 	*/
// 	void queue_push(t_queue *, void *element);

// 	/**
// 	* @NAME: queue_pop
// 	* @DESC: quita el primer elemento de la cola
// 	*/
// 	void *queue_pop(t_queue *);

// 
typedef struct SafeQueue
{

	// ! Private:

	/**
	 * @brief Thread safety ensurer.
	 * @private
	 */
	pthread_mutex_t _mtx;

	/**
	 * @brief queue implementation.
	 * @private
	 */
	t_queue *_queue;

	// ! Public:

} safe_queue_t;


/**
 * @brief safely add an element at the last of the queue.
 *
 * @return .
 */
safe_queue_t safe_queue_push(t_queue *, void *element);

/**
 * @brief safely remove the last elementf of the queue.
 *
 * @return .
 */
safe_queue_t *safe_queue_pop(t_queue *);