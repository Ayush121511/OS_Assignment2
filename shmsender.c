#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include <sys/mman.h>
#include <unistd.h>
#include <string.h>

typedef struct Node{
    char STRING_ARR[10*10];
    int IND;
}Node;

#define SHM_SIZE 50 * sizeof(Node)

char strings[50][11];



int FLAG1=0;


int main()
{
    int index=0;
    for(int i=0; i<50; i++){
        strings[i];
        char string[10+1];

        for(int i=0; i<10;i++){
        
            int charnum = (rand()%26)+97;
            string[i] = (char)charnum;
        }
        string[10]='\0';
        strcpy(strings[i],string);
        printf("%s\n", strings[i]);
    }
    int fd = shm_open("/aditya", O_CREAT | O_RDWR, 0600);
    if (fd < 0) {
        printf("Error creating shm object\n");
        return EXIT_FAILURE;
    }

    ftruncate(fd, SHM_SIZE);
    Node* INFO = (Node*) mmap(0, SHM_SIZE, PROT_READ|PROT_WRITE, MAP_SHARED, fd, 0);
    INFO[6].IND=0;

    while(FLAG1==0){
        while(INFO[6].IND!=0);
        for(int itr=0; itr<5; itr++){
            strcpy(INFO[itr].STRING_ARR,strings[index]);
            INFO[itr].IND=index;
            if(index==49){
                FLAG1=1;
                break;
            }
            index++;
            
        }

        INFO[6].IND=1;
        

        while(INFO[6].IND!=2);
        printf("From Receiver: %s %d\n",INFO[5].STRING_ARR,INFO[4].IND);

        INFO[6].IND=0;

    }


    
    munmap(INFO,SHM_SIZE);
    close(fd);
    return EXIT_SUCCESS;
}