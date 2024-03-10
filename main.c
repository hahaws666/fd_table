#include "datahandling.c"

/*
to receive the data and do the output parts
*/
int main(int argc, char **argv) {
    c_m* res = handling_data();// get all the data and store them in res
    printf("\033[H\033[J"); // clear the screen
    int node = -1, threshold = -1; // set the default value
    int txt=0, bin=0;
    int process=0, vnode=0, composite = 0, systemwide=0; //
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
                process=1;
                
                
            }
            else if (strcmp(stringPart, "--vnode") == 0) {
                vnode=1;
                
            }
            else if (strcmp(stringPart, "--systemWide") == 0) {
                systemwide=1;

            }
            else if ( strcmp(stringPart, "--composite") == 0){
                composite=1;

                
            } 
            else if(isInteger(stringPart)){
                node = atoi(stringPart);
            }
            else if (strcmp(stringPart, "--threshold") == 0)
            {   
                threshold = atoi(strtok(NULL, "")); 
                print_queue(res,node,1,1,1,1);
                print_threshold(res,threshold);
            }
            else if (strcmp(stringPart,"--output_TXT") == 0){
                txt=1;
            }
            else if (strcmp(stringPart,"--output_binary")==0){
                bin=1;
                
            }
            else
            {
                printf("invalid input.\n");
            }
            i++;
    }
    if (process ==1)
    {
        print_queue(res,node,1,0,0,-1);
    }
    if (vnode == 1)
    {
        print_queue(res,node,0,0,1,-1);
    }
    if (systemwide == 1)
    {
        print_queue(res,node,1,1,0,-1);
    }
    if (composite == 1 ||process+vnode+ systemwide ==0)
    {

        print_queue(res,node,1,1,1,-1);
    }

    if (bin==1)
    {
        write_binary_file(res,node);
    }
    if (txt==1)
    {
        write_txt_file(res,node);
    }
    
    
    
    
    }
    return 0;
}