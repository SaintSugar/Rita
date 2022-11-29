#include <iostream>
#include <string.h>

using namespace std;

char *tostring(int a) {
    char buf[100];
    int n = 0;
    a *= 10;
    while (a > 9)
    {   
        a /= 10;
        buf[n] = a % 10 + '0';
        n++;
    }
    
    char *res = new char[n+1];

    for (int i = 0; i < n; i++) {
        res[i] = buf[n - 1 - i];
    }
    res[n] = 0;
    
    return res;
}

void paste_on_index(char **where, char *paste, int index) {
    char *new_line = new char[strlen(*where) + strlen(paste) + 1];

    for (int k = 0; k < index; k++) new_line[k] = (*where)[k];
                
    for (int k = index; k < index + strlen(paste); k++) new_line[k] = paste[k - index];
    
    for (int k = index + strlen(paste); (*where)[k - strlen(paste) - 1] != 0; k++) new_line[k] = (*where)[k - strlen(paste)];

    delete [] *where;
    *where = new_line;
}

void print_array(char **A, int N) {
    for (int i = 0; i < N; i++) {
        cout << A[i] << endl;
    }
}

void get_line(char **buf) {
    char c = 0;
    int N = 0;
    while (true) {
        c = cin.get();
        if (c == '\n') break;
        char *buf2 = new char[N + 2];
        for (int i = 0; i < N; i++) buf2[i] = (*buf)[i];
        buf2[N] = c;
        buf2[N + 1] = 0;
        delete [] buf;
        *buf = buf2;
        N++;
    }
}

char **get_text(int *len) {
    char **mem;
    int N = 0;
    char *buf;
    char flag = 0;
    while (true) {
        get_line(&buf);

        if (strcmp(buf, "yes") == 0) break;

        char *new_line = new char[strlen(buf)];
        strcpy(new_line, buf);

        char **new_mem = new char*[N+1];
        for (int j = 0; j < N; j++) new_mem[j] = mem[j];
        new_mem[N] = new_line;
        N++;
        
        delete [] mem;
        mem = new_mem;
    }
    *len = N;
    return mem;
}

void task(char ***array, int N) {

    char **mem = *array;
    for (int i = 0; i < N; i++) {
        int num = 1;
        for (int j = 0; mem[i][j] != 0; j++) {
            if ((mem[i][j - 1] == ' ' || j == 0) && islower(mem[i][j])) {
                char* numberstring = tostring(num);
                paste_on_index(&mem[i], numberstring, j);
                num++;
                delete [] numberstring;
            }
        }
    }
    *array = mem;
}

int main() {
    int N;
    char **mem = get_text(&N);

    task(&mem, N);
    
    print_array(mem, N);

    return 0;
}