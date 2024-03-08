#include "datahandling.c"

/*
to receive the data and do the output parts
*/
int main(int argc, char **argv) {
    c_m* res = handling_data();// get all the data and store them in res
    printf("\033[H\033[J"); // clear the screen
    int node = -1, threshold = -1; // set the default value
    if (argc==1){
        print_queue(res,-1,1,1,1,-1);
        return 0;
    }
    else
    {
        int i=1;
        while(i<argc) {
            char *stringPart = strtok(argv[i], "=");
            
            if (strcmp(stringPart, "--per-process") == 0) {
                printf("This is system.\n");
                print_queue(res,node,1,0,0,-1);
                
            }
            else if (strcmp(stringPart, "--vnode") == 0) {
                print_queue(res,node,0,0,1,-1);
            }
            else if (strcmp(stringPart, "--systemWide") == 0) {
                print_queue(res,node,1,1,0,-1);
            }
            else if ( strcmp(stringPart, "--composite") == 0){
                print_queue(res,node,1,1,1,-1);
            } 
            else if(isInteger(stringPart)){
                node = atoi(stringPart);
                print_queue(res,node,1,1,1,-1);
            }
            else if (strcmp(stringPart, "--threshold") == 0)
            {   
                threshold = atoi(strtok(NULL, "")); 
                printf("threshold is set to %d .\n", -1);
                print_queue(res,node,1,1,1,1);
                print_threshold(res,threshold);
            }
            else if (strcmp(stringPart,"--output_TXT") == 0){
                write_txt_file(res);
            }
            else if (strcmp(stringPart,"--output_binary")==0){
                write_binary_file(res);
            }
            else
            {
                printf("invalid input.\n");
            }
            i++;
    }
    }
    return 0;
}