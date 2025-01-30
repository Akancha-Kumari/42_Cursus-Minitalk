// server.c
#include "minitalk.h"

void signal_handler(int signo, siginfo_t *info, void *context)
{
    static int bit_index = 0;
    static unsigned char character = 0;

    (void)context;
    if (signo == SIGUSR1) // Bit 0
        character <<= 1;
    else if (signo == SIGUSR2) // Bit 1
        character = (character << 1) | 1;

    bit_index++;

    if (bit_index == 8)
    {
        if (character == '\0') // End of message
            write(1, "\n", 1);
        else
            write(1, &character, 1);

        bit_index = 0;
        character = 0;
    }

    // Send acknowledgment to client
    kill(info->si_pid, SIGUSR1);
}

int main()
{
    struct sigaction sa;

    sa.sa_flags = SA_SIGINFO;
    sa.sa_sigaction = signal_handler;
    sigemptyset(&sa.sa_mask);

    printf("Server PID: %d\n", getpid());

    if (sigaction(SIGUSR1, &sa, NULL) == -1 || sigaction(SIGUSR2, &sa, NULL) == -1)
    {
        perror("sigaction failed");
        return 1;
    }

    while (1)
        pause(); // Wait for signals

    return 0;
}
