#include <stdio.h>
#include <unistd.h>
#include <signal.h>
#include <string.h>

static int exit_flag = 0;

static void handler (int signum)
{
    if (signum == SIGTERM) {
        printf("TERM signal received, exiting program\n");
        exit_flag = 1;
    } else {
        printf("Not a TERM signal: %d (%s)\n", signum, strsignal(signum));
    }
}

int main (int argc, char *argv[])
{
    struct sigaction act;

    memset (&act, '\0', sizeof(act));
    act.sa_handler = &handler;
    if (sigaction(SIGTERM, &act, NULL) < 0) {
        perror ("sigaction");
        return 1;
    }
    if (sigaction(SIGINT, &act, NULL) < 0) {
        perror ("sigaction");
        return 1;
    }

    while (!exit_flag) usleep(100000);

    return 0;
}