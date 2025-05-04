#pragma once

typedef struct Client
{
    char *name;
    char *region;
} Client;

typedef struct ClientList
{
    struct Client *clients;
    int count;
} ClientList;
