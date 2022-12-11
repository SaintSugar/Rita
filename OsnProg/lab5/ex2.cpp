#include <iostream>
#include <ctime>
using namespace std;

float **array_init(int N, int M ) {
    srand(time(NULL));
    float **A = new float*[N];
    for (int i = 0; i < N; i++) {
        A[i] = new float[M];
        for (int j = 0; j < M; j++) {
            if (j >= M/(N * 1.0) * i) A[i][j] = rand() % 1000 * 0.01 + 1;
            else A[i][j] = 0;
       }
    }
    return A;
}

void print_Matrix(float **A, int N, int M) {
    for (int i = 0; i < N; i++) {
        for (int j = 0; j < M; j++) {
            cout << A[i][j] << "\t";
        }
        cout << endl;
    }
}

void add_element(float ***A, int len, float *el) {
    float **B = new float*[len+1];
    for (int i = 0; i < len; i++) B[i] = (*A)[i];
    B[len] = el;
    delete *A;
    *A = B;
}

float **task(float **A, int N, int M, int *len) {
    float **result = new float*[1];
    result[0] = &A[0][0];
    *len = 1;
    for (int i = 0; i < N; i++) {
        for (int j = 0; j < M; j++) {
            if (j >= M/(N * 1.0) * i)
                if (A[i][j] < *(result[0])) {
                    delete result;
                    *len = 1;
                    result = new float*[1];
                    result[0] = &A[i][j];
                }
                else if (A[i][j] == *(result[0]))
                {
                    add_element(&result, N, &A[i][j]);
                    (*len)++;
                }
                
                
        }
    }
    return result;
}

int main() {
    int N, M;
    int len;
    cout << "Enter N and M" << endl;
    cin >> N;
    cin >> M;
    float **A;
    A = array_init(N, M);
    print_Matrix(A, N, M);
    float **result = task(A, N, M, &len);
    cout << "Minimum elent is " << **result << endl;
    cout << len << " element";
    if (len == 1)
        cout << " was found" << endl;
    else
        cout << "s were found" << endl;
    return 0;    
}