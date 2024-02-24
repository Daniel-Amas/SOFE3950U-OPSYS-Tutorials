#define _XOPEN_SOURCE 600 // required for barriers to work 
#include <stdlib.h> 
#include <stdio.h> 
#include <pthread.h>
#include <unistd.h> 

void *hello_world(void *arg){
    //random sleep btw 1-3 sec
    sleep(rand() % 3 + 1);

    printf("Hello World\n");

    pthread_exit(NULL);
};
void *goodbye(void *arg){
    //random sleep btw 1-3 sec
    sleep(rand() % 3 + 1);

    printf("Goodbye\n");

    pthread_exit(NULL);
};

int main(void){
    pthread_t thread1, thread2;

    //create threads
    if(pthread_create(&thread1, NULL, hello_world, NULL) != 0){
        perror("Error creating thread 1");
        return EXIT_FAILURE;
    }    

    if(pthread_create(&thread2, NULL, goodbye, NULL) != 0){
        perror("Error creating thread 2");
        return EXIT_FAILURE;
    }    

    pthread_join(thread1, NULL);
    pthread_join(thread2, NULL);

    return EXIT_SUCCESS;
} 