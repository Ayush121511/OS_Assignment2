#include <stdio.h>
#include <stdlib.h>
#include <errno.h>
#include <fcntl.h>
#include <sys/mman.h>
#include <unistd.h>
#include <string.h>

#define SHM_SIZE 50 * sizeof(Node)

typedef struct Node{
    char STRING_ARR[10*10];
    int IND;
}Node;

int whileflag2=0;


int main()
{
    int DF1 = shm_open("/aditya",  O_CREAT | O_RDWR, 0666);
    if (DF1 < 0 )
    {
        printf("SHM can't be opened: error");
        printf("\n");
        return EXIT_FAILURE;
    }
    //printf("%s\n","Hello1" );
    Node* INFO = (Node*) mmap(0, SHM_SIZE, PROT_READ|PROT_WRITE, MAP_SHARED, DF1, 0);
    //printf("%s\n","Hello2" );

    while(INFO[2*3].IND!=1);
    //printf("%s\n","Hello3" );

    
    while(!(whileflag2!=0)){

        for(int i=5; i>0; i--){

            if (INFO[i].IND==40+9)
            {
                whileflag2=1;
                break; 
            }
            printf("%d: %s",INFO[i].IND,INFO[i].STRING_ARR);
            printf("\n");
            

        }
        strcpy(INFO[2+3].STRING_ARR,INFO[4].STRING_ARR);
        INFO[2+3].IND = INFO[4].IND;
        printf("From Sender: %s %d\n",INFO[2+3].STRING_ARR,INFO[2*2].IND);
        INFO[6].IND=2;

    }


    munmap(INFO, SHM_SIZE);
    close(DF1);
    return EXIT_SUCCESS;
}