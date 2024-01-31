#include <stdio.h>

void compareNumbers(double doubleArr[]){


}

int main (){
    double doubleArr[] = {1.2, 5.5, 2.1, 3.3, 3.3};

    for(int i = 0; i < sizeof(doubleArr)/sizeof(doubleArr[0]); i++){
        double currentVal = doubleArr[i];
        double previousVal = doubleArr[i - 1];

        printf("This is the current value: %.1f /n", currentVal);
        printf("This is the previous value: %.1f /n", previousVal);
    }
    // compareNumbers(doubleArr);

    return 0;
}