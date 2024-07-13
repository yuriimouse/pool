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

typedef struct entity_attribute
{
    char *name;
    char *value;
    struct entity_attribute *next;
} entity_attribute;

/**
 * Entity attributes builder
 *
 * @param name
 * @param value
 * @return entity_attribute*
 */
entity_attribute *entity_set(entity_attribute *list, const char *name, const char *value);

/**
 * Gets entity attribute by name
 *
 * @param name
 * @return char*
 */
char *entity_get(entity_attribute *list, const char *name);

typedef struct pool_entity
{
    char *name;
    char *type;
    void *entity;
    int (*destructor)(void *);
    entity_attribute *list;
    pool_entity *next;
} pool_entity;

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
int pool_add(const char *name, const char *type, void *entity, int (*destructor)(void *), entity_attribute *list);

/**
 * Deregisters entity by name
 *
 * @param name
 * @return char*
 */
int pool_delete(const char *name);

/**
 * Replace an entity in the pool
 *
 * @param name
 * @param type
 * @param entity
 * @param destructor
 * @param list
 * @return int
 */
int pool_replace(const char *name, const char *type, void *entity, int (*destructor)(void *), entity_attribute *list);

/**
 * Gets entity by name
 *
 * @param name
 * @return char*
 */
pool_entity *pool_get(const char *name);

/**
 * Gets the version
 * 
 * @return const char* 
 */
const char *pool_version();

#endif // POOL_H
