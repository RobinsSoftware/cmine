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
src/consolecommand.c

*/

#include <stdlib.h>

#include <cmine/in.h>
#include <cmine/out.h>
#include <cmine/cmine.h>

#include "internal.h"

ConsoleCommand _quit_console_command(String input)
{
    if (!_active)
        return NULL;

    println("Shutting down server.");
    _active = false;

    return NULL;
}
