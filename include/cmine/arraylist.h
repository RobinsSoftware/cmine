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
include/cmine/arraylist.h

*/

#ifndef CM_ARRAYLIST_H
#define CM_ARRAYLIST_H

#include <stdlib.h>

#ifdef __cplusplus
extern "C"
{
#endif

    typedef struct ArrayList
    {
        void **data;
        size_t size;
    } * ArrayList;

    // creates a new arraylist
    // @return new list ptr
    extern ArrayList arraylist_create();
    // gets the size of an arraylist
    extern int arraylist_size(ArrayList list);
    // gets the value stored at the index
    extern void *arraylist_get(ArrayList list, int index);
    // sets the value at a given index
    extern void arraylist_set(ArrayList list, int index, void *value);
    // adds a value to the arraylist
    extern void arraylist_add(ArrayList list, void *value);
    // adds the values of an array to the arraylist
    // @param elements amount of items in the array to copy
    extern void arraylist_add_array(ArrayList list, void *array, size_t elements);
    // adds the values of an arraylist to another arraylist
    extern void arraylist_add_arraylist(ArrayList list, ArrayList add);
    // remove an element at a specified index
    extern void arraylist_remove(ArrayList list, int index);
    // removes the first element that matches the provided value
    extern void arraylist_remove_first(ArrayList list, void *value);
    // removes all elements that match the provided value
    extern void arraylist_remove_all(ArrayList list, void *value);
    // clears all elements
    extern void arraylist_clear(ArrayList list);

#ifdef __cplusplus
}
#endif
#endif
