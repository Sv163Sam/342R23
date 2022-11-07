#ifndef UNTITLED_HELPER_H
#define UNTITLED_HELPER_H

#include <iostream>
#include <cstring>
#include <vector>
#include <algorithm>
#include <random>
#include <unistd.h>
#include <ctime>
#include <fstream>

#include <wait.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <sys/fcntl.h>

#include <csignal>
#include <pthread.h>
#include "mqueue.h"

#include "check.h"

struct game_result
{
    unsigned g_time = 0.0;
    int array_size = 0;
    int att_count = 0;
    int space_indicator = 0; //for files
};

void get_game_space(int indicator);
void increment_game_count(int count);
void set_game_time(unsigned time);
void str_display(const std::string& data);
void mes_display(const std::string& data, const int value);
void stat_display();
void assumption_display(int value);
void answer_display(bool flag);
void set_array_size(int size);
void write_file();
void game_all_write(int value);
void answer_all(bool flag);
#endif //UNTITLED_HELPER_H
