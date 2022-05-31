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
include/cmine/thread.h

*/

#ifndef CM_THREAD_H
#define CM_THREAD_H

#include <stdbool.h>
#include <stdint.h>
#include <pthread.h>

#ifdef __cplusplus
extern "C"
{
#endif

    // method to call on thread execution
    typedef void (*Thread)(void *arg);

    // internal use only
    typedef struct RepeatingThread
    {
        pthread_t id;
        uint64_t repeats, delay, owner;
        volatile bool kill;
        Thread function;
        void *arg;
    } * RepeatingThread;

    // internal use only
    typedef struct AsyncThread
    {
        pthread_t id;
        uint64_t owner;
        Thread function;
        void *arg;
    } * AsyncThread;

    /**
     * sleeps the current thread for a specified time in milliseconds
     *
     * @param millis milliseconds to sleep for
     */
    extern void sleep_millis(uint64_t millis);

    /**
     * launches a thread to run a specified method
     *
     * @param method thread method to call upon launch
     * @param arg argument to pass to the thread
     * @param owner owner of the thread
     */
    extern void async_once(Thread method, void *arg, uint64_t owner);

    /**
     * launches a thread to run a specified method on repeat
     *
     * @param method thread method to call each time
     * @param arg argument to pass to the thread
     * @param amount amount of repeats (0 if infinite)
     * @param delay amount of time between each call
     * @param owner owner of the thread
     */
    extern void async_repeat(Thread method, void *arg, uint64_t amount, uint64_t delay, uint64_t owner);

#ifdef __cplusplus
}
#endif

#endif
