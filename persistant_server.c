#include "pipe_networking.h"

int main() {
  int to_client;
  int from_client;

  from_client = server_handshake( &to_client );

  while (from_client = server_handshake(&to_client)) {
    srand(time(NULL));
    while (1) {
      int x = rand() % 101;
      write(to_client, &x, 4);
      printf("Sending %d to client(s)\n", x);
      sleep(1);
    }

    close(to_client);
    close(from_client);
  }
}
