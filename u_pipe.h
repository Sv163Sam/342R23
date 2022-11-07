#ifndef UNTITLED_U_PIPE_H
#define UNTITLED_U_PIPE_H

#include "helper.h"

namespace U_PIPE
{
    void guess_player(const int pipe_fd[], const int pipe_fd_s[], pid_t pid);
    void assump_player(const int pipe_fd[], const int pipe_fd_s[], pid_t pid);
}
#endif
