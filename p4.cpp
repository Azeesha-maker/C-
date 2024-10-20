#include <iostream>
#include <fstream>
#include <string>
using namespace std;

class temp {
    string userName, Email, password;
    string searchName, searchPass, searchEmail;
    fstream file;
public:
    void login();
    void SignUp();
    void forgot();
} obj;

int main() {
    char choice;
    while (true) {
        cout << "1-Login\n";
        cout << "2-Sign-Up\n";
        cout << "3-Forgot Password\n";
        cout << "4-Exit\n";
        cout << "Enter Your Choice:: ";
        cin >> choice;
        cin.ignore(); // Clear the newline character from the input buffer

        switch (choice) {
            case '1':
                obj.login();
                break;
            case '2':
                obj.SignUp();
                break;
            case '3':
                obj.forgot();
                break;
            case '4':
                return 0;
            default:
                cout << "Invalid Selection...!" << endl;
        }
    }
}

void temp::SignUp() {
    cout << "\nEnter your user name :: ";
    getline(cin, userName);
    cout << "Enter your Email Address:: ";
    getline(cin, Email);
    cout << "Enter your password:: ";
    getline(cin, password);

    // Check for existing username or email
    string existingUser, existingEmail;
    bool userExists = false;

    file.open("loginData.txt", ios::in);
    while (getline(file, existingUser, '*') && getline(file, existingEmail, '*')) {
        getline(file, password); // Read the password for each entry
        if (existingUser == userName || existingEmail == Email) {
            userExists = true;
            break;
        }
    }
    file.close();

    if (userExists) {
        cout << "User already exists! Please try another username or email." << endl;
        return;
    }

    file.open("loginData.txt", ios::out | ios::app);
    file << userName << "*" << Email << "*" << password << endl;
    file.close();
    cout << "Sign Up Successful!" << endl;
}

void temp::login() {
    cout << "----------------login-----------" << endl;
    cout << "Enter your user name ::" << endl;
    getline(cin, searchName);
    cout << "Enter the Password::" << endl;
    getline(cin, searchPass);

    file.open("loginData.txt", ios::in);
    if (!file.is_open()) {
        cout << "Unable to open file for reading." << endl;
        return;
    }

    string existingUser, existingEmail;
    bool found = false;

    while (getline(file, existingUser, '*') &&
           getline(file, existingEmail, '*') &&
           getline(file, password)) {
        if (existingUser == searchName) {
            found = true;
            if (password == searchPass) {
                cout << "\nAccount Login is Successful..." << endl;
                cout << "\nUserName:: " << existingUser << endl;
                cout << "\nEmail:: " << existingEmail << endl;
                break; // Exit after successful login
            } else {
                cout << "Password is incorrect :(" << endl;
                break; // Exit after failed password
            }
        }
    }
    
    if (!found) {
        cout << "Username not found." << endl;
    }

    file.close();
}

void temp::forgot() {
    cout << "\n Enter your Username:: ";
    getline(cin, searchName);
    cout << "\n Enter your Email Address:: ";
    getline(cin, searchEmail);

    file.open("loginData.txt", ios::in);
    if (!file.is_open()) {
        cout << "Unable to open file for reading." << endl;
        return;
    }

    string existingUser, existingEmail;
    bool found = false;

    while (getline(file, existingUser, '*') &&
           getline(file, existingEmail, '*') &&
           getline(file, password)) {
        if (existingUser == searchName && existingEmail == searchEmail) {
            found = true;
            cout << "\nAccount Found....!";
            cout << "Your Password:: " << password << endl;
            break; // Exit after found
        }
    }

    if (!found) {
        cout << "Username or Email not found." << endl;
    }

    file.close();
}


