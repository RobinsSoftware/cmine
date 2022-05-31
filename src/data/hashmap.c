/*
Copyright 2022 ROBINS SOFTWARE

Licensed under the Apache License, Version 2.0 (the "License");
you may not use this file except in compliance with the License.
You may obtain a copy of the License at

    http://www.apache.org/licenses/LICENSE-2.0

Unless required by applicable law or agreed to in writing, software
distributed under the License is distributed on an "AS IS" BASIS,
WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
See the License for the specific language governing permissions and
limitations under the License.

CMine by Robins Software <3
https://github.com/RobinsSoftware/cmine
src/data/hashmap.c

*/

#include <string.h>

#include <cmine/data/arraylist.h>
#include <cmine/data/hashmap.h>
#include <cmine/memory.h>

HashMapNode _hashmap_get_node(HashMap map, void *key)
{
    for (int i = 0; i < arraylist_size(map->list); i++)
    {
        HashMapNode node = (HashMapNode)arraylist_get(map->list, i);

        if ((map->string && strcmp((char *)node->key, (char *)key)) || !map->string && node->key == key)
            return node;
    }

    return NULL;
}

void _hashmap_finalize(HashMap map)
{
    hashmap_clear(map);
    free(map->list);
}

HashMap hashmap_create(bool string)
{
    HashMap map = memory_alloc(END_OF_PROGRAM, sizeof(struct ArrayList), (MemoryFinalizer)&_hashmap_finalize);
    map->list = calloc(1, sizeof(struct ArrayList));
    map->string = string;
    return map;
}

ArrayList hashmap_keys(HashMap map)
{
    ArrayList keys = arraylist_create();

    for (int i = 0; i < arraylist_size(map->list); i++)
        arraylist_add(keys, ((HashMapNode)arraylist_get(map->list, i))->key);

    return keys;
}

ArrayList hashmap_values(HashMap map)
{
    ArrayList values = arraylist_create();

    for (int i = 0; i < arraylist_size(map->list); i++)
        arraylist_add(values, ((HashMapNode)arraylist_get(map->list, i))->value);
    
    return values;
}

void hashmap_put(HashMap map, void *key, void *value)
{
    HashMapNode node = (HashMapNode) _hashmap_get_node(map, key);

    if (node == NULL)
        node = calloc(1, sizeof(struct HashMapNode));

    node->key = key;
    node->value = value;
    arraylist_add(map->list, node);
}

void hashmap_remove(HashMap map, void *key)
{
    HashMapNode node = _hashmap_get_node(map, key);

    if (node == NULL)
        return;

    arraylist_remove_first(map->list, node);
    free(node);
}

void hashmap_remove_values(HashMap map, void *value)
{
    for (int i = 0; i < arraylist_size(map->list); i++)
    {
        HashMapNode node = (HashMapNode)arraylist_get(map->list, i);

        if (node->value == value)
        {
            arraylist_remove_first(map->list, node);
            free(node);
        }
    }
}

bool hashmap_contains_key(HashMap map, void *key)
{
    if (_hashmap_get_node(map, key) != NULL)
        return true;
    return false;
}

void *hashmap_get(HashMap map, void *key)
{
    if (_hashmap_get_node(map, key) != NULL)
        return ((HashMapNode) _hashmap_get_node(map, key))->value;
    return NULL;
}

void hashmap_clear(HashMap map)
{
    for (int i = 0; i < arraylist_size(map->list); i++)
        free(arraylist_get(map->list, i));

    arraylist_clear(map->list);
}
