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
include/cmine/memory.h

*/

#ifndef CM_MEMORY_H
#define CM_MEMORY_H

#include <stdbool.h>

#ifdef __cplusplus
extern "C"
{
#endif

    // groups of memory that will clear together at a specified time during runtime
    typedef enum MemoryGroup
    {
        // clears at the end of program
        END_OF_PROGRAM,
        // clears after next tick in game
        GAME_TICK,
        // clears after an event is called
        EVENT_CALLED,
        // internal use only
        GC_LAST
    } MemoryGroup;

    // memory finalizer method
    typedef void (*MemoryFinalizer)(void *memory);

    typedef struct MemoryNode
    {
        void *memory;
        MemoryFinalizer finalizer;
        int position;
    } * MemoryNode;

    /**
     *
     * allocates memory that will free with a specified group
     *
     * @param group group to clear with
     * @param size amount of memory to allocate
     * @param finalizer finalizer to call before freeing memory (nullable)
     *
     * @return allocated memory node
     */
    extern void *memory_alloc(MemoryGroup group, int size, MemoryFinalizer finalizer);

    /**
     * reallocates memory previously allocated by the collector
     *
     * @param memory memory to reallocate
     * @param size new size of memory chunk
     *
     * @return reallocated memory node
     */
    extern void *memory_realloc(void *memory, int size);

    /**
     * track memory for removal with a specified group during runtime
     *
     * @param group group to clear with
     * @param memory memory to track
     * @param finalizer finalizer to call before freeing memory (nullable)
     *
     * @return collector's memory node created
     */
    extern MemoryNode memory_track(MemoryGroup group, void *memory, MemoryFinalizer finalizer);

    /**
     * frees a chunk of allocated memory
     *
     * @param memory memory to free
     */
    extern void memory_free(void *memory);

    /**
     * frees all allocated memory from a specified group
     *
     * @param group group to free
     */
    extern void memory_free_all(MemoryGroup group);

    /**
     * attaches a finalizer (deconstructor) to a memory node to be called before freeing a specified piece of memory
     *
     * @param node node to attach finalizer to
     * @param finalizer finalizer to use (nullable)
     */
    extern void memory_attach_finalizer(MemoryNode node, MemoryFinalizer finalizer);

    /**
     * finds a memory node corresponding with a given memory address
     *
     * @param memory memory allocated by the collector
     *
     * @return memory node (if found)
     */
    extern MemoryNode memory_find(void *memory);

#ifdef __cplusplus
}
#endif
#endif
