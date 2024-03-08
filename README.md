# fd_table
For this program we will build a tool to display the tables used by the OS to keep track of open files, assignation of File Descriptors (FD) and processes.

## how to use
1. Open a terminal
2. go to the direction
3. input "make'
4. `./fd_table` + $(other falgs)
5. make help to get help make clean to clean

# Description

## File: main.c
this file gets the input and show the result through other two file

### Functions

#### int main () : to receive the data and do the output parts

## File: queue_and_output_handling
handling queue operations and do the oput helper functions


### Functions
#### bool isInteger(const char* str) 
 to check is int
#### c_m* create_new(pid_t pid, int fd, const char *fname, unsigned long inode)
to setting up a new data structure
#### c_m* add_to_queue(c_m* original, c_m* new)
add new nodes into the queue
#### void print_queue(c_m * res, int pid, int process,int systemwide ,int vnodes, int threshold )
to print the queue
#### void print_threshold(c_m *res, int threshold)
to print the pid and fd with bigger than the threshold
#### void write_txt_file(c_m *res)
to output the result of lnk list into a txt file
#### void write_binary_file( c_m *res) 
to output the output into a binary file

## File datahandling.c
this file receive all the informations about the nodes and input them in to the link list
### functions
#### c_m* handling_data()
to deal with all data and output a link list as the result 

# how i get this  
firstly i use the link list to store all the data then i get pids and their branches with reading the "/proc" and its directory
