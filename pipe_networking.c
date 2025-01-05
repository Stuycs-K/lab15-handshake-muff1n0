#include "pipe_networking.h"
//UPSTREAM = to the server / from the client
//DOWNSTREAM = to the client / from the server
/*=========================
  server_setup

  creates the WKP and opens it, waiting for a  connection.
  removes the WKP once a connection has been made

  returns the file descriptor for the upstream pipe.
  =========================*/
int server_setup() {
  mkfifo(WKP, 0644);
  int from_client = open(WKP, O_RDONLY);
  remove(WKP);
  return from_client;
}

/*=========================
  server_handshake
  args: int * to_client

  Performs the server side pipe 3 way handshake.
  Sets *to_client to the file descriptor to the downstream pipe (Client's private pipe).

  returns the file descriptor for the upstream pipe (see server setup).
  =========================*/
int server_handshake(int *to_client) {
  int from_client = server_setup();


  char syn[30];
  read(from_client, syn, 30);
  
  *to_client = open(syn, O_WRONLY);

  srand(time(NULL));
  int synack = rand();
  write(*to_client, &synack, 4);

  int ack;
  read(from_client, &ack, 4);
  if (ack != synack + 1) {
    exit(1);
  }
  return from_client;
}


/*=========================
  client_handshake
  args: int * to_server

  Performs the client side pipe 3 way handshake.
  Sets *to_server to the file descriptor for the upstream pipe.

  returns the file descriptor for the downstream pipe.
  =========================*/
int client_handshake(int *to_server) {
  char pp[30];
  sprintf(pp, "%d", getpid());
  mkfifo(pp, 0644);

  *to_server = open(WKP, O_WRONLY);
  write(*to_server, pp, 30);



  int from_server = open(pp, O_RDONLY);
  remove(pp);

  int ack;
  read(from_server, &ack, 4);
  ack++;
  write(*to_server, &ack, 4);



  return from_server;
}


/*=========================
  server_connect
  args: int from_client

  handles the subserver portion of the 3 way handshake

  returns the file descriptor for the downstream pipe.
  =========================*/
int server_connect(int from_client) {
  int to_client  = 0;
  return to_client;
}


int server_handshake_half(int *to_client, int from_client) {
  char syn[30];
  read(from_client, syn, 30);
  
  *to_client = open(syn, O_WRONLY);

  srand(time(NULL));
  int synack = rand();
  write(*to_client, &synack, 4);

  int ack;
  read(from_client, &ack, 4);
  if (ack != synack + 1) {
    exit(1);
  }
  return from_client;
}
