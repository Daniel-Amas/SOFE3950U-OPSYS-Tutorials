#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>

void *bellcurve (void *arg){
	(void) arg;
	int *grade = (int *) arg;
	double bellcurved = (*grade) * 1.50;
	printf ("Grade after Bellcurve: %.2f\n", bellcurved);
        pthread_exit(NULL);

}

int main() {
	int grades[5];

	printf("Enter 5 student's grades: \n");
	for (int i=0; i<5; i++) {
	 scanf("%d", &grades[i]);
	}

	pthread_t thread[5];
	for (int i=0; i<5; i++) {
	pthread_create(&thread[i], NULL, bellcurve, (void *) &grades[i]);
	}

	for (int i=0; i<5; i++) {
	pthread_join(thread[i], NULL);
	}

	return 0;
}