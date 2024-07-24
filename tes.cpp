#include <iostream>
using namespace std;

const int max_data = 10;
const int max_data_account = 5;

string usernameLog, passwordLog;
bool isLogin = false;
int counterLogin = 1;

struct accountStack {
    int data_position;
    string dataUsername[max_data_account];
    string dataPassword[max_data_account];
};

accountStack admin;

void stackAdminInitialization() {
    admin.data_position = -1;
}

bool isStackAdminEmpty() {
    if (admin.data_position == -1) {
        return true;
    } else {
        return false;
    }
}

bool isStackAdminFull() {
    if (admin.data_position == max_data_account - 1) {
        return true;
    } else {
        return false;
    }
}

void pushAdminData(string usernameData, string passwordData) {
    if (!isStackAdminFull()) {
        admin.data_position++;
        admin.dataUsername[admin.data_position] = usernameData;
        admin.dataPassword[admin.data_position] = passwordData;
        cout << "Data entered successfully" << endl;
    } else {
        cout << "Data entry failed !" << endl;
    }
}

void popAdminData() {
    if (!isStackAdminEmpty()) {
        admin.data_position--;
        cout << "Successfully deleted data" << endl;
    } else {
        cout << "Failed to delete data !" << endl;
    }
}

void showAdminData() {
    if (!isStackAdminEmpty()) {
        for (int c = admin.data_position; c >= 0; c--) {
            cout << "===== Admin Account Data =====" << endl;
            cout << "Username : " << admin.dataUsername[c] << endl;
            cout << "Password : " << admin.dataPassword[c] << endl;
            cout << "==========================" << endl << endl;
        }
    } else {
        cout << "Failed to show data !" << endl;
    }
}

struct mystack {
    int data_position;
    string name[max_data];
    float age[max_data];
    char gender[max_data];
    string destination[max_data];
    string origin[max_data];
    string seatNumber[max_data];
};

mystack passenger;

void stackPassengerInitialization() {
    passenger.data_position = -1;
}

bool isStackPassengerEmpty() {
    if (passenger.data_position == -1) {
        return true;
    } else {
        return false;
    }
}

bool isStackPassengerFull() {
    if (passenger.data_position == max_data - 1) {
        return true;
    } else {
        return false;
    }
}

void pushPassengerData(string nameData, float ageData, char genderData, string destinationData, string originData, string seatNumberData) {
    if (!isStackPassengerFull()) {
        passenger.data_position++;
        passenger.name[passenger.data_position] = nameData;
        passenger.age[passenger.data_position] = ageData;
        passenger.gender[passenger.data_position] = genderData;
        passenger.destination[passenger.data_position] = destinationData;
        passenger.origin[passenger.data_position] = originData;
        passenger.seatNumber[passenger.data_position] = seatNumberData;
        cout << "Data entered successfully" << endl;
    } else {
        cout << "Data entry failed !" << endl;
    }
}

void popPassengerData() {
    if (!isStackPassengerEmpty()) {
        passenger.data_position--;
        cout << "Successfully deleted data" << endl;
    } else {
        cout << "Failed to delete data !" << endl;
    }
}

void showPassengerData() {
    if (!isStackPassengerEmpty()) {
        for (int c = passenger.data_position; c >= 0; c--) {
            cout << "===== Passenger Data =====" << endl;
            cout << "Name : " << passenger.name[c] << endl;
            cout << "Gender : " << passenger.gender[c] << endl;
            cout << "Age : " << passenger.age[c] << endl;
            cout << "Destination : " << passenger.destination[c] << endl;
            cout << "Origin : " << passenger.origin[c] << endl;
            cout << "Seat Number : " << passenger.seatNumber[c] << endl;
            cout << "==========================" << endl << endl;
        }
    } else {
        cout << "Failed to show data !" << endl;
    }
}

void searchAccountData(string dataUsernameInputed, string dataPasswordInputed) {
    if (!isStackAdminEmpty()) {
        int c = admin.data_position;
        do {
            if (admin.dataUsername[c] == dataUsernameInputed) {
                if (admin.dataPassword[c] == dataPasswordInputed) {
                    isLogin = true;
                }
            }
            c--;
        } while (isLogin == false && c >= 0);
    } else {
        cout << "No account at all" << endl;
    }
}

void login() {
    do {
        cout << "=== Login Page ===" << endl;
        cout << "Username : ";
        cin >> usernameLog;
        cout << "Password : ";
        cin >> passwordLog;
        searchAccountData(usernameLog, passwordLog);
        if (isLogin == true) {
            cout << "Login successful..." << endl;
        } else {
            cout << "Login failed..." << endl;
            counterLogin++;
        }
        cout << "===================" << endl << endl;
    } while (isLogin == false && counterLogin <= 3);
    if (counterLogin > 3) {
        cout << "Your Account has been blocked" << endl;
    }
}

void menu() {
    int yourChoice = 1;
    char repeat;
    string passengerName;
    float passengerAge;
    char passengerGender;
    string passengerDestination;
    string passengerOrigin;
    string passengerSeatNumber;
    string newUsernameAdmin;
    string newPasswordAdmin;
    do {
        cout << "===== Train Xpress Company =====" << endl;
        cout << "Welcome, " << usernameLog << endl;
        cout << "What do you need ? " << endl;
        cout << "1. Input passenger data" << endl;
        cout << "2. Remove passenger data" << endl;
        cout << "3. Show passenger data" << endl;
        cout << "4. Add admin account" << endl;
        cout << "5. Show admin account" << endl;
        cout << "0. Exit" << endl;
        cout << "Please choose the number : ";
        cin >> yourChoice;
        cout << endl;
        switch (yourChoice) {
            case 1 :
                do {
                    cout << "=== Input Passenger Data ===" << endl;
                    cout << "Passenger Name : ";
                    cin >> passengerName;
                    cout << "Passenger Age : ";
                    cin >> passengerAge;
                    cout << "Passenger Gender (F/M): ";
                    cin >> passengerGender;
                    cout << "Passenger Destination : ";
                    cin >> passengerDestination;
                    cout << "Passenger Origin : ";
                    cin >> passengerOrigin;
                    cout << "Seat Number : ";
                    cin >> passengerSeatNumber;
                    pushPassengerData(passengerName, passengerAge, passengerGender, passengerDestination, passengerOrigin, passengerSeatNumber);
                    cout << "Repeat adding data (y/n) ? ";
                    cin >> repeat;
                } while (repeat == 'y' || repeat == 'Y');
                break;
            case 2 :
                do {
                    cout << "=== Remove Passenger Data ===" << endl;
                    popPassengerData();
                    cout << "Repeat remove data (y/n) ? ";
                    cin >> repeat;
                } while (repeat == 'y' || repeat == 'Y');
                break;
            case 3 :
                do {
                    cout << "=== Show Passenger Data ===" << endl;
                    showPassengerData();
                    cout << "Repeat show data (y/n) ? ";
                    cin >> repeat;
                } while (repeat == 'y' || repeat == 'Y');
                break;
            case 4 :
                do {
                    cout << "=== Create Admin Account ===" << endl;
                    cout << "New Username : ";
                    cin >> newUsernameAdmin;
                    cout << "New Password : ";
                    cin >> newPasswordAdmin;
                    pushAdminData(newUsernameAdmin, newPasswordAdmin);
                    cout << "Repeat create admin account (y/n) ? ";
                    cin >> repeat;
                } while (repeat == 'y' || repeat == 'Y');
                break;
            case 5 :
                do {
                    cout << "=== Show Admin Data ===" << endl;
                    showAdminData();
                    cout << "Repeat show data (y/n) ? ";
                    cin >> repeat;
                } while (repeat == 'y' || repeat == 'Y');
                break;
            case 0 :
                cout << "See you next time" << endl << endl;
                break;
            default:
                cout << "Please repeat your choice" << endl;
                break;
        }
    } while (yourChoice != 0);
}

void startApp() {
    stackAdminInitialization();
    stackPassengerInitialization();
    pushAdminData("Admin", "admin");
    pushAdminData("SuperAdmin", "superadmin");
    do {
        login();
        if (isLogin == true) {
            menu();
            isLogin = false;
            counterLogin = 1;
        }
    } while (isLogin == false && counterLogin <= 3);
}

int main() {
    startApp();
    return 0;
}
