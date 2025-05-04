#pragma once

#include "client.h"

#define VAR_HOME "HOME"

#define VAR_AWS_RAT_PROFILE "AWS_PROFILE"

#define VAR_AWS_RAT_REGION "AWS_DEFAULT_REGION"

ClientList get_client_list();

void free_client_list(struct ClientList client_list);