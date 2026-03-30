/* file_reader_sys.c */
#include <fcntl.h>
#include <unistd.h>

int main() {
    char buffer[256];
    // YOUR CODE HERE
    // 1. Open "output.txt" for reading using open()
    int fd = open("output.txt", O_RDONLY);
    if (fd == -1) {
        write(STDERR_FILENO, "Error opening file\n", 19);
        return 1;
    }
    
    // 2. Read content into buffer using read() in a loop
    // 3. Write the content to the terminal (fd 1) using write()
    ssize_t bytes_read;
    while ((bytes_read = read(fd, buffer, sizeof(buffer) - 1)) > 0) {
        buffer[bytes_read] = '\0';  // Null-terminate the buffer
        write(STDOUT_FILENO, buffer, bytes_read);
    }
    
    // Check for read error
    if (bytes_read == -1) {
        write(STDERR_FILENO, "Error reading file\n", 19);
        close(fd);
        return 1;
    }
    
    // 4. Close the file using close()
    close(fd);
    
    return 0;
}