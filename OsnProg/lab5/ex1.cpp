#include <iostream>
#include <string.h>

using namespace std;

int get_int_len(int a) {
    int res = 1;
    if (a < 0) res++;
    while (a > 10) {
        a = a / 10;
        res++;
    }
    return res;
}

int main() {
    char **mem;
    int N = 0;

    char buf[1000];
    string buf_str;
    char flag = 0;

   while (true) {
        getline(cin, buf_str);
        strcpy(buf, buf_str.c_str());

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
    for (int i = 0; i < N; i++) {
        cout << int(mem[i][strlen(mem[i])]) << endl;
    }
    for (int i = 0; i < N; i++) {
        int num = 1;
        for (int j = 0; mem[i][j] != 0; j++) {
            if ((mem[i][j - 1] == ' ' || j == 0) && islower(mem[i][j])) {
                char* numberstring = new char[get_int_len(num)];
                sprintf(numberstring, "%d", num);

                char *new_line = new char[strlen(mem[i]) + get_int_len(num) + 1];

                for (int k = 0; k < j; k++) new_line[k] = mem[i][k];
                
                for (int k = j; k < j + get_int_len(num); k++) new_line[k] =  numberstring[k - j];
                
                for (int k = j + get_int_len(num); mem[i][k - get_int_len(num) - 1] != 0; k++) new_line[k] = mem[i][k - get_int_len(num)];

                delete [] mem[i];
                mem[i] = new_line;
                num++;
            }
        }
        cout << endl;
    }
    for (int i = 0; i < N; i++) {
        cout << mem[i] << endl;
    }

    return 0;
}