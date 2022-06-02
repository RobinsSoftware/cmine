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

CMine by Robins Software
https://github.com/RobinsSoftware/cmine
src/cmine.c

*/

#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <stdbool.h>

#include <cmine/cmine.h>
#include <cmine/out.h>
#include <cmine/thread.h>
#include <cmine/hashmap.h>
#include <cmine/memory.h>
#include <cmine/arraylist.h>
#include <cmine/packetdata.h>

#include "internal.h"

bool _color = true, _debug, _ipv6, _help;
volatile bool _active = true;
char _address[40] = "127.0.0.1";
uint16_t _port = 25565;

extern void _process_args(int argc, String argv[]);

int main(int argc, String argv[])
{
    _process_args(argc, argv);

    if (_help) {
        printf("> CMine Launch Flags <\
        \n-a <address> - Set server address (default: 127.0.0.1.)\
        \n-p <port> - Set server port (default: 25565.)\
        \n-c - Disable color in output\
        \n-d - Show debug output logging\
        \n-h - Show available flags\
        \n");
        return 0;
    }

    println_debug("Launching in debug mode.");

    print("Starting CMine ");
    printf(CMINE_VERSION);
    printf(".");
    end_line();

    print("Launching with address ");
    printf("%s:%d.", _address, _port);
    end_line();

    async_once((Thread) &_socket_init, NULL, 0);
    async_once((Thread) &_input_listener, NULL, 0);

    while (_active);

    // shutdown
    println_debug("Killing repeating tasks.");
    _kill_all_repeating();

    println_debug("Freeing leftover memory (end of program).");
    memory_free_all(END_OF_PROGRAM);

    return 0;
}

void _process_args(int argc, char *argv[])
{
    for (int i = 0; i < argc; i++)
    {
        if (argv[i][0] != '-')
            continue;

        switch ((uint8_t)argv[i][1])
        {
        case 'h':
            _help = true;
            break;

        // no color
        case 'c':
            _color = false;
            break;

        // use ipv6
        case '6':
            _ipv6 = true;
            break;

        // port
        case 'p':
            sscanf(argv[i + 1], "%d", (int *)&_port);
            i++;
            break;

        // address
        case 'a':
            sscanf(argv[i + 1], "%s", _address);
            i++;
            break;

        case 'd':
            _debug = true;
            break;
        }
    }
}
