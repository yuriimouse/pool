#ifndef UNIT_TEST_DEFS_H
#define UNIT_TEST_DEFS_H

#define _GNU_SOURCE

#define FREE_AND_NULL(x) \
    if (x)               \
        free(x);         \
    x = NULL

#define START_USING_TEST_DATA(path)                                                     \
    {                                                                                   \
        char *_str = NULL;                                                              \
        FILE *_fp;                                                                      \
        asprintf(&_str, "%s%s", (path), __func__);                                      \
        if ((_fp = fopen(_str, "r")))                                                   \
        {                                                                               \
            FREE_AND_NULL(_str);                                                        \
            size_t _len = 0;                                                            \
            for (int _read = 0; (_read = getline(&_str, &_len, _fp)) != -1; free(_str)) \
            {                                                                           \
                if (strlen(_str) && _str[0] != '#')

#define USE_OF_THE_TEST_DATA(...) sscanf(_str, __VA_ARGS__)

#define FINISH_USING_TEST_DATA             \
    FREE_AND_NULL(_str);                   \
    }                                      \
    fclose(_fp);                           \
    }                                      \
    else                                   \
    {                                      \
        printf("'%s' not found...", _str); \
        free(_str);                        \
        CU_ASSERT_TRUE_FATAL(0);           \
    }                                      \
    }

#endif // UNIT_TEST_DEFS_H
