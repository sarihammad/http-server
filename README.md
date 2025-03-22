# HTTP Server

A lightweight multithreaded HTTP server written in C. Serves static files from a public directory and handles HTTP/1.0 GET requests.

## Features

- Serves static files (HTML, CSS, JS)
- Handles multiple clients via multithreading using pthread
- Implements graceful shutdowns with signals

## Getting Started

### Clone the Repository

```bash
git clone https://github.com/sarihammad/http-server.git
cd http-server
```

### Build with make

```bash
make
```

This compiles the server and produces a server binary in the project root.

### Test the Server

1. Run the server:

```bash
./server 8080
```

2. In another terminal, test with curl:
```bash
curl http://localhost:8080/
```

Expected Output:

```html
<!-- public/index.html -->
<!DOCTYPE html>
<html lang="en">
<head>
  <meta charset="UTF-8" />
  <title>C HTTP Server</title>
</head>
<body>
  <h1>Hello from your C HTTP Server.</h1>
</body>
</html>
```