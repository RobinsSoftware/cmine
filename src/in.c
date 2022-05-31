#include <stdlib.h>
#include <stdio.h>
#include <string.h>

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
src/in.c

*/

#include <cmine/thread.h>
#include <cmine/data/hashmap.h>
#include <cmine/data/string.h>

#include "internal.h"

HashMap commands;

void _load_default_commands() {
    hashmap_put(commands, "quit", _quit_console_command);
}

Thread _input_listener(void *arg)
{
    commands = hashmap_create(true);
    _load_default_commands();

    char line[1024];
    while (true)
    {
        fgets(line, 1024, stdin);
        String arg0 = strtok(line, " ");
        
        ConsoleCommand command = hashmap_get(commands, arg0);
        command(string_trim(line));
    }    
}

