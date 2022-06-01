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

SBPacket _handshake_packet(ClientData client, uint8_t *buffer, uint8_t *return_buffer, size_t packet_max)
{
    int protocol;
    int cursor = varint_read(&protocol, buffer, packet_max);

    char address[255];
    cursor += string_read((String)(buffer + cursor), address, packet_max - cursor);

    short port = ((unsigned short)buffer[cursor] << 8) | (unsigned char)buffer[cursor + 1];
    cursor += 2;

    int next;
    cursor += varint_read(&next, buffer + cursor, packet_max - cursor);
    
    client->state = next;

    return NULL;
}

SBPacket _status_request_packet(ClientData client, uint8_t *buffer, uint8_t *return_buffer, size_t packet_max)
{
    String motd = "{\"version\": {\"name\": \"CMine 1.18.2\",\"protocol\": 758},\"players\": {\"max\": 10,\"online\": 1,\"sample\": [{\"name\": \"lola_0x4dd\",\"id\": \"f89dd8c0-47d4-47e5-aece-6fdc06dd9b6d\"}]},\"description\": {\"text\": \"CMine Test\"}}";
    
    int cursor = varint_write(0x00, (return_buffer + cursor));
    cursor += string_write(motd, (String) (return_buffer + cursor));

    client->return_send = true;
    client->return_size = cursor;

    return NULL;
}

SBPacket _status_ping(ClientData client, uint8_t *buffer, uint8_t *return_buffer, size_t packet_max)
{
    int cursor = varint_write(0x01, return_buffer);

    for (int i = 0; i < 8; i++)
        return_buffer[i + cursor++] = buffer[i];

    client->return_send = true;
    client->return_size = cursor; 
    client->terminate = true;

    return NULL;
}

void _parse_packet(ClientData client, uint8_t *buffer, uint8_t *return_buffer, size_t packet_max)
{
    int length;
    int cursor = varint_read(&length, buffer, packet_max);
    int packet;
    cursor += varint_read(&packet, buffer + cursor, packet_max - cursor);

    switch (client->state)
    {
    case HANDSHAKE:
        _handshake_packet(client, buffer + cursor, return_buffer, packet_max - cursor);
        break;
    case STATUS:
        switch (packet)
        {
        case 0x00:
            _status_request_packet(client, buffer + cursor, return_buffer, packet_max - cursor);
            break;
        case 0x01:
            _status_ping(client, buffer + cursor, return_buffer, packet_max - cursor);
            break;
        break;
        }
    case LOGIN:
        break;
    case PLAY:
        break;
    }
}
