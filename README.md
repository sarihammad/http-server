# HTTP Server

A lightweight multithreaded HTTP server written in C. Serves static files from a public directory and handles HTTP/1.0 GET requests.

## Features

- Serves static files (HTML, CSS, JS)
- Handles multiple clients via multithreading using pthread
- Implements graceful shutdowns with signals