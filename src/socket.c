#include <stdlib.h>
#include <netinet/in.h>
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

#include <arpa/inet.h>

#include <cmine/cmine.h>
#include <cmine/memory.h>
#include <cmine/out.h>
#include <cmine/thread.h>

#include "internal.h"

int _sid;

Thread _client_init(void *arg)
{
    int cid = *((int *)arg);

    // TODO!!!

    return NULL;
}

Thread _socket_init(void *arg)
{
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

        setsockopt(_sid, SOL_SOCKET, SO_REUSEADDR, ((const void*) true), sizeof(int));


    if (bind(_sid, (_ipv6 ? ((struct sockaddr*)&address_ipv6) : ((struct sockaddr*)&address)), sizeof(struct sockaddr)) != 0)
    {
        println_err("Failed to bind to address.");
        _active = false;
        return NULL;
    } else {
        println_debug("Address bound successfully.");
    }

    listen(_sid, 10);

    int cid = 0;

    while (true) {
        struct sockaddr client_address;
        socklen_t size = sizeof(client_address);
        cid = accept(_sid, &client_address, &size);

        async_once((Thread) &_client_init, &cid, 0);
    }

    return NULL;
}