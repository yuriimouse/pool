#ifndef POOL_H
#define POOL_H

#define _GNU_SOURCE

#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#ifndef VERSION
#define VERSION "0"
#endif

#define FREE_AND_NULL(x) \
    if (x)               \
    {                    \
        free(x);         \
        x = NULL;        \
    }

typedef struct pool_attribute
{
    char *name;
    char *value;
    struct pool_attribute *next;
} pool_attribute;

/**
 * Pool attributes builder
 *
 * @param name
 * @param value
 * @return pool_attribute*
 */
pool_attribute *pool_attributeSet(pool_attribute *list, const char *name, const char *value);

/**
 * Gets pool attribute by name
 *
 * @param name
 * @return char*
 */
char *pool_attributeGet(pool_attribute *list, const char *name);

/**
 * Destroy pool
 *
 * @param name
 */
void pool_destroy();

/**
 * Registers an entity in the pool
 *
 * @param name
 * @param type
 * @param entity
 * @param destructor
 * @param list
 * @return int
 */
int pool_add(const char *name, const char *type, void *entity, int (*destructor)(void *), pool_attribute *list);

/**
 * Gets entity type by name
 *
 * @param name
 * @return char*
 */
char *pool_getType(const char *name);

/**
 * Gets entity by name
 *
 * @param name
 * @return char*
 */
void *pool_getEntity(const char *name);

/**
 * Gets entity attributes list by name
 *
 * @param name
 * @return char*
 */
pool_attribute *pool_getAttributes(const char *name);

/**
 * Gets the version
 *
 * @return const char*
 */
const char *pool_version();

#endif // POOL_H
