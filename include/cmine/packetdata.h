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
include/cmine/packetdata.h

*/

#ifndef CM_PACKETDATA_H
#define CM_PACKETDATA_H

#include <stdint.h>
#include <stdlib.h>

#include <cmine/packetdata.h>

#ifdef __cplusplus
extern "C"
{
#endif

typedef char *String;

extern int varint_size(int32_t input);
extern int varint_write(int32_t input, uint8_t* buffer);
extern int varint_read(int32_t* output, uint8_t* buffer);
extern int varlong_size(int64_t input);
extern int varlong_write(int64_t input, uint8_t* buffer);
extern int varlong_read(int64_t* output, uint8_t* buffer);
extern int string_read(uint8_t *buffer, String output);
extern int string_write(const String source, uint8_t *output);

#ifdef __cplusplus
}
#endif

#endif
