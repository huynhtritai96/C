The `poll()` function in C is used for monitoring multiple file descriptors (like sockets) to see if they are ready for some I/O operations, such as reading, writing, or handling errors. Unlike `select()`, `poll()` does not have a limitation on the number of file descriptors it can monitor, and it uses an array of `pollfd` structures to manage the file descriptors.

### **Key Components of `poll()`**

1. **`pollfd` Structure**:
   The `pollfd` structure is used to specify the file descriptors and the events you are interested in.

   ```c
   struct pollfd {
       int fd;         // File descriptor to monitor
       short events;   // Events of interest (input)
       short revents;  // Events that occurred (output)
   };
   ```

   - **`fd`**: The file descriptor to monitor (e.g., socket, file).
   - **`events`**: The events you want to monitor (e.g., readable, writable, etc.).
   - **`revents`**: The events that actually occurred, set by `poll()` when it returns.

2. **Events**:
   You can monitor several types of events using `poll()`:

   - **`POLLIN`**: There is data to read.
   - **`POLLOUT`**: Writing is possible without blocking.
   - **`POLLERR`**: An error occurred.
   - **`POLLHUP`**: The other side of the connection is hung up.
   - **`POLLPRI`**: There is urgent ("out-of-band") data to read.

3. **poll() Function**:
   ```c
   int poll(struct pollfd *fds, nfds_t nfds, int timeout);
   ```

   - **`fds`**: An array of `pollfd` structures, one for each file descriptor to monitor.
   - **`nfds`**: The number of file descriptors in the `fds` array.
   - **`timeout`**: Maximum time in milliseconds that `poll()` will block waiting for events. A value of `-1` means it will block indefinitely until an event occurs.

   **Return Value**:
   - Returns the number of file descriptors that have events to report.
   - Returns `0` if the timeout period expires with no events.
   - Returns `-1` on error and sets `errno`.

---

### **Example of a TCP Server Using `poll()`**

Below is an example of a TCP server using `poll()` to handle multiple client connections concurrently without creating separate threads or processes.

```c
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <unistd.h>
#include <arpa/inet.h>
#include <poll.h>

#define PORT 8080
#define MAX_CLIENTS 10
#define BUFFER_SIZE 1024

int main() {
    int server_fd, new_socket, client_socket[MAX_CLIENTS], activity;
    struct sockaddr_in address;
    int addrlen = sizeof(address);
    char buffer[BUFFER_SIZE];

    struct pollfd fds[MAX_CLIENTS + 1];
    int nfds = 1;  // Start by monitoring just the server socket
    int i;

    // Initialize client_socket[] to 0 (not checked by poll if 0)
    for (i = 0; i < MAX_CLIENTS; i++) {
        client_socket[i] = 0;
    }

    // Create the server socket
    if ((server_fd = socket(AF_INET, SOCK_STREAM, 0)) == 0) {
        perror("Socket creation failed");
        exit(EXIT_FAILURE);
    }

    // Bind the socket to the port
    address.sin_family = AF_INET;
    address.sin_addr.s_addr = INADDR_ANY;
    address.sin_port = htons(PORT);

    if (bind(server_fd, (struct sockaddr *)&address, sizeof(address)) < 0) {
        perror("Bind failed");
        close(server_fd);
        exit(EXIT_FAILURE);
    }

    // Listen for incoming connections
    if (listen(server_fd, 3) < 0) {
        perror("Listen failed");
        close(server_fd);
        exit(EXIT_FAILURE);
    }

    // Initialize the pollfd structure for the server socket
    fds[0].fd = server_fd;
    fds[0].events = POLLIN;  // Monitor for incoming connections (readable)

    printf("Server listening on port %d\n", PORT);

    while (1) {
        // Call poll() to wait for events
        activity = poll(fds, nfds, -1);  // Timeout = -1 means wait indefinitely

        if (activity < 0) {
            perror("Poll error");
            exit(EXIT_FAILURE);
        }

        // Check if there is an incoming connection on the server socket
        if (fds[0].revents & POLLIN) {
            // Accept the incoming connection
            if ((new_socket = accept(server_fd, (struct sockaddr *)&address, (socklen_t *)&addrlen)) < 0) {
                perror("Accept failed");
                exit(EXIT_FAILURE);
            }

            printf("New connection, socket fd is %d, ip is : %s, port : %d\n",
                   new_socket, inet_ntoa(address.sin_addr), ntohs(address.sin_port));

            // Add new socket to client_socket[] array and fds[] array for monitoring
            for (i = 0; i < MAX_CLIENTS; i++) {
                if (client_socket[i] == 0) {
                    client_socket[i] = new_socket;
                    fds[i + 1].fd = new_socket;
                    fds[i + 1].events = POLLIN;  // Monitor for incoming data
                    nfds++;
                    printf("Added new client on fd %d\n", new_socket);
                    break;
                }
            }
        }

        // Check all client sockets for incoming data
        for (i = 1; i < nfds; i++) {
            if (fds[i].revents & POLLIN) {
                int sd = fds[i].fd;
                int valread = read(sd, buffer, BUFFER_SIZE);
                if (valread == 0) {
                    // Client disconnected
                    printf("Client disconnected, fd %d\n", sd);
                    close(sd);
                    client_socket[i - 1] = 0;  // Mark slot as available
                    fds[i].fd = -1;  // Mark pollfd entry as invalid
                     --;
                } else {
                    // Echo the data back to the client
                    buffer[valread] = '\0';
                    printf("Received message: %s\n", buffer);
                    send(sd, buffer, valread, 0);
                }
            }
        }
    }

    return 0;
}
```

### **Explanation of the Example**

1. **Socket Creation**:
   - The server creates a TCP socket using `socket()` and binds it to the specified port (`8080`).

2. **pollfd Setup**:
   - `fds[0]` monitors the server socket (`server_fd`) for incoming connections using the event `POLLIN` (ready for reading).
   - `fds[]` is used to monitor multiple file descriptors (server socket and client sockets).
   
3. **Main Loop**:
   - The `poll()` function is called to monitor all active file descriptors. It blocks until an event occurs (e.g., a new connection or incoming data).
   - **New Connections**: When a new connection is detected (`fds[0].revents & POLLIN`), the server accepts the connection and adds the new client socket to the `fds[]` array.
   - **Client Data**: If data is ready to be read from a client socket (`fds[i].revents & POLLIN`), the server reads the data and echoes it back to the client.

4. **Client Management**:
   - The server keeps track of client sockets using the `client_socket[]` array. When a client disconnects, its socket is closed, and its `pollfd` entry is marked as invalid by setting `fds[i].fd = -1`.

---

### **Advantages of `poll()`**

1. **No Hard Limit on File Descriptors**:
   - Unlike `select()`, `poll()` does not have a built-in limit on the number of file descriptors it can handle.
   
2. **Simpler Input Handling**:
   - Unlike `select()`, where file descriptor sets need to be reset after each call, `poll()` maintains an array of `pollfd` structures, which is easier to manage.

3. **Supports More Events**:
   - `poll()` can monitor more types of events (such as `POLLIN`, `POLLOUT`, and `POLLERR`).

---

### **Disadvantages of `poll()`**

1. **O(n) Complexity**:
   - Like `select()`, `poll()` still scans all file descriptors linearly, which can be inefficient for a large number of connections.

2. **Array Overhead**:
   - The `pollfd` array is recreated and copied each time `poll()` is called, which can lead to inefficiency in large-scale applications.

3. **No Edge Triggering**:
   - `poll()` is level-triggered, meaning it will notify you as long as the condition holds (e.g., a file descriptor is readable), unlike edge-triggered models (`epoll()`, `kqueue()`).

---

### **Use Cases**

- **Medium-Sized Applications**: `poll()` is suitable for applications with a moderate number of file descriptors (more than 1024 but not millions).
- **POSIX Systems**: Works on most

 POSIX systems, making it more portable than `epoll()` or `kqueue()`.
- **Cross-Platform Applications**: Useful for applications that need to monitor a dynamic number of file descriptors across different platforms.

In large-scale applications (e.g., high-performance web servers), alternatives like `epoll()` (Linux) or `kqueue()` (BSD/macOS) are generally more efficient. However, `poll()` is still widely used for many medium-scale applications where the simplicity of API and cross-platform support are important.