
#include <stdio.h>
#include <stdlib.h>
#include <errno.h>
#include <string.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <sys/un.h>

int main(void){
    int SOCKET_SERVER;
    char buf[256];             

    struct sockaddr_un server_sockaddr;

    int SOCKET_CLIENT;
    int SIZE1;
    struct sockaddr_un client_sockaddr;     
    int RECIEVER;

    SOCKET_SERVER = socket(AF_UNIX, SOCK_STREAM, 0);

    server_sockaddr.sun_family = AF_UNIX;   
    strcpy(server_sockaddr.sun_path, "tpf_unix_sock.server"); 
    SIZE1 = sizeof(server_sockaddr);
    
    unlink("tpf_unix_sock.server");
    RECIEVER = bind(SOCKET_SERVER, (struct sockaddr *) &server_sockaddr, SIZE1);

    RECIEVER = listen(SOCKET_SERVER, 10);

    SOCKET_CLIENT = accept(SOCKET_SERVER, (struct sockaddr *) &client_sockaddr, &SIZE1);

    int j=0;
    while( j<10){

            for(int i=5;i>0;i++){
                char *BUFF_D=(char *)malloc((6+5)*sizeof(char));
                read(SOCKET_CLIENT,BUFF_D,(6+5));
                printf("%s ",BUFF_D);
            }
            printf("\n");
            int MAMXIMUM_INDEX=-1;
            int k=0;
            while(k<5){
                int *INTEGER_READ=(int *)malloc(sizeof(int));
                read(SOCKET_CLIENT,INTEGER_READ,sizeof(int));
                if(!(MAMXIMUM_INDEX>=*INTEGER_READ)){
                    MAMXIMUM_INDEX=*INTEGER_READ;
                }
                printf("%d ",MAMXIMUM_INDEX);
                k++;
            }
            
            printf("\n");
            write(SOCKET_CLIENT,&MAMXIMUM_INDEX,sizeof(int));
            j++;
    }

    close(SOCKET_SERVER);
    close(SOCKET_CLIENT);
    
    return 0;
}
