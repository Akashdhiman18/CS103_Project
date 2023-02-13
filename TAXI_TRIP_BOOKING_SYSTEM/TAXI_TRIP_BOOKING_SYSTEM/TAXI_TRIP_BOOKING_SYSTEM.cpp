#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
#include <string>
#include <map>
#include <vector>
#include <fstream>
#include <ctime>
#include <sstream>

using namespace std;

struct TaxiRide {
    string passengerName;
    string pickupAddress;
    string destinationAddress;
    double fare;
    time_t time;
};
struct ReportItem{
    string itemName;
    string itemDescription;
};
struct ReportComplaint {
    string driverName;
    string complaintDescription;
};
struct User_account
{
    string username;
    string password;
};
class Driver {
public :

    void view_reportitem()
    {

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
            infile.ignore(1, '\n');
            reportItems.push_back(reportItem);
        }

        infile.close();

        if (reportItems.empty()) {
            cout << "No report item found." << endl;
        }
        else {
            cout << "Report Items:" << endl;

            for (const auto& reportItems : reportItems) {
                cout << "Item name: " << reportItem.itemName << endl;
                cout << "Item description: " <<reportItem.itemDescription << endl;
            }
        }
    }

    void view_reportComplaint()
    {

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
            infile.ignore(1, '\n');
            reportComplaints.push_back(reportComplaint);
        }

        infile.close();

        if (reportComplaints.empty()) {
            cout << "No report complaint found." << endl;
        }
        else {
            cout << "Report Complaints:" << endl;

            for (const auto& reportComplaint : reportComplaints) {
                cout << "Driver name: " << reportComplaint.driverName << endl;
                cout << "Enter complaint: " << reportComplaint.complaintDescription << endl;
            }
        }
    }
    void logindriver()
    {
        string filename = "d:/driveraccount.doc";
        ifstream infile(filename);
        User_account account;
        cout << "Enter Username : ";
        cin>>account.username;
        cout << "Enter Password : ";
        cin>>account.password;
        bool login_successful = false;
        string line;
        while (getline(infile, line)) {
            if (line == account.username) {
                getline(infile, line);
                if (line == account.password) {
                    login_successful = true;
                    break;
                }
            }
        }
        infile.close();
        if (login_successful) {
            cout << "Login successful!" << endl;
            cout << " ------------------------------------" << endl;
            cout << "| Welcome to the User Panel         |" << endl;
            cout << " ------------------------------------" << endl;
            while (true)
            {
                cout << "\n1. View report item" << "\n";
                cout << "2. View report complaint" << "\n";
                cout << "4. Exit" << "\n";
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
                    cout << "GOOD BYE !" << endl;
                }

                else
                {
                    cout << "Invaild";
                }
            }
        }
    }

};
class Customer {
public:

    void bookTrip()
    {
        cout << "************ BOOK A TRIP **************" << endl;
        cout << "Book Trip successfully !" << endl;
        string filename = "d:/booktrip.doc";
        ofstream outfile(filename, ios::app);
        TaxiRide ride;
        cout << "Enter passenger name: ";
        cin>> ride.passengerName;
        cout << "Enter pickup address: ";
        cin>>ride.pickupAddress;
        cout << "Enter destination address: ";
        cin>>ride.destinationAddress;
        cout << "Enter fare: ";
        cin >> ride.fare;

        // Add ride to the file
        outfile << ride.passengerName << endl;
        outfile << ride.pickupAddress << endl;
        outfile << ride.destinationAddress << endl;
        outfile << ride.fare << endl;
        outfile << ride.time << endl;
        outfile.close();
        cout << "Taxi ride booked successfully." << endl;

    }
    void report_Item()
    {

        string filename = "d:/report_Item.doc";
        ofstream outfile(filename, ios::app);
        ReportItem report;
        cout << "************ REPORT LOST ITEM  **************" << endl;
        cout << "\nEnter item name: ";
        cin>> report.itemName;
        cout << "Enter item description: ";
        cin>>report.itemDescription;
  

        // Add ride to the file
        outfile << report.itemName << endl;
        outfile << report.itemDescription << endl;
        outfile.close();  
        cout << "\nLost item reported successfully!" << "\n";
    }
    void report_Complaint()
    {
        string filename = "d:/report_complaint.doc";
        ofstream outfile(filename, ios::app);
        ReportComplaint reportComplaint;
        cout << "************ REPORT LOST ITEM  **************" << endl;
        cout << "\nEnter driver name: ";
        cin>>reportComplaint.driverName;
        cout << "Enter item description: ";
        cin>>reportComplaint.complaintDescription;
   

        // Add ride to the file
        outfile << reportComplaint.driverName << endl;
        outfile << reportComplaint.complaintDescription << endl;
        outfile.close();
        cout << "\nComplaint reported successfully!" << "\n";
    }
   
    void loginCustomer() {
        string filename = "d:/customeraccount.doc";
        ifstream infile(filename);
        User_account account;
        cout << "Enter Username : ";
        getline(cin, account.username);
        cout << "Enter Password : ";
        getline(cin, account.password);
        bool login_successful = false;
        string line;
        while (getline(infile, line)) {
            if (line == account.username) {
                getline(infile, line);
                if (line == account.password) {
                    login_successful = true;
                    break;
                }
            }
        }
        infile.close();
        if (login_successful) {
            cout << "Login successful!" << endl;
            cout << " ------------------------------------" << endl;
            cout << "| Welcome to the User Panel         |" << endl;
            cout << " ------------------------------------" << endl;
            while (true)
            {
                cout << "\n1. Book a trip" << "\n";
                cout << "2. Report lost item" << "\n";
                cout << "3. Report a complaint" << "\n";
                cout << "4. Exit" << "\n";
                cout << "Enter your choice : ";
                int opt;
                cin >> opt;
                if (opt == 1)
                {
                    bookTrip();
                }
                else if (opt == 2)
                {
                    report_Item();
                }
                else if (opt == 3)
                {
                    report_Complaint();
                }
                else if (opt == 4)
                {
                    cout << "GOOD BYE !" << endl;
                }

                else
                {
                    cout << "Invaild";
                }
            }
        }
        else {
            cout << "Login failed. Please check your username and password." << endl;
        }
    }
};

class Admin {
public:
   ;
    void register_Customer() {

        string filename = "d:/customeraccount.doc";
        ofstream outfile(filename, ios::app);
        cout << "------------- Create a customer account ------------" << endl;
        User_account account;
        cout << "Enter Username : ";
        cin >> account.username;
        cout << "Enter Password : " ;
        cin >> account.username;

    
        // Add ride to the file
        outfile << account.username << endl;
        outfile << account.password << endl;
        outfile.close();
        system("PAUSE");
        cout << "Register successfully !" << endl;
        
        system("cls");




    }

    void register_Driver() {

        string filename = "d:/driveraccount.doc";
        ofstream outfile(filename, ios::app);
        cout << "---------------- Create a driver account --------------" << endl;
        User_account account;
        cout << "Enter Username : ";
        cin>>account.username;
        cout << "Enter Password : ";
        cin>> account.password;


        // Add ride to the file
        outfile << account.username << endl;
        outfile << account.password << endl;
        outfile.close();
        cout << "Register successfully !" << endl;
    }
    void login_Admin()
    {

        string username, password;
        bool is_valid = false;

        while (!is_valid) {
            cout << "Enter Username: ";
            cin >> username;

            cout << "Enter Password: ";
            cin >> password;

            // check if username and password are valid
            if (username == "admin" && password == "password123") {
                is_valid = true;
                // if username and password are valid, show the taxi boking panel
                cout << "  ------------------------------------" << endl;
                cout << " | Welcome to the Admin Panel        |" << endl;
                cout << "  ------------------------------------" << endl;
                cout << "1. View Booking Trip" << endl;
                cout << "2. Update Profile" << endl;
                cout << "3. Add new Customer OR Driver" << endl;
                cout << "4. Exit" << endl;
                cout << "Enter your choice : " << endl;
                int choice_num;
                cin >> choice_num;
                if (choice_num == 1)
                {
                    ViewCustomer_detials();
                }
                else if (choice_num == 3)
                {
                    cout << "\n******* REGISTER FOR A NEW MEMBER ******** " << endl;
                    cout << "\n1. Register as a Customer" << "\n";
                    cout << "2. Register as a Driver" << "\n";
                    cout << "Your choice : ";
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
                else if (choice_num == 4)
                {
                    
                }


            }
            
            else {
                cout << "Invalid username or password. Please try again." << endl;
            }
        }
    }
    void edit_AccountDetail_Customer()
    {
        

    }
    void edit_AccountDetail_Driver()
    {

    }
    void ViewCustomer_detials()
    {
        string filename = "d:/customeraccount.doc";
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
            infile.ignore(1, '\n');
            rides.push_back(ride);
        }

        infile.close();

        if (rides.empty()) {
            cout << "No taxi rides found." << endl;
        }
        else {
            cout << "Taxi rides:" << endl;

            for (const auto& ride : rides) {
                cout << "Passenger name: " << ride.passengerName << endl;
                cout << "Pickup address: " << ride.pickupAddress << endl;
                cout << "Destination address: " << ride.destinationAddress << endl;
                cout << "Fare: " << ride.fare << endl << endl;
                cout << "Time: " << ride.time << endl << endl;
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
}

int main() {
    Admin admin;
    int choice;
    Customer customer;
    Driver driver;
    while (true)
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
