#include <iostream>
#include <ctime>

#define N 10

using namespace std;

void array_init(int A[N][N], int a, int b) {
    srand(time(NULL));
    for (int i = 0; i < N; i++) {
        for (int j = 0; j < N; j++) {
            A[i][j] = rand() % (1 + b - a) + a;
        }
    }
}

void feel_figure_by_zero(int A[N][N], bool exclude_diag) {
    for (int i = 0; i < N; i++) {
        for (int j = 0; j - exclude_diag < i; j++) {
            A[i][j] = 0;
        }
    }
}

void print_array(int A[N][N]) {
    for (int i = 0; i < N; i++) {
        for (int j = 0; j < N; j++) {
            if (A[i][j] >= 0) cout << " ";
            cout << A[i][j] << "\t";
        }
        cout << endl;

    }
}

void search_min_max(int A[N][N], int result[2], bool exclude_diag) {
    result[0] = 0;
    result[1] = A[0][exclude_diag];

    for (int i = 0; i < N - exclude_diag; i++) {
        for (int j = i + exclude_diag; j < N; j++) {
            if (std::abs(A[i][j]) > std::abs(result[0])) result[0] = A[i][j];
            if (std::abs(A[i][j]) < std::abs(result[1])) result[1] = A[i][j];
        }
    }
}

int main() {
    int A[N][N];
    array_init(A, -100, 100);
    feel_figure_by_zero(A, true);
    print_array(A);
    
    int result[2];
    search_min_max(A, result, true);

    cout << result[0] << " " << result[1] << endl;


    return 0;
}