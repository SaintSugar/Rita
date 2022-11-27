#include <iostream>
#include <string.h>
using namespace std;


struct credit
    {	int 	id; 
        char* 	first_name;		
        char* 	second_name;		
        double  sum;
        int 	interest;
    };


credit* add(credit *Ptr, int i) {
    cout << "--------------------\n";
    if (i > 0)
    {
        credit *Buff_database = new credit[i+1];
        for (int j = 0; j < i; j++)
        {
            Buff_database[j] = Ptr[j];
        }
        delete[] Ptr;
        Ptr = Buff_database;
    } else {
        Ptr = new credit[1];
    }    

    char buff[20];

    cout << "New account:\nNumber: ";
    cin >> Ptr[i].id;

    cout << "\nFirst name: ";
    cin >> buff;
    Ptr[i].first_name = new char[strlen(buff) + 1];
    strcpy(Ptr[i].first_name, buff);

    cout << "\nSecond name: ";
    cin >> buff;
    Ptr[i].second_name = new char[strlen(buff) + 1];
    strcpy(Ptr[i].second_name, buff);

    cout << "\nSum: ";
    cin >> Ptr[i].sum;

    cout << "\nInterest: ";
    cin >> Ptr[i].interest;

    return Ptr;
}


void info_line(credit *Ptr, int k) {
    cout << Ptr[k].id;
    if (Ptr[k].id < 10000000) {cout << "\t";}
    else {cout << " | ";}  

    int l;
    cout << Ptr[k].first_name;
    l = strlen(Ptr[k].first_name);
    if (l < 8) {cout << "\t\t";}
    else if (l < 12 && l >= 8) {cout << "\t";}
    else {cout << " | ";} 

    cout << Ptr[k].second_name;
    l = strlen(Ptr[k].second_name);
    if (l < 8) {cout << "\t\t";}
    else if (l < 12 && l >= 8) {cout << "\t";}
    else {cout << " | ";} 

    cout << Ptr[k].sum;
    if (Ptr[k].sum < 10000000) {cout << "\t";}
    else {cout << " | ";} 

    cout << Ptr[k].interest << "\n";
}


void ID_info(credit *Ptr, int n) {
    int k = 0, ID;
    cout << "--------------------\n";
    cout << "Input client ID: ";
    cin >> ID;

    cout << "\n- - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -\n";
    cout << "ID\tFirst name\tSecond name\tSum\tInterest\n";
    cout << "- - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -\n";
    
    for (int i = 0; i < n; i++)
    {
        if (Ptr[i].id == ID)
        {
            info_line(Ptr, i);
            k++;
        }
    }
    cout << "- - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -\n";
    cout << "Number of records: " << k << "\n\n";
}


void search(credit *Ptr, int n) {
    cout << "--------------------\n";
    cout << "Input first and second name: ";

    char f_name[20];
    cin >> f_name;

    char s_name[20];
    cin >> s_name;

    double Sum = 0;
    bool Found = false;

    cout << "\nIDs ";
    for (int i = 0; i < n; i++)
    {
        if (!strcmp(Ptr[i].first_name, f_name) && !strcmp(Ptr[i].second_name, s_name))
        {
            Found = true;
            Sum += Ptr[i].sum;
            cout << Ptr[i].id << " ";
        }
    }
    
    if (!Found)
    {
        cout << "are not located.";
    } else {
        cout << "\nSum: " << Sum;
    }
    cout << "\n\n";
}

void search_interest(credit *Database, int N) {
    cout << "--------------------\n";
    cout << "Input interest: ";
    int Interest;
    cin >> Interest;

    credit *Answer = new credit[N];
    int AnsN = 0;
    cout << "\nClients:\n";
    for (int i = 0; i < N; i++) {
        if (Database[i].interest == Interest) {
            bool flag = true;
            for (int j = 0; j < AnsN; j++) {
                if (strcmp(Database[i].first_name, Answer[j].first_name) == 0 && strcmp(Database[i].second_name, Answer[j].second_name) == 0) {
                    flag = false;
                    break;
                }
            }
            if (flag) {
                Answer[AnsN] = Database[i];
                cout << Answer[AnsN].first_name << " " << Answer[AnsN].second_name << endl;
                AnsN++;
            }
        }
    }
    if (AnsN == 0)
    {
        cout << "Not located.\n";
    }
    
    cout << endl;
}

void pause() {
    cout << "Press Enter to continue...";
    cin.get();
    cin.get();
}

void menu(credit *Database, int n) {
    char command;
    while (true) {
        cout << "###################################\n";
        cout << "\t\tMENU\n";
        cout << "###################################\n";
        cout << "1. Add new bill.\n";
        cout << "2. Print bill information.\n";
        cout << "3. Client bills information search.\n";
        cout << "4. Get clients by credit interest.\n";
        cout << "5. Exit.\n\n";
        cout << "Command: ";
        cin >> command;

        if (command == '5') {
            delete[] Database;
            cout << "\n####################################\n";
            cout << "# Thank you for trusting our bank! #" << endl;
            cout << "####################################\n\n";
            break;
        }
        else if (command == '1')
        {
            Database = add(Database, n);
            n++;
        }
        else if (command == '2')
        {
            ID_info(Database, n);
            pause();
        }
        else if (command == '3')
        {
            search(Database, n);
            pause();
        }
        else if (command == '4')
        {
            search_interest(Database, n);
            pause();
        }
        
    }
}


int main()
{
    int n;
    cout << "\nInput n: ";
    cin >> n;

    // Изначальный ввод базы данных
    credit *Database;
    for (int i = 0; i < n; i++)
    {
        Database = add(Database, i);
    }
    
    menu(Database, n);

    return 0;
}


//4 1 qwe rty 1000 2 2 asd fgh 10000 2 3 qwe rty 20 2 4 asd fgh 2325 10