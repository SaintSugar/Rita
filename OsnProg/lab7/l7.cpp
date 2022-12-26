#include <iostream>
#include <string.h>

#define WIDTH 2

using namespace std;
struct date {
    int day;
    char *month;
    int year;
};
struct fio {
    char *surname;
    char *name;
    char *father;
};

struct book {
    fio FIO;
    date Birth;
    char *Title;
    char *Publish;
    int Year;
};

date Read_Date() {
    date Birthdate;
    int day;
    char buf[20];
    int year;

    cin >> day >> buf >> year;
    Birthdate.day = day;
    Birthdate.year = year;

    char *month = new char(strlen(buf)+1);
    strcpy(month, buf);
    Birthdate.month = month;
    return(Birthdate);
}

fio Read_FIO() {
    fio FIO;
    cout << "Full name" << endl;
    char buf_surname[50];
    char buf_name[50];
    char buf_father[50];
    cin >> buf_surname >> buf_name >> buf_father;
    char *surname = new char(strlen(buf_surname)+1);
    char *name = new char(strlen(buf_name)+1);
    char *father = new char(strlen(buf_father)+1);
    strcpy(surname, buf_surname);
    strcpy(name, buf_name);
    strcpy(father, buf_father);
    FIO.surname = surname;
    FIO.name = name;
    FIO.father = father;
    return(FIO);
}

char *get_line() {
    char *buf = nullptr;
    char c = 0;
    int N = 0;
    while (true) {
        scanf("%c", &c);
        if (c == '\n' && N > 0) break;
        else if (c == '\n' && N == 0) {
            while (c == '\n') {
                scanf("%c", &c);
            }
        }
        char *buf2 = new char[N + 2];
        for (int i = 0; i < N; i++) buf2[i] = buf[i];
        buf2[N] = c;
        buf2[N + 1] = '\0';
        delete buf;
        buf = buf2;
        N++;
    }
    return buf;
}

void Pause() {
    cout << "Press Enter to continue...";
    char c;
    scanf("%c", &c);   
}

void AddBook(book **library, int *N) {
    fio Fio;
    Fio = Read_FIO();
    
    date Birth;
    cout << "Birtdate" << endl;
    Birth = Read_Date();
    
    cout << "Title: ";
    char *title;
    title = get_line();

    cout << "Publising house: ";
    char *p_h;
    p_h = get_line();

    cout << "Year: ";
    int year;
    cin >> year;

    book Book;
    Book.FIO = Fio;
    Book.Birth = Birth;
    Book.Title = title;
    Book.Publish = p_h;
    Book.Year = year;
    *N += 1;
    book *memory = new book[*N];
    for (int i = 0; i < (*N) - 1; i++) 
        memory[i] = (*library)[i];
    memory[(*N)-1] = Book;
    delete *library;
    *library = memory;    
}

int IntLength (int Y) {
    int k = 0;
    while (Y != 0) {
        Y = Y/10;
        k++;
    }
    return k;
}

book MaximusBookus(book *library, int *index){
    int N = index[0];
    book SUS = library[index[1]];
    for (int i = 1; i <= N; i++) {
        int k = index[i];
        if (strlen(library[k].FIO.surname) > strlen(SUS.FIO.surname))
            SUS.FIO.surname = library[k].FIO.surname;
        if (strlen(library[k].FIO.name) > strlen(SUS.FIO.name))
            SUS.FIO.name = library[k].FIO.name;
        if (strlen(library[k].FIO.father) > strlen(SUS.FIO.father))
            SUS.FIO.father = library[k].FIO.father;

        if (library[k].Birth.day > SUS.Birth.day)
            SUS.Birth.day = library[k].Birth.day;
        if (library[k].Birth.year > SUS.Birth.year)
            SUS.Birth.year = library[k].Birth.year; 
        if (strlen(library[k].Birth.month) > strlen(SUS.Birth.month))
            SUS.Birth.month = library[k].Birth.month;
        
        if (strlen(library[k].Title) > strlen(SUS.Title))
            SUS.Title = library[k].Title;
        if (strlen(library[k].Publish) > strlen(SUS.Publish))
            SUS.Publish = library[k].Publish;
        if (library[k].Year > SUS.Year)
            SUS.Year = library[k].Year;            
    }
    SUS.Year = IntLength(SUS.Year);
    SUS.Birth.day = IntLength(SUS.Birth.day) + strlen(SUS.Birth.month) + IntLength(SUS.Birth.year) + 2;
    return SUS;
}

void PrintChar(char c, int times) {
    for (int i = 0; i < times; i++)
        cout << c;
}

int Information(book *library, int *index) {
    if (index[0] == 0) {
        cout << "Zero elements found by your request :c" << endl;
        return -1;
    }

    book MaximumBook = MaximusBookus(library, index);
    
    char TitleSurname[] = "Surname";
    char TitleName[] = "Name";
    char TitleFather[] = "Father";

    char TitleBirth[] = "Birthdate";

    char TitleBook[] = "Book title";
    char TitlePublisher[] = "Publisher";
    char TitleYear[] = "Year";

    if (strlen(TitleName) > strlen(MaximumBook.FIO.name))
        MaximumBook.FIO.name = TitleName;
    if (strlen(TitleSurname) > strlen(MaximumBook.FIO.surname))
        MaximumBook.FIO.surname = TitleSurname;
    if (strlen(TitleFather) > strlen(MaximumBook.FIO.father))
        MaximumBook.FIO.father = TitleFather;

    if (strlen(TitleBirth) > MaximumBook.Birth.day)
        MaximumBook.Birth.day = strlen(TitleBirth);

    if (strlen(TitleBook) > strlen(MaximumBook.Title))
        MaximumBook.Title = TitleBook;
    if (strlen(TitlePublisher) > strlen(MaximumBook.Publish))
        MaximumBook.Publish = TitlePublisher;
    if (strlen(TitleYear) > MaximumBook.Year)
        MaximumBook.Year = strlen(TitleYear);
    
    int Tabs[7];
    Tabs[0] = strlen(MaximumBook.FIO.surname) / 8 + WIDTH;
    Tabs[1] = strlen(MaximumBook.FIO.name) / 8 + WIDTH;
    Tabs[2] = strlen(MaximumBook.FIO.father) / 8 + WIDTH;

    Tabs[3] = (MaximumBook.Birth.day) / 8 + WIDTH;
    
    Tabs[4] = strlen(MaximumBook.Title) / 8 + WIDTH;
    Tabs[5] = strlen(MaximumBook.Publish) / 8 + WIDTH;
    Tabs[6] = MaximumBook.Year / 8 + WIDTH;

    cout << TitleSurname;
    PrintChar('\t' ,Tabs[0] - strlen(TitleSurname) / 8);
    
    cout << TitleName;
    PrintChar('\t' ,Tabs[1] - strlen(TitleName) / 8);

    cout << TitleFather;
    PrintChar('\t' ,Tabs[2] - strlen(TitleFather) / 8);

    cout << TitleBirth;
    PrintChar('\t' ,Tabs[3] - strlen(TitleBirth) / 8);
    
    cout << TitleBook;
    PrintChar('\t' ,Tabs[4] - strlen(TitleBook) / 8);
    
    cout << TitlePublisher;
    PrintChar('\t' ,Tabs[5] - strlen(TitlePublisher) / 8);
    
    cout << TitleYear;
    PrintChar('\t' ,Tabs[6] - strlen(TitleYear) / 8);

    cout << endl;

    PrintChar('_', (Tabs[0] + Tabs[1] + Tabs[2] + Tabs[3] + Tabs[4] + Tabs[5] + Tabs[6]) * 8);
    
    cout << endl << endl;

    int N=index[0];
    int k;
    for (int i = 1; i <= N; i++) {
        k = index[i];
        cout << library[k].FIO.surname;
        PrintChar('\t' ,Tabs[0] - strlen(library[k].FIO.surname) / 8);
        
        cout << library[k].FIO.name;
        PrintChar('\t' ,Tabs[1] - strlen(library[k].FIO.name) / 8);

        cout << library[k].FIO.father;
        PrintChar('\t', Tabs[2] - strlen(library[k].FIO.father) / 8);

        cout << library[k].Birth.day << " " << library[k].Birth.month << " " << library[k].Birth.year;
        PrintChar('\t', Tabs[3] - (strlen(library[k].Birth.month) + IntLength(library[k].Birth.day) + IntLength(library[k].Birth.year) + 2) / 8);
        
        cout << library[k].Title;
        PrintChar('\t' ,Tabs[4] - strlen(library[k].Title) / 8);
        
        cout << library[k].Publish;
        PrintChar('\t' ,Tabs[5] - strlen(library[k].Publish) / 8);
        
        cout << library[k].Year;
        PrintChar('\t' ,Tabs[6] - library[k].Year / 8);

        cout << endl << endl;
    }
    return 0;
}


int *Find_Book_by_Title(book *library, int N, char *Title) {
    int *index = new int [1];
    index[0] = 0;
    for (int i = 0; i < N; i++) {
        if (strcmp(library[i].Title, Title) == 0) {
            index[0]++;
            int *el = new int [index[0]+1];
            for (int j = 0; j < index[0]; j++) 
                el[j] = index[j];
            el[index[0]] = i;
            delete index;
            index = el;
        } 
    }
    return index;
}

int *Find_Book_by_Autor(book *library, int N, char *Surname, char *Name, char *Father) {
    int *index = new int [1];
    index[0] = 0;
    for (int i = 0; i < N; i++) {
        if (strcmp(library[i].FIO.surname, Surname) == 0 && strcmp(library[i].FIO.name, Name) == 0 && strcmp(library[i].FIO.father, Father) == 0) {
            index[0]++;
            int *el = new int [index[0]+1];
            for (int j = 0; j < index[0]; j++) 
                el[j] = index[j];
            el[index[0]] = i;
            delete index;
            index = el;
        } 
    }
    return index;
}

int *Find_Book_by_Publisher(book *library, int N, char *p_h) {
    int *index = new int [1];
    index[0] = 0;
    for (int i = 0; i < N; i++) {
        if (strcmp(library[i].Publish, p_h) == 0) {
            index[0]++;
            int *el = new int [index[0]+1];
            for (int j = 0; j < index[0]; j++) 
                el[j] = index[j];
            el[index[0]] = i;
            delete index;
            index = el;
        } 
    }
    return index;
}



int MonthToInt(date M) {
    if (strcmp(M.month, "january") == 0 || strcmp(M.month, "January") == 0) return 1;
    if (strcmp(M.month, "february") == 0 || strcmp(M.month, "February") == 0) return 2;
    if (strcmp(M.month, "march") == 0 || strcmp(M.month, "March") == 0) return 3;
    if (strcmp(M.month, "april") == 0 || strcmp(M.month, "April") == 0) return 4;
    if (strcmp(M.month, "may") == 0 || strcmp(M.month, "May") == 0) return 5;
    if (strcmp(M.month, "june") == 0 || strcmp(M.month, "June") == 0) return 6;
    if (strcmp(M.month, "july") == 0 || strcmp(M.month, "July") == 0) return 7;
    if (strcmp(M.month, "august") == 0 || strcmp(M.month, "August") == 0) return 8;
    if (strcmp(M.month, "september") == 0 || strcmp(M.month, "September") == 0) return 9;
    if (strcmp(M.month, "october") == 0 || strcmp(M.month, "October") == 0) return 10;
    if (strcmp(M.month, "november") == 0 || strcmp(M.month, "November") == 0) return 11;
    if (strcmp(M.month, "december") == 0 || strcmp(M.month, "December") == 0) return 12;
    return (-1);
}

int Age(date Birth, date Current) {
    int Age = Current.year - Birth.year;
    int CurrentMonth, BirthMonth;
    CurrentMonth = MonthToInt(Current);
    BirthMonth = MonthToInt(Birth);
    if (CurrentMonth > BirthMonth) return Age;
    else if (CurrentMonth < BirthMonth) return (Age-1);
    if (Current.day < Birth.day) return (Age - 1);
    return Age;
}

bool Is_Retirement_Age(date Birth, date Current, int tooOldAge) {
    int Author_Age = Age(Birth, Current);
    if (Author_Age >= tooOldAge) return true;
    return false;
}

int *Find_Retirement_Age_Author(book *library, int N, date Current) {
    int *index = new int [1];
    index[0] = 0;
    for (int i = 0; i < N; i++) {
        if (Is_Retirement_Age(library[i].Birth, Current, 60)) {
            index[0]++;
            int *el = new int [index[0]+1];
            for (int j = 0; j < index[0]; j++) 
                el[j] = index[j];
            el[index[0]] = i;
            delete index;
            index = el;
        } 
    }
    return index;
}

int *Sort_Author(book *library, int *array_of_indexs) {
    int *index = array_of_indexs;

    int *author_index = new int [1];
    author_index[0] = 0;

    for (int i = 1; i <= index[0]; i++) {
        bool flag = true;
        for (int j = 1; j <= author_index[0]; j++) {
            if (strcasecmp(library[index[i]].FIO.surname, library[author_index[j]].FIO.surname) == 0 && strcasecmp(library[index[i]].FIO.name, library[author_index[j]].FIO.name) == 0 && strcasecmp(library[index[i]].FIO.father, library[author_index[j]].FIO.father) == 0) {
                flag = false;
                break;
            }
        }
        if (flag) {
            author_index[0]++;
            int *new_author = new int[author_index[0] + 1];
            for (int j = 0; j < author_index[0]; j++)
                new_author[j] = author_index[j];
            new_author[author_index[0]] = index[i];
            delete author_index;
            author_index = new_author;
        } 
    }
    delete index;

    for (int i = 0; i <= author_index[0]; i++) {
        for (int j = 2; j <= author_index[0] - i; j++) {

            bool surname1 = strcasecmp(library[author_index[j]].FIO.surname, library[author_index[j - 1]].FIO.surname) < 0;
            bool surname0 = strcasecmp(library[author_index[j]].FIO.surname, library[author_index[j - 1]].FIO.surname) == 0;
            bool name1 = strcasecmp(library[author_index[j]].FIO.name, library[author_index[j - 1]].FIO.name) < 0;
            bool name0 = strcasecmp(library[author_index[j]].FIO.name, library[author_index[j - 1]].FIO.name) == 0;
            bool father1 = strcasecmp(library[author_index[j]].FIO.father, library[author_index[j - 1]].FIO.father) < 0;
                        
            if (surname1 || (surname0 && name1) || (surname0 && name0 && father1)) {
                int buf = author_index[j];
                author_index[j] = author_index[j - 1];
                author_index[j - 1] = buf;
            }
        }
    }
    if (author_index[0] == 0) {
        cout << endl <<"No authors found!" << endl << endl;
        return nullptr;
    }
    cout << endl <<"List of authors:" << endl << endl;
    for (int i = 1; i <= author_index[0]; i++) {
        cout << library[author_index[i]].FIO.surname << " " << library[author_index[i]].FIO.name << " " << library[author_index[i]].FIO.father << endl << endl;
    }
    return author_index;
}

int SaveLibrary (book *library, int N, char *filename) {
    FILE *f = fopen(filename, "w");
    if (f == nullptr) {
        return -1;
    }
    fprintf(f, "%d\n", N);
    book Book;
    for (int i = 0; i < N; i++) {
        Book = library[i];
        fprintf(f, "%s\n%s\n%s\n%d\n%s\n%d\n%d\n%s\n%s\n",
        Book.FIO.name, Book.FIO.surname, Book.FIO.father, 
        Book.Birth.day, Book.Birth.month, Book.Birth.year,
        Book.Year,
        Book.Title, 
        Book.Publish
        );
    }
    fclose(f);
    return 0;
}


int LoadLibrary(book **library, int *N, char *filename) {
    FILE *f = fopen(filename, "r");
    if (f == nullptr) {
        return 0;
    }
    delete (*library);
    fscanf(f, "%d", N);
    (*library) = new book[*N];
    char buf[100];
    for (int i = 0; i < *N; i++) {        
        book Book;
        char name[100], surname[100], father[100], month[100];
        char *title;
        fscanf(f, "%s%s%s%d%s%d%d\n",
        name, surname, father, 
        &Book.Birth.day, month, &Book.Birth.year,
        &Book.Year
        );
        Book.FIO.name = new char[strlen(name) + 1];
        Book.FIO.father = new char[strlen(father) + 1];
        Book.FIO.surname = new char[strlen(surname) + 1];
        Book.Birth.month = new char[strlen(month) + 1];

        strcpy(Book.FIO.name, name);
        strcpy(Book.FIO.surname, surname);
        strcpy(Book.FIO.father, father);
        strcpy(Book.Birth.month, month);

        
        fgets(buf, 1000, f);
        title = new char[strlen(buf)];
        strcpy(title, buf);
        title[strlen(buf) - 1] = '\0';

        Book.Title = title;

        char *p_h;
        fgets(buf, 1000, f);
        p_h = new char[strlen(buf)];
        strcpy(p_h, buf);
        p_h[strlen(buf) - 1] = '\0';

        Book.Publish = p_h;
       
        cout << Book.FIO.surname << Book.FIO.name << Book.FIO.father << Book.Birth.day << Book.Birth.month << Book.Birth.year << Book.Title << Book.Publish << Book.Year << endl;
        (*library)[i] = Book;
    }

    fclose(f);
    return *N;
}

void ShowAllLibrary (book *library, int N) {
    int *f = new int[N+1];
    f[0] = N;
    for(int i = 0; i < N; i++)
        f[i+1] = i;
    Information(library, f);
}

int menu(book **library, int *N) {
    cout << "Library(book)" <<endl << endl;
    while (true) {
        int num;
        cout << "Add new book..............................1\n";
        cout << "Get information about the book............2\n";
        cout << "Find all books of the autor...............3\n";
        cout << "Find all autors of the piblishing house...4\n";
        cout << "Find all authors of retirement age........5\n";
        cout << "Show all books............................6\n";
        cout << "Exit the program..........................7\n";
        cout << "..........................................\n";
        cout << "Enter the number of function: ";
        scanf("%d", &num);
        switch (num) {
            case 1: {
                AddBook(library, N);
                break;
            }
            case 2: {
                cout << "Enter the title: ";
                char *buf;
                buf = get_line();
                int *index = Find_Book_by_Title(*library, *N, buf);
                Information(*library, index);
                delete index;
                delete buf;
                Pause();
                break;
            }
            case 3: {
                cout << "Enter author's full name ";
                char sbuf[100];
                char nbuf[100];
                char fbuf[100];
                cin >> sbuf >> nbuf >> fbuf;
                int *index = Find_Book_by_Autor(*library, *N, sbuf, nbuf, fbuf);
                Information(*library, index);
                delete index;
                Pause();
                char c;
                scanf("%c", &c);
                break;
            }
            case 4: {
                cout << "Enter the publisher's name: ";
                char *buf;
                buf = get_line();
                int *index = Find_Book_by_Publisher(*library, *N, buf);
                int *authors = Sort_Author(*library, index);
                delete authors;
                delete buf;
                delete index;
                Pause();
                break;
            }
            case 5: {
                cout << "Enter the current date: ";
                date current = Read_Date();
                int *index = Find_Retirement_Age_Author(*library, *N, current);
                int *authors = Sort_Author(*library, index);
                delete authors;
                delete index;
                Pause();
                char c;
                scanf("%c", &c);
                break;

            }
            case 7: {
                cout << "Program is over.";
                return 0;
            }
            case 6: {
                ShowAllLibrary(*library, *N);
                Pause();
                char c;
                scanf("%c", &c);
            }
        }
        cout << endl;
    }
}

int main() {
    book *library = nullptr;
    int N = 0;
    N = LoadLibrary(&library, &N, "Lib");    
    menu(&library, &N);
    SaveLibrary(library, N, "Lib");
    return 0;
}


