# HTTP Server

Multithreaded HTTP server.

## Getting Started

### Clone the Repo

```bash
git clone https://github.com/sarihammad/http-server.git
cd http-server
```

### Build with make

```bash
make
```

### Run the Server

1. Run the server:

```bash
./server 8080
```

2. In another terminal, test with curl:

```bash
curl http://localhost:8080/
```

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
