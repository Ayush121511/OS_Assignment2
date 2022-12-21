
#include <stdio.h>
#include <stdlib.h>
#include <errno.h>
#include <string.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <sys/un.h>

char Arr1[5*10][10+1];

int main(void){
	printf("HEllo");

    struct sockaddr_un server_sockaddr; 
    int SOCKET_CLIENT;

    int SIZE1;
    struct sockaddr_un client_sockaddr; 
    int RECIEVER;
    SOCKET_CLIENT = socket(AF_UNIX, SOCK_STREAM, 0);

    client_sockaddr.sun_family = AF_UNIX;   
    strcpy(client_sockaddr.sun_path, "tpf_unix_sock.client"); 
    SIZE1 = sizeof(client_sockaddr);
    
    unlink("tpf_unix_sock.client");
    RECIEVER = bind(SOCKET_CLIENT, (struct sockaddr *) &client_sockaddr, SIZE1);

    server_sockaddr.sun_family = AF_UNIX;
    strcpy(server_sockaddr.sun_path, "tpf_unix_sock.server");
    RECIEVER = connect(SOCKET_CLIENT, (struct sockaddr *) &server_sockaddr, SIZE1);
    


    for(int j=0;j<10;j++){
        i=5;
        while(i>0){
            char STRING_LIST[11];
            int j=0;
            for(int j=0;j<10;j++){
                STRING_LIST[j]=(char)((rand()%26)+65);
            }
            STRING_LIST[10]='\0';
            strcpy(Arr1[5-i-1],STRING_LIST);
        }

        for(int i=0;i<5;i++){
            write(SOCKET_CLIENT,Arr1[i],10+1);

        }
        int i=5*j
        while(i<5*(j-1)+10)
        {
            write(SOCKET_CLIENT,&i,sizeof(int));
            i++;
        }

        int* MAXIMUM_INDEX=(int*)malloc(sizeof(int));
        read(SOCKET_CLIENT,MAXIMUM_INDEX,sizeof(int));
        printf("INDEX-MAXIMUM: ");
        printf("%d\n",*MAXIMUM_INDEX);

    }

    close(SOCKET_CLIENT);
    
    return 0;
}
