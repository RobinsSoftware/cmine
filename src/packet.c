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

#include <json.h>

#include <cmine/packet.h>
#include <cmine/socket.h>
#include <cmine/out.h>
#include <cmine/cmine.h>
#include <cmine/packetdata.h>

#include "internal.h"

// HANDSHAKE

void _handshake_packet(ClientData client, uint8_t *buffer)
{
    int protocol;
    int cursor = varint_read(&protocol, buffer);

    char address[256];
    cursor += string_read(buffer + cursor, address);

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

    struct json_object *status = json_object_new_object();

    // update players
    struct json_object *players = json_object_new_object();

    json_object_object_add(players, "max", json_object_new_int(24));
    json_object_object_add(players, "online", json_object_new_int(0));
    json_object_object_add(status, "players", players);

    // description
    struct json_object *description = json_object_new_object();
    json_object_object_add(description, "text", json_object_new_string("CMine Test"));
    json_object_object_add(status, "description", description);

    // version
    struct json_object *version = json_object_new_object();
    json_object_object_add(version, "name", json_object_new_string("CMine 1.18.2"));
    json_object_object_add(version, "protocol", json_object_new_int(758));
    json_object_object_add(status, "version", version);

    // favicon
    struct json_object *favicon;
    if (_use_icon)
    {
        // enough room for an icon 
        char icon_buffer[24 + _icon_size];
        sprintf(icon_buffer, "%s%s", "data:image/png;base64,", _icon);
        favicon = json_object_new_string(icon_buffer);
        json_object_object_add(status, "favicon", favicon);
    }

    cursor += string_write((String)json_object_to_json_string_ext(status, JSON_C_TO_STRING_PLAIN), buffer + cursor);

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

void _login_disconnect(ClientData client, String message)
{
    uint8_t buffer[PACKET_MAX];
    int cursor = varint_write(0x00, buffer);

    struct json_object *json;

    json = json_object_new_object();
    json_object_object_add(json, "text", json_object_new_string(message));

    cursor += string_write((String)json_object_to_json_string_ext(json, JSON_C_TO_STRING_PLAIN), buffer + cursor);

    if (_debug)
    {
        print_debug("Disconnecting: ");
        printf("%s", client->username);
        end_line();
    }

    _send_raw_packet(client, buffer, cursor);
}

void _login_start(ClientData client, uint8_t *buffer) // cb 0x00
{
    string_read(buffer, client->username);

    if (_debug)
    {
        print_debug("Connecting: ");
        printf("%s", client->username);
        end_line();
    }

    _login_disconnect(client, "Failed to connect.");

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
