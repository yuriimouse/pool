/**
 * @file pool.c
 * @author Yurii Prudius (yurii.prudius@gmail.com) [https://github.com/yuriimouse/pool]
 * @brief An automatically managed list of named typed entities
 * @version 2.2.1
 * @date 2024-07-15
 * 
 * @copyright Copyright (c) 2024
 * 
 */
#include "pool.h"
#include <errno.h>

typedef struct pool_entity
{
    char *name;
    char *type;
    void *entity;
    void (*destructor)(void *);
    pool_attribute *list;
    struct pool_entity *next;
} pool_entity;

static pool_entity *_pool_ = NULL;

/**
 * Entity attributes builder.
 * The duplicate will replace the previous value.
 *
 * @param name
 * @param value
 * @return pool_attribute*
 */
pool_attribute *pool_attributeSet(pool_attribute *list, const char *name, const char *value)
{
    if (name && value)
    {
        pool_attribute *new = malloc(sizeof(pool_attribute));
        if (!new)
        {
            errno = ENOMEM;
            return list;
        }
        new->name = strdup(name);
        new->value = strdup(value);
        new->next = list ? list : NULL;
        return new;
    }
    errno = EINVAL;
    return list;
}

/**
 * Gets entity attribute by name
 *
 * @param name
 * @return char*
 */
char *pool_attributeGet(pool_attribute *list, const char *name)
{
    if (name)
    {
        pool_attribute *ptr = NULL;
        for (ptr = list; ptr; ptr = ptr->next)
        {
            if (!strcmp(name, ptr->name))
            {
                break;
            }
        }
        return ptr ? ptr->value : NULL;
    }
    errno = EINVAL;
    return NULL;
}

/**
 * Destruct entity record
 *
 * @param record
 * @return pool_entity *
 */
static pool_entity *entity_destruct(pool_entity *record)
{
    if (record)
    {
        FREE_AND_NULL(record->name);
        FREE_AND_NULL(record->type);

        if (record->destructor)
        {
            record->destructor(record->entity);
        }
        record->entity = NULL;

        // attributes list destroy and free
        for (pool_attribute *ptr = record->list; ptr;)
        {
            FREE_AND_NULL(ptr->name);
            FREE_AND_NULL(ptr->value);
            pool_attribute *next = ptr->next;
            free(ptr);
            ptr = next;
        }
        record->list = NULL;
        return record;
    }
    errno = EINVAL;
    return NULL;
}

/**
 * Destroy pool
 *
 * @param name
 * @return char*
 */
void pool_destroy()
{
    for (pool_entity *ptr = _pool_; ptr;)
    {
        entity_destruct(ptr);
        pool_entity *next = ptr->next;
        free(ptr);
        ptr = next;
    }
}

/**
 * Gets entity by name
 *
 * @param name
 * @return char*
 */
static pool_entity *pool_get(const char *name)
{
    if (name)
    {
        pool_entity *ptr = NULL;
        for (ptr = _pool_; ptr; ptr = ptr->next)
        {
            if (!strcmp(name, ptr->name))
            {
                break;
            }
        }
        return ptr;
    }
    errno = EINVAL;
    return NULL;
}

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
int pool_add(const char *name, const char *type, void *entity, void (*destructor)(void *), pool_attribute *list)
{
    if (name && type && entity)
    {
        if (pool_get(name))
        {
            errno = EEXIST;
            return 0;
        }
        pool_entity *new = malloc(sizeof(pool_entity));
        if (!new)
        {
            errno = ENOMEM;
            return 0;
        }
        new->name = strdup(name);
        new->type = strdup(type);
        new->entity = entity;
        new->destructor = destructor;
        new->list = list;
        new->next = _pool_;

        _pool_ = new;
        return 1;
    }
    errno = EINVAL;
    return 0;
}

/**
 * Gets entity type by name
 *
 * @param name
 * @return char*
 */
char *pool_getType(const char *name)
{
    pool_entity *entity = pool_get(name);
    return entity ? entity->type : NULL;
}

/**
 * Gets entity by name
 *
 * @param name
 * @return char*
 */
void *pool_getEntity(const char *name)
{
    pool_entity *entity = pool_get(name);
    return entity ? entity->entity : NULL;
}

/**
 * Gets entity attributes list by name
 *
 * @param name
 * @return char*
 */
pool_attribute *pool_getAttributes(const char *name)
{
    pool_entity *entity = pool_get(name);
    return entity ? entity->list : NULL;
}

/**
 * Gets the version
 *
 * @return const char*
 */
const char *pool_version()
{
    return VERSION;
}
