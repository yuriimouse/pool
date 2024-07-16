/**
 * @author Yurii Prudius
 **/
#include "defines.h"

#include <CUnit/Basic.h>
#include <cjson/cJSON.h>
#include <inttypes.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include <pool/pool.h>

static void test_pool(void)
{
    char *entity = NULL;
    char *type = NULL;
    char *list = NULL;
    char *values = NULL;

    printf("\n%s\n", __func__);
    // fill
    START_USING_TEST_DATA("data/")
    {
        USE_OF_THE_TEST_DATA("%m[^:] : %ms %m[^=] = %m[^\n]", &entity, &type, &list, &values);
        // +code
        {
            pool_attribute *attrs = NULL;
            cJSON *json = NULL;
            char *name = '@' == entity[0] ? entity + 1 : entity;
            FILE_CONTENTS_READ(buffer, "%s_data/%s.json", DATA_PATH, name)
            {
                json = cJSON_Parse(buffer);
                cJSON *element = NULL;
                cJSON_ArrayForEach(element, json)
                {
                    attrs = pool_attributeSet(attrs, element->string, element->valuestring);
                }
            }
            FILE_CONTENTS_DONE;
            cJSON_Delete(json);

            int created = pool_add(entity, type, strdup(entity), free, attrs);
            attrs = NULL;
            CU_ASSERT_EQUAL_FATAL(created, 1);

            char *actual_type = pool_getType(entity);
            CU_ASSERT_PTR_NOT_NULL_FATAL(actual_type);
            CU_ASSERT_STRING_EQUAL_FATAL(actual_type, type);

            char *actual_entity = pool_getEntity(entity);
            CU_ASSERT_STRING_EQUAL_FATAL(actual_entity, entity);

            for (char *sname = NULL, *name = strtok_r(list, ", ", &sname), *sval = NULL, *val = strtok_r(values, ", ", &sval);
                 name && val;
                 name = strtok_r(NULL, ", ", &sname), val = strtok_r(NULL, ", ", &sval))
            {
                char *actual_attr = pool_getAttributeByName(entity, name);
                if (actual_attr)
                {
                    CU_ASSERT_STRING_EQUAL(val, actual_attr);
                }
                else
                {
                    CU_ASSERT_FALSE(strcmp(val, "NULL"));
                }
            }
        }
        // -code
        FREE_AND_NULL(entity);
        FREE_AND_NULL(type);
        FREE_AND_NULL(list);
        FREE_AND_NULL(values);
    }
    FINISH_USING_TEST_DATA;
    pool_destroy();
}

CU_TestInfo testing_pool[] =
    {
        {"(test_pool)", test_pool},
        CU_TEST_INFO_NULL,
};
