# HTTPserver
used Beej's guide to network programming nice book btw :)
# Simple HTTP Server in C

A basic HTTP server written in C using Linux socket programming.  
The server listens on port `8080`, accepts client connections, processes HTTP requests, and serves simple HTML pages.

## Features
- TCP socket server using POSIX sockets
- Binds to port `8080`
- Handles HTTP GET requests
- Supports multiple routes:
  - `/` → Home page
  - `/about` → About page
  - Any other route → 404 page
- Sends proper HTTP response headers

## Technologies Used
- C Programming
- Linux Socket API
- TCP/IP Networking

## Compilation

```bash
gcc server.c -o server
```

## Running the Server

```bash
./server
```

## Open in Browser

```text
http://localhost:8080
```

## Available Routes

| Route | Description |
|------|-------------|
| `/` | Home Page |
| `/about` | About Page |
| Any other route | 404 Error Page |

## Example Pages

### Home Page
```html
<h1>Welcome Home!</h1>
<p>Arpit's Server is running.</p>
```

### About Page
```html
<h1>About Page</h1>
<p>First-year engineering project.</p>
```

## Future Improvements
- Multi-threaded client handling
- Serve external HTML files
- Add POST request support
- Better logging and error handling
- Persistent connections
