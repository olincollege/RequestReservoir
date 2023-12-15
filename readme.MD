# Request Reservoir


This is a simple HTTP server implemented in C, capable of handling basic HTTP requests and serving static content.

## Features:
- Listens on a specified port (default: 8080) for incoming HTTP requests.
- Handles HTTP GET requests.
- Serves a basic HTML page at the root path ("/").
- Returns a "404 Not Found" response for other paths.
- Implements basic error handling and cleanup.

## Prerequisites
Before you can use this HTTP server, make sure you have the following prerequisites installed on your system:

GCC (GNU Compiler Collection): This server is written in C and needs a C compiler to build.
POSIX-compatible operating system: The server uses POSIX system calls and should work on most Unix-like operating systems.

## Usage
1. Clone the repo to your local machine:
   ```git clone https://github.com/alexiswu-01/requestreservoir```
2. complie the server using gcc:
   
    ```
    cd requestreservoir
    gcc main.c -o -http-server
    ```
3. Run the server:
   ```./http-server```
   By default, the server listens on port 8080. You can change the port by modifying the PORT constant in main.c.

4. Open your web browser and access http://localhost:8080 to see the server in action. You should see a simple HTML page with the message "Alexis's Server."

## Project Structure
The project consists of two main files:

- main.c: Contains the server implementation, including socket creation, binding, listening, and request handling.


- setup.h: Header file with function prototypes and necessary includes for main.c.