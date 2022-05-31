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
include/cmine/out.h

*/

#ifndef CM_OUT_H
#define CM_OUT_H

#ifdef __cplusplus
extern "C"
{
#endif

    // font mode to use (if available in your terminal)
    typedef enum FontMode
    {
        RESET,
        BOLD,
        DIM,
        ITALIC,
        UNDERLINE,
        BLINK,
        REVERSE,
        HIDDEN,
        STRIKETHROUGH
    } FontMode;

    // font color to use (if available in your terminal)
    typedef enum FontColor
    {
        BLACK,
        RED,
        GREEN,
        YELLOW,
        BLUE,
        MAGENTA,
        CYAN,
        WHITE,
        DEFAULT,
        BRIGHT_BLACK,
        BRIGHT_RED,
        BRIGHT_GREEN,
        BRIGHT_YELLOW,
        BRIGHT_BLUE,
        BRIGHT_MAGENTA,
        BRIGHT_CYAN,
        BRIGHT_WHITE
    } FontColor;

    /**
     * gets the ANSI code for a specified font mode
     *
     * @param mode font mode to use
     * @return char* ANSI code
     */
    extern char *font_mode(FontMode mode);

    /**
     * gets the ANSI code for a specified font color
     *
     * @param color font color to use
     * @return char* ANSI code
     */
    extern char *font_color(FontColor color);

    /**
     * prints a line
     *
     * @param message message to print
     */
    extern void println(char *message);

    /**
     * prints a line
     *
     * @param message message to print
     */
    extern void println_err(char *message);

    /**
     * prints a line
     *
     * @param message message to print
     */
    extern void println_debug(char *message);

    /**
     * prints a message without adding a newline character.
     * call an endline with 'end_line();'
     *
     * @param message message
     */
    extern void print(char *message);

    /**
     * prints a message without adding a newline character.
     * call an endline with 'end_line();'
     *
     * @param message message
     */
    extern void print_err(char *message);

    /**
     * prints a message without adding a newline character.
     * call an endline with 'end_line();'
     *
     * @param message message
     */
    extern void print_debug(char *message);

    extern void end_line();

#ifdef __cplusplus
}
#endif

#endif
