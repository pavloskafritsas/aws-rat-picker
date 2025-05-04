#pragma once

#include "client.h"

const char *get_aws_rat_path();

void start_aws_rat(const char *aws_rat_path, Client client);