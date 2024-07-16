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
int pool_add(const char *name, const char *type, void *entity, void (*destructor)(void *), pool_attribute *list);

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
 * @return void*
 */
void *pool_getEntity(const char *name);

/**
 * Gets the entity attributes list by name
 *
 * @param name
 * @return pool_attribute*
 */
pool_attribute *pool_getAttributes(const char *name);

/**
 * A macro for iterating over a list of attributes
 */
#define pool_attributesForeach(element, list) for (pool_attribute *element = (list != NULL) ? list : NULL; element != NULL; element = element->next)

/**
 * A macro for get the attribute by entity name and attribute name
 */
#define pool_getAttributeByName(entity_name, attr_name) pool_attributeGet(pool_getAttributes(entity_name), attr_name)

/**
 * Gets the version
 *
 * @return const char*
 */
const char *pool_version();

#endif // POOL_H
