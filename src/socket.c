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
src/socket.c

*/

#include <stdlib.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <unistd.h>
#include <string.h>

#include <stdio.h>

#include <cmine/arraylist.h>
#include <cmine/socket.h>
#include <cmine/cmine.h>
#include <cmine/memory.h>
#include <cmine/out.h>
#include <cmine/thread.h>
#include <cmine/packetdata.h>

#include "internal.h"

#define PACKET_MAX 4096

volatile ArrayList connected;
int _sid;

void _out_packet_size(ClientData client, uint8_t *buffer)
{
    int size = client->return_size;
    int shift = varint_size(size);

    memmove((buffer + shift), buffer, size);
    varint_write(size, buffer);

    client->return_size = size + shift;
}

Thread _client_init(void *arg)
{
    int cid = *((int *)arg);
    ClientData client = calloc(1, sizeof(struct ClientData));
    arraylist_add(connected, socket);
    
    client->cid = cid;
    client->terminate = false;

    uint8_t buffer[PACKET_MAX];
    uint8_t return_buffer[PACKET_MAX];
    bool return_send;
    int nbytes, return_size;

    while (true)
    {
        nbytes = read(cid, buffer, PACKET_MAX);

        if (nbytes < 1)
            break;

        printf("IN: ");
                for (int i = 0; i < nbytes; i++)
                printf("%x ", buffer[i]);
                printf("\n");

        _parse_packet(client, buffer, return_buffer, PACKET_MAX);

        if (client->return_send)
        {
            client->return_send = false;
            _out_packet_size(client, return_buffer);
            
            printf("OUT: ");
                for (int i = 0; i < client->return_size; i++)
                printf("%x ", return_buffer[i]);
                printf("\n");

            if (send(cid, return_buffer, client->return_size, 0) == -1)
                break;
        }
        if (client->terminate)
            break;
    }

    arraylist_remove_first(connected, client);
    free(client);
    return NULL;
}

Thread _socket_init(void *arg)
{
    connected = arraylist_create();
    struct sockaddr_in address;
    struct sockaddr_in6 address_ipv6;

    if (_ipv6)
    {
        inet_pton(AF_INET6, _address, &(address_ipv6.sin6_addr));
        address_ipv6.sin6_port = htons(_port);
        address_ipv6.sin6_family = AF_INET6;

        _sid = socket(PF_INET6, SOCK_STREAM, IPPROTO_TCP);
    }
    else
    {
        inet_pton(AF_INET, _address, &(address.sin_addr));
        address.sin_port = htons(_port);
        address_ipv6.sin6_family = AF_INET;

        _sid = socket(PF_INET, SOCK_STREAM, IPPROTO_TCP);
    }

    setsockopt(_sid, SOL_SOCKET, SO_REUSEADDR, ((const void *)true), sizeof(int));

    if (bind(_sid, (_ipv6 ? ((struct sockaddr *)&address_ipv6) : ((struct sockaddr *)&address)), sizeof(struct sockaddr)) != 0)
    {
        println_err("Failed to bind to address.");
        _active = false;
        return NULL;
    }
    else
    {
        println_debug("Address bound successfully.");
    }

    listen(_sid, 10);

    int cid = 0;

    while (true)
    {
        struct sockaddr client_address;
        socklen_t size = sizeof(client_address);
        cid = accept(_sid, &client_address, &size);

        async_once((Thread)&_client_init, &cid, 0);
    }

    return NULL;
}
