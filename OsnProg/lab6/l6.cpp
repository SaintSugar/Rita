#include <iostream>
#include <string.h>

#define WIDTH 2

using namespace std;


struct book {
    char *Surname;
    char *Name;
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
    cout << "Surname: ";
    char *surname;
    char buf[100];
    cin >> buf;
    surname = new char[strlen(buf)+1];
    strcpy(surname, buf);

    cout << "Name: ";
    char *name;
    cin >> buf;
    name = new char[strlen(buf)+1];
    strcpy(name, buf);


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
    Book.Surname = surname;
    Book.Name = name;
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
        if (strlen(library[k].Surname) > strlen(SUS.Surname))
            SUS.Surname = library[k].Surname;
        if (strlen(library[k].Name) > strlen(SUS.Name))
            SUS.Name = library[k].Name;
        if (strlen(library[k].Title) > strlen(SUS.Title))
            SUS.Title = library[k].Title;
        if (strlen(library[k].Publish) > strlen(SUS.Publish))
            SUS.Publish = library[k].Publish;
        if (library[k].Year > SUS.Year)
            SUS.Year = library[k].Year;            
    }
    SUS.Year = IntLength(SUS.Year);
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
    char TitleBook[] = "Book title";
    char TitlePublisher[] = "Publisher";
    char TitleYear[] = "Year";

    if (strlen(TitleName) > strlen(MaximumBook.Name))
        MaximumBook.Name = TitleName;
    if (strlen(TitleSurname) > strlen(MaximumBook.Surname))
        MaximumBook.Surname = TitleSurname;
    if (strlen(TitleBook) > strlen(MaximumBook.Title))
        MaximumBook.Title = TitleBook;
    if (strlen(TitlePublisher) > strlen(MaximumBook.Publish))
        MaximumBook.Publish = TitlePublisher;
    if (strlen(TitleYear) > MaximumBook.Year)
        MaximumBook.Year = strlen(TitleYear);
    
    int Tabs[5];
    Tabs[0] = strlen(MaximumBook.Surname) / 8 + WIDTH;
    Tabs[1] = strlen(MaximumBook.Name) / 8 + WIDTH;
    Tabs[2] = strlen(MaximumBook.Title) / 8 + WIDTH;
    Tabs[3] = strlen(MaximumBook.Publish) / 8 + WIDTH;
    Tabs[4] = MaximumBook.Year / 8 + WIDTH;

    cout << TitleSurname;
    PrintChar('\t' ,Tabs[0] - strlen(TitleSurname) / 8);
    
    cout << TitleName;
    PrintChar('\t' ,Tabs[1] - strlen(TitleName) / 8);
    
    cout << TitleBook;
    PrintChar('\t' ,Tabs[2] - strlen(TitleBook) / 8);
    
    cout << TitlePublisher;
    PrintChar('\t' ,Tabs[3] - strlen(TitlePublisher) / 8);
    
    cout << TitleYear;
    PrintChar('\t' ,Tabs[4] - strlen(TitleYear) / 8);

    cout << endl;

    PrintChar('_', (Tabs[0] + Tabs[1] + Tabs[2] + Tabs[3] + Tabs[4]) * 8);
    
    cout << endl << endl;

    int N=index[0];
    int k;
    for (int i = 1; i <= N; i++) {
        k = index[i];
        cout << library[k].Surname;
        PrintChar('\t' ,Tabs[0] - strlen(library[k].Surname) / 8);
        
        cout << library[k].Name;
        PrintChar('\t' ,Tabs[1] - strlen(library[k].Name) / 8);
        
        cout << library[k].Title;
        PrintChar('\t' ,Tabs[2] - strlen(library[k].Title) / 8);
        
        cout << library[k].Publish;
        PrintChar('\t' ,Tabs[3] - strlen(library[k].Publish) / 8);
        
        cout << library[k].Year;
        PrintChar('\t' ,Tabs[4] - library[k].Year / 8);

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

int *Find_Book_by_Autor(book *library, int N, char *Name, char *Surname) {
    int *index = new int [1];
    index[0] = 0;
    for (int i = 0; i < N; i++) {
        if (strcmp(library[i].Name, Name) == 0 && strcmp(library[i].Surname, Surname) == 0) {
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

int *Sort_Author(book *library, int N, char *p_h) {
    int *index = Find_Book_by_Publisher(library, N, p_h);

    int *author_index = new int [1];
    author_index[0] = 0;

    for (int i = 1; i <= index[0]; i++) {
        bool flag = true;
        for (int j = 1; j <= author_index[0]; j++) {
            if (strcasecmp(library[index[i]].Name, library[author_index[j]].Name) == 0 && strcasecmp(library[index[i]].Surname, library[author_index[j]].Surname) == 0) {
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

            bool name1 = strcasecmp(library[author_index[j]].Name, library[author_index[j - 1]].Name) < 0;
            bool name0 = strcasecmp(library[author_index[j]].Name, library[author_index[j - 1]].Name) == 0;
            bool surname1 = strcasecmp(library[author_index[j]].Surname, library[author_index[j - 1]].Surname) < 0;
            bool surname0 = strcasecmp(library[author_index[j]].Surname, library[author_index[j - 1]].Surname) == 0;

            if (surname1 || (surname0 && name1)) {
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
        cout << library[author_index[i]].Surname << " " << library[author_index[i]].Name << endl << endl;
    }
    return author_index;
}
int menu(book **library, int *N) {
    cout << "Library(book)" <<endl << endl;
    while (true) {
        int num;
        cout << "Add new book..............................1\n";
        cout << "Get information about the book............2\n";
        cout << "Find all books of the autor...............3\n";
        cout << "Find all autors of the piblishing house...4\n";
        cout << "Exit the program..........................5\n";
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
                cout << "Enter author's name and surname: ";
                char nbuf[100];
                cin >> nbuf;
                char sbuf[100];
                cin >> sbuf;
                int *index = Find_Book_by_Autor(*library, *N, nbuf, sbuf);
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
                int *authors = Sort_Author(*library, *N, buf);
                delete authors;
                delete buf;
                Pause();
                break;
            }
            case 5: {
                cout << "Program is over.";
                return 0;
            }
            case 6: {
                int a[100];
                a[0] = *N;
                for (int i = 1; i <= a[0]; i++) {
                    a[i] = i - 1;
                }
                Information(*library, a);
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
    menu(&library, &N);
    return 0;
}
