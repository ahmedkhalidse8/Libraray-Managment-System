#include <iostream>
#include <fstream>
#include <vector>
#include <string>

using namespace std;

class Book {
public:
    int id;
    string title;
    string author;
    bool isBorrowed;

    Book(int id, string title, string author, bool isBorrowed = false)
        : id(id), title(title), author(author), isBorrowed(isBorrowed) {}

    void display() const {
        cout << "ID: " << id << ", Title: " << title
             << ", Author: " << author
             << ", Status: " << (isBorrowed ? "Borrowed" : "Available") << endl;
    }
};

class Library {
private:
    vector<Book> books;

    void saveToFile() {
        ofstream outFile("books.txt");
        for (const auto &book : books) {
            outFile << book.id << "|" << book.title << "|" << book.author
                    << "|" << book.isBorrowed << endl;
        }
        outFile.close();
    }

    void loadFromFile() {
        ifstream inFile("books.txt");
        if (!inFile) return;

        books.clear();
        string line;
        while (getline(inFile, line)) {
            size_t idEnd = line.find('|');
            size_t titleEnd = line.find('|', idEnd + 1);
            size_t authorEnd = line.find('|', titleEnd + 1);

            int id = stoi(line.substr(0, idEnd));
            string title = line.substr(idEnd + 1, titleEnd - idEnd - 1);
            string author = line.substr(titleEnd + 1, authorEnd - titleEnd - 1);
            bool isBorrowed = stoi(line.substr(authorEnd + 1));

            books.emplace_back(id, title, author, isBorrowed);
        }
        inFile.close();
    }

public:
    Library() {
        loadFromFile();
    }

    ~Library() {
        saveToFile();
    }

    void addBook() {
        int id;
        string title, author;
        cout << "Enter Book ID: ";
        cin >> id;
        cin.ignore();
        cout << "Enter Book Title: ";
        getline(cin, title);
        cout << "Enter Author: ";
        getline(cin, author);

        books.emplace_back(id, title, author);
        cout << "Book added successfully!\n";
    }

    void displayBooks() {
        if (books.empty()) {
            cout << "No books in the library.\n";
            return;
        }
        for (const auto &book : books) {
            book.display();
        }
    }

    void searchBook() {
        string keyword;
        cout << "Enter keyword to search (Title/Author): ";
        cin.ignore();
        getline(cin, keyword);

        for (const auto &book : books) {
            if (book.title.find(keyword) != string::npos || book.author.find(keyword) != string::npos) {
                book.display();
            }
        }
    }

    void borrowBook() {
        int id;
        cout << "Enter Book ID to borrow: ";
        cin >> id;

        for (auto &book : books) {
            if (book.id == id) {
                if (book.isBorrowed) {
                    cout << "Book is already borrowed.\n";
                } else {
                    book.isBorrowed = true;
                    cout << "You have borrowed the book: " << book.title << "\n";
                }
                return;
            }
        }
        cout << "Book not found.\n";
    }

    void returnBook() {
        int id;
        cout << "Enter Book ID to return: ";
        cin >> id;

        for (auto &book : books) {
            if (book.id == id) {
                if (!book.isBorrowed) {
                    cout << "Book is not borrowed.\n";
                } else {
                    book.isBorrowed = false;
                    cout << "Book returned successfully!\n";
                }
                return;
            }
        }
        cout << "Book not found.\n";
    }
};

int main() {
    Library library;
    int choice;

    do {
        cout << "\nLibrary Management System\n";
        cout << "1. Add Book\n";
        cout << "2. Display Books\n";
        cout << "3. Search Book\n";
        cout << "4. Borrow Book\n";
        cout << "5. Return Book\n";
        cout << "6. Exit\n";
        cout << "Enter your choice: ";
        cin >> choice;

        switch (choice) {
            case 1: library.addBook(); break;
            case 2: library.displayBooks(); break;
            case 3: library.searchBook(); break;
            case 4: library.borrowBook(); break;
            case 5: library.returnBook(); break;
            case 6: cout << "Exiting...\n"; break;
            default: cout << "Invalid choice. Try again.\n";
        }
    } while (choice != 6);

    return 0;
}
