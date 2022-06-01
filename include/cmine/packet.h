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
include/cmine/packet.h

*/

#ifndef CM_PACKET_H
#define CM_PACKET_H

#include <stdint.h>
#include <stdlib.h>
#include <stdbool.h>

#include <cmine/string.h>
#include <cmine/socket.h>

#ifdef __cplusplus
extern "C"
{
#endif

    typedef enum PacketState
    {
        HANDSHAKE,
        STATUS,
        LOGIN,
        PLAY
    } PacketState;

    typedef struct ClientData
    {
        PacketState state;
        int protocol, cid;
        size_t return_size;
        bool return_send, terminate;
    } * ClientData;

    typedef void (*SBPacket)(ClientData *client, uint8_t *buffer, uint8_t *return_buffer, size_t packet_max);

#ifdef __cplusplus
}
#endif

#endif