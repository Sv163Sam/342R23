#include "u_pipe.h"
#include "signals.h"
#include "mes_queue.h"

int main()
{
    int game_mode_var = 0;
    str_display("Please, select a game execution: ");
    str_display("1 - By processes with synchronization type - unnamed pipe");
    str_display("2 - By processes with synchronization type - message queue");
    str_display("3 - By signals with synchronization type - real time signals");

    std::cin >> game_mode_var;
    switch(game_mode_var)
    {
        case 1:
        {
            remove(".//u_pipe_game_stat.txt");
            remove(".//u_pipe_all_game.txt");
            int count = 0;
            bool game_flag = true;

            int fd[2];
            int fd_s[2];
            check(pipe(fd));
            check(pipe(fd_s));
            pid_t p_id = check(fork());

            do {
                if(count % 2 != 0) game_flag = false;
                if (p_id) {
                    if(game_flag) U_PIPE::guess_player(fd, fd_s, p_id);
                    else
                    {
                        sleep(1);
                        U_PIPE::assump_player(fd, fd_s, p_id);
                    }
                }
                else
                {
                    if(game_flag) U_PIPE::assump_player(fd, fd_s, p_id);
                    else
                    {
                        sleep(1);
                        U_PIPE::guess_player(fd, fd_s, p_id);
                    }
                }
                count++;
                if (!game_flag) game_flag = true;
                get_game_space(game_mode_var);
            }while(count < 11);
            exit(EXIT_SUCCESS);
            break;
        }
        case 2:
        {
            remove(".//m_queue_game_stat.txt");
            remove(".//m_queue_all_game.txt");
            int count = 0;
            bool game_flag = true;

            auto d = check(mq_open("/mymq", O_CREAT, S_IRUSR | S_IWUSR, NULL));
            auto d1 = check(mq_open("/mymq1", O_CREAT, S_IRUSR | S_IWUSR, NULL));
            check(mq_close(d));

            pid_t p = check(fork());

            do {
                if(count % 2 != 0) game_flag = false;
                if (p) {
                    mqd_t mqd = check(mq_open("/mymq", O_RDWR, S_IRWXU));
                    mqd_t mqd1 = check(mq_open("/mymq1",O_RDWR, S_IRWXU));
                    if(game_flag) M_QUEUE::guess_player(mqd, mqd1, p);
                    else
                    {
                        sleep(1);
                        M_QUEUE::assump_player(mqd, mqd1, p);
                    }
                }
                else
                {
                    mqd_t mqd = check(mq_open("/mymq", O_RDWR, S_IRWXU));
                    mqd_t mqd1 = check(mq_open("/mymq1",O_RDWR, S_IRWXU));
                    if(game_flag) M_QUEUE::assump_player(mqd, mqd1, p);
                    else
                    {
                        sleep(1);
                        M_QUEUE::guess_player(mqd, mqd1, p);
                    }
                }
                count++;
                if (!game_flag) game_flag = true;
                get_game_space(game_mode_var);
            }while(count < 11);
            exit(EXIT_SUCCESS);
        }
        case 3:
        {
            /*
            remove(".//signals_game_stat.txt");
            remove(".//signals_all_game.txt");
            pid_t p_id = check(fork());

            for (int i = 0; i < 10; i++)
            {
                unsigned int start_time = clock();
                if (p_id) {
                    if (i % 2 == 0)
                    {
                        SIGNALS::guess_player(p_id);
                    }
                    else
                    {
                        usleep(100000);
                        SIGNALS::assump_player(getppid());
                    }
                }
                else
                {
                    if (i % 2 == 0)
                    {
                        SIGNALS::assump_player(getppid());
                    }
                    else
                    {
                        usleep(100000);
                        SIGNALS::guess_player(p_id);
                    }
                }
                get_game_space(game_mode_var);
                unsigned int end_time = clock();
                set_game_time(end_time - start_time);
            }
            std::cout << "GAME END";
            exit(EXIT_SUCCESS);
            break;
             */
            //signal_value = 0;
            pid_t main_id = getpid();
            srand(time(0));

            pid_t child_id = check(fork());
            bool isParent;
            pid_t IDParent;
            pid_t IDChild;
            std::string player_name;

            if (child_id > 0)
            {
                isParent = true;
                IDParent = main_id;
                IDChild = child_id;
                player_name = "Player 1";
            }
            else
            {
                isParent = false;
                IDParent = main_id;
                IDChild = getpid();
                player_name = "Player 2";
            }
            for (int i = 1; i < 4; i++) {
                if (i % 2 != 0) {
                    if (child_id == 0) {
                        SIGNALS::assump_player(IDParent, isParent);
                    } else {
                        printf("--— Game %d —--\n", i);
                        SIGNALS::guess_player(IDChild);
                    }
                } else {
                    if (child_id > 0) {
                        SIGNALS::assump_player(IDChild, isParent);
                    } else {
                        printf("--— Game %d —--\n", i);
                        SIGNALS::guess_player(IDParent);
                    }
                }
            }
            if (child_id == 0)
            {
                printf("I'm child. I'm exiting now!\n");
                exit(EXIT_SUCCESS);
            }
            else
            {
                atexit(SIGNALS::on_ended);
                exit(EXIT_FAILURE);
            }
        }
        default:
        {
            exit(EXIT_FAILURE);
        }
    }

}


/*
int main()
{

}
// time, attempts
*/
