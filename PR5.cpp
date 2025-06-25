#include <iostream>
#include <string>
#include <vector>
#include <regex>
#include <stdexcept>

using namespace std;

class LibraryItem {
private:
    string title;
    string author;
    string dueDate;

public:
    virtual ~LibraryItem() {}

    string getTitle() const { return title; }
    string getAuthor() const { return author; }
    string getDueDate() const { return dueDate; }

    void setTitle(string newTitle) { title = newTitle; }
    void setAuthor(string newAuthor) { author = newAuthor; }
    void setDueDate(string newDueDate) { dueDate = newDueDate; }

    virtual void checkOut() = 0;
    virtual void returnItem() = 0;
    virtual void displayDetails() const = 0;
};

class Book : public LibraryItem {
private:
    string isbn;

public:
    Book(string title, string author, string dueDate, string isbn) {
        setTitle(title);
        setAuthor(author);
        setDueDate(dueDate);
        if (!regex_match(isbn, regex("[0-9]{10}|[0-9]{13}"))) {
            throw invalid_argument("Invalid ISBN format.");
        }
        this->isbn = isbn;
    }

    void checkOut() override {
        cout << "Book \"" << getTitle() << "\" checked out.\n";
    }

    void returnItem() override {
        cout << "Book \"" << getTitle() << "\" returned.\n";
    }

    void displayDetails() const override {
        cout << "[Book] Title: " << getTitle()
             << ", Author: " << getAuthor()
             << ", Due Date: " << getDueDate()
             << ", ISBN: " << isbn << endl;
    }
};

class DVD : public LibraryItem {
private:
    int duration;

public:
    DVD(string title, string author, string dueDate, int duration) {
        if (duration < 0)
            throw invalid_argument("Duration cannot be negative.");
        setTitle(title);
        setAuthor(author);
        setDueDate(dueDate);
        this->duration = duration;
    }

    void checkOut() override {
        cout << "DVD \"" << getTitle() << "\" checked out.\n";
    }

    void returnItem() override {
        cout << "DVD \"" << getTitle() << "\" returned.\n";
    }

    void displayDetails() const override {
        cout << "[DVD] Title: " << getTitle()
             << ", Author: " << getAuthor()
             << ", Due Date: " << getDueDate()
             << ", Duration: " << duration << " minutes" << endl;
    }
};

class Magazine : public LibraryItem {
private:
    int issueNumber;

public:
    Magazine(string title, string author, string dueDate, int issueNumber) {
        if (issueNumber < 0)
            throw invalid_argument("Issue number cannot be negative.");
        setTitle(title);
        setAuthor(author);
        setDueDate(dueDate);
        this->issueNumber = issueNumber;
    }

    void checkOut() override {
        cout << "Magazine \"" << getTitle() << "\" checked out.\n";
    }

    void returnItem() override {
        cout << "Magazine \"" << getTitle() << "\" returned.\n";
    }

    void displayDetails() const override {
        cout << "[Magazine] Title: " << getTitle()
             << ", Author: " << getAuthor()
             << ", Due Date: " << getDueDate()
             << ", Issue #: " << issueNumber << endl;
    }
};

void menu() {
    vector<LibraryItem*> libraryItems;

    int choice;
    do {
        cout << "\n---- Library Management System ----\n";
        cout << "1. Add Book\n2. Add DVD\n3. Add Magazine\n";
        cout << "4. Display All Items\n5. Check Out Item\n6. Return Item\n7. Exit\n";
        cout << "Enter your choice: ";
        cin >> choice;

        try {
            if (choice == 1) {
                string title, author, dueDate, isbn;
                cin.ignore();
                cout << "Enter title: ";
                getline(cin, title);
                cout << "Enter author: ";
                getline(cin, author);
                cout << "Enter due date: ";
                getline(cin, dueDate);
                cout << "Enter ISBN (10 or 13 digits): ";
                getline(cin, isbn);
                libraryItems.push_back(new Book(title, author, dueDate, isbn));
                cout << "Book added.\n";
            }
            else if (choice == 2) {
                string title, author, dueDate;
                int duration;
                cin.ignore();
                cout << "Enter title: ";
                getline(cin, title);
                cout << "Enter author: ";
                getline(cin, author);
                cout << "Enter due date: ";
                getline(cin, dueDate);
                cout << "Enter duration (in minutes): ";
                cin >> duration;
                libraryItems.push_back(new DVD(title, author, dueDate, duration));
                cout << "DVD added.\n";
            }
            else if (choice == 3) {
                string title, author, dueDate;
                int issueNumber;
                cin.ignore();
                cout << "Enter title: ";
                getline(cin, title);
                cout << "Enter author: ";
                getline(cin, author);
                cout << "Enter due date: ";
                getline(cin, dueDate);
                cout << "Enter issue number: ";
                cin >> issueNumber;
                libraryItems.push_back(new Magazine(title, author, dueDate, issueNumber));
                cout << "Magazine added.\n";
            }
            else if (choice == 4) {
                cout << "\nLibrary Items:\n";
                for (auto item : libraryItems)
                    item->displayDetails();
            }
            else if (choice == 5) {
                int idx;
                cout << "Enter item number to check out (1 to " << libraryItems.size() << "): ";
                cin >> idx;
                if (idx < 1 || idx > libraryItems.size())
                    throw out_of_range("Invalid item number.");
                libraryItems[idx - 1]->checkOut();
            }
            else if (choice == 6) 
			{
                int idx;
                cout << "Enter item number to return (1 to " << libraryItems.size() << "): ";
                cin >> idx;
                if (idx < 1 || idx > libraryItems.size())
                    throw out_of_range("Invalid item number.");
                libraryItems[idx - 1]->returnItem();
            }
            else if (choice == 7) 
			{
                cout << "Exiting...\n";
            }
            else 
			{
                cout << "Invalid option. Try again.\n";
            }
        } catch (exception& e) 
		{
            cerr << "Error: " << e.what() << endl;
        }

    } while (choice != 7);

    for (auto item : libraryItems)
        delete item;
}

int main() 
{
    menu();
}
/*
output:---- Library Management System ----
1. Add Book
2. Add DVD
3. Add Magazine
4. Display All Items
5. Check Out Item
6. Return Item
7. Exit
Enter your choice: 2
Enter title: 3
Enter author: 4
Enter due date: 2
Enter duration (in minutes): 2
DVD added.

---- Library Management System ----
1. Add Book
2. Add DVD
3. Add Magazine
4. Display All Items
5. Check Out Item
6. Return Item
7. Exit
*/
