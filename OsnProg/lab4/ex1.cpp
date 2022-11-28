#include <iostream>
#include <ctime>
#define N1 10
#define N2 5

using namespace std;

void array_init(int *A, int N) {
    srand(time(NULL));
    for (int i = 0; i < N; i++) {
        A[i] = rand() % 100;
        if (i == N / 2) A[i] = 0;
        cout << A[i] << " ";
    }
    cout << endl;
}

int *get_ptr(int *A, int N) {
    int i;
    for (i = 0; i < N; i++) {
        if (A[i] == 0) break;
    }

    if (i == N) return nullptr; 
    return A + i;
}

int print_sum(int *A, int N) {
    int *p = get_ptr(A, N);
    if (p == nullptr) {
        cout << "Zero elements not found!" << endl;
        return -1;
    }

    int s1 = 0, s2 = 0;
    int i;
    
    for(i = 0; A + i != p; i++) s1 += A[i];
    for (i; i < N; i++) s2 += A[i];

    cout << "First sum: " << s1 << endl;
    cout << "Second sum: " << s2 << endl;

    return 0;
}

int main() {
    int A[N1], B[N2];

    array_init(A, N1);
    print_sum(A, N1);

    array_init(B, N2);
    print_sum(B, N2);   
    
    return 0;
}