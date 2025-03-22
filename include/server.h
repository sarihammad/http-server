#ifndef SERVER_H
#define SERVER_H

/**
 * Starts the TCP server on the specified port.
 *
 * Sets up the socket, binds it, listens for incoming connections,
 * and spawns a new thread for each client.
 *
 * @param port The port number the server will listen on.
 */
void start_server(int port);

/**
 * Handles an individual client request.
 *
 * Reads and parses a basic HTTP GET request and serves a static file
 * from the "public" directory. Responds with appropriate HTTP status codes.
 *
 * @param client_socket The file descriptor for the connected client.
 */
void handle_client(int client_socket);

/**
 * Thread entry point to manage client connections in a separate thread.
 *
 * Unwraps the client socket passed as a pointer, processes the request,
 * and performs cleanup (socket close and memory free).
 *
 * @param arg Pointer to the client socket file descriptor (int *).
 * @return NULL (required by pthread signature).
 */
void *thread_worker(void *arg);

#endif // SERVER_H