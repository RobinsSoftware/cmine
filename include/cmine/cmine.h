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
include/cmine/cmine.h

*/

#ifndef CMINE_H
#define CMINE_H

#include <stdint.h>
#include <stdbool.h>

#ifdef __cplusplus
extern "C"
{
#endif

#define CMINE_VERSION "v0.1.0"

    extern bool _color, _debug, _ipv6;
    extern char _address[40];
    extern uint16_t _port;

#ifdef __cplusplus
}
#endif

#endif
