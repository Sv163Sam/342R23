#ifndef UNTITLED_HELPER
#define UNTITLED_HELPER

#include "helper.h"
game_result object;
void write_file()
{
    std::ofstream outfile;
    if(object.space_indicator == 1) outfile.open(".//u_pipe_game_stat.txt", std::ios::app);
    else
        if (object.space_indicator == 2) outfile.open(".//m_queue_game_stat.txt", std::ios::app);
        else if (object.space_indicator == 3) outfile.open(".//signals_game_stat.txt", std::ios::app);

    if(outfile.is_open())
    {
        outfile << "In this game the array had a size of: " << object.array_size << "\nGame ended after attempt number: " << object.att_count<< "\nGame time was: " << object.g_time << "\n" << std::endl;
    }
    outfile.close();
}

void game_all_write(int value)
{
    std::ofstream outfile;
    if(object.space_indicator == 1) outfile.open(".//u_pipe_all_game.txt", std::ios::app);
    else
        if (object.space_indicator == 2) outfile.open(".//m_queue_all_game.txt", std::ios::app);
        else if (object.space_indicator == 3) outfile.open(".//signals_all_game.txt", std::ios::app);

    if(outfile.is_open())
    {
        outfile << "My assumption is: " << value << std::endl;
    }
    outfile.close();
}

void answer_all(bool flag)
{
    std::ofstream outfile;
    if(object.space_indicator == 1) outfile.open(".//u_pipe_all_game.txt", std::ios::app);
    else
        if (object.space_indicator == 2) outfile.open(".//m_queue_all_game.txt", std::ios::app);
        else if (object.space_indicator == 3) outfile.open(".//signals_all_game.txt", std::ios::app);

    if(outfile.is_open())
    {
        if(!flag) outfile << "Your answer is false" << "\n" << std::endl;
        else outfile << "Your answer is true" << "\n" << "---------------" << "\n" << std::endl;
    }
    outfile.close();
}

void get_game_space(int indicator)
{
    object.space_indicator = indicator;
}

void increment_game_count(int count)
{
    object.att_count = count;
}

void set_game_time(unsigned time)
{
    object.g_time = time;
    write_file();
}

void set_array_size(int size)
{
    object.array_size = size;
}

void str_display(const std::string& data)
{
    std::cout << data << std::endl;
}

void mes_display(const std::string& data, const int value)
{
    std::cout << data << value << std::endl;
}

void assumption_display(int value)
{
    std::cout << "My assumption is: " << value << std::endl;
}

void answer_display(bool flag)
{
    if (flag)
        std::cout << "Your answer is right! Congratulations. Your game just ended. Change places." << std::endl;
    else
        std::cout << "You're not right." << std::endl;
}

#endif