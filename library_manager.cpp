#include <iostream>
#include <fstream>
#include <vector>
#include <algorithm> // For std::find_if
#include <iomanip>

using namespace std;

// Book class to represent each book in the library
class Book {
private:
    string title;
    string author;
    int year;

public:
    Book(const string& title, const string& author, int year)
        : title(title), author(author), year(year) {}

    // Getter methods
    string getTitle() const { return title; }
    string getAuthor() const { return author; }
    int getYear() const { return year; }

    // Function to display book details
    void display() const {
        cout << setw(25) << left << title
             << setw(20) << left << author
             << setw(10) << left << year << endl;
    }

    // Function to check if the book matches a given title
    bool matchesTitle(const string& searchTitle) const {
        return title == searchTitle;
    }
};

// Library class to manage books
class Library {
private:
    vector<Book> books;

public:
    // Function to add a book to the library
    void addBook(const Book& book) {
        books.push_back(book);
    }

    // Function to remove a book from the library by title
    void removeBook(const string& titleToRemove) {
        vector<Book>::iterator it = findBookByTitle(titleToRemove);
        if (it != books.end()) {
            books.erase(it);
            cout << "Book '" << titleToRemove << "' removed from the library.\n";
        } else {
            cout << "Book '" << titleToRemove << "' not found in the library.\n";
        }
    }

    // Function to display all books in the library
    void displayBooks() const {
        cout << "Library Catalog:\n";
        cout << setw(25) << left << "Title"
             << setw(20) << left << "Author"
             << setw(10) << left << "Year" << endl;
        cout << setfill('-') << setw(55) << "-" << setfill(' ') << endl;
        for (const Book& book : books) {
            book.display();
        }
        cout << endl;
    }

    // Function to save library catalog to a file
    void saveCatalogToFile(const string& filename) const {
        ofstream file(filename);
        if (!file) {
            cerr << "Error opening file: " << filename << endl;
            return;
        }
        
        file << "Library Catalog:\n";
        file << setw(25) << left << "Title"
             << setw(20) << left << "Author"
             << setw(10) << left << "Year" << endl;
        file << setfill('-') << setw(55) << "-" << setfill(' ') << endl;
        for (const Book& book : books) {
            file << setw(25) << left << book.getTitle()
                 << setw(20) << left << book.getAuthor()
                 << setw(10) << left << book.getYear() << endl;
        }
        file.close();
        cout << "Library catalog saved to " << filename << endl;
    }

    // Function to search for a book by title
    void searchByTitle(const string& searchTitle) const {
        vector<Book>::const_iterator it = findBookByTitle(searchTitle);
        if (it != books.end()) {
            cout << "Book found:\n";
            it->display();
        } else {
            cout << "Book with title '" << searchTitle << "' not found.\n";
        }
    }

private:
    // Function to find a book by title (helper function)
    vector<Book>::iterator findBookByTitle(const string& searchTitle) {
        return find_if(books.begin(), books.end(), FindByTitle(searchTitle));
    }

    // Function to find a book by title for const Library objects (helper function)
    vector<Book>::const_iterator findBookByTitle(const string& searchTitle) const {
        return find_if(books.begin(), books.end(), FindByTitle(searchTitle));
    }

    // Functor to compare book titles
    struct FindByTitle {
        string titleToFind;

        FindByTitle(const string& title) : titleToFind(title) {}

        bool operator()(const Book& book) const {
            return book.getTitle() == titleToFind;
        }
    };
};

int main() {
    Library library;

    // Menu-driven user interface
    char choice;
    do {
        cout << "\n--------------------------------------------------------\n";
        cout << "\n     Library Management System Menu created by Yana     \n";
        cout << "\n--------------------------------------------------------\n";
        cout << "\n1. Add a Book\n";
        cout << "2. Remove a Book\n";
        cout << "3. Search for a Book by Title\n";
        cout << "4. Display All Books\n";
        cout << "5. Save Library Catalog to File\n";
        cout << "6. Exit\n";
        cout << "\nEnter your choice (1-6): ";
        cin >> choice;
        cin.ignore(); // Ignore newline character after reading choice

        switch (choice) {
            case '1': {
                string title, author;
                int year;
                cout << "Enter title: ";
                getline(cin, title);
                cout << "Enter author: ";
                getline(cin, author);
                cout << "Enter year: ";
                cin >> year;
                cin.ignore(); // Ignore newline character after reading integer input
                library.addBook(Book(title, author, year));
                cout << "Book added to the library.\n";
                break;
            }
            case '2': {
                string titleToRemove;
                cout << "Enter the title of the book to remove: ";
                getline(cin, titleToRemove);
                library.removeBook(titleToRemove);
                break;
            }
            case '3': {
                string searchTitle;
                cout << "Enter the title of the book to search for: ";
                getline(cin, searchTitle);
                library.searchByTitle(searchTitle);
                break;
            }
            case '4':
                library.displayBooks();
                break;
            case '5':
                library.saveCatalogToFile("library_catalog.txt");
                break;
            case '6':
                cout << "Exiting...\n";
                break;
            default:
                cout << "Invalid choice. Please enter a number from 1 to 6.\n";
                break;
        }

    } while (choice != '6');

    return 0;
}
