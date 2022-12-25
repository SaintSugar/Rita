#include <iostream>
#include <string.h>

#define WIDTH 2

using namespace std;

struct fio {
    char* name;
    char* surname;
    char* father;
};

struct date {
    int day;
    char* month;
    int year;
};

struct book {
    fio FIO;
    date Birth;
    char *Title;
    char *Publish;
    int Year;
};

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
    cout << "Surname: ";
    char buf[100];
    cin >> buf;
    Fio.surname = new char[strlen(buf)+1];
    strcpy(Fio.surname, buf);

    cout << "Name: ";
    cin >> buf;
    Fio.name = new char[strlen(buf)+1];
    strcpy(Fio.name, buf);

    cout << "Father: ";
    cin >> buf;
    Fio.father = new char[strlen(buf)+1];
    strcpy(Fio.father, buf);

    date Birth;
    cout << "Birth date: ";
    scanf("%d%s%d", &Birth.day, buf, &Birth.year);
    Birth.month = new char[strlen(buf) + 1];
    strcpy(Birth.month, buf);


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
char *fget_line(FILE *f) {
    char *buf = nullptr;
    char c = 0;
    int N = 0;
    while (true) {
        fscanf(f, "%c", &c);
        if (c == '\n' && N > 0) break;
        else if (c == '\n' && N == 0) {
            while (c == '\n') {
                fscanf(f, "%c", &c);
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
int LoadLibrary(book **library, int *N, char *filename) {
    FILE *f = fopen(filename, "r");
    if (f == nullptr) {
        return -1;
    }
    delete (*library);
    fscanf(f, "%d", N);
    (*library) = new book[*N];
    char buf[100];
    for (int i = 0; i < *N; i++) {
        /*fio Fio;
        fscanf(f, "%s", buf);
        Fio.name = new char[strlen(buf)+1];
        strcpy(Fio.name, buf);

        fscanf(f, "%s", buf);
        Fio.surname = new char[strlen(buf)+1];
        strcpy(Fio.surname, buf);

        fscanf(f, "%s", buf);
        Fio.father = new char[strlen(buf)+1];
        strcpy(Fio.father, buf);


        date Birth;
        int year;
        fscanf(f, "%d%s%d%d", &Birth.day, buf, &Birth.year, &year);
        Birth.month = new char[strlen(buf) + 1];
        strcpy(Birth.month, buf);


        char *title;
        fgets(buf, 1000, f);
        title = new char[strlen(buf)];
        strcpy(title, buf);
        title[strlen(buf) - 1] = '\0';

        char *p_h;
        fgets(buf, 1000, f);
        p_h = new char[strlen(buf)];
        strcpy(p_h, buf);
        p_h[strlen(buf) - 1] = '\0';

        */
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

int main() {
    book *library = nullptr;
    int N = 0;
    N = LoadLibrary(&library, &N, "ldb.ldb");
    int *f = new int[N+1];
    f[0] = N;
    for(int i = 0; i < N; i++)
        f[i+1] = i;
    Information(library, f);
    AddBook(&library, &N);
    SaveLibrary(library, N, "ldb.ldb");
    return 0;

}
