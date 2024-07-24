#include<iostream>
#include<stdlib.h>
#include<conio.h>
using namespace std;

int theChoice;

struct theAccount {
    theAccount* prev;
    string theusername;
    string thepassword;
    int userrole;
    theAccount* next;
};

theAccount* userAccount;
theAccount* theAccountHead;
theAccount* theAccountTail;
theAccount* theAccountHelper;

void strips() {
    cout << "\t" << "==================================" << endl;
}

void welcomePage() {
    strips();
    cout << "\t" << "=== Welcome To Telkom Hospital ===" << endl;
    strips();
    cout << endl;
}

void initTheAccount() {
    theAccountHead = NULL;
    theAccountTail = NULL;
}

bool isTheAccountEmpty() {
    return theAccountHead == NULL && theAccountTail == NULL;
}

bool theAccountUsernameChecker(string usernameChecked) {
    if (isTheAccountEmpty()) {
        return true;
    } else {
        theAccountHelper = theAccountHead;
        while (theAccountHelper != NULL) {
            if (theAccountHelper->theusername == usernameChecked) {
                return false;
            }
            theAccountHelper = theAccountHelper->next;
        }
        return true;
    }
}

void accountMaker() {
    string usernameCreate, passwordCreate;
    int userroleCreate;
    strips();
    cout << "\t" << "=== Create an Account ===" << endl;
    strips();
    do {
        cout << "\t" << "Enter username: ";
        cin >> usernameCreate;
        if (!theAccountUsernameChecker(usernameCreate)) {
            cout << "\t" << "The username has been owned by the other user" << endl;
            cout << "\t" << "Please choose other username" << endl;
        }
    } while (!theAccountUsernameChecker(usernameCreate));

    cout << "\t" << "Enter password: ";
    cin >> passwordCreate;
    cout << "\t" << "=== User Role ===" << endl;
    cout << "\t" << "1. Patient" << endl;
    cout << "\t" << "2. Admin" << endl;
    cout << "\t" << "3. Doctor" << endl;
    cout << "\t" << "Note: Unless you are a patient, the HR head will not verify this account application" << endl;
    do {
        cout << "\t" << "Your role (1 - 3): ";
        cin >> userroleCreate;
        if (userroleCreate != 1 && userroleCreate != 2 && userroleCreate != 3) {
            cout << "\t" << "Wrong choice!" << endl;
            cout << "\t" << "Please choose again" << endl << endl;
        }
    } while (userroleCreate != 1 && userroleCreate != 2 && userroleCreate != 3);

    userAccount = new theAccount;
    userAccount->theusername = usernameCreate;
    userAccount->thepassword = passwordCreate;
    userAccount->userrole = userroleCreate;
    userAccount->prev = NULL;
    userAccount->next = NULL;
}

void addingAccount() {
    system("cls");
    accountMaker();
    if (isTheAccountEmpty()) {
        theAccountHead = userAccount;
        theAccountTail = userAccount;
    } else {
        theAccountTail->next = userAccount;
        userAccount->prev = theAccountTail;
        theAccountTail = userAccount;
    }
    cout << "\t" << "Account Created Successfully..." << endl;
}

void addingAccountWithParams(string usernameArg, string passwordArg, int roleArg) {
    userAccount = new theAccount;
    userAccount->theusername = usernameArg;
    userAccount->thepassword = passwordArg;
    userAccount->userrole = roleArg;
    userAccount->prev = NULL;
    userAccount->next = NULL;
    if (isTheAccountEmpty()) {
        theAccountHead = userAccount;
        theAccountTail = userAccount;
    } else {
        theAccountTail->next = userAccount;
        userAccount->prev = theAccountTail;
        theAccountTail = userAccount;
    }
}

void readUserAccount() {
    strips();
    cout << "\t" << "=== View all Account ===" << endl;
    strips();
    if (isTheAccountEmpty()) {
        cout << "\t" << "No Account at all" << endl;
    } else {
        theAccountHelper = theAccountTail;
        while (theAccountHelper != NULL) {
            cout << "\t" << "Username: " << theAccountHelper->theusername << endl;
            cout << "\t" << "Password: " << theAccountHelper->thepassword << endl;
            if (theAccountHelper->userrole == 1) {
                cout << "\t" << "Role: Patient" << endl;
            } else if (theAccountHelper->userrole == 2) {
                cout << "\t" << "Role: Admin" << endl;
            } else {
                cout << "\t" << "Role: Doctor" << endl;
            }
            theAccountHelper = theAccountHelper->prev;
        }
    }
}

void doctorPage() {
    int doctorChoice;
    do {
        system("cls");
        welcomePage();
        cout << "\t" << "Welcome, Dr. " << theAccountHelper->theusername << endl;
        cout << "\t" << "May I help you Doctor? " << endl;
        cout << "\t" << "1. Profile" << endl;
        cout << "\t" << "2. Schedule" << endl;
        cout << "\t" << "3. Online Diagnosis" << endl;
        cout << "\t" << "4. Message" << endl;
        cout << "\t" << "5. Note" << endl;
        cout << "\t" << "6. Your Patients" << endl;
        cout << "\t" << "0. Log Out" << endl;
        cout << "\t" << "Your choice (0 - 6): ";
        cin >> doctorChoice;
        if (doctorChoice > 0) {
            cout << "\t" << "You're very busy today, Doctor" << endl;
            getch();
        } else {
            cout << "\t" << "See you again, Doctor" << endl;
        }
    } while (doctorChoice != 0);
}

void adminPage() {
    int adminChoice;
    do {
        system("cls");
        welcomePage();
        cout << "\t" << "Welcome, Admin " << theAccountHelper->theusername << endl;
        cout << "\t" << "May I help you? " << endl;
        cout << "\t" << "1. Profile" << endl;
        cout << "\t" << "2. Doctor" << endl;
        cout << "\t" << "3. Patients" << endl;
        cout << "\t" << "4. Nurse" << endl;
        cout << "\t" << "5. Hospital Room" << endl;
        cout << "\t" << "6. Your Schedule" << endl;
        cout << "\t" << "0. Log Out" << endl;
        cout << "\t" << "Your choice (0 - 6): ";
        cin >> adminChoice;
        if (adminChoice > 0) {
            cout << "\t" << "You're very busy today" << endl;
            getch();
        } else {
            cout << "\t" << "See you again" << endl;
        }
    } while (adminChoice != 0);
}

void patientPage() {
    int patientChoice;
    do {
        system("cls");
        welcomePage();
        cout << "\t" << "Welcome, Mr/Ms. " << theAccountHelper->theusername << endl;
        cout << "\t" << "May I help you? " << endl;
        cout << "\t" << "1. Profile" << endl;
        cout << "\t" << "2. Your Condition" << endl;
        cout << "\t" << "3. Booking" << endl;
        cout << "\t" << "4. Bill" << endl;
        cout << "\t" << "5. History" << endl;
        cout << "\t" << "0. Log Out" << endl;
        cout << "\t" << "Your choice (0 - 5): ";
        cin >> patientChoice;
        if (patientChoice > 0) {
            cout << "\t" << "You're very healthy today" << endl;
            getch();
        } else {
            cout << "\t" << "See you again" << endl;
            cout << "\t" << "Hopefully always healthy" << endl;
        }
    } while (patientChoice != 0);
}

void loginPage() {
    system("cls");
    int loginTrial = 1;
    bool loginState = false;
    bool isUsernameFounded = false;
    string usernameInput, passwordInput;
    welcomePage();
    cout << "\t" << "=== Login Page ===" << endl;
    do {
        cout << "\t" << "Username: ";
        cin >> usernameInput;
        cout << "\t" << "Password: ";
        cin >> passwordInput;
        if (isTheAccountEmpty()) {
            cout << "\t" << "Register first please..." << endl;
        } else {
            theAccountHelper = theAccountHead;
            while (theAccountHelper != NULL && !isUsernameFounded) {
                if (theAccountHelper->theusername == usernameInput) {
                    isUsernameFounded = true;
                } else {
                    theAccountHelper = theAccountHelper->next;
                }
            }
            if (isUsernameFounded) {
                if (theAccountHelper->thepassword == passwordInput) {
                    loginState = true;
                } else {
                    isUsernameFounded = false;
                    cout << "\t" << "Login Failed: Password Incorrect..." << endl << endl;
                    loginTrial++;
                }
            } else {
                cout << "\t" << "Login Failed: No Username..." << endl << endl;
                loginTrial++;
            }
        }
    } while (loginTrial <= 3 && !loginState);
    if (loginState) {
        if (theAccountHelper->userrole == 1) {
            patientPage();
        } else if (theAccountHelper->userrole == 2) {
            adminPage();
        } else {
            doctorPage();
        }
    } else {
        cout << "\t" << "Repeat from the beginning..." << endl;
        theChoice = 0;
    }
}

void homePage() {
    do {
        system("cls");
        welcomePage();
        cout << "\t" << "Please login or register if you haven't account" << endl;
        cout << "\t" << "1. Login" << endl;
        cout << "\t" << "2. Register" << endl;
        cout << "\t" << "0. Exit" << endl;
        cout << "\t" << "Please type your choice (0 - 2): ";
        cin >> theChoice;
        switch (theChoice) {
        case 1:
            loginPage();
            break;
        case 2:
            addingAccount();
            break;
        case 0:
            cout << "\t" << "=== Good Bye ===" << endl;
            break;
        default:
            cout << "\t" << "=== Sorry your choice incorrect ===" << endl;
            cout << "\t" << "=== Please choose again ===" << endl;
            break;
        }
        getch();
    } while (theChoice > 0);
}

int main() {
    addingAccountWithParams("Abdul", "123", 1);
    addingAccountWithParams("Ani", "123", 2);
    addingAccountWithParams("Rhoma", "123", 3);
    homePage();
    return 0;
}
