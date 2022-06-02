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
src/packet.c

*/

#include <stdint.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>

#include <stdio.h>

#include <cmine/packet.h>
#include <cmine/socket.h>
#include <cmine/out.h>
#include <cmine/packetdata.h>

#include "internal.h"

// HANDSHAKE

void _handshake_packet(ClientData client, uint8_t *buffer)
{
    int protocol;
    int cursor = varint_read(&protocol, buffer);

    char address[256];
    cursor += string_read((String)(buffer + cursor), address);

    short port = ((unsigned short)buffer[cursor] << 8) | (unsigned char)buffer[cursor + 1];
    cursor += 2;

    int next;
    cursor += varint_read(&next, buffer + cursor);

    client->state = next;
}

// STATUS

void _status_response_packet(ClientData client) // cb 0x00
{
    uint8_t buffer[PACKET_MAX];
    int cursor = varint_write(0x00, buffer);

    String motd = "{\"version\": {\"name\": \"CMine 1.18.2\",\"protocol\": 758},\"players\":{\"max\": 10,\"online\": 1,\"sample\": [{\"name\": \"lola_0x4dd\",\"id\": \"f89dd8c0-47d4-47e5-aece-6fdc06dd9b6d\"}]},\"description\": {\"text\": \"CMine Test\"}}";
    cursor += string_write(motd, (String)(buffer + cursor));

    _send_raw_packet(client, buffer, cursor);
}

void _status_request_packet(ClientData client, uint8_t *buffer) // sb 0x00
{
    _status_response_packet(client);
}

void _status_pong(ClientData client) // cb 0x01
{
    uint8_t buffer[PACKET_MAX];
    int cursor = varint_write(0x01, buffer);
    cursor += 8;

    _send_raw_packet(client, buffer, cursor);
}

void _status_ping(ClientData client, uint8_t *buffer) // sb 0x01
{
    _status_pong(client);
    client->terminate = true;
}

// LOGIN

void _login_start(ClientData client, uint8_t *buffer)
{
    char username[17];
    string_read((String)buffer, username);

    print("Login request from: ");
    printf("%s", username);
    end_line();

    client->terminate = true; // temp
}

// Packet routing

void _parse_packet(ClientData client, uint8_t *buffer)
{
    int length, packet;
    int cursor = varint_read(&length, buffer);
    cursor += varint_read(&packet, buffer + cursor);

    uint8_t *data = buffer + cursor;

    switch (client->state)
    {
    case HANDSHAKE:
        _handshake_packet(client, data);
        break;
    case STATUS:
        switch (packet)
        {
        case 0x00:
            _status_request_packet(client, data);
            break;
        case 0x01:
            _status_ping(client, data);
            break;
        }
        break;
    case LOGIN:
        switch (packet)
        {
        case 0x00:
            _login_start(client, data);
            break;
        }
        break;
    case PLAY:
        break;
    }
}
