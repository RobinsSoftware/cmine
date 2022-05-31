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
src/out.c

*/

#include <cmine/cmine.h>
#include <cmine/out.h>

#include <stdlib.h>
#include <stdio.h>
#include <time.h>

char *font_mode(FontMode mode)
{
    if (!_color)
        return "";

    switch (mode)
    {
    case RESET:
        return "\033[0m";
    case BOLD:
        return "\033[1m";
    case DIM:
        return "\033[2m";
    case ITALIC:
        return "\033[3m";
    case UNDERLINE:
        return "\033[4m";
    case BLINK:
        return "\033[5m";
    case REVERSE:
        return "\033[7m";
    case HIDDEN:
        return "\033[8m";
    case STRIKETHROUGH:
        return "\033[9m";
    }

    return "";
}

char *font_color(FontColor color)
{
    if (!_color)
        return "";

    switch (color)
    {
    case BLACK:
        return "\033[0;30m";
    case RED:
        return "\033[0;31m";
    case GREEN:
        return "\033[0;32m";
    case YELLOW:
        return "\033[0;33m";
    case BLUE:
        return "\033[0;34m";
    case MAGENTA:
        return "\033[0;35m";
    case CYAN:
        return "\033[0;36m";
    case WHITE:
        return "\033[0;37m";
    case DEFAULT:
        return "\033[0;39m";
    case BRIGHT_BLACK:
        return "\033[0;90m";
    case BRIGHT_RED:
        return "\033[0;91m";
    case BRIGHT_GREEN:
        return "\033[0;92m";
    case BRIGHT_YELLOW:
        return "\033[0;93m";
    case BRIGHT_BLUE:
        return "\033[0;94m";
    case BRIGHT_MAGENTA:
        return "\033[0;95m";
    case BRIGHT_CYAN:
        return "\033[0;96m";
    case BRIGHT_WHITE:
        return "\033[0;97m";
    }

    return "";
}

void print_timestamp()
{
    time_t t = time(0);
    struct tm *pt = localtime(&t);
    printf("[%02d/%02d/%04d-%02d:%02d:%02d] ", pt->tm_mon, pt->tm_mday, pt->tm_year + 1900, pt->tm_hour, pt->tm_min, pt->tm_sec);
}

void println(char *message)
{
    print_timestamp();
    printf("INFO: %s\n", message);
}

void println_err(char *message)
{
    printf("%s", font_color(RED));
    print_timestamp();
    printf("ERROR: %s%s\n", message, font_mode(RESET));
}

void println_debug(char *message)
{
    if (!_debug)
        return;

    printf("%s", font_color(YELLOW));
    print_timestamp();
    printf("DEBUG: %s%s\n", message, font_mode(RESET));
}

void print(char *message)
{
    print_timestamp();
    printf("INFO: %s", message);
}

void print_err(char *message)
{
    printf("%s", font_color(RED));
    print_timestamp();
    printf("ERROR: %s", message);
}

void print_debug(char *message)
{
    if (!_debug)
        return;

    printf("%s", font_color(YELLOW));
    print_timestamp();
    printf("DEBUG: %s", message);
}

void end_line() {
    printf("%s\n", font_mode(RESET));
}
