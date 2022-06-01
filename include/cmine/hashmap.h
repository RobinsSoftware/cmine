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
include/cmine/hashmap.h

*/

#ifndef CM_HASHMAP_H
#define CM_HASHMAP_H

#include <stdbool.h>

#include <cmine/arraylist.h>

#ifdef __cplusplus
extern "C"
{
#endif

    // hashmap datatype for storing key/value pairs
    typedef struct HashMap {
        ArrayList list;
        bool string;
    } * HashMap;

    // internal use only
    typedef struct HashMapNode
    {
        void *key;
        void *value;
    } * HashMapNode;

    /**
     * creates a new hashmap
     * (allocates memory, make sure to clear with memory_free)
     * 
     * @param string if keys are strings, setting this to true will compare strings with strcmp and not their pointers
     * @return newly created hashmap
     */
    extern HashMap hashmap_create(bool string);

    /**
     * gets all keys in a map
     * 
     * @param map map to pull keys from
     * @return list of keys
     */
    extern ArrayList hashmap_keys(HashMap map);

    /**
     * gets all values in a map
     * 
     * @param map map to pull values from
     * @return list of values
     */
    extern ArrayList hashmap_values(HashMap map);

    /**
     * adds/replaces a key/value pair into the specified hashmap
     * 
     * @param map map to add key/value pair to
     * @param key key to set
     * @param value value to set
     */
    extern void hashmap_put(HashMap map, void *key, void *value);

    /**
     * removes a key/value pair from a hashmap given the specified key
     * 
     * @param map map to remove key from
     * @param key key to remove
     */
    extern void hashmap_remove(HashMap map, void *key);

    /**
     * removes any key/value pair from a hashmap given the specified value
     * 
     * @param map map to remove the values from
     * @param value value to scan for
     */
    extern void hashmap_remove_values(HashMap map, void *value);

    /**
     * checks if a hashmap contains a key
     * 
     * @param map map to check for key
     * @param key key to scan for
     * 
     * @return true if hashmap contains key
     */
    extern bool hashmap_contains_key(HashMap map, void *key);

    /**
     * gets a value at a specified key in the hashmap
     * 
     * @param map map to pull from
     * @param key key to return
     * 
     * @return value ptr
     */
    extern void *hashmap_get(HashMap map, void *key);

    /**
     * clears all key/value pairs from a hashmap
     * 
     * @param map map to clear
     */
    extern void hashmap_clear(HashMap map);

#ifdef __cplusplus
}
#endif

#endif
