#include "minitalk.h"

// client.c

void send_bit(int pid, unsigned char c)
{
    for (int i = 7; i >= 0; i--)
    {
        if ((c >> i) & 1)
            kill(pid, SIGUSR2); // Send 1
        else
            kill(pid, SIGUSR1); // Send 0
        usleep(100);            // Prevent signal loss
    }
}

void handle_ack(int signo)
{
    (void)signo;
}

int main(int argc, char *argv[])
{
    if (argc != 3)
    {
        printf("Usage: %s <PID> <Message>\n", argv[0]);
        return 1;
    }

    int server_pid = atoi(argv[1]);
    char *message = argv[2];

    struct sigaction sa;
    sa.sa_flags = 0;
    sa.sa_handler = handle_ack;
    sigemptyset(&sa.sa_mask);
    sigaction(SIGUSR1, &sa, NULL);

    for (int i = 0; message[i] != '\0'; i++)
        send_bit(server_pid, message[i]);

    send_bit(server_pid, '\0'); // Send end-of-message character

    return 0;
}
