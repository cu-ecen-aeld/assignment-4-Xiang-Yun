#include <stdio.h>
#include <stdlib.h>
#include <syslog.h>
#include <string.h>
#include <sys/stat.h>
#include <errno.h>

void print_usage(const char *program_name) {
    fprintf(stderr, "Usage: %s <file> <string>\n", program_name);
}

void write_to_file(const char *file_path, const char *string_to_write) {
    // Ensure directory exists
    char *dir_path = strdup(file_path); // Duplicate file_path
    if (dir_path == NULL) {
        perror("strdup");
        exit(EXIT_FAILURE);
    }
    
    // Find the last slash to separate file name from path
    char *last_slash = strrchr(dir_path, '/');
    if (last_slash != NULL) {
        *last_slash = '\0'; // Terminate string at the slash
        if (mkdir(dir_path, 0777) == -1 && errno != EEXIST) { // Make directory, but only if it doesn't exist
            perror("mkdir");
            free(dir_path); // Free memory
            exit(EXIT_FAILURE);
        }
    }
    free(dir_path); // Free memory


    // Open the file for writing
    FILE *file = fopen(file_path, "w");
    if (file == NULL) {
        syslog(LOG_ERR, "Error opening file %s: %s", file_path, strerror(errno));
        exit(1);
    }

    // Write the string to the file
    if (fprintf(file, "%s", string_to_write) < 0) {
        syslog(LOG_ERR, "Error writing to file %s: %s", file_path, strerror(errno));
        fclose(file);
        exit(1);
    }

    // Close the file
    if (fclose(file) != 0) {
        syslog(LOG_ERR, "Error closing file %s: %s", file_path, strerror(errno));
        exit(1);
    }

    // Log the successful write operation
    syslog(LOG_DEBUG, "Writing %s to %s", string_to_write, file_path);
}

int main(int argc, char *argv[]) {
    openlog("writer", LOG_PERROR | LOG_CONS, LOG_USER);

    // Check if the correct number of arguments are provided
    if (argc != 3) {
        print_usage(argv[0]);
        syslog(LOG_ERR, "Error: Incorrect number of arguments provided");
        closelog();
        return EXIT_FAILURE;
    }

    const char *file_path = argv[1];
    const char *string_to_write = argv[2];

    // Write the string to the file
    write_to_file(file_path, string_to_write);

    // Close the connection to the syslog
    closelog();
    
    return EXIT_SUCCESS;
}