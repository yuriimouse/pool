#include "pool.h"
// #include <ctype.h>
#include <errno.h>

static pool_entity *_pool_ = NULL;

/**
 * Entity attributes builder.
 * The duplicate will replace the previous value.
 *
 * @param name
 * @param value
 * @return entity_attribute*
 */
entity_attribute *entity_set(entity_attribute *list, const char *name, const char *value)
{
    if (name && value)
    {
        entity_attribute *new = malloc(sizeof(entity_attribute));
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
char *entity_get(entity_attribute *list, const char *name)
{
    if (name)
    {
        entity_attribute *ptr = NULL;
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
 * Registers an entity in the pool
 *
 * @param name
 * @param type
 * @param entity
 * @param destructor
 * @param list
 * @return int
 */
int pool_add(const char *name, const char *type, void *entity, int (*destructor)(void *), entity_attribute *list)
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
 * Destroy entity
 *
 * @param name
 * @return int
 */
static int pool_destruct(pool_entity *record)
{
    return 0;
}

/**
 * Deregisters entity by name
 *
 * @param name
 * @return char*
 */
int pool_delete(const char *name)
{
    return 0;
}

/**
 * Deregisters entity by name
 *
 * @param name
 * @return char*
 */
int pool_destroy()
{

    return 0;
}

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
int pool_replace(const char *name, const char *type, void *entity, int (*destructor)(void *), entity_attribute *list)
{
    return 0;
}

/**
 * Gets entity by name
 *
 * @param name
 * @return char*
 */
pool_entity *pool_get(const char *name)
{
    if (name)
    {
        entity_attribute *ptr = NULL;
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
 * Gets the version
 *
 * @return const char*
 */
const char *pool_version()
{
    return VERSION;
}
