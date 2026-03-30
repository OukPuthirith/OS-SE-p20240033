/* file_creator_sys.c */
#include <fcntl.h>    // open(), O_WRONLY, O_CREAT, O_TRUNC
#include <unistd.h>   // write(), close()
#include <string.h>   // strlen()

int main() {
    // YOUR CODE HERE
    // 1. Open/create "output.txt" using open()
    int fd = open("output.txt", O_WRONLY | O_CREAT | O_TRUNC, 0644);
    if (fd == -1) {
        write(STDERR_FILENO, "Error opening file\n", 19);
        return 1;
    }
    
    // 2. Write "Hello from Operating Systems class!\n" using write()
    char *message = "Hello from Operating Systems class!\n";
    write(fd, message, strlen(message));
    
    // 3. Close the file using close()
    close(fd);
    
    // 4. Print "File created successfully!\n" to the terminal using write()
    char *success_msg = "File created successfully!\n";
    write(STDOUT_FILENO, success_msg, strlen(success_msg));
    
    return 0;
}