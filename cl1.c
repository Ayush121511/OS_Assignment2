#include <stdio.h>
#include <stdlib.h>
#include <errno.h>
#include <string.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <sys/un.h>

#define DATA "Hello from client"

int main(void){

    struct sockaddr_un server_sockaddr; 
    int SOCKET_CLIENT;
    int RECIEVER;

    struct sockaddr_un client_sockaddr; 

    int SIZE1;

    SOCKET_CLIENT = socket(AF_UNIX, SOCK_STREAM, 0);

    client_sockaddr.sun_family = AF_UNIX;   
    strcpy(client_sockaddr.sun_path, "tpf_unix_sock.client"); 
    SIZE1 = sizeof(client_sockaddr);
    
    unlink("tpf_unix_sock.client");
    RECIEVER = bind(SOCKET_CLIENT, (struct sockaddr *) &client_sockaddr, SIZE1);

    server_sockaddr.sun_family = AF_UNIX;
    strcpy(server_sockaddr.sun_path, "tpf_unix_sock.server");
    RECIEVER = connect(SOCKET_CLIENT, (struct sockaddr *) &server_sockaddr, SIZE1);

    for(int j=0;i<10;j++){
        int i=0;
        while(i<5){
            char arr_str[11];
            j=10;
            while (j>0)
            {
                arr_str[10-j]=(char)((rand()%(20+6))+35+30);
                j--;
            }
            arr_str[10]='\0';
            strcpy(arr1[i],arr_str);
            i++;
        }

        for(int i=0;i<5;i++){
            write(SOCKET_CLIENT,&i,sizeof(int));
        }

        int i=5*j;
        while( i<5*(j+1)){
            write(SOCKET_CLIENT,&i,sizeof(int));
            i++;
        }

        int* MAMXIMUM_INDEX=(int*)malloc(sizeof(int));
        read(SOCKET_CLIENT,MAMXIMUM_INDEX,sizeof(int));
        printf("Max index: " "+%d\n",*MAMXIMUM_INDEX);

        j++;

    }

    close(SOCKET_CLIENT);
    
    return 0;
}