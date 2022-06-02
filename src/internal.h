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
src/internal.h

*/

#ifndef UTIL_INTERNAL_H
#define UTIL_INTERNAL_H

#include <cmine/thread.h>
#include <cmine/in.h>
#include <cmine/socket.h>

#ifdef __cplusplus
extern "C"
{
#endif

    extern bool _active;

    // listen for console commands
    extern Thread _input_listener(void *arg);

    // init sockets
    extern Thread _socket_init(void *arg);

    // kills repeating tasks
    extern void _kill_all_repeating();

    // commands
    extern ConsoleCommand _quit_console_command(String input);

    extern void _parse_packet(ClientData data, uint8_t *buffer);

    extern void _send_raw_packet(ClientData client, uint8_t *buffer, size_t size);


#ifdef __cplusplus
}
#endif

#endif
