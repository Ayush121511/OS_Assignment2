#include <stdio.h>
#include <sys/syscall.h>
#include <linux/kernel.h>
#include <unistd.h>
#include <errno.h>

#define TWOD_COPY_SYSCALL 451

const int N = 2;

int main (){
    float src_arr[2][5];
    int i;
    for (int i = 0; i < 2; i++)
    {
        for (int j = 0; j < 5; j++)
        {
            src_arr[i][j]=i+j+0.1;
        }
        
    }
    float dest_arr[2][5];
    long sys_call_status = syscall(TWOD_COPY_SYSCALL, src_arr,dest_arr,5);
    if (sys_call_status != EFAULT)
    {
        printf("Successfully invoked\n");
        int i;
        for ( i = 0;i< 2; i++)  {
            for (int j = 0; j < 5; j++)
            {
                if(src_arr[i][j]!=dest_arr[i][j]){
                    printf("Error : %.2f %.2f\n",src_arr[i][j],dest_arr[i][j]);
                    return 0;
                }
            }
            
        }
        printf("Success\n");
    }
    
}