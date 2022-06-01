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
src/arraylist.c

*/

#include <stdlib.h>
#include <stdio.h>
#include <stdbool.h>
#include <string.h>

#include <cmine/arraylist.h>
#include <cmine/memory.h>

ArrayList arraylist_create()
{
    ArrayList list = memory_alloc(END_OF_PROGRAM, sizeof(struct ArrayList), (MemoryFinalizer) &arraylist_clear);
    return list;
}

int arraylist_size(ArrayList list)
{
    return list->size;
}

void *arraylist_get(ArrayList list, int index)
{
    void **data = list->data + (sizeof(void*) * index);
    return *data;
}

bool arraylist_contains(ArrayList list, void *value)
{
    for (int i = 0; i < list->size; i++)
        if (arraylist_get(list, i) == value)
            return true;
    return false;
}

void arraylist_set(ArrayList list, int index, void *value)
{
    void **data = list->data + (sizeof(void*) * index);
    *data = value;
}

void arraylist_add(ArrayList list, void *value)
{
    list->size++;
    list->data = realloc(list->data, list->size * sizeof(void*));
    arraylist_set(list, list->size - 1, value);
}

void arraylist_add_array(ArrayList list, void* array, size_t elements)
{
    list->size += elements;
    list->data = realloc(list->data, list->size * sizeof(void*));
    memcpy((*list->data + (list->size - elements) * sizeof(void*)), array, (list->size - elements) * sizeof(void*));
}

void arraylist_add_arraylist(ArrayList list, ArrayList add)
{
    list->size += add->size;
    list->data = realloc(list->data, list->size * sizeof(void*));
    memcpy((*list->data + ((list->size - add->size) * sizeof(void*))), add->data, (list->size - add->size) * sizeof(void*));
}

void arraylist_remove(ArrayList list, int index)
{
    list->size--;
    memcpy((*list->data + (index * sizeof(void))), (*list->data + ((index + 1) * sizeof(void))), (list->size - index) * sizeof(void*));
    list->data = realloc(list->data, list->size * sizeof(void*));
}

void arraylist_remove_first(ArrayList list, void *value)
{
    for (int i = 0; i < list->size; i++)
        if (list->data == value)
            arraylist_remove(list, i);
}

void arraylist_remove_all(ArrayList list, void *value)
{
    while (arraylist_contains(list, value))
        arraylist_remove_first(list, value);
}

void arraylist_clear(ArrayList list)
{   
    if (list->data == NULL)
        return;

    free(list->data);
    list->data = NULL;
    list->size = 0;
}
