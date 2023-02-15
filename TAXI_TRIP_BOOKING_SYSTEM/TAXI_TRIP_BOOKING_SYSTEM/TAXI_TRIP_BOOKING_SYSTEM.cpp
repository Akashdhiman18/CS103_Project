#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
#include <string>
#include <map>
#include <vector>
#include <fstream>
#include <iomanip>
#include <ctime>
#include<windows.h> 
#include <sstream>
#include<conio.h>
#include <time.h>     

using namespace std;

struct TaxiRide {
    string passengerName;
    string pickupAddress;
    string destinationAddress;
    double fare{};
    time_t time_date{};

};
struct ReportItem {
    string itemName;
    string itemDescription;
    string location;
    time_t time_date{};
};
struct ReportComplaint {
    string driverName;
    string complaintDescription;
    time_t time_date{};
};
struct User_account {
    string username;
    string password;
    string phoneNumber;
    string email;
};

class Driver {
public:

    void view_reportitem()
    {
        Sleep(1000);
        system("cls");
        string filename = "d:/report_Item.doc";
        ifstream infile(filename);

        if (!infile) {
            cerr << "Error: could not open file " << filename << endl;
            return;
        }

        ReportItem reportItem;
        vector<ReportItem> reportItems;

        // Read all rides from the file
        while (getline(infile, reportItem.itemName)) {
            getline(infile, reportItem.itemDescription);
            getline(infile, reportItem.location);
            infile >> reportItem.time_date;
            infile.ignore(1, '\n');
            reportItems.push_back(reportItem);
        }

        infile.close();

        if (reportItems.empty()) {
            cout << "No report item found." << endl;
        }
        else {
            cout << "***************** Report Items ****************" << endl;

            for (const auto& reportItems : reportItems) {
                cout << "Item name: " << reportItem.itemName << endl;
                cout << "Item description: " << reportItem.itemDescription << endl;
                cout << "Time: " << std::put_time(std::localtime(&reportItem.time_date), "%c") << endl << endl;
            }
        }
    }

    void view_reportComplaint()
    {
        Sleep(700);
        system("cls");
        string filename = "d:/report_complaint.doc";
        ifstream infile(filename);

        if (!infile) {
            cerr << "Error: could not open file " << filename << endl;
            return;
        }

        ReportComplaint reportComplaint;
        vector<ReportComplaint> reportComplaints;

        // Read all rides from the file
        while (getline(infile, reportComplaint.driverName)) {
            getline(infile, reportComplaint.complaintDescription);
            infile >> reportComplaint.time_date;
            infile.ignore(1, '\n');
            reportComplaints.push_back(reportComplaint);
        }

        infile.close();

        if (reportComplaints.empty()) {
            cout << "No report complaint found." << endl;
        }
        else {
            cout << "****************** Report Complaints *******************" << endl;

            for (const auto& reportComplaint : reportComplaints) {
                cout << "Driver name: " << reportComplaint.driverName << endl;
                cout << "Enter complaint: " << reportComplaint.complaintDescription << endl;
                cout << "Time: " << std::put_time(std::localtime(&reportComplaint.time_date), "%c") << endl << endl;
            }
        }
    }
    void logindriver()
    {
        Sleep(700);
        system("cls");
        string filename = "d:/driver_account.doc";
        ifstream infile(filename);
        User_account account;
        int attempts = 0;
        map<string, string> accounts;
        cout << "\n******* User login *******" << endl;;
        while (attempts < 3) {
            cout << "\nEnter Username : ";
            cin >> account.username;

            // Ask for password and hide input
            cout << "Enter Password : ";
            char ch;
            string password = "";
            while ((ch = _getch()) != '\r') { // '\r' is the enter key
                if (ch == '\b') { // handle backspace key
                    if (!password.empty()) {
                        password.pop_back();
                        cout << "\b \b"; // erase the last character from the console
                    }
                }
                else {
                    password.push_back(ch);
                    cout << "*"; // print a star instead of the actual character
                }
            }
            account.password = password;

            string line;
            while (getline(infile, line)) {
                account.username = line;
                getline(infile, line);
                account.email = line;
                getline(infile, line);
                account.phoneNumber = line;
                getline(infile, line);
                account.password = line;
                accounts[account.username] = account.password;
            }
            infile.clear();
            infile.seekg(0, ios::beg); // Reset file pointer to beginning
            if (accounts.find(account.username) != accounts.end() && accounts[account.username] == account.password) {
                cout << "\nLoading......." << endl;
                Sleep(800);
                system("cls");
                cout << "\nLogin successful" << endl;
                cout << " ------------------------------------" << endl;
                cout << "| Welcome to the User Panel         |" << endl;
                cout << " ------------------------------------" << endl;
                while (true)
                {
                    cout << "\n1.View report item" << "\n";
                    cout << "2. View report complaint" << "\n";
                    cout << "3. Exit" << "\n";
                    cout << "Enter your choice : ";
                    int opt;
                    cin >> opt;
                    if (opt == 1)
                    {
                        view_reportitem();
                    }
                    else if (opt == 2)
                    {
                        view_reportComplaint();
                    }


                    else if (opt == 3)
                    {
                        break;
                    }
                    else {
                        cout << "\nInvalid option. Try again." << endl;
                    }
                }
                break;
            }
            else {
                cout << "\nInvalid username or password. Try again." << endl;
                attempts++;
            }
        }
        infile.close();
        if (attempts >= 3) {
            cout << "\nMaximum login attempts exceeded. Please try again later." << endl;
        }

    }

};
class Customer {
public:

    void bookTrip()
    {
        Sleep(1000);
        system("cls");
        cout << "\n************ BOOK A TRIP **************" << endl;
        string filename = "d:/taxi_trips.doc";
        ofstream outfile(filename, ios::app);
        TaxiRide ride;
        cout << "\nEnter passenger name: ";
        cin >> ride.passengerName;
        cout << "Enter pickup address: ";
        cin >> ride.pickupAddress;
        cout << "Enter destination address: ";
        cin >> ride.destinationAddress;
        cout << "Enter fare: ";
        cin >> ride.fare;
        ride.time_date = std::time(nullptr);

        // Add ride to the file
        outfile << ride.passengerName << endl;
        outfile << ride.pickupAddress << endl;
        outfile << ride.destinationAddress << endl;
        outfile << ride.fare << endl;
        outfile << std::asctime(std::localtime(&ride.time_date)) << endl;


        outfile.close();
        cout << "\nTaxi ride booked successfully." << endl;

    }



    void report_Item()
    {
        Sleep(1000);
        system("cls");

        string filename = "d:/report_Item.doc";
        ofstream outfile(filename, ios::app);
        ReportItem report;
        cout << "\n************ REPORT LOST ITEM  **************" << endl;
        cout << "\nEnter item name: ";
        cin >> report.itemName;
        cout << "Enter item description: ";
        cin >> report.itemDescription;
        cout << "Enter location :";
        cin >> report.location;

        report.time_date = std::time(nullptr);
        // Add ride to the file
        outfile << report.itemName << endl;
        outfile << report.itemDescription << endl;
        outfile << report.location << endl;
        outfile << std::asctime(std::localtime(&report.time_date)) << endl;
        outfile.close();
        cout << "\nLost item reported successfully!" << "\n";
    }
    void report_Complaint()
    {
        Sleep(1000);
        system("cls");
        string filename = "d:/report_complaint.doc";
        ofstream outfile(filename, ios::app);
        ReportComplaint reportComplaint;
        cout << "\n************ REPORT LOST ITEM  **************" << endl;
        cout << "\nEnter driver name: ";
        cin >> reportComplaint.driverName;
        cout << "Enter item description: ";
        cin >> reportComplaint.complaintDescription;

    
        reportComplaint.time_date = std::time(nullptr);
        // Add ride to the file
        outfile << reportComplaint.driverName << endl;
        outfile << reportComplaint.complaintDescription << endl;
        outfile << std::asctime(std::localtime(&reportComplaint.time_date)) << endl;
        outfile.close();
        cout << "\nComplaint reported successfully " << "\n";
    }

    void loginCustomer() {
        Sleep(700);
        system("cls");
        string filename = "d:/customer.doc";
        ifstream infile(filename);
        User_account account;
        int attempts = 0;
        map<string, string> accounts;
        cout << "\n******* User login *******" << endl;;
        while (attempts < 3) {
            cout << "\nEnter Username : ";
            cin >> account.username;

            // Ask for password and hide input
            cout << "Enter Password : ";
            char ch;
            string password = "";
            while ((ch = _getch()) != '\r') { // '\r' is the enter key
                if (ch == '\b') { // handle backspace key
                    if (!password.empty()) {
                        password.pop_back();
                        cout << "\b \b"; // erase the last character from the console
                    }
                }
                else {
                    password.push_back(ch);
                    cout << "*"; // print a star instead of the actual character
                }
            }
            account.password = password;

            string line;
            while (getline(infile, line)) {
                account.username = line;
                getline(infile, line);
                account.email = line;
                getline(infile, line);
                account.phoneNumber = line;
                getline(infile, line);
                account.password = line;
                accounts[account.username] = account.password;
            }
            infile.clear();
            infile.seekg(0, ios::beg); // Reset file pointer to beginning
            if (accounts.find(account.username) != accounts.end() && accounts[account.username] == account.password) {
                cout << "\nLoading......." << endl;
                Sleep(800);
                system("cls");
                cout << "\nLogin successful " << endl;
                cout << " ------------------------------------" << endl;
                cout << "| Welcome to the User Panel         |" << endl;
                cout << " ------------------------------------" << endl;
                while (true) {
                    cout << "\n1. Book  trip" << "\n";
                    cout << "2. Report lost item" << "\n";
                    cout << "3. Report a complaint" << "\n";
                    cout << "4. Exit" << "\n";
                    cout << "Enter your choice : ";
                    int opt;
                    cin >> opt;
                    if (opt == 1) {
                        bookTrip();
                    }
                    else if (opt == 2) {
                        report_Item();
                    }
                    else if (opt == 3) {
                        report_Complaint();
                    }
                    else if (opt == 4) {

                        break; // exit while loop and program
                    }
                    else {
                        cout << "\nInvalid option. Try again." << endl;
                    }
                }
                break;
            }
            else {
                cout << "\nInvalid username or password. Try again." << endl;
                attempts++;
            }
        }
        infile.close();
        if (attempts >= 3) {
            cout << "\nMaximum login attempts exceeded. Please try again later." << endl;
        }

    }


};


class Admin {
public:


    string get_password() {
        string password = "";
        char c;
        while ((c = _getch()) != '\r') {
            if (c == '\b') {
                if (password.size() > 0) {
                    password.pop_back();
                    cout << "\b \b";
                }
            }
            else {
                password += c;
                cout << "*";
            }
        }
        cout << endl;
        return password;
    }
    void register_Customer() {
        Sleep(700);
        system("cls");
        string filename = "d:/customer.doc";
        ofstream outfile(filename, ios::app);
        cout << "------------- Create a customer account ------------" << endl;
        User_account account;
        cout << "Enter  username : ";
        cin >> account.username;
        cout << "Enter email address :";
        cin >> account.email;
        cout << "Enter phone number :";
        cin >> account.phoneNumber;
        cout << "Enter  Password : ";
        account.password = get_password();


        // Add ride to the file
        outfile << account.username << endl;
        outfile << account.email << endl;
        outfile << account.phoneNumber << endl;
        outfile << account.password << endl;

        outfile.close();

        cout << "Register successfully " << endl;
        Sleep(1000);
        system("cls");


    }

    void register_Driver() {
        Sleep(700);
        system("cls");
        string filename = "d:/driver_account.doc";
        ofstream outfile(filename, ios::app);
        cout << "---------------- Create a driver account --------------" << endl;
        User_account account;
        cout << "Enter Username : ";
        cin >> account.username;
        cout << "Enter email address :";
        cin >> account.email;
        cout << "Enter phone number :";
        cin >> account.phoneNumber;
        cout << "Enter  Password : ";
        account.password = get_password();



        // Add ride to the file
        outfile << account.username << endl;
        outfile << account.email << endl;
        outfile << account.phoneNumber << endl;
        outfile << account.password << endl;
        outfile.close();
        cout << "Register successfully " << endl;
        Sleep(1000);
        system("cls");
    }
    void login_Admin()
    {
        Sleep(700);
        system("cls");
        string username, password;
        bool is_valid = false;
        int attempts = 0;
        const int max_attempts = 3; // maximum login attempts
        cout << "---------------- Admin  account --------------" << endl;
        while (attempts < max_attempts) {
            while (!is_valid) {
                cout << "\nEnter Username: ";
                cin >> username;

                cout << "Enter Password: ";
                // hide password input
                char ch;
                string password = "";
                while ((ch = _getch()) != '\r') { // '\r' is the enter key
                    if (ch == '\b') { // handle backspace key
                        if (!password.empty()) {
                            password.pop_back();
                            cout << "\b \b"; // erase the last character from the console
                        }
                    }
                    else {
                        password.push_back(ch);
                        cout << "*"; // print a star instead of the actual character
                    }
                }

                // check if username and password are valid
                if (username == "admin" && password == "password123") {
                    is_valid = true;
                    cout << "\nLoading......." << endl;
                    Sleep(800);
                    system("cls");
                    // if username and password are valid, show the taxi booking panel
                    while (true)
                    {
                        cout << "  ------------------------------------" << endl;
                        cout << " | Welcome to the Admin Panel        |" << endl;
                        cout << "  ------------------------------------" << endl;
                        cout << "1. View ride history" << endl;
                        cout << "2. Delete customer / driver" << endl;
                        cout << "3. Add new customer / driver" << endl;
                        cout << "4. Edit customer / driver " << endl;
                        cout << "5. Exit" << "\n";
                        cout << "Enter your choice : ";
                        int choice_num;
                        cin >> choice_num;
                        if (choice_num == 1)
                        {
                            Viewride_detials();
                        }
                        else if (choice_num == 3)
                        {
                            Sleep(700);
                            system("cls");
                            cout << "\n******* REGISTER FOR A NEW MEMBER ******** " << endl;
                            cout << "\n1. Register as a Customer" << "\n";
                            cout << "2. Register as a Driver" << "\n";
                            cout << "Your choice :";
                            int option;
                            cin >> option;
                            if (option == 1)
                                register_Customer();
                            else if (option == 2)
                                register_Driver();
                            else {
                                cout << "Invalid choice" << endl;
                            }
                        }
                        else if (choice_num == 2)
                        {
                            Sleep(700);
                            system("cls");
                            cout << "\n******* Delete customer / driver ******** " << endl;
                            cout << "\n1. Delete customer" << "\n";
                            cout << "2.  Delete driver" << "\n";
                            cout << "Your choice :";
                            int option;
                            cin >> option;
                            if (option == 1)
                                delete_AccountDetail_Customer();
                            else if (option == 2)
                                delete_AccountDetail_Driver();
                            else {
                                cout << "Invalid choice" << endl;
                            }
                        }
                        else if (choice_num == 4)
                        {
                            Sleep(700);
                            system("cls");
                            cout << "\n******* Edit cutomer / driver ******** " << endl;
                            cout << "\n1. Edit Customer" << "\n";
                            cout << "2. Edit  Driver" << "\n";
                            cout << "Your choice : ";
                            int option;
                            cin >> option;
                            if (option == 1)
                                edit_AccountDetail_Customer();
                            else if (option == 2)
                                edit_AccountDetail_driver();
                            else {
                                cout << "Invalid choice" << endl;
                            }
                        }
                        else if (choice_num == 5)
                        {
                            break;
                        }
                        else
                        {
                            cout << "Invalid choice. Please try again." << endl;
                        }
                    }
                }
                else {
                    attempts++;
                    if (attempts >= max_attempts) {
                        cout << "\nMaximum login attempts exceeded. Please try again later." << endl;
                        break;

                    }
                    else {
                        cout << "\nInvalid username or password. Please try again. " << endl;
                    }

                }
            }
        }
    }



    void edit_AccountDetail_Customer()
    {
        Sleep(1000);
        system("cls");
        string filename = "d:/customer.doc";
        ifstream infile(filename);

        if (!infile) {
            cerr << "Error: could not open file " << filename << endl;
            return;
        }

        vector<User_account> customers;

        // Read all customers from the file
        User_account customer;
        while (infile >> customer.username >> customer.email >> customer.phoneNumber >> customer.password) {
            customers.push_back(customer);
        }

        infile.close();

        if (customers.empty()) {
            cout << "No customers found." << endl;
            return;
        }
        cout << "********** Update profile **************" << endl;
        cout << "\nEnter the name of the customer you wish to edit: ";
        string name;
        cin >> name;

        bool found = false;
        for (auto& customer : customers) {
            if (customer.username == name) {
                cout << "Enter new username name: ";
                cin >> customer.username;
                found = true;
                break;
            }
        }

        if (!found) {
            cout << "Customer not found." << endl;
            return;
        }

        // Write the updated customers back to the file
        ofstream outfile(filename);

        if (!outfile) {
            cerr << "Error: could not open file " << filename << endl;
            return;
        }

        for (const auto& customer : customers) {
            outfile << customer.username << " " << customer.email << " " << customer.phoneNumber << " " << customer.password << endl;
        }

        outfile.close();

        cout << "Customer account details updated successfully." << endl;
    }


    void edit_AccountDetail_driver()
    {

        Sleep(700);
        system("cls");
        string filename = "d:/driveraccount.doc";
        ifstream infile(filename);

        if (!infile) {
            cerr << "Error: could not open file " << filename << endl;
            return;
        }

        vector<User_account> drivers;

        // Read all customers from the file
        User_account driver;
        while (infile >> driver.username >> driver.email >> driver.phoneNumber >> driver.password) {
            drivers.push_back(driver);
        }

        infile.close();

        if (drivers.empty()) {
            cout << "No drivers found." << endl;
            return;
        }
        cout << "********** Update profile **************" << endl;
        cout << "\nEnter the name of the driver you wish to edit: ";
        string name;
        cin >> name;

        bool found = false;
        for (auto& driver : drivers) {
            if (driver.username == name) {
                cout << "Enter new username name: ";
                cin >> driver.username;
                found = true;
                break;
            }
        }

        if (!found) {
            cout << "Driver not found." << endl;
            return;
        }

        // Write the updated customers back to the file
        ofstream outfile(filename);

        if (!outfile) {
            cerr << "Error: could not open file " << filename << endl;
            return;
        }

        for (const auto& driver : drivers) {
            outfile << driver.username << " " << driver.email << " " << driver.phoneNumber << " " << driver.password << endl;
        }

        outfile.close();

        cout << "Driver account details updated successfully." << endl;
    }
    void delete_AccountDetail_Driver()
    {
        Sleep(1000);
        system("cls");
        string filename = "d:/driveraccount.doc";
        ifstream infile(filename);

        if (!infile) {
            cerr << "Error: could not open file " << filename << endl;
            return;
        }

        vector<User_account> drivers;

        // Read all customers from the file
        User_account driver;
        while (infile >> driver.username >> driver.email >> driver.phoneNumber >> driver.password) {
            drivers.push_back(driver);
        }

        infile.close();

        if (drivers.empty()) {
            cout << "No driver found." << endl;
            return;
        }
        cout << "*********** Delete account *******************" << endl;
        cout << "\nEnter the name of the driver you wish to delete: ";
        string name;
        cin >> name;

        bool found = false;
        for (auto it = drivers.begin(); it != drivers.end(); it++) {
            if (it->username == name) {
                drivers.erase(it);
                found = true;
                break;
            }
        }

        if (!found) {
            cout << "Driver not found." << endl;
            return;
        }

        // Write the updated customers back to the file
        ofstream outfile(filename);

        if (!outfile) {
            cerr << "Error: could not open file " << filename << endl;
            return;
        }

        for (const auto& driver : drivers) {
            outfile << driver.username << " " << driver.email << " " << driver.phoneNumber << " " << driver.password << endl;
        }

        outfile.close();

        cout << "Driver account deleted successfully." << endl;
    }


    void delete_AccountDetail_Customer()
    {
        Sleep(700);
        system("cls");
        string filename = "d:/customeraccount.doc";
        ifstream infile(filename);

        if (!infile) {
            cerr << "Error: could not open file " << filename << endl;
            return;
        }

        vector<User_account> customers;

        // Read all customers from the file
        User_account customer;
        while (infile >> customer.username >> customer.email >> customer.phoneNumber >> customer.password) {
            customers.push_back(customer);
        }

        infile.close();

        if (customers.empty()) {
            cout << "No customers found." << endl;
            return;
        }
        cout << "************ Delete account ******************" << endl;
        cout << "\nEnter the name of the customer you wish to delete: ";
        string name;
        cin >> name;

        bool found = false;
        for (auto it = customers.begin(); it != customers.end(); it++) {
            if (it->username == name) {
                customers.erase(it);
                found = true;
                break;
            }
        }

        if (!found) {
            cout << "Customer not found." << endl;
            return;
        }

        // Write the updated customers back to the file
        ofstream outfile(filename);

        if (!outfile) {
            cerr << "Error: could not open file " << filename << endl;
            return;
        }

        for (const auto& customer : customers) {
            outfile << customer.username << " " << customer.email << " " << customer.phoneNumber << " " << customer.password << endl;
        }

        outfile.close();

        cout << "Customer account deleted successfully." << endl;
    }

    void Viewride_detials()
    {
        Sleep(1000);
        system("cls");
        string filename = "d:/taxi_trips.doc";
        ifstream infile(filename);

        if (!infile) {
            cerr << "Error: could not open file " << filename << endl;
            return;
        }

        TaxiRide ride;
        vector<TaxiRide> rides;

        // Read all rides from the file
        while (getline(infile, ride.passengerName)) {
            getline(infile, ride.pickupAddress);
            getline(infile, ride.destinationAddress);
            infile >> ride.fare;
            infile >> ride.time_date;
            infile.ignore(1, '\n');
            rides.push_back(ride);
        }

        infile.close();

        if (rides.empty()) {
            cout << "No taxi rides found." << endl;
        }
        else {
            cout << "\n------ Taxi trip history --------\n" << endl;

            for (const auto& ride : rides) {
                cout << "Passenger name: " << ride.passengerName << endl;
                cout << "Pickup address: " << ride.pickupAddress << endl;
                cout << "Destination address: " << ride.destinationAddress << endl;
                cout << "Fare: " << ride.fare << endl;
                cout << "Time: " << std::put_time(std::localtime(&ride.time_date), "%c") << endl << endl;

            }
        }
    }


};
void handleRegistration(Admin& admin) {
    cout << "\n******* REGISTER FOR A NEW MEMBER ******** " << endl;
    cout << "\n1. Register as a Customer" << "\n";
    cout << "2. Register as a Driver" << "\n";
    cout << "Your choice : ";
    int option;
    cin >> option;
    if (option == 1)
        admin.register_Customer();
    else if (option == 2)
        admin.register_Driver();
    else {
        cout << "Invalid choice" << endl;
    }
}

void handletologin(Customer& customer, Driver& driver)
{
    cout << "\n******* LOGIN ACCOUNT ******** " << endl;
    cout << "\n1. Login as a Customer" << "\n";
    cout << "2. Login as a Driver" << "\n";
    cout << "Your choice : ";
    int options;
    cin >> options;
    if (options == 1)
    {
        customer.loginCustomer();
    }
    else if (options == 2)
    {
        driver.logindriver();
    }
    else
    {
        cout << "Invaild option . Try again";

    }


}


int main() {
    Admin admin;
    int choice;
    Customer customer;
    Driver driver;
    do
    {

        cout << " ---------------------------------" << endl;
        cout << "|     TAXI TRIP BOOKING SYSTEM   |" << endl;
        cout << " ---------------------------------" << endl;
        cout << "1.  Login Admin   " << endl;
        cout << "2.  User Login    " << endl;
        cout << "3.  Register " << endl;
        cout << "4.  For Exit    " << endl;
        cout << "Your choice :";

        cin >> choice;

        switch (choice) {
        case 1:
            admin.login_Admin();
            break;
        case 2:
            handletologin(customer, driver);
            break;
        case 3:
            cin.ignore();
            handleRegistration(admin);
            break;
        case 4:
            cout << "GOODBYE ! " << endl;
            return 0;
        default:
            cout << "Invalid choice. Please try again." << endl;
            break;
        }
        cout << endl;
    } while (choice != 4);

    return 0;
}
