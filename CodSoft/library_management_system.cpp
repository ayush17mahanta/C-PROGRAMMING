#include <iostream>
#include <vector>
#include <algorithm>
#include <ctime>
using namespace std;

struct Book {
    string title;
    string author;
    string ISBN;
    bool available;
};

struct Borrower {
    string name;
    int id;
    vector<Book*> borrowedBooks;
};

vector<Book> books;
vector<Borrower> borrowers;
int nextBorrowerId = 1;

void addBook() {
    Book newBook;
    cout << "Enter book title: ";
    getline(cin, newBook.title);
    cout << "Enter book author: ";
    getline(cin, newBook.author);
    cout << "Enter book ISBN: ";
    getline(cin, newBook.ISBN);
    newBook.available = true;
    books.push_back(newBook);
    cout << "Book added successfully!" << endl;
}

void searchBooks() {
    string keyword;
    cout << "Enter search keyword: ";
    cin.ignore();
    getline(cin, keyword);
    transform(keyword.begin(), keyword.end(), keyword.begin(), ::tolower);

    cout << "Search results:" << endl;
    for (const Book& book : books) {
        string title = book.title;
        string author = book.author;
        string ISBN = book.ISBN;
        transform(title.begin(), title.end(), title.begin(), ::tolower);
        transform(author.begin(), author.end(), author.begin(), ::tolower);
        transform(ISBN.begin(), ISBN.end(), ISBN.begin(), ::tolower);

        if (title.find(keyword) != string::npos ||
            author.find(keyword) != string::npos ||
            ISBN.find(keyword) != string::npos) {
            cout << "Title: " << book.title << ", Author: " << book.author << ", ISBN: " << book.ISBN << ", Available: " << (book.available ? "Yes" : "No") << endl;
        }
    }
}

void checkoutBook() {
    int borrowerId;
    cout << "Enter borrower ID: ";
    cin >> borrowerId;

    Borrower* borrower = nullptr;
    for (Borrower& b : borrowers) {
        if (b.id == borrowerId) {
            borrower = &b;
            break;
        }
    }

    if (borrower == nullptr) {
        cout << "Borrower not found." << endl;
        return;
    }

    string ISBN;
    cout << "Enter book ISBN to checkout: ";
    cin.ignore();
    getline(cin, ISBN);

    for (Book& book : books) {
        if (book.ISBN == ISBN && book.available) {
            book.available = false;
            borrower->borrowedBooks.push_back(&book);
            cout << "Book checked out successfully!" << endl;
            return;
        }
    }

    cout << "Book not available." << endl;
}

void returnBook() {
    string ISBN;
    cout << "Enter book ISBN to return: ";
    cin.ignore();
    getline(cin, ISBN);

    for (Book& book : books) {
        if (book.ISBN == ISBN) {
            book.available = true;
            cout << "Book returned successfully!" << endl;
            return;
        }
    }

    cout << "Book not found." << endl;
}

void calculateFine() {
    // Assuming a flat fine rate per day
    const double fineRatePerDay = 0.50;

    time_t now = time(0);
    tm* currentDate = localtime(&now);

    for (Borrower& borrower : borrowers) {
        for (Book* book : borrower.borrowedBooks) {
            // Calculate days overdue
            time_t dueDate = mktime(currentDate);
            dueDate += 604800; // Add 7 days (for demonstration purposes)
            tm* dueDateStruct = localtime(&dueDate);

            if (dueDateStruct->tm_year > currentDate->tm_year ||
                (dueDateStruct->tm_year == currentDate->tm_year && dueDateStruct->tm_yday > currentDate->tm_yday)) {
                double daysOverdue = difftime(now, mktime(dueDateStruct)) / (60 * 60 * 24);
                double fine = daysOverdue * fineRatePerDay;
                cout << "Borrower: " << borrower.name << ", Book: " << book->title << ", Fine: $" << fine << endl;
            }
        }
    }
}

int main() {
    int choice;
    do {
        cout << "\nLibrary Management System\n";
        cout << "1. Add Book\n";
        cout << "2. Search Books\n";
        cout << "3. Checkout Book\n";
        cout << "4. Return Book\n";
        cout << "5. Calculate Fine\n";
        cout << "6. Exit\n";
        cout << "Enter your choice: ";
        cin >> choice;
        cin.ignore();

        switch (choice) {
            case 1: addBook(); break;
            case 2: searchBooks(); break;
            case 3: checkoutBook(); break;
            case 4: returnBook(); break;
            case 5: calculateFine(); break;
            case 6: cout << "Exiting...\n"; break;
            default: cout << "Invalid choice. Try again.\n";
        }
    } while (choice != 6);

    return 0;
}

