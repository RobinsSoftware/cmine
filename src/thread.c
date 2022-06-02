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
src/thread.c

*/

#include <cmine/thread.h>
#include <cmine/arraylist.h>
#include <cmine/memory.h>
#include <cmine/out.h>

#include <stdlib.h>
#include <stdint.h>

#include <unistd.h>
#include <pthread.h>

ArrayList repeating;

void _kill_all_repeating()
{
    if (repeating == NULL)
        return;

    for (int i = 0; i < arraylist_size(repeating); i++)
        ((RepeatingThread)arraylist_get(repeating, i))->kill = true;
}

void *_thread(void *arg)
{
    AsyncThread thread = (AsyncThread)arg;

    ((Thread) thread->function)(thread->arg);

    free(thread);

    return NULL;
}

void *_repeating_thread(void *arg)
{
    RepeatingThread thread = (RepeatingThread)arg;

    if (thread->repeats == 0)
        while (!thread->kill)
        {
            sleep_millis(thread->delay);
            ((Thread)thread->function)(thread->arg);
        }
    else
        for (int i = 0; i < thread->repeats && !thread->kill; i++)
        {
            sleep_millis(thread->delay);
            ((Thread)thread->function)(thread->arg);
        }

    arraylist_remove_first(repeating, &thread);
    free(thread);

    return NULL;
}

void sleep_millis(uint64_t millis)
{
    usleep(millis * 1000);
}

void async_once(Thread method, void* arg, uint64_t owner)
{
    AsyncThread thread = calloc(1, sizeof(struct AsyncThread));

    thread->function = method;
    thread->owner = owner;
    thread->arg = arg;

    if (pthread_create(&thread->id, NULL, _thread, thread) != 0)
    {
        println_err("Failed to create new async thread.");
        return;
    }

    pthread_detach(thread->id);
}

void async_repeat(Thread method, void* arg, uint64_t amount, uint64_t delay, uint64_t owner)
{
    RepeatingThread thread = calloc(1, sizeof(struct RepeatingThread));

    thread->delay = delay;
    thread->repeats = amount;
    thread->function = method;
    thread->arg = arg;
    thread->owner = owner;

    if (pthread_create(&thread->id, NULL, _repeating_thread, thread) != 0)
    {
        println_err("Failed to create new async repeating thread.");
        return;
    }

    pthread_detach(thread->id);

    if (repeating == NULL)
        repeating = arraylist_create();

    arraylist_add(repeating, &thread);
}
