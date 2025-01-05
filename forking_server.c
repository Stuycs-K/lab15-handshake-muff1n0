#include "pipe_networking.h"

int main() {
    signal(SIGINT, sighandler);
    signal(SIGPIPE, sighandler);

    while (1) {
        int to_client;
        int from_client = server_setup();
        int p = fork();
        if (p > 0) {
            server_handshake_half(&to_client, from_client);
            srand(time(NULL));
            int x = rand() % 101;
            while (write(to_client, &x, 4) != -1) {
                printf("Sending %d to client(s)\n", x);
                sleep(1);
                x = rand() % 101;
            }
        }
        close(to_client);
        close(from_client);
    }
}

static void sighandler(int signo)
{
    if (signo == SIGINT)
    {
        remove(WKP);
        exit(0);
    }
}
