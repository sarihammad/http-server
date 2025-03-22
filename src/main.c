#include <stdio.h>      // For printf, fprintf
#include <stdlib.h>     // For atoi, exit
#include "server.h"     // Declaration of start_server()

/**
 * Entry point of the HTTP server application.
 *
 * Accepts an optional command-line argument to specify the port number.
 * Defaults to port 8080 if no argument is provided.
 *
 * Example usage:
 *     ./server             // Starts server on port 8080
 *     ./server 3000        // Starts server on port 3000
 *
 * @param argc Argument count
 * @param argv Argument vector (argv[1] may contain the port number)
 * @return 0 on success, non-zero on error
 */
int main(int argc, char *argv[]) {
    int port = 8080;  // Default port

    if (argc == 2) {
        port = atoi(argv[1]);  // Convert command-line arg to integer

        // Basic validation: valid port range is 1–65535
        if (port < 1 || port > 65535) {
            fprintf(stderr, "Error: Invalid port number '%s'. Port must be between 1 and 65535.\n", argv[1]);
            return 1;
        }
    } else if (argc > 2) {
        fprintf(stderr, "Usage: %s [port]\n", argv[0]);  // Too many arguments
        return 1;
    }

    printf("Starting server on port %d...\n", port);
    start_server(port);  // Start the server

    return 0;  // Success
}