/**
 * example_test.c
 *
 * @file Example test cases
 * @author Tomás Sánchez
 * @since  02.17.2022
 */
#include <stdlib.h>

#include "ctest.h"
#include "example.h"

CTEST(example, whenExample_then_isExitSuccess)
{
    ASSERT_EQUAL(EXIT_SUCCESS, example());
};

CTEST(example, whenExampleHello_then_shouldReturnHelloWorld)
{
    ASSERT_STR("Hello, world!", hello_message());
}