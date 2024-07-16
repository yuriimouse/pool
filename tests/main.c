/**
 * @brief The main unit test module
 * @author Yurii Prudius
 **/
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "defines.h"
#include <CUnit/Basic.h>
#include <pool/pool.h>

extern CU_TestInfo testing_attributes[];
// extern CU_TestInfo testing_pool_string[];
// extern CU_TestInfo testing_pool_address[];
// extern CU_TestInfo testing_pool_mask[];
// extern CU_TestInfo testing_pool_contains[];

static int checkError(CU_ErrorCode error)
{
    if (error)
    {
        int errCode = CU_get_error();
        fprintf(stderr, "Error: %s\n", CU_get_error_msg());
        CU_cleanup_registry();
        return errCode;
    }
    return 0;
}

int main(int argc, char *argv[])
{
    int ret = 0;

    if (CUE_SUCCESS != CU_initialize_registry())
    {
        printf("\nInitialization of Test Registry failed.");
    }
    else
    {
        CU_SuiteInfo suites[] =
            {
                // suite name, init, clean, NULL, NULL, array of tests
                {"[testing_attributes]", NULL, NULL, NULL, NULL, testing_attributes},
                // {"[pool_string]", NULL, NULL, NULL, NULL, testing_pool_string},
                // {"[pool_address]", NULL, NULL, NULL, NULL, testing_pool_address},
                // {"[pool_mask]", NULL, NULL, NULL, NULL, testing_pool_mask},
                // {"[pool_contains]", NULL, NULL, NULL, NULL, testing_pool_contains},
                CU_SUITE_INFO_NULL,
            };

        if ((ret = checkError(CU_register_suites(suites))))
        {
            return ret;
        }

        if (argc > 1)
        {
            if (argv[1])
            {
                if (!strcmp("-v", argv[1]))
                {
                    CU_basic_set_mode(CU_BRM_VERBOSE); // Maximum output of run details
                }
                else if (!strcmp("-s", argv[1]))
                {
                    CU_basic_set_mode(CU_BRM_SILENT); // No output is printed except error messages
                }
                else
                {
                    CU_basic_set_mode(CU_BRM_NORMAL); // Failures and run summary are printed
                }
            }
        }

        if ((ret = checkError(CU_basic_run_tests())))
        {
            return ret;
        }

        CU_cleanup_registry();
        return 0;
    }
}
