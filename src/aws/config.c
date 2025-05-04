#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <iniparser/iniparser.h>

#include "aws/config.h"

#include "messages.h"

#define PATH_DEF_DICTIONARY "/.aws/credentials"

#define DICTIONARY_KEY_REGION ":region"

void free_client_list(struct ClientList client_list)
{
    for (int i = 0; i < client_list.count; i++)
    {
        free(client_list.clients[i].name);
        free(client_list.clients[i].region);
    }

    free(client_list.clients);
}

void free_dictionary(dictionary *dictionary)
{
    iniparser_freedict(dictionary);
    dictionary = NULL;
}

const char *get_env_home()
{
    const char *env_home = getenv(VAR_HOME);

    if (!env_home)
    {
        fprintf(stderr, "%s\n", ERROR_HOME);

        exit(EXIT_FAILURE);
    }

    return env_home;
}

const char *get_dictionary_path()
{
    const char *home = get_env_home();

    char *path;

    size_t home_len = strlen(home);

    size_t path_aws_creds_len = strlen(PATH_DEF_DICTIONARY);

    size_t path_len = (home_len + path_aws_creds_len) * sizeof(char) + 1;

    path = (char *)malloc(path_len);

    strlcpy(path, home, path_len);

    strlcat(path, PATH_DEF_DICTIONARY, path_len);

    const char *dictionary_path = strdup(path);

    free(path);
    path = NULL;

    return dictionary_path;
}

dictionary *load_dictionary()
{
    const char *path = get_dictionary_path();

    dictionary *dictionary = iniparser_load(path);

    if (!dictionary)
    {
        fprintf(stderr, "Failed to load credentials file.\n");
        exit(EXIT_FAILURE);
    }

    return dictionary;
}

const char *get_client_region_from_dictionary(dictionary *dictionary, const char *client_name)
{
    char *key;

    size_t client_name_len = strlen(client_name);

    size_t key_suffix_len = strlen(DICTIONARY_KEY_REGION);

    size_t key_len = (client_name_len + key_suffix_len) * sizeof(char) + 1;

    key = (char *)malloc(key_len);

    key[0] = '\0';

    strlcat(key, client_name, key_len);

    strlcat(key, DICTIONARY_KEY_REGION, key_len);

    const char *region = iniparser_getstring(dictionary, key, "undefined");

    free(key);
    key = NULL;

    return region;
}

struct ClientList get_client_list()
{
    struct ClientList client_list = {0};

    dictionary *dictionary = load_dictionary();

    int clients_len = iniparser_getnsec(dictionary);

    struct Client *clients = (struct Client *)malloc(clients_len * sizeof(struct Client));

    if (!clients)
    {
        fprintf(stderr, "Memory allocation failed for clients.\n");

        free_dictionary(dictionary);

        exit(EXIT_FAILURE);
    }

    for (int i = 0; i < clients_len; i++)
    {
        const char *name = iniparser_getsecname(dictionary, i);
        const char *region = get_client_region_from_dictionary(dictionary, name);

        clients[i].name = strdup(name);
        clients[i].region = strdup(region);

        if (!clients[i].name || !clients[i].region)
        {
            fprintf(stderr, "Memory allocation failed for client data.\n");
            // Free already allocated items before returning
            for (int j = 0; j < i; j++)
            {
                free(clients[j].name);
                free(clients[j].region);
            }
            free(clients);

            exit(EXIT_FAILURE);
        }
    }

    free_dictionary(dictionary);

    client_list.clients = clients;
    client_list.count = clients_len;

    return client_list;
}

const char *get_aws_rat_path()
{
    char *path;

    const char *env_home = get_env_home();

    if (asprintf(
            &path,
            "%s/Projects/Prosperty/aws_rat/aws_resource_access_tool.sh",
            env_home) == -1)
    {
        fprintf(stderr, "%s\n", ERROR_SCRIPT_PATH);

        exit(EXIT_FAILURE);
    }

    const char *aws_rat_path = strdup(path);

    free(path);
    path = NULL;

    if (access(aws_rat_path, F_OK) != 0)
    {
        printf("AWS RAT does not exist in: %s\n", aws_rat_path);

        exit(EXIT_FAILURE);
    }

    return aws_rat_path;
}