/**
 * @author Yurii Prudius
 **/
#include "defines.h"

#include <CUnit/Basic.h>
#include <inttypes.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include <pool/pool.h>

static void test_attributes(void)
{
    char *key = NULL;
    char *value = NULL;

    pool_attribute *attrs = NULL;

    printf("\n%s\n", __func__);
    // fill
    START_USING_TEST_DATA("data/")
    {
        USE_OF_THE_TEST_DATA("%ms = %ms", &key, &value);

        if ('-' != value[0])
        {
            attrs = pool_attributeSet(attrs, key, value);
        }
        FREE_AND_NULL(key);
        FREE_AND_NULL(value);
    }
    FINISH_USING_TEST_DATA;

    // check
    START_USING_TEST_DATA("data/")
    {
        USE_OF_THE_TEST_DATA("%ms = %ms", &key, &value);

        char *actual = pool_attributeGet(attrs, key);
        if (actual)
        {
            CU_ASSERT_STRING_EQUAL(value, actual);
        }
        else
        {
            CU_ASSERT_STRING_EQUAL(value, "-");
        }
        FREE_AND_NULL(key);
        FREE_AND_NULL(value);
    }
    FINISH_USING_TEST_DATA;

    // part of internal function
    // attributes list destroy and free
    for (pool_attribute *ptr = attrs; ptr;)
    {
        FREE_AND_NULL(ptr->name);
        FREE_AND_NULL(ptr->value);
        pool_attribute *next = ptr->next;
        free(ptr);
        ptr = next;
    }
    attrs = NULL;
}

CU_TestInfo testing_attributes[] =
    {
        {"(attributes)", test_attributes},
        CU_TEST_INFO_NULL,
};
