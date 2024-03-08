#include "queue_and_output_handling.c"
/*
to deal with all data and output a link list as the result 
*/
c_m* handling_data() {
    c_m* result = NULL;
    DIR* proc_dir = opendir("/proc");
    if (proc_dir == NULL) {
        // perror("Failed to open /proc");
        return NULL;
    }

    struct dirent* proc_entry;
    while ((proc_entry = readdir(proc_dir)) != NULL) {
        if (!isdigit(proc_entry->d_name[0])) continue;

        int pid = atoi(proc_entry->d_name);
        char fd_path[MAX_LEN];
        snprintf(fd_path, sizeof(fd_path), "/proc/%d/fd", pid);
        DIR* fd_dir = opendir(fd_path);
        if (fd_dir == NULL) {
            continue; // Skip if unable to open fd directory
        }

        struct dirent* fd_entry;
        while ((fd_entry = readdir(fd_dir)) != NULL) {
            if (!isdigit(fd_entry->d_name[0])) continue;

            int fd = atoi(fd_entry->d_name);
            snprintf(fd_path, sizeof(fd_path), "/proc/%d/fd/%d", pid, fd);
            char filename[MAX_LEN];
            ssize_t len = readlink(fd_path, filename, sizeof(filename) - 1);
            if (len == -1) {
                // perror("readlink failed");
                continue;
            }
            filename[len] = '\0';

            struct stat file_stat;
            if (stat(filename, &file_stat) == -1) {
                continue;
            }

            c_m* new_node = create_new(pid, fd, filename, file_stat.st_ino);
            if (new_node == NULL) {
                continue; // Handle allocation failure if needed
            }
            // }perror("readlink failed");
            result = add_to_queue(result, new_node);
        }
        closedir(fd_dir); // Close fd directory after use
    }
    closedir(proc_dir); // Close proc directory after use
    return result;
}