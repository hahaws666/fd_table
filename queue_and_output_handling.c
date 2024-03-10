#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <dirent.h>
#include <unistd.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <errno.h>
#include <ctype.h>
#include <stdio.h>
#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/utsname.h>
#include <sys/sysinfo.h>
#include <sys/resource.h>
#include <utmp.h>
#include <unistd.h>
#include <stdbool.h>
#include <time.h>
#include <ctype.h>

#define MAX_LEN 1024

/*
to check is int
*/
bool isInteger(const char* str) {
    if (str == NULL || *str == '\0') {
        // Empty string or NULL pointer
        return false;
    }

    // Skip leading whitespace characters
    while (*str == ' ' || *str == '\t') {
        str++;
    }

    // Check for an optional sign
    if (*str == '+' || *str == '-') {
        str++;
    }

    //Check if the remaining characters are digits
    while (*str != '\0') {
        if (!isdigit(*str)) {
            return false;
        }
        str++;
    }

    return true;
}// find if char is int

/*
to create a link list like data structure
*/
typedef struct compressed_table {
    pid_t pid; // process id
    int fd; // file descriptor
    char fname[MAX_LEN]; // symbolic link path name or canonical path name
    unsigned long inode; // inode number
    struct compressed_table *next; // pointer to next node
} c_m;

/*
to setting up a new data structure
*/
c_m* create_new(pid_t pid, int fd, const char *fname, unsigned long inode) {
    c_m* result = (c_m*)calloc(1, sizeof(c_m));
    if (result == NULL) {
        // perror("calloc failed");
        return NULL;
    }
    result->pid = pid;
    result->fd = fd;
    strncpy(result->fname, fname, MAX_LEN - 1);
    result->fname[MAX_LEN - 1] = '\0';
    result->inode = inode;
    result->next = NULL;
    return result;
}


/*
add new nodes into the queue
*/
c_m* add_to_queue(c_m* original, c_m* new) {
    if (original == NULL) {
        return new;
    }
    c_m* tmp = original;
    while (tmp->next != NULL) {
        tmp = tmp->next;
    }
    tmp->next = new;
    return original;
}


/*
to print the queue
*/
void print_queue(c_m * res, int pid, int process,int systemwide ,int vnodes, int threshold ){
    int counter = 0;
    printf("\t pid \t");
    if (res == NULL) 
    {
        return;
    }
    if (process==1)
    {
        printf("fd\t");
    }
    if (systemwide== 1)
    {
        printf("filename\t\t");
    }
    if (vnodes== 1)
    {
        printf("inode\t");
    }
    printf("\n");
    if (threshold== 0)
    {
        printf("No one knows the CSCB09 better than me\n");
    }
    
    printf("\t========================================\n\n");
    while (res!= NULL) 
    {

        if (pid !=-1)
        {
            if (res->pid == pid)
            {
                    printf("%d\t",counter);
                    counter++;

                        printf("%d    ", res->pid);
                        if (process==1)
                            {
                                printf("%d   ", res->fd);
                            }
                        if (systemwide== 1)
                            {
                                printf("%s\t", res->fname);
                            }
                        if (vnodes== 1)
                            {
                                printf("%ld   ", res -> inode );
                            }
                        if (process * vnodes *systemwide ==0)
                        {
                            printf("%d   ", res->fd);
                            printf("%s\t", res->fname);
                            printf("%ld   ", res -> inode );
                        }
                printf("\n");
            }
            
        }
        else
        {
                    printf("%d\t",counter);
                    counter++;

                        printf("%d    ", res->pid);
                        if (process==1)
                            {
                                printf("%d   ", res->fd);
                            }
                        if (systemwide== 1)
                            {
                                printf("%s   ", res->fname);
                            }
                        if (vnodes== 1)
                            {
                                printf("%ld   ", res -> inode );
                            }
                    
                        printf("\n");
        }

        res  = res->next;
    }
    
}


/*
to print the pid and fd with bigger than the threshold
*/
void print_threshold(c_m *res, int threshold){
    printf("## Offending processes:\n");
    int counter = 0;
    int last =0;
    while (res->next!=NULL)
    {
        if (res->pid==last)
        {
            counter++;
        }
        else
        {
  
            if (counter > threshold)
            {
                printf("%d (%d) \t",res->pid,counter);
            }
            counter=1;
            last = res->pid;
        }
        
        res=res->next;
    }
    
}

/*
to output the result of lnk list into a txt file
*/
void write_txt_file(c_m *res,int node) {
    FILE *fp = fopen("compositeTable.txt", "w"); // Open for writing in text mode
    if (fp == NULL) {
        perror("Failed to open file");
        return;
    }
    fprintf(fp, "\t pid \t fd \t filename \t\t inode\n");
    fprintf(fp, "\t=================================================\n");
    if (node ==-1)
    {
        while (res != NULL) {
            fprintf(fp, "%d\t%d\t%s\t%lu\n", res->pid, res->fd, res->fname, res->inode);
            res = res->next;
        }
    }
    else
    {
        while (res != NULL) {
            if (res->pid ==node)
            {
                fprintf(fp, "%d\t%d\t%s\t%lu\n", res->pid, res->fd, res->fname, res->inode);
            }
        res = res->next;
    }
    }
    fclose(fp); // Close the file after writing
}


/*
to output the output into a binary file
*/
void write_binary_file( c_m *res,int node) {
    FILE *fp = fopen("compositeTable.bin", "wb"); // Open for writing in binary mode
    if (fp == NULL) {
        perror("Failed to open file");
        return;
    }
    if (node == -1) {
    {
            while (res != NULL) {
            // Write numeric data directly
            fwrite(&res->pid, sizeof(int), 1, fp);
            fwrite(&res->fd, sizeof(int), 1, fp);
            fwrite(&res->inode, sizeof(int), 1, fp);
            // For the string, write the length followed by the string itself
            int fname_len = strlen(res->fname);  //get length
            fwrite(res->fname, sizeof(char), fname_len, fp);
            fwrite(&(res->inode), sizeof(ino_t), 1, fp); 
            fwrite("\n", sizeof(char), 1, fp); //writes a newline to file

            res = res->next;
        }
    }
    }
    else
    {
        while (res != NULL) {
            if (res->pid==node)
                {
                    fwrite(&res->pid, sizeof(int), 1, fp);
                    fwrite(&res->fd, sizeof(int), 1, fp);
                    fwrite(&res->inode, sizeof(int), 1, fp);
                    // For the string, write the length followed by the string itself
                    int fname_len = strlen(res->fname);  //get length
                    fwrite(res->fname, sizeof(char), fname_len, fp);
                    fwrite(&(res->inode), sizeof(ino_t), 1, fp); 
                    fwrite("\n", sizeof(char), 1, fp); //writes a newline to file
                }
                


            res = res->next;
        }
    }
    


    fclose(fp); // Close the file after writing
}