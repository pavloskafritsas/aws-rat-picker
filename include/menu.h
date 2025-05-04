#pragma once

#include "aws/client.h"

void print_menu(struct ClientList client_list);

void print_selected_client_info(Client client);

int get_index(int min, int max);

struct Client select_client(struct ClientList client_list);
