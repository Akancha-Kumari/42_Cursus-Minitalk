#include "minitalk.h"

volatile sig_atomic_t acknowledgment_received = 0;

static int check_valid_pid(char *argv[])
{
    int i = 0;
    int pid;
    while (argv[1][i] != '\0')
    {
        if (!(argv[1][i] >= '0' && argv[1][i] <= '9'))
        {
            printf("Error: PID shoild contain only integers.\n");
            return (1);
        }
        i++;
    }
    pid = ft_atoi(argv[1]);
    if (pid <= 0)
    {
        printf("Error: PID should be greater than 0.\n");
        return (1);
    }
    return (pid);
}

static void send_char_to_bit(int pid, char ch)
{
    int i;
    i = 7;
    while (i >= 0)
    {
        if ((ch >> i) & 1)
            kill(pid, SIGUSR1);
        else
            kill(pid, SIGUSR2);
        usleep(100);
        acknowledgment_received = 0;
        i--;
    }
}

static void handle_acknowledge(int signo)
{
    (void)signo;
    acknowledgment_received = 1;
}

int main(int argc, char *argv[])
{
    if (argc == 3)
    {
        int pid = check_valid_pid(argv);
        char *message = argv[2];
        struct sigaction sa;
        sa.sa_flags = 0;
        sa.sa_handler = handle_acknowledge;
        sigemptyset(&sa.sa_mask);
        sigaction(SIGUSR1, &sa, NULL);
        int i = 0;
        while (message[i] != '\0')
        {
            send_char_to_bit(pid, message[i]);
            i++;
        }
        send_char_to_bit(pid, '\0');
    }
    else
    {
        printf("\e[33mTry: ./client <PID> <MESSAGE>\e[0m\n");
        exit(1);
    }
    return (0);
}
