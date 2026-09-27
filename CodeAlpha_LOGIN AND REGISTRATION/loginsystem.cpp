#include <iostream>
#include <fstream>
#include <string>
using namespace std;

const string FILENAME = "users.txt";
const int MAXIMUM_USERS = 100;


bool usernameExists(string username) {
    ifstream inFile(FILENAME);
    string userstored, storedPass;

    while (inFile >> userstored >> storedPass) {
        if (userstored == username) {
            inFile.close();
            return true;
        }
    }

    inFile.close();
    return false;
}

void registerUser() {
    string username, password;

    cout << "\n--- REGISTRATION ---\n";
    cout << "Enter a username: ";
    cin >> username;

    if (username.length() < 3) {
        cout << "Username too short! Must be at least 3 characters.\n";
        return;
    }

    if (usernameExists(username)) {
        cout << "Username already taken! Please choose another one.\n";
        return;
    }

    cout << "Enter a password: ";
    cin >> password;

    if (password.length() < 4) {
        cout << "Password too short! Must be at least 4 characters.\n";
        return;
    }


    ofstream outFile(FILENAME, ios::app);
    outFile << username << " " << password << endl;
    outFile.close();

    cout << "Registration successful! You can now log in.\n";
}

void loginUser() {
    string username, password;

    cout << "\n--- LOGIN ---\n";
    cout << "Enter  username: ";
    cin >> username;
    cout << "Enter  password: ";
    cin >> password;

    ifstream inFile(FILENAME);
    string userstored, passwordstored;
    bool found = false;
    bool correctPassword = false;

    while (inFile >> userstored >> passwordstored) {
        if (userstored == username) {
            found = true;
            if (passwordstored == password) {
                correctPassword = true;
            }
            break;
        }
    }

    inFile.close();

    if (!found) {
        cout << "No account found with that username.\n";
    }
    else if (!correctPassword) {
        cout << "Incorrect password!\n";
    }
    else {
        cout << "Login successful! Welcome, " << username << ".\n";
    }
}

int main() {
    int choice;

    cout << "===== LOGIN AND REGISTRATION SYSTEM =====\n";

    do {
        cout << "1. Register " << endl;
        cout << "2. login " << endl;
        cout << "0.exit" << endl;
        cout << "Enter your choice: ";
        cin >> choice;

        if (choice == 1) {
            registerUser();
        }
        else if (choice == 2) {
            loginUser();
        }
        else if (choice == 0) {
            cout << "Exiting program. \n";
        }
        else {
            cout << "Wrong choice, try again.\n";
        }

    } while (choice != 0);

    return 0;
}
