#include <stdio.h>
#include "server.h"

int main(int argc, char *argv[]) {
    int port = 8080;
    if (argc == 2) {
        port = atoi(argv[1]);
    }
    printf("Starting server on port %d...\n", port);
    start_server(port);
    return 0;
}