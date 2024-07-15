#include <iostream>
#include <fstream>
#include <vector>
#include <sstream>
#include <ctime>
#include <map>

using namespace std;

struct Book {
    string title;
    string author;
    string isbn;
    bool issued;
};

struct User {
    int rollNo;
    string name;
    map<string, time_t> issuedBooks; //map of book title to issue date
    int fine = 0;
};

vector<Book> books;
vector<User> users;

//Function to add a new book to the library
void addBook() {
    Book newBook;
    cout << endl << "Enter book title: ";
    cin.ignore();
    getline(cin, newBook.title);
    cout << "Enter book author: ";
    getline(cin, newBook.author);
    cout << "Enter book ISBN: ";
    getline(cin, newBook.isbn);
    for (auto& book : books) {
        if (book.isbn == newBook.isbn) {
            cout << endl << "Book with same ISBN already exists!" << endl;
            return;
        }
    }
    newBook.issued = false;
    books.push_back(newBook);
    cout << endl << "Book added successfully!" << endl;
}

//Function to issue a book to a user
void issueBook(int rollNo) {
    string isbn;
    cout << "Enter book ISBN: ";
    cin.ignore();
    getline(cin, isbn);
    for (auto& book : books) {
        if (book.isbn == isbn && !book.issued) {
            book.issued = true;
            bool userFound = false;
            for (auto& user : users) {
                if (user.rollNo == rollNo) {
                    user.issuedBooks[book.title] = time(0); //issue date
                    cout << endl << "Book issued successfully!" << endl;
                    userFound = true;
                    return;
                }
            }
            if (!userFound) {
                User newUser;
                cout << endl << "You are a new User so Enter your name: ";
                getline(cin, newUser.name);
                newUser.rollNo = rollNo;
                newUser.issuedBooks[book.title] = time(0); //issue date
                users.push_back(newUser);
                cout << endl << "Book issued successfully!" << endl;
                return;
            }
        }
    }
    cout << endl << "Book not found or already issued." << endl;
}

//Function to return a book
void returnBook(int rollNo) {
    string isbn;
    cout << "Enter book ISBN: ";
    cin.ignore();
    getline(cin, isbn);
    for (auto& user : users) {
        if (user.rollNo == rollNo) {
            for (auto& book : books) {
                if (book.isbn == isbn && user.issuedBooks.find(book.title) != user.issuedBooks.end()) {
                    book.issued = false;
                    time_t issueDate = user.issuedBooks[book.title];
                    time_t returnDate = time(0); //return date
                    int days = difftime(returnDate, issueDate) / (60*60*24); //convert seconds to days
                    user.issuedBooks.erase(book.title);
                    cout << endl << "Book returned successfully!" << endl;
                    if (days > 14) {
                        user.fine = (days - 14) * 5; //calculate fine
                        cout<< "Your fine for " << days - 14 << " is: " << user.fine;

                    } else {
                        cout<< "You have no fine." << endl;
                    }
                    return;
                }
            }
        }
    }
    cout << endl << "Book not found or not issued to you." << endl;
}

//Function to check if a book is available
void checkAvailability() {
    string isbn;
    cout << endl << "Enter book ISBN: ";
    cin.ignore();
    getline(cin, isbn);
    for (auto& book : books) {
        if (book.isbn == isbn) {
            if (!book.issued) {
                cout << endl << "Book is available!" << endl;
            } else {
                cout << endl << "Book is not available!" << endl;
            }
            return;
        }
    }
    cout << endl << "Book not found!" << endl;
}

//Function to save records to file
void saveRecords() {
    ofstream file("library.txt");
    if (!file) {
        cout << "Unable to open file for writing!" << endl;
        return;
    }

    file << "Books:" << endl;
    for (auto& book : books) {
        file << book.title << "," << book.author << "," << book.isbn << "," << (book.issued ? 1 : 0) << endl;
    }
    file << "Users:" << endl;
    for (auto& user : users) {
        file << user.rollNo << "," << user.name;
        for (auto& issuedBook : user.issuedBooks) {
            file << "," << issuedBook.first << "," << issuedBook.second;
        }
        file << "," << user.fine << endl;
    }
    file.close();
}

//Function to load records from file
void loadRecords() {
    ifstream file("library.txt");
    if (!file) {
        cout << "No records found. Starting fresh." << endl;
        return;
    }

    string line;
    bool readingBooks = false;
    bool readingUsers = false;

    while (getline(file, line)) {
        if (line == "Books:") {
            readingBooks = true;
            readingUsers = false;
        } else if (line == "Users:") {
            readingBooks = false;
            readingUsers = true;
        } else {
            stringstream ss(line);
            if (readingBooks) {
                string title, author, isbn, issuedStr;
                getline(ss, title, ',');
                getline(ss, author, ',');
                getline(ss, isbn, ',');
                getline(ss, issuedStr, ',');
                bool issued = stoi(issuedStr);
                Book book = {title, author, isbn, issued};
                books.push_back(book);
            } else if (readingUsers) {
                int rollNo;
                string name, fineStr;
                getline(ss, line, ',');
                rollNo = stoi(line);
                getline(ss, name, ',');
                User user = {rollNo, name, {}, 0};
                while (getline(ss, line, ',')) {
                    if (isdigit(line[0])) {
                        user.fine = stoi(line);
                    } else {
                        string title = line;
                        getline(ss, line, ',');
                        time_t issueDate = stoi(line);
                        user.issuedBooks[title] = issueDate;
                    }
                }
                users.push_back(user);
            }
        }
    }
    file.close();
}

int main() {
    loadRecords();
    srand(time(0));

    int rollNo;
    int choice;
    while (true) {
        cout << endl << "\t*** Library Management System ***" << endl;
        cout << endl << "1. Add a new book" << endl;
        cout << "2. Issue a book" << endl;
        cout << "3. Return a book" << endl;
        cout << "4. Check book availability" << endl;
        cout << "5. Exit" << endl;
        cout << "Enter your choice: ";
        cin >> choice;

        switch (choice) {
            case 1:
                addBook();
                break;
            case 2:
                cout << endl << "Enter your roll number: ";
                cin >> rollNo;
                issueBook(rollNo);
                break;
            case 3:
                cout << endl << "Enter your roll number: ";
                cin >> rollNo;
                returnBook(rollNo);
                break;
            case 4:
                checkAvailability();
                break;
            case 5:
                cout << endl << "\tThank You";
                saveRecords();
                return 0;
            default:
                cout<< endl << "Invalid choice, enter the correct choice." << endl;
                break;
        }
    }
}
