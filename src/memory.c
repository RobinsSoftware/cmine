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
src/memory.c

*/

#include <stdlib.h>
#include <stdio.h>

#include <cmine/data/arraylist.h>
#include <cmine/memory.h>
#include <cmine/out.h>

// optional use garbage collector
// minimalistic, will try to prevent memory leaks & clean up
// by doing sweeps upon events being fired within the engine

// taken from lolasengine :3

ArrayList groups[GC_LAST];

void *memory_alloc(MemoryGroup group, int size, MemoryFinalizer finalizer)
{
    void *ptr = calloc(1, size);
    memory_track(group, ptr, finalizer);
    return ptr;
}

void *memory_realloc(void *ptr, int size)
{
    MemoryNode node = memory_find(ptr);
    void *new = realloc(ptr, size);

    if (node != NULL)
        node->memory = new;
    else
        println_err("Memory address provided is not stored by the garbage collector. (memory_realloc).");

    return new;
}

MemoryNode memory_track(MemoryGroup group, void *memory, MemoryFinalizer finalizer)
{
    if (memory == NULL)
    {
        println_err("Null memory pointer provided. (memory_track).");
        return NULL;
    }
    
    if (groups[group] == NULL)
        groups[group] = calloc(1, sizeof(struct ArrayList));

    MemoryNode node = calloc(1, sizeof(struct MemoryNode));

    if (groups[group] == NULL || node == NULL)
    {
        println_err("Memory allocation failed. (memory_track).");
        return NULL;
    }
    
    node->memory = memory; 
    node->finalizer = finalizer;
    node->position = group;

    arraylist_add(groups[group], node);

    return node;
}

void memory_track_move(MemoryNode node, int id)
{
    arraylist_remove_first(groups[node->position], node);
    arraylist_add(groups[id], node);

    node->position = id;
}

void memory_free(void *memory)
{
    MemoryNode node = memory_find(memory);

    if (node != NULL)
    {
        arraylist_remove_first(groups[node->position], node);

        if (node->finalizer != NULL)
            ((MemoryFinalizer) node->finalizer)(node->memory);

        free(node);
    }
    
    free(memory);
}

void memory_free_all(MemoryGroup group)
{
    if (groups[group] == NULL)
        return;

    for (int i = 0; i < arraylist_size(groups[group]); i++)
    {
        MemoryNode node = (MemoryNode) arraylist_get(groups[group], i);
        
        if (node->finalizer != NULL)
            ((MemoryFinalizer) node->finalizer)(node->memory);

        free(node->memory);
        free(node);
    }

    arraylist_clear(groups[group]);
    free(groups[group]);
    
    groups[group] = NULL;
}

void memory_attach_finalizer(MemoryNode node, MemoryFinalizer finalizer)
{
    node->finalizer = finalizer;
}

MemoryNode memory_find(void *memory)
{
    for (int i = 0; i < GC_LAST + 1; i++)
    {
        if (groups[i] == NULL)
            continue;
        for (int j = 0; j < groups[i]->size; i++)
            if (arraylist_get(groups[i], j) == memory) 
                return arraylist_get(groups[i], j);
    }

    return NULL;
}
