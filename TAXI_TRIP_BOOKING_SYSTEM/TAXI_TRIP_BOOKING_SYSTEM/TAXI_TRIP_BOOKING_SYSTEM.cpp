# define _CRT_SECURE_NO_WARNINGS
#include <iostream>
#include <string>
#include <map>
#include <vector>
#include <fstream>
#include <ctime>
#include <sstream>



using namespace std;
//new register for customer
class Customer
{
public:
    string name;
    string phone;
    string location;
    vector<string> tripHistory;

    
    void writeToFile_BookTripCustomer(const string& customer_name, const string& pick_location, const string& drop_location, const string& fare, const time_t time)
    {
        ofstream fout("d:/booktrip.doc", ios::app);
        fout <<customer_name<< "," <<pick_location << "," <<drop_location<< "," <<fare<< "," << asctime(localtime(&time)) << endl;
        fout.close();
    }
    void writedatatoregister_customer(const string& username, const string& password) {
        ofstream fout("d:/customeraccount.doc", ios::app);
        fout << username << '\t' << password << endl;
        fout.close();
    }
    
};
class LostItems {
    string items;
    string complaints;
public:
    //write data in REPORT ITEM File
    void reportLostItem(const string& itemName,const string& itemDescription,const time_t time) {
        ofstream fout("d:/report_Item.doc", ios::app);
        fout << itemName << "," << itemDescription<< "," << asctime(localtime(&time)) << endl;
        fout.close();
    }

    void viewLostItems() {
        cout << "Lost Items:" << "\n";
        for (const auto& item : items) {
           
        }
    }
    //write data in REPORT COMPLAINT file
    void reportComplaint(const string& complaint,const string& driver, const time_t time) {
        ofstream fout("d:/report_Item.doc", ios::app);
        fout << complaint << "," << driver<< "," << asctime(localtime(&time)) << endl;
        fout.close();
        
    }

    void viewComplaints() {
        cout << "Complaints:" << "\n";
        for (const auto& comp : complaints) {
          //  cout << "Driver: " << comp.first << ", Complaint: " << comp.second << "\n";
        }
    }
};

//new register for driver 
void writedatatoregister_driver(const string& username, const string& password) {
    ofstream fout("d:/driveraccount.doc", ios::app);
    fout << username << '\t' << password << endl;
    fout.close();
}










int main()
{
    Customer customers;
    LostItems lostitems;
    cout << " ---------------------------------" << endl;
    cout << "|     TAXI TRIP BOOKING SYSTEM   |" << endl;
    cout << " ---------------------------------" << endl;

    cout << "1.  For Login Admin   " << endl;
    cout << "2.  For User Login    " << endl;
    cout << "3.  Register " << endl;
    cout << "4.  For Exit    " << endl;
    cout << "Your choice :";
    int choice;
    cin >> choice;

    switch (choice) {
    case 1: {

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
                cout << "4.Logout" << endl;
                cout << "Enter your choice : " << endl;
                int choice_num;
                cin >> choice_num;
                if (choice_num == 3)
                {

                    cout << "\n******* REGISTER FOR A NEW MEMBER ******** " << endl;
                    cout << "\n1. Register as a Customer" << "\n";
                    cout << "2. Register as a Driver" << "\n";
                    cout << "Your choice : ";
                    int option;
                    cin >> option;
                    if (option == 1)
                    {
                        cout << "------------- Create a customer account ------------" << endl;
                        string username, password;
                        cout << "Enter Username : ";
                        cin >> username;
                        cout << "Enter Password : ";
                        cin >> password;
                        customers.writedatatoregister_customer(username, password);
                        cout << "Register successfully !" << endl;


                    }
                    else if (option == 2)
                    {
                        cout << "---------------- Create a driver account --------------" << endl;
                        string username, password;
                        cout << "Enter Username : ";
                        cin >> username;
                        cout << "Enter Password : ";
                        cin >> password;
                        writedatatoregister_driver(username, password);
                        cout << "Register sucessfully !" << endl;
                    }


                }
            }
            else {
                cout << "Invalid username or password. Please try again." << endl;
            }
        }

        break;
    }
    case 2:
    {
        cout << "\n******* LOGIN ACCOUNT ******** " << endl;
        cout << "\n1. Login as a Customer" << "\n";
        cout << "2. Login as a Driver" << "\n";
        cout << "Your choice : ";
        int options;
        cin >> options;
        if (options == 1)
        {
            bool found = false;
            string filename = "d:/customeraccount.doc";
            string username, password, line;
            cout << "------------- Login a customer account ------------" << endl;
    
            cout << "Enter Username : ";
            cin >> username;
            cout << "Enter Password : ";
            cin >> password;
          
            ifstream fin("d:/customeraccount.doc");
            while (getline(fin, line)) {
                size_t pos = line.find('\t');
                string file_username = line.substr(0, pos);
                string file_password = line.substr(pos + 1);
                if (username == file_username && password == file_password) {
                    found = true;

                    break;
                }
            }
            fin.close();

            if (found) {
                cout << "Login successful!" << endl;
                cout << " ------------------------------------" << endl;
                cout << "| Welcome to the User Panel        |" << endl;
                cout << " ------------------------------------" << endl;
                while (true)
                {
                    cout << "\n1. Book a trip" << "\n";
                    cout << "2. Report lost item" << "\n";
                    cout << "3. View transaction history" << "\n";
                    cout << "4. Report a complaint" << "\n";
                    cout << "5. Exit" << "\n";
                    cout << "Enter your choice : ";
                    int opt;
                    cin >> opt;
                    if (opt == 1)
                    {
                        string customerName, pick_location, drop_location, fare;
                        std::time_t time = std::time(nullptr);
                        cout << "************ BOOK A TRIP **************" << endl;
                        cout << "\nEnter customer name: ";
                        cin >> customerName;
                        cout << "Enter Pick up location: ";
                        cin >> pick_location;
                        cout << "Enter Drop location: ";
                        cin >> drop_location;
                        cout << "Enter Fare : ";
                        cin >> fare;
                        customers.writeToFile_BookTripCustomer(customerName, pick_location, drop_location, fare, time);
                        cout << "Book Trip successfully !" << endl;


                    }
                    else if (opt == 2)
                    {
                        string itemName, itemDescription;
                        std::time_t time = std::time(nullptr);
                        cout << "************ REPORT LOST ITEM  **************" << endl;
                        cout << "\nEnter item name: ";
                        cin >> itemName;
                        cout << "Enter item description: ";
                        cin >> itemDescription;
                        lostitems.reportLostItem(itemName, itemDescription, time);
                        cout << "\nLost item reported successfully!" << "\n";
                    }
                    else if (opt == 3)
                    {

                    }
                    else if (opt == 4)
                    {
                        cout << "************ REPORT A COMPLAINT **************" << endl;
                        string driverName, complaint;
                        std::time_t time = std::time(nullptr);
                        cout << "\nEnter driver name: ";
                        cin >> driverName;
                        cout << "Enter complaint: ";
                        cin >> complaint;
                        lostitems.reportComplaint(complaint, driverName, time);
                        cout << "\nComplaint reported successfully!" << "\n";
                    }
                    
                }
                break;
            }
            

        }
        else if (options == 2)
        {
            bool found = false;
            cout << "---------------- Login a driver account --------------" << endl;
            string username, password,line;
            cout << "Enter Username : ";
            cin >> username;
            cout << "Enter Password : ";
            cin >> password;
            ifstream fin("d:/driveraccount.doc");
            while (getline(fin, line)) {
                size_t pos = line.find('\t');
                string file_username = line.substr(0, pos);
                string file_password = line.substr(pos + 1);
                if (username == file_username && password == file_password) {
                    found = true;
                    break;
                }
            }
            fin.close();

            if (found) {
                cout << "Login successful!" << endl;
                cout << "\n1. Book a trip" << "\n";
                cout << "2. Report lost item" << "\n";
                cout << "3. View transaction history" << "\n";
                cout << "4. Report a complaint" << "\n";
                cout << "5. Exit" << "\n";
                cout << "Enter your choice : ";
            }
            else {
                cout << "Invalid username or password." << endl;
            }
        }
        break;


    }
    case 3:
    {
        cout << "\n******* REGISTER FOR A NEW MEMBER ******** " << endl;
        cout << "\n1. Register as a Customer" << "\n";
        cout << "2. Register as a Driver" << "\n";
        cout << "Your choice : ";
        int option;
        cin >> option;
        if (option == 1)
        {
            cout << "------------- Create a customer account ------------" << endl;
            string username, password;
            cout << "Enter Username : ";
            cin >> username;
            cout << "Enter Password : ";
            cin >> password;
            customers.writedatatoregister_customer(username, password);
            cout << "Register successfully !" << endl;


        }
        else if (option == 2)
        {
            cout << "---------------- Create a driver account --------------" << endl;
            string username, password;
            cout << "Enter Username : ";
            cin >> username;
            cout << "Enter Password : ";
            cin >> password;
            writedatatoregister_driver(username, password);
            cout << "Register sucessfully !" << endl;
        }
        break;
    }
    case 4:
    {
        cout << "GOODBYE ! " << endl;
    }
    }
    return 0;

}