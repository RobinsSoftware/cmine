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
src/packetdata.c

*/

#include <stdint.h>
#include <stdlib.h>
#include <string.h>

#include <cmine/packetdata.h>

// https://github.com/basinserver/basin/blob/master/src/network.c
// basin code start
int varint_size(int32_t input) {
    for (int32_t x = 1; x < 5; x++)
        if ((input & -1 << x * 7) == 0) return x;
    

    return 5;
}

int varlong_size(int64_t input) {
    for (uint8_t x = 1; x < 10; ++x)
        if (((input & -1) << (x * 7)) == 0) return x;

    return 10;
}

int varint_write(int32_t input, uint8_t* buffer) {
    int i = 0;

    while ((input & -128) != 0) {
        buffer[i++] = (input & 127) | 128;
        input >>= 7;
    }

    buffer[i++] = input;
    return i;
}

int varlong_write(int64_t input, uint8_t* buffer) {
    int i = 0;

    while ((input & -128) != 0) {
        buffer[i++] = (input & 127) | 128;
        input >>= 7;
    }

    buffer[i++] = input;
    return i;
}

int varint_read(int32_t* output, uint8_t* buffer) {
    *output = 0;
    int v2 = 0;
    signed char v3;

    do {
        v3 = buffer[v2];
        *output |= (v3 & 127) << (v2++ * 7);
        if (v2 > 5) return v2;
    } while ((v3 & 128) == 128);

    return v2;
}

int varlong_read(int64_t* output, uint8_t* buffer) {
    *output = 0;
    int v2 = 0;
    signed char v3;

    do {
        v3 = buffer[v2];
        *output |= (v3 & 127) << (v2++ * 7);
        if (v2 > 10) return v2;
    } while ((v3 & 128) == 128);

    return v2;
}
// basin code end

int string_read(uint8_t *buffer, String output)
{
    int size;
    int cursor = varint_read(&size, buffer);

    for (int i = 0; i < size; i++)
        output[i] = buffer[cursor++];
    
    output[size] = '\0';

    return cursor;
}

int string_write(const String source, uint8_t *output)
{
    int cursor = varint_write(strlen(source), output);

    for (int i = 0; i < strlen(source); i++)
        output[cursor++] = source[i];

    return cursor;
}

int bytearray_read(uint8_t *buffer, uint8_t *output)
{
    int size;
    int cursor = varint_read(&size, buffer);

    for (int i = 0; i < size; i++)
        output[i] = buffer[cursor++];
    
    return cursor;
}

int bytearray_write(const String source, uint8_t *output, size_t size)
{
    int cursor = varint_write(size, output);

    for (int i = 0; i < size; i++)
        output[cursor++] = source[i];

    return cursor;
}

union _short_conversion
{
    short s;
    uint8_t a[2];
};

union _int_conversion
{
    int i;
    uint8_t a[2];
};

union _long_conversion
{
    long l;
    uint8_t a[8];
};

union _float_conversion
{
    float f;
    uint8_t a[4];
};

union _double_conversion
{
    float d;
    uint8_t a[8];
};


int short_write(short input, String output)
{
    union _short_conversion c;
    c.s = input;

    for (int i = 0; i < 2; i++)
    {
        output[i] = c.a[i];
    }

    return 2;
}

int int_write(int input, String output)
{
    union _int_conversion c;
    c.i = input;

    for (int i = 0; i < 4; i++)
    {
        output[i] = c.a[i];
    }

    return 4;
}

int long_write(long input, String output)
{
    union _long_conversion c;
    c.l = input;

    for (int i = 0; i < 8; i++)
    {
        output[i] = c.a[i];
    }

    return 8;
}

int float_write(float input, String output)
{
    union _float_conversion c;
    c.f = input;

    for (int i = 0; i < 4; i++)
    {
        output[i] = c.a[i];
    }

    return 4;
}

int double_write(double input, String output)
{
    union _double_conversion c;
    c.d = input;

    for (int i = 0; i < 8; i++)
    {
        output[i] = c.a[i];
    }

    return 8;
}
