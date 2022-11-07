#ifndef UNTITLED_MES_QUEUE
#define UNTITLED_MES_QUEUE

#include "mes_queue.h"
namespace M_QUEUE {
    void guess_player(mqd_t mqd, mqd_t mqd1, pid_t pid) {
        int end_range = 1 + (int) random() % 20;
        int value = 1 + (int) random() % end_range;
        int one = 1;
        int zero = 0;
        bool flag = false;

        str_display("A number is guessed");
        mes_display("Our range is: ", end_range);
        mes_display("Value is: ", value);
        check(mq_send(mqd, (char *) &end_range, sizeof(end_range), 0));

        do {
            int *assumption = new int[8 * 1024 / sizeof(int)];
            if (check(mq_receive(mqd1, (char *) assumption, 8 * 1024, nullptr))) {
                if (*assumption == value) {
                    check(mq_send(mqd, (char *) &one, sizeof(one), 0));
                    answer_display(true);
                    flag = true;
                }
                else
                {
                    check(mq_send(mqd, (char *) &zero, sizeof(zero), 0));
                    answer_display(false);
                }
            } else
                _exit(EXIT_FAILURE);
        } while (!flag);
        return;
    }

    void assump_player(mqd_t mqd, mqd_t mqd1, pid_t pid) {
        int *range = new int[8 * 1024 / sizeof(int)];
        int value = 0;
        int *flag = new int[8 * 1024 / sizeof(int)];
        std::vector<int> attempt = {};

        if (check(mq_receive(mqd, (char *) range, 8 * 1024, nullptr))) {
            for (int i = 1; i < range[0]; i++) {
                attempt.push_back(i);
            }
            std::random_device rd;
            std::mt19937 g(rd());
            std::shuffle(attempt.begin(), attempt.end(), g);
            int st;
            do {
                if(waitpid(pid,&st, WNOHANG)>0){
                    std::cout << "slomalos" << std::endl;
                    exit(0);
                }
                usleep(100);
                value = attempt[0];
                assumption_display(value);
                check(mq_send(mqd1, (char *) &value, 1, 0));
                if (check(mq_receive(mqd, (char *) flag, 8 * 1024, nullptr))) {
                    if (flag[0] == 0) {
                        attempt.erase(attempt.begin());
                        //increment_game_count();
                    }
                } else {
                    _exit(EXIT_FAILURE);
                }
            } while (flag[0] == 0);
            return;
        }
        _exit(EXIT_FAILURE);
    }
}
#endif