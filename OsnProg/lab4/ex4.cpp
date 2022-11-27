#include <iostream>
#include <stdlib.h>
#include <ctime>
#define N1 10
#define N2 5

using namespace std;

int sum(int *a, int b) {
    int c = *a + b;
    *a = *a + 1;
    return c;
}

int main() {
    int A[N1], B[N2];
    srand(time(0));
    for (int i = 0; i < N1; i++) {
        A[i] = rand() % 100;
    }
    int a = 1, b = 2;
    
    cout << a << endl;
    cout << sum(&a, b) << endl;
    cout << a << endl;

    return 0;
}