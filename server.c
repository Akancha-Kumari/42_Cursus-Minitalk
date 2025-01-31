#include "minitalk.h"

volatile sig_atomic_t acknowledgment_received = 0;

void signal_handler(int signal, siginfo_t *info, void *context)
{
    static int bit = 0;
    static unsigned char ch = 0;

    (void)context;
    if (signal == SIGUSR1) // Bit 1
        ch = (ch << 1) | 1;
    else if (signal == SIGUSR2) // Bit 0
        ch <<= 1;

    bit++;
    if (bit == 8)
    {
        if (ch == '\0')
            write(1, "\n", 1);
        else
            write(1, &ch, 1);
        bit = 0;
        ch = 0;
        acknowledgment_received = 1;
        if (info->si_pid > 0)
            kill(info->si_pid, SIGUSR1);
    }
}

int main()
{
    struct sigaction sa;

    int pid = getpid();
    printf("\e[94mPID\e[0m \e[96m->\e[0m %d\n", pid);
    printf("\e[90mWaiting for a message...\e[0m\n");
    sa.sa_sigaction = signal_handler;
    sa.sa_flags = SA_SIGINFO;
    sigemptyset(&sa.sa_mask);
    if (sigaction(SIGUSR1, &sa, NULL) == -1 || sigaction(SIGUSR2, &sa, NULL) == -1)
    {
        write(1, "sigaction failed\n", 17);
        return (1);
    }
    while (1)
        pause();
    return (0);
}
