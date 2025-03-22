#include "server.h"
#include <stdio.h>           // Standard I/O functions (printf, fopen, fread, ...)
#include <stdlib.h>          // Memory allocation (malloc, free), exit(), ...
#include <string.h>          // String operations (strcmp, strcat, etc.)
#include <unistd.h>          // UNIX system calls (read, write, close, ...)
#include <arpa/inet.h>       // Network functions (sockaddr_in, htons, inet_addr, ...)
#include <pthread.h>         // POSIX threads for multithreading

#define BUFFER_SIZE 4096     // Constant buffer size for reads & writes


/**
 * Thread worker function to handle a client connection.
 *
 * This function is passed to pthread_create. It extracts the client socket
 * from the argument, calls handle_client(), closes the socket, and frees memory.
 *
 * @param arg A pointer to an integer (the client socket file descriptor)
 * @return NULL (required by pthread signature)
 */
void *thread_worker(void *arg) {
    int client_socket = *(int *)arg;         // Dereference the socket pointer
    handle_client(client_socket);            // Handle HTTP request/response logic
    close(client_socket);                    // Close the client socket after handling the request
    free(arg);                               // Free dynamically allocated memory for socket pointer
    return NULL;                             // Required for pthread function return
}

/**
 * Starts the TCP server on the given port.
 *
 * This function sets up the socket, binds it to the port, listens for
 * incoming connections, and spawns a new thread for each accepted client.
 *
 * @param port The port number on which the server will listen for connections.
 */
void start_server(int port) {
    int server_fd, client_fd;                        // File descriptors for server and client sockets
    struct sockaddr_in server_addr, client_addr;     // Address structs for server and client
    socklen_t client_len = sizeof(client_addr);      // Length of client address struct (required by `accept`)

    server_fd = socket(AF_INET, SOCK_STREAM, 0);     // Create TCP socket (IPv4)
    if (server_fd < 0) {
        perror("Socket failed");                     // Print error if socket creation fails
        exit(1);                                     // Exit the program with failure status
    }

    server_addr.sin_family = AF_INET;                // Use IPv4
    server_addr.sin_port = htons(port);              // Convert port number to network byte order
    server_addr.sin_addr.s_addr = INADDR_ANY;        // Bind to all available local interfaces (0.0.0.0)

    // Bind the server socket to the specified IP address and port.
    if (bind(server_fd, (struct sockaddr *)&server_addr, sizeof(server_addr)) < 0) {
        perror("Bind failed");                       // Port may already be in use or inaccessible
        exit(1);                                     // Exit on binding error
    }

    // Begin listening for incoming connections with a backlog queue of 10
    if (listen(server_fd, 10) < 0) {
        perror("Listen failed");
        exit(1);
    }

    printf("Server listening on port %d...\n", port);   // Server ready message

    while (1) {
        client_fd = accept(server_fd, (struct sockaddr *)&client_addr, &client_len);
        if (client_fd < 0) {
            perror("Accept failed");                   // Continue accepting other clients on failure
            continue;
        }

        pthread_t tid;                                 // Thread ID
        int *client_sock = malloc(sizeof(int));        // Allocate memory to pass socket to thread
        *client_sock = client_fd;                      // Store the client socket in the allocated memory

        pthread_create(&tid, NULL, thread_worker, client_sock);  // Create new thread to handle client
        pthread_detach(tid);                           // Automatically free thread resources on exit
    }

    close(server_fd);                                  // Unreachable here, but included for completeness
}

/**
 * Handles a single client's HTTP request.
 *
 * Parses the request from the client socket, checks the HTTP method,
 * and serves a static file from the "public" directory. Supports only GET requests.
 *
 * @param client_socket The file descriptor of the connected client.
 */
void handle_client(int client_socket) {
    char buffer[BUFFER_SIZE];                          // Buffer to read client request
    read(client_socket, buffer, sizeof(buffer) - 1);   // Read request into buffer

    char method[8], path[1024];                        // Buffers for parsed HTTP method and path
    sscanf(buffer, "%s %s", method, path);             // Parse request line, e.g., "GET /index.html"

    // Reject non-GET requests with 405 response
    if (strcmp(method, "GET") != 0) {
        write(client_socket, "HTTP/1.1 405 Method Not Allowed\r\n\r\n", 36);
        return;
    }

    char full_path[2048] = "public";                   // Base directory for serving files

    // Serve "index.html" by default if "/" is requested
    if (strcmp(path, "/") == 0) {
        strcat(full_path, "/index.html");
    } else {
        strcat(full_path, path);                       // Append requested path to base
    }

    FILE *fp = fopen(full_path, "r");                  // Attempt to open requested file
    if (!fp) {
        write(client_socket, "HTTP/1.1 404 Not Found\r\n\r\n", 26);  // Respond with 404 if not found
        return;
    }

    write(client_socket, "HTTP/1.1 200 OK\r\n\r\n", 19);            // Respond with 200 OK header

    char file_buffer[BUFFER_SIZE];                     // Buffer for reading file contents
    size_t bytes;

    // Read file in chunks and send to client
    while ((bytes = fread(file_buffer, 1, sizeof(file_buffer), fp)) > 0) {
        write(client_socket, file_buffer, bytes);
    }

    fclose(fp);                                        // Close file after sending
}