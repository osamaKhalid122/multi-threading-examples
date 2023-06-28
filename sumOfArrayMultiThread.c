#include <windows.h>
#include <stdlib.h>
#include <stdio.h>
#include <time.h>

int thread_sum;

typedef struct data {
    int* arr;
    int thread_num;
} data;

int arrSize = 1000;

void halfSum(void* p) {
    data* ptr = (data*)p;
    int n = ptr->thread_num;
    int T0 = 0;
    int T1 = 0;

        if (n == 0) {
            for (int i = 0; i < arrSize/2; i++)
            {

                thread_sum = thread_sum + ptr->arr[i];
                printf("Array Elements of T0 are %d\n\r", ptr->arr[i]);
            }
        }        

        if (n == 1) 
        {
            for (int i = arrSize / 2; i < arrSize; i++)
            {
                thread_sum = thread_sum + ptr->arr[i];
                printf("Array Elements of T1 are %d\n\r",ptr->arr[i]);
            }
        }

 
}

int main(void) 
{
    // Declare integer array [1,2,3,4,5,6,7,8,9,10]:
    double time_taken = 0;
    clock_t begin = clock();
    int* int_arr = (int*)calloc(arrSize, sizeof(int));
    HANDLE ThreadHandle0;
    HANDLE ThreadHandle1;

    for (int i = 0; i < arrSize; i++)
    if (int_arr)
        {
            int_arr[i] = i + 1;
           printf("Array Elements of Main are %d\n\r", int_arr[i]);
        }
    
    // Declare arguments for both threads:

    data thread_data[2];
    thread_data[0].thread_num = 0;
    thread_data[0].arr = int_arr;
    thread_data[1].thread_num = 1;
    thread_data[1].arr = int_arr;


    // Declare thread IDs:
    DWORD threadID[2];
    
    // Start both threads:
    ThreadHandle0 = CreateThread(NULL,0, halfSum, &thread_data[0], 0, &threadID[0]);
    ThreadHandle1 = CreateThread(NULL,0, halfSum, &thread_data[1], 0, &threadID[1]);

    printf("ID of Thread 0 = %p\n", &threadID[0]);
    printf("ID of Thread 0 = %p\n", &threadID[1]);


    if (ThreadHandle0 != 0)
    {
        WaitForSingleObject(ThreadHandle0, INFINITE);
        CloseHandle(ThreadHandle0);
    }
    
    if (ThreadHandle1 != 0)
    {
        WaitForSingleObject(ThreadHandle1, INFINITE);
        CloseHandle(ThreadHandle1);
    }
    // Declare space for sum:

    printf("Sum of whole array = %d\n", thread_sum);
    clock_t end = clock();
    time_taken +=( (double)(end - begin) )/ CLOCKS_PER_SEC;
    printf("Time taken by program is = %f\n", time_taken);
    return 0;
}
