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
#include <filesystem>
#include <time.h>     
#include <algorithm>
#include <cmath>



using namespace std;
// File Names
string REPORT_ITEM = "d:/LostItems.csv";
string REPORT_COMPLAINT = "d:/ReportComplaints.csv";
string CUSTOMER = "d:/Customer.csv";
string DRIVER = "d:/Driver.csv";
string TRIP_BOOK = "d:/BookTrip.csv";

struct TripDetails {
    string tripid;
    string pickupLocation;
    string destination;
    string dateOfTravel;
    string timeOfTravel;
    time_t time_date{};
    double fare{};
    float distance{}; // in kilometers
    string status;
};


struct ReportComplaint {
    string driverName;
    string complaintDescription;
    time_t time_date{};
};
struct UserAccount {

    string UserId;
    string username;
    string password;
    string phoneNumber;
    string email;
};
struct ReportItem {
    string itemName;
    string itemDescription;
    string location;
    time_t time_date{};
};
struct DriverAccount {
    string DriverId;
    string name;
    string email;
    string password;
    string phone;
    string licenseNumber;
    string carLicensePlate;
};


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


class Driver {
public:

    string trim(const string& str) {
        size_t start = str.find_first_not_of(" \t\r\n");
        size_t end = str.find_last_not_of(" \t\r\n");
        return (start != string::npos && end != string::npos) ? str.substr(start, end - start + 1) : "";
    }

    void acceptTripByDriver(string driverid, string driverName) {
        Sleep(700);
        system("cls");

        cout << "\n| ----------REQUESTED TRIP------------|" << endl;
        // Open the trip booking file in input/output mode
        fstream file(TRIP_BOOK, ios::in | ios::out);
        if (!file) {
            cerr << "Error: could not open file " << TRIP_BOOK << endl;
            return;
        }


        string line;
        getline(file, line);


        // Find the oldest pending trip and print its details
        bool found = false;
        while (getline(file, line)) {
            stringstream ss(line);
            string field;
            getline(ss, field, ',');
            string tripId = field;
            getline(ss, field, ',');
            string userId = field;
            getline(ss, field, ',');
            string userName = field;
            getline(ss, field, ',');
            string driver = field;
            getline(ss, field, ',');
            string status = field;
            getline(ss, field, ',');
            string pickupLocation = field;
            getline(ss, field, ',');
            string destination = field;
            getline(ss, field, ',');
            string distance = field;
            getline(ss, field, ',');
            string dateOfTravel = field;
            getline(ss, field, ',');
            string timeOfTravel = field;
            getline(ss, field, ',');
            string fare = field;
            getline(ss, field);
            string timeDate = field;

            if (status == "Pending") {
                found = true;

                // Print the details of the pending trip

                cout << "\nTrip id :" << tripId << endl;
                cout << "User id :" << userId << endl;
                cout << "User name :" << userName << endl;
                cout << "Pickup location :" << pickupLocation << endl;
                cout << "Destination :" << destination << endl;
                cout << "Distance :" << distance << endl;
                cout << "Date of travel :" << dateOfTravel << endl;
                cout << "Time of travel :" << timeOfTravel << endl;
                cout << "Fare :" << fare << endl;

                // Ask the driver if they want to accept or reject the trip
                char choice;
                cout << "\nDo you want to accept this trip? (y/n) ";
                cin >> choice;

                if (choice == 'y') {
                    // Update the driver name and status for the trip
                    stringstream update;
                    update << tripId << ",";
                    update << userId << ",";
                    update << userName << ",";
                    update << driverName << ",";
                    update << "Accepted" << ",";
                    update << pickupLocation << ",";
                    update << destination << ",";
                    update << distance << ",";
                    update << dateOfTravel << ",";
                    update << timeOfTravel << ",";
                    update << fare << ",";
                    update << timeDate;

                    // Position the output pointer at the start of the line and write the entire line
                    streampos pos = file.tellg();
                    file.seekp(pos - static_cast<streamoff>(line.length()), ios::beg);
                    file << update.str() << endl;

                    cout << "\nTrip with trip ID " << tripId << " has been accepted by " << driverName << "." << endl;
                    break;
                }
                else {
                    cout << "\nTrip with trip ID " << tripId << " has been rejected by " << driverName << "." << endl;
                    break;
                }
            }
        }

        if (!found) {
            cout << "Error: no pending trips found." << endl;
        }

        file.close();

    }
    void viewAcceptedTripsByDriver(string driverName) {
        Sleep(700);
        system("cls");

        // Open the trip booking file in input mode
        ifstream file(TRIP_BOOK, ios::in);
        if (!file) {
            cerr << "Error: could not open file " << TRIP_BOOK << endl;
            return;
        }
        cout << "\n|-------------- VIEW ACCEPTED TRIP------------|\n" << endl;
        // Set the column widths and alignment
        const int idWidth = 13;
        const int nameWidth = 15;
        const int locWidth = 15;
        const int fareWidth = 10;
        const int dateWidth = 15;
        cout << left << setw(idWidth) << "ID" << setw(nameWidth) << "Name"
            << setw(locWidth) << "Pickup " << setw(locWidth) << "Destination"
            << setw(locWidth) << "Distance"
            << setw(dateWidth) << "Date Travel" << setw(dateWidth) << "Time Travel"
            << right << setw(fareWidth) << "Fare" << endl;

        // Print the details of all completed trips by the driver
        string line;
        getline(file, line); // Skip the header row

        bool found = false;
        while (getline(file, line)) {
            stringstream ss(line);
            string field;
            getline(ss, field, ',');
            string tripId = field;
            getline(ss, field, ',');
            string userId = field;
            getline(ss, field, ',');
            string userName = field;
            getline(ss, field, ',');
            string driver = field;
            getline(ss, field, ',');
            string status = field;
            getline(ss, field, ',');
            string pickupLocation = field;
            getline(ss, field, ',');
            string destination = field;
            getline(ss, field, ',');
            string distance = field;
            getline(ss, field, ',');
            string dateOfTravel = field;
            getline(ss, field, ',');
            string timeOfTravel = field;
            getline(ss, field, ',');
            string fare = field;
            getline(ss, field);
            string timeDate = field;

            if (status == "Accepted" && driver == driverName) {
                found = true;

                // Print the details of the completed trip in a formatted table
                cout << left << setw(idWidth) << tripId << setw(nameWidth) << userName
                    << setw(locWidth) << pickupLocation << setw(locWidth) << destination
                    << setw(locWidth) << distance
                    << setw(dateWidth) << dateOfTravel << setw(dateWidth) << timeOfTravel
                    << right << setw(fareWidth) << fare << endl;
            }
        }

        if (!found) {
            cout << "No completed trips found for driver " << driverName << "." << endl;
        }

        file.close();


    }
    void viewAvailableTrips() {
        Sleep(700);
        system("cls");
        // Open the trips file for reading
        ifstream file(TRIP_BOOK);

        // Check if the file is open
        if (!file.is_open()) {
            cout << "Error opening file." << endl;
            return;
        }
        cout << "\n|---------- AVAILABLE TRIPS-----------|" << endl;
        // Read the file and display the trips with status "Pending"
        string line;
        getline(file, line); // Skip the header row
        while (getline(file, line)) {
            stringstream ss(line);
            string tripIdStr;
            string userId;
            string name;
            string driverName;
            string status;
            string pickup;
            string destination;
            string distance;
            string dateOfTravel;
            string timeOfTravel;
            string fare;
            string time_date;
            getline(ss, tripIdStr, ',');
            getline(ss, userId, ',');
            getline(ss, name, ',');
            getline(ss, driverName, ',');
            getline(ss, status, ',');
            getline(ss, pickup, ',');
            getline(ss, destination, ',');
            getline(ss, distance, ',');
            getline(ss, dateOfTravel, ',');
            getline(ss, timeOfTravel, ',');
            getline(ss, fare, ',');
            getline(ss, time_date, ',');
            if (status == "Pending") {
                cout << "\n" << tripIdStr << " - " << name << " (" << pickup << " to " << destination << " on " << dateOfTravel << " at " << timeOfTravel << ") - " << fare << endl;
            }
        }

        // Close the file
        file.close();
    }



    void loginDriver() {
        Sleep(700);
        system("cls");

        ifstream infile(DRIVER);
        int attempts = 0;
        string line;
        stringstream ss;
        cout << "+-----------------------------------+" << endl;
        cout << "|           User Login              |" << endl;
        cout << "+-----------------------------------+" << endl;
        while (attempts < 3) {
            cout << "\nEnter Username : ";
            string username;
            cin >> username;

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

            bool isLoggedIn = false;
            while (getline(infile, line)) {
                ss.clear(); // clear any error flags from previous read
                ss.str(line); // set the string stream to the current line

                string DriverId, fileUsername, email, phoneNumber, licenseNumber, carLicense, filePassword;
                getline(ss, DriverId, ',');
                getline(ss, fileUsername, ',');
                getline(ss, email, ',');
                getline(ss, phoneNumber, ',');
                getline(ss, licenseNumber, ',');
                getline(ss, carLicense, ',');
                getline(ss, filePassword, ',');

                if (fileUsername == username && filePassword == password) {
                    isLoggedIn = true;
                    cout << "\nLoading......." << endl;
                    Sleep(800);
                    system("cls");

                    cout << "\nLogin successful " << endl;
                    cout << " ------------------------------------" << endl;
                    cout << "| Welcome to the User Panel         |" << endl;
                    cout << " ------------------------------------" << endl;
                    cout << "\nYour UserId is: " << DriverId << endl;
                    while (true) {
                        cout << "\n1. View available trips" << endl;
                        cout << "2. Accept a trip" << endl;
                        cout << "3. Complete a trip" << endl;
                        cout << "4. Exit" << endl;


                        int opt;
                        while (true) {
                            cout << "Enter your choice (1-4): ";
                            cin >> opt;

                            if (cin.fail() || opt < 1 || opt > 4) {
                                cout << "Invalid input. Please enter a number between 1 and 4." << endl;
                                cin.clear();
                                cin.ignore(10000, '\n'); // ignore any remaining input in the buffer
                            }
                            else {
                                break;
                            }
                        }
                        if (opt == 1) {
                            viewAvailableTrips();

                        }
                        else if (opt == 2) {
                            acceptTripByDriver(DriverId, fileUsername);


                        }
                        else if (opt == 3) {
                            viewAcceptedTripsByDriver(fileUsername);
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
            }
            if (!isLoggedIn) {
                cout << "\nInvalid username or password. Try again." << endl;
                attempts++;
            }
            else {
                break;
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

    void reportComplaint(string userId) {
        Sleep(700);
        system("cls");

        ofstream outfile(REPORT_COMPLAINT, ios::app);
        ReportComplaint reportComplaint;
        cout << "\n|------- REPORT COMPLAINT -------|" << endl;
        cout << "\nEnter driver name: ";
        cin >> reportComplaint.driverName;
        cout << "Enter complaint description: ";
        cin.ignore(); // to clear the newline character from the input buffer
        cin >> reportComplaint.complaintDescription;

        reportComplaint.time_date = std::time(nullptr);

        // Check if the file is empty
        ifstream infile(REPORT_COMPLAINT);
        bool isEmpty = infile.peek() == std::ifstream::traits_type::eof();
        infile.close();

        // Write column names to file if it's empty
        if (isEmpty) {
            outfile << "user Id ,Driver Name, Complaint Description, Time/Date" << endl;
        }

        // Add complaint to the file
        outfile << userId << ",";
        outfile << reportComplaint.driverName << ",";
        outfile << reportComplaint.complaintDescription << ",";
        outfile << std::asctime(std::localtime(&reportComplaint.time_date));

        outfile.close();
        cout << "\nThank you for reporting the complaint. We will look into the matter and get back to you soon." << endl;
    }

    void reportLostItem(string userId) {

        Sleep(700);
        system("cls");
        cout << "\n|------- REPORT FOR LOST ITEMS -------|" << endl;
        ofstream outfile(REPORT_ITEM, ios::app);
        ReportItem item;
        cout << "\nEnter location where the item was lost: ";
        cin >> item.location;
        cout << "Enter item name: ";
        cin >> item.itemName;
        cout << "Enter item description: ";
        cin.ignore(); // to clear the input buffer before getline
        getline(cin, item.itemDescription);
        item.time_date = std::time(nullptr);

        // Check if file is empty
        ifstream infile(REPORT_ITEM);
        bool is_empty = infile.peek() == ifstream::traits_type::eof();
        infile.close();

        // Add header row if file is empty
        if (is_empty) {
            outfile << "User ID,Location,Item Name,Item Description,Time/Date\n";
        }

        // Add item to the file
        outfile << userId << ",";
        outfile << item.location << ",";
        outfile << item.itemName << ",";
        outfile << item.itemDescription << ",";
        outfile << std::asctime(std::localtime(&item.time_date));


        outfile.close();
        cout << "\nThank you for reporting the lost item. We will try our best to locate it." << endl;
    }
    string generateTripId() {
        static int idCounter = 0; // Initialize the trip ID counter
        std::ostringstream oss;
        oss << "TRIPID" << std::setfill('0') << std::setw(2) << idCounter; // 
        idCounter++; // Increment the trip ID counter for the next trip
        return oss.str();
    }


    void bookTrip(string userId, string Name) {
        Sleep(700);
        system("cls");
        cout << "\n|------- BOOK TRIP -------|" << endl;
        ofstream outfile(TRIP_BOOK, ios::app);
        TripDetails trip;
        cout << "\nEnter pickup location: ";
        cin >> trip.pickupLocation;
        cout << "Enter destination: ";
        cin >> trip.destination;
        cout << "Enter date of travel (MM/DD/YYYY):";
        cin >> trip.dateOfTravel;
        cout << "Enter time of travel (24-hr format): ";
        cin >> trip.timeOfTravel;
        trip.time_date = std::time(nullptr);
        trip.status = "Pending";
        trip.tripid = generateTripId(); // generate a unique trip ID
        const float RATE_PER_KM = 3.50; // define rate per kilometer

        cout << "Enter distance of the trip in kilometers: ";
        cin >> trip.distance;

        trip.fare = trip.distance * RATE_PER_KM;
        cout << "Fare is $" << trip.fare << endl;

        // Add header row if file is empty
        ifstream infile(TRIP_BOOK);
        bool is_empty = infile.peek() == ifstream::traits_type::eof();
        infile.close();
        if (is_empty) {
            outfile << "Trip ID,User ID,Name,Driver Name,Status,Pickup Location,Destination,Distance,DateofTravel,Time of Travel,Fare,Time/Date\n";
        }

        // Add trip details to the file
        outfile << trip.tripid << ",";
        outfile << userId << ",";
        outfile << Name << ",";
        outfile << ","; // Driver name is not yet known at this point
        outfile << trip.status << ",";
        outfile << trip.pickupLocation << ",";
        outfile << trip.destination << ",";
        outfile << trip.distance << ",";
        outfile << trip.dateOfTravel << ",";
        outfile << trip.timeOfTravel << ",";
        outfile << "$" << trip.fare << ",";
        outfile << std::asctime(std::localtime(&trip.time_date));

        outfile.close();
        cout << "\nTrip booked successfully! Please wait for a driver to accept your request." << endl;

    }
    void viewBookingHistory(string userId) {
        Sleep(700);
        system("cls");
        ifstream infile(TRIP_BOOK);
        cout << "\n|------- VIEW BOOKING TRIP HISTORY -------|" << endl;
        string line;
        bool header = true; // flag to skip header row
        int count = 0;
        while (getline(infile, line)) {
            if (header) {
                header = false;
                continue;
            }
            stringstream ss(line);
            vector<string> tokens;
            string token;
            while (getline(ss, token, ',')) {
                tokens.push_back(token);
            }
            if (tokens.size() >= 11 && tokens[1] == userId) {
                count++;
                if (count == 1) {
                    cout << "\nBooking history for user ID : " << userId << "\n";
                }
                cout << "\nTrip ID: " << tokens[0] << endl;
                cout << "Driver name: " << tokens[3] << endl;
                cout << "Status: " << tokens[4] << endl;
                cout << "Pickup location: " << tokens[5] << endl;
                cout << "Destination: " << tokens[6] << endl;
                cout << "Distance :" << tokens[7] << endl;
                cout << "Date of travel: " << tokens[8] << endl;
                cout << "Time of travel: " << tokens[9] << endl;
                cout << "Fare: " << tokens[10] << endl;
                cout << "Time/date: " << tokens[11] << endl;
            }
        }
        if (count == 0) {
            cout << "\nNo booking history found for user ID " << userId << "." << endl;
        }
        infile.close();
    }


    void loginCustomer() {
        Sleep(700);
        system("cls");
        ifstream infile(CUSTOMER);
        int attempts = 0;
        string line;
        stringstream ss;

        // Print login box
        cout << "+-----------------------------------+" << endl;
        cout << "|           User Login              |" << endl;
        cout << "+-----------------------------------+" << endl;

        while (attempts < 3) {
            cout << "\nEnter Username : ";
            string username;
            cin >> username;

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

            bool isLoggedIn = false;
            while (getline(infile, line)) {
                ss.clear(); // clear any error flags from previous read
                ss.str(line); // set the string stream to the current line

                string fileUsername, email, phoneNumber, filePassword, userId;
                getline(ss, userId, ',');
                getline(ss, fileUsername, ',');
                getline(ss, email, ',');
                getline(ss, phoneNumber, ',');
                getline(ss, filePassword, ',');

                if (fileUsername == username && filePassword == password) {
                    isLoggedIn = true;

                    // Print login success message and user menu box
                    cout << "\nLoading......." << endl;
                    Sleep(800);
                    system("cls");

                    cout << "+-----------------------------------+" << endl;
                    cout << "|       Welcome to the User Menu    |" << endl;
                    cout << "+-----------------------------------+" << endl;
                    cout << "\nYour User Id is: " << userId << endl;

                    // User menu options loop
                    while (true) {
                        cout << "\n1. Book trip" << "\n";
                        cout << "2. Report lost item" << "\n";
                        cout << "3. Report a complaint" << "\n";
                        cout << "4. View your booking history" << "\n";
                        cout << "5. Exit" << "\n";


                        int opt;

                        while (true) {
                            cout << "Enter your choice (1-5): ";
                            cin >> opt;

                            if (cin.fail() || opt < 1 || opt > 5) {
                                cout << "Invalid input. Please enter a number between 1 and 5." << endl;
                                cin.clear();
                                cin.ignore(10000, '\n'); // ignore any remaining input in the buffer
                            }
                            else {
                                break;
                            }
                        }

                        if (opt == 1) {
                            bookTrip(userId, username);
                        }
                        else if (opt == 2) {
                            reportLostItem(userId);
                        }
                        else if (opt == 3) {
                            reportComplaint(userId);
                        }
                        else if (opt == 4) {
                            viewBookingHistory(userId);
                        }
                        else if (opt == 5) {
                            break; // exit while loop and program
                        }
                        else {
                            cout << "\nInvalid option. Try again." << endl;
                        }
                    }

                    break;
                }
            }

            if (!isLoggedIn) {
                cout << "\nInvalid username or password. Try again." << endl;
                attempts++;
            }
            else {
                break;
            }
        }

        infile.close();

        if (attempts >= 3) {
            cout << "\nMaximum login attempts exceeded. Please try again later." << endl;
        }
    }

};
class Admin
{
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
    vector<string> split(string str, char delimiter) {
        vector<string> tokens;
        stringstream ss(str);
        string token;
        while (getline(ss, token, delimiter)) {
            tokens.push_back(token);
        }
        return tokens;
    }

    void registerDriver() {
        Sleep(700);
        system("cls");

        // Open the DRIVER CSV file in append mode
        ofstream outfile(DRIVER, ios::app);
        if (!outfile) {
            cerr << "Error: could not open file " << DRIVER << endl;
            return;
        }

        cout << "\n|------------- CREATE A DRIVER ACCOUNT ------------" << endl;

        // Create a new Driver object
        DriverAccount driver;

        // Generate a new DriverId as the number of lines in the file plus 1
        int driverId = 1;
        string line;
        ifstream countFile(DRIVER);
        getline(countFile, line);  // skip the column names
        while (getline(countFile, line)) {
            driverId++;
        }
        countFile.close();
        driver.DriverId = driverId;

        // Prompt the user to enter the driver information
        cout << "\nEnter  name: ";
        cin.ignore();
        getline(cin, driver.name);
        cout << "Enter email address: ";
        cin >> driver.email;
        cout << "Enter phone number: ";
        cin >> driver.phone;
        cout << "Enter license number: ";
        cin.ignore();
        getline(cin, driver.licenseNumber);
        cout << "Enter car license plate: ";
        cin >> driver.carLicensePlate;
        cout << "Enter password: ";
        driver.password = get_password();

        // Write column names to the file if it's empty
        ifstream checkFile(DRIVER);
        if (checkFile.peek() == ifstream::traits_type::eof()) {
            outfile << "DriverId,Name,Email,PhoneNumber,LicenseNumber,Car License Plate,Password" << endl;
        }
        countFile.close();

        // Add driver to the file
        outfile << driverId << ",";
        outfile << driver.name << ",";
        outfile << driver.email << ",";
        outfile << driver.phone << ",";
        outfile << driver.licenseNumber << ",";
        outfile << driver.carLicensePlate << ",";
        outfile << driver.password << endl;

        outfile.close();

        cout << "Driver registration successful." << endl;
        Sleep(1000);
        system("cls");
    }
    void registerCustomer() {
        Sleep(700);
        system("cls");

        // Open the CUSTOMER CSV file in append mode
        ofstream outfile(CUSTOMER, ios::app);
        if (!outfile) {
            cerr << "Error: could not open file " << CUSTOMER << endl;
            return;
        }

        cout << "\n|------------- CREATE A CUSTOMER ACCOUNT ------------|" << endl;

        // Create a new UserAccount object
        UserAccount account;

        // Generate a new UserId as the number of lines in the file plus 1
        int userId = 1;
        string line;
        ifstream countFile(CUSTOMER);
        getline(countFile, line);  // skip the column names
        while (getline(countFile, line)) {
            userId++;
        }
        countFile.close();
        account.UserId = userId;

        // Prompt the user to enter the account information
        cout << "Enter username: ";
        cin.ignore();
        getline(cin, account.username);
        cout << "Enter email address: ";
        cin >> account.email;
        cout << "Enter phone number: ";
        cin >> account.phoneNumber;
        cout << "Enter password: ";
        account.password = get_password();

        // Write column names to the file if it's empty
        ifstream checkFile(CUSTOMER);
        if (checkFile.peek() == ifstream::traits_type::eof()) {
            outfile << "UserId,Name,Email,PhoneNumber,Password" << endl;
        }
        checkFile.close();

        // Add account to the file
        outfile << userId << ",";
        outfile << account.username << ",";
        outfile << account.email << ",";
        outfile << account.phoneNumber << ",";
        outfile << account.password << endl;

        outfile.close();

        cout << "Customer registration successful." << endl;
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
        cout << "+-----------------------------------+" << endl;
        cout << "|           Admin Login              |" << endl;
        cout << "+-----------------------------------+" << endl;
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
                        cout << " |    WELCOME TO ADMINISTRATOR MENU  |" << endl;
                        cout << "  ------------------------------------" << endl;
                        cout << "\n1. View all trips" << endl;
                        cout << "2. Delete customer / driver" << endl;
                        cout << "3. Add new customer / driver" << endl;
                        cout << "4. Update customer " << endl;
                        cout << "5. View all driver" << endl;
                        cout << "6. View all customer " << endl;
                        cout << "7. View report lost item" << endl;
                        cout << "8. View report complaint" << endl;
                        cout << "9. Exit" << "\n";
                        int choice_num;
                        while (true) {
                            cout << "Enter your choice (1-9): ";
                            cin >> choice_num;

                            if (cin.fail() || choice_num < 1 || choice_num > 9) {
                                cout << "Invalid input. Please enter a number between 1 and 9." << endl;
                                cin.clear();
                                cin.ignore(10000, '\n'); // ignore any remaining input in the buffer

                            }
                            else {
                                break;
                            }
                        }
                        switch (choice_num) {
                        case 1:
                            viewAllBookingHistroy();
                            break;
                        case 2:

                            Sleep(700);
                            system("cls");
                            cout << "+---------------------------------+" << endl;
                            cout << "|       Delete User Account       |" << endl;
                            cout << "+---------------------------------+" << endl;
                            cout << "\nPlease select the type of account to delete:\n";
                            cout << "1. Delete Customer Account\n";
                            cout << "2. Delete Driver Account\n";
                            int option;
                            while (true) {
                                cout << "Enter your choice (1-2): ";
                                cin >> option;

                                if (cin.fail() || option < 1 || option > 2) {
                                    cout << "Invalid input. Please enter a number between 1 and 2." << endl;
                                    cin.clear();
                                    cin.ignore(10000, '\n'); // ignore any remaining input in the buffer
                                }
                                else {
                                    break;
                                }
                            }
                            if (option == 1)
                                deleteCustomerAccount();
                            else if (option == 2)
                                deleteDriverAccount();
                            else {
                                cout << "Invalid choice" << endl;
                            }

                            break;
                        case 3:

                            Sleep(700);
                            system("cls");
                            cout << "+----------------------------------------+" << endl;
                            cout << "|     REGISTER FOR A NEW MEMBER          |" << endl;
                            cout << "+----------------------------------------+" << endl;
                            cout << "\nPlease select your member type:\n";
                            cout << "\n1. Register  Customer" << "\n";
                            cout << "2. Register  Driver" << "\n";
                            int opt;
                            while (true) {
                                cout << "Enter your choice (1-2): ";
                                cin >> opt;

                                if (cin.fail() || opt < 1 || opt > 2) {
                                    cout << "Invalid input. Please enter a number between 1 and 2." << endl;
                                    cin.clear();
                                    cin.ignore(10000, '\n'); // ignore any remaining input in the buffer
                                }
                                else {
                                    break;
                                }
                            }
                            if (opt == 1)
                                registerCustomer();
                            else if (opt == 2)
                                registerDriver();
                            else {
                                cout << "Invalid choice" << endl;
                            }

                            break;

                        case 4:

                            UpdateCustomerAccount();
                            break;


                        case 5:
                            viewAllDrivers();
                            break;
                        case 6:
                            viewAllCustomer();
                            break;
                        case 7:
                            viewAllReportLost();
                            break;
                        case 8:
                            viewAllReportComplaint();
                            break;
                        case 9:
                            return;
                            break;
                        default:
                            cout << "Invalid choice. Please try again." << endl;
                            break;

                        }

                    }
                    break;
                  

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
   
    
    void UpdateCustomerAccount() {
        Sleep(700);
        system("cls");

        cout << "+-----------------------------------------------+" << endl;
        cout << "|     Update Customer Account Information      |" << endl;
        cout << "+-----------------------------------------------+" << endl;

        // Prompt the admin to enter the UserId of the account to be updated
        string userId;
        cout << "\nEnter the UserId of the account to be updated: ";
        cin >> userId;

        // Open the CUSTOMER CSV file in input/output mode
        fstream file(CUSTOMER, ios::in | ios::out);
        if (!file) {
            cerr << "Error: could not open file " << CUSTOMER << endl;
            return;
        }

        // Print the column names
        string line;
        getline(file, line);

        // Update the name and email fields for the account with the matching UserId
        bool found = false;

        while (getline(file, line)) {
            stringstream ss(line);
            string field;
            getline(ss, field, ',');
            string rowUserId = field;
            getline(ss, field, ',');
            string userName = field;
            getline(ss, field, ',');
            string email = field;
            getline(ss, field, ',');
            string phoneNumber = field;
            getline(ss, field, ',');
            string password = field;

            if (rowUserId == userId) {
                found = true;

                // Prompt the admin to enter the new name and email for the account
                string newUserName, newEmail;
                cout << "Enter the new name for the account: ";
                cin.ignore();
                getline(cin, newUserName);
                cout << "Enter the new email for the account: ";
                cin >> newEmail;
                cout << "Enter the new phone number  for the account: ";
                cin >> phoneNumber;
                cout << "Enter the new password  for the account: ";
                cin >> password;

                // Construct the updated line as a string
                stringstream updatedLine;
                updatedLine << newUserName << ",";
                updatedLine << newEmail << ",";
                updatedLine << phoneNumber << ",";
                updatedLine << password;

                // Get the current position in the file and overwrite the old line with the updated line
                streampos pos = file.tellg();
                file.seekp(pos - static_cast<streamoff>(line.length()), ios::beg);
                file << updatedLine.str() << endl;

                cout << "Customer account with UserId " << userId << " has been updated." << endl;
                break;
            }
        }

        if (!found) {
            cout << "Error: customer account with UserId " << userId << " not found." << endl;
        }

        file.close();
    }

    void deleteCustomerAccount() {
        Sleep(700);
        system("cls");
        cout << "\n|------------- Delete  customer account ------------|" << endl;

        // Prompt the admin to enter the UserId of the account to be deleted
        int userId;
        cout << "\nEnter the UserId of the account to be deleted: ";
        cin >> userId;

        // Open the CUSTOMER CSV file in input mode
        ifstream infile(CUSTOMER);
        if (!infile) {
            cerr << "Error: could not open file " << CUSTOMER << endl;
            return;
        }

        // Read the contents of the file into memory
        vector<string> lines;
        string line;
        getline(infile, line);  // read and ignore the column names
        while (getline(infile, line)) {
            lines.push_back(line);
        }
        infile.close();

        // Delete the desired row from the data in memory
        bool found = false;
        for (auto it = lines.begin(); it != lines.end(); it++) {
            stringstream ss(*it);
            string field;
            getline(ss, field, ',');
            int rowUserId = stoi(field);
            if (rowUserId == userId) {
                lines.erase(it);
                found = true;
                break;
            }
        }

        // Overwrite the input file with the updated data
        if (found) {
            ofstream outfile(CUSTOMER);
            outfile << "UserId,Name,Email,PhoneNumber,Password" << endl;
            for (auto it = lines.begin(); it != lines.end(); it++) {
                outfile << *it << endl;
            }
            outfile.close();
            cout << "Customer account with UserId " << userId << " has been deleted." << endl;
        }
        else {
            cout << "Error: customer account with UserId " << userId << " not found." << endl;
        }

        Sleep(1000);
        system("cls");
    }
    void viewAllDrivers() {
        Sleep(700);
        system("cls");
        cout << "\n|------------- All drivers ------------|" << endl;

        // Open the DRIVER CSV file in input mode
        ifstream infile(DRIVER);
        if (!infile) {
            cerr << "Error: could not open file " << DRIVER << endl;
            return;
        }

        // Read and print the column names
        string line;
        getline(infile, line);  // read and ignore the column names
        stringstream ss(line);
        string field;
        cout << left << setw(12) << "DriverId"
            << left << setw(15) << "Name"
            << left << setw(15) << "Email "
            << left << setw(20) << "Phone Number"
            << left << setw(20) << "License Number"
            << left << setw(12) << "Car License" << endl;

        // Read and print each row of data
        while (getline(infile, line)) {
            stringstream ss(line);
            getline(ss, field, ',');
            cout << left << setw(12) << field;  // DriverId
            getline(ss, field, ',');
            cout << left << setw(15) << field;  //  Name
            getline(ss, field, ',');
            cout << left << setw(15) << field;  // email 
            getline(ss, field, ',');
            cout << left << setw(20) << field;  // Phone Number
            getline(ss, field, ',');
            cout << left << setw(20) << field;  // License Number
            getline(ss, field, ',');
            cout << left << setw(12) << field << endl;  // car license
        }

        infile.close();

    }

    void viewAllReportLost() {
        Sleep(700);
        system("cls");
        cout << "\n|------------- Report lost item ------------|" << endl;


        ifstream infile(REPORT_ITEM);
        if (!infile) {
            cerr << "Error: could not open file " << REPORT_ITEM << endl;
            return;
        }

        // Read and print the column names
        string line;
        getline(infile, line);  // read and ignore the column names
        stringstream ss(line);
        string field;
        cout << left << setw(12) << "User Id"
            << left << setw(15) << "Location"
            << left << setw(15) << "Item Name "
            << left << setw(20) << "Item Description"
            << left << setw(20) << "Time / Date" << endl;


        // Read and print each row of data
        while (getline(infile, line)) {
            stringstream ss(line);
            getline(ss, field, ',');
            cout << left << setw(12) << field;  // userid
            getline(ss, field, ',');
            cout << left << setw(15) << field;  //  location
            getline(ss, field, ',');
            cout << left << setw(15) << field;  // item name
            getline(ss, field, ',');
            cout << left << setw(20) << field;  // item description
            getline(ss, field, ',');
            cout << left << setw(20) << field << endl; // time/ date

        }

        infile.close();

    }
    void viewAllReportComplaint() {
        Sleep(700);
        system("cls");
        cout << "\n|------------- Report complaint ------------|" << endl;


        ifstream infile(REPORT_COMPLAINT);
        if (!infile) {
            cerr << "Error: could not open file " << REPORT_COMPLAINT << endl;
            return;
        }

        // Read and print the column names
        string line;
        getline(infile, line);  // read and ignore the column names
        stringstream ss(line);
        string field;
        cout << left << setw(12) << "User Id"
            << left << setw(15) << "Driver Name"
            << left << setw(26) << "Complaint Description "
            << left << setw(20) << "Time / Date" << endl;


        // Read and print each row of data
        while (getline(infile, line)) {
            stringstream ss(line);
            getline(ss, field, ',');
            cout << left << setw(12) << field;  // userid
            getline(ss, field, ',');
            cout << left << setw(15) << field;  //  driver name
            getline(ss, field, ',');
            cout << left << setw(26) << field;  //  complaint description
            getline(ss, field, ',');
            cout << left << setw(20) << field << endl;;  // time 


        }

        infile.close();

    }
    void viewAllCustomer() {

        Sleep(700);
        system("cls");
        cout << "\n|------------- All Customer ------------|" << endl;

        // Open the CUSTOMER CSV file in input mode
        ifstream infile(CUSTOMER);
        if (!infile) {
            cerr << "Error: could not open file " << CUSTOMER << endl;

        }

        // Read and print the column names
        string line;
        getline(infile, line);  // read and ignore the column names
        stringstream ss(line);
        string field;
        cout << left << setw(12) << "User Id"
            << left << setw(15) << "Name"
            << left << setw(15) << "Email "
            << left << setw(20) << "Phone Number" << endl;

        // Read and print each row of data
        while (getline(infile, line)) {
            stringstream ss(line);
            getline(ss, field, ',');
            cout << left << setw(12) << field;  // User id 
            getline(ss, field, ',');
            cout << left << setw(15) << field;  //  Name
            getline(ss, field, ',');
            cout << left << setw(15) << field;  // email 
            getline(ss, field, ',');
            cout << left << setw(20) << field << endl;  // Phone Number

        }

        infile.close();

    }
    void viewAllBookingHistroy() {
        Sleep(700);
        system("cls");
        ifstream infile(TRIP_BOOK);
        string line;
        bool header = true; // flag to skip header row
        int count = 0;
        cout << "\n|------------- View Booking History--------------|" << endl;
        while (getline(infile, line)) {
            if (header) {
                header = false;
                continue;
            }
            stringstream ss(line);
            vector<string> tokens;
            string token;
            while (getline(ss, token, ',')) {
                tokens.push_back(token);
            }
            if (tokens.size() >= 12) {
                count++;
                if (count == 1) {
                    cout << "\nTrip Bookig " << endl;
                }
                cout << "\nTrip ID: " << tokens[0] << endl;
                cout << "Driver name: " << tokens[3] << endl;
                cout << "Status: " << tokens[4] << endl;
                cout << "Pickup location: " << tokens[5] << endl;
                cout << "Destination: " << tokens[6] << endl;
                cout << "Distance :" << tokens[7] << endl;
                cout << "Date of travel: " << tokens[8] << endl;
                cout << "Time of travel: " << tokens[9] << endl;
                cout << "Fare: " << tokens[10] << endl;
                cout << "Time/date:" << tokens[11] << endl;
            }
        }
        if (count == 0) {
            cout << "\nNo booking history " << endl;
        }
        infile.close();
    }

    void deleteDriverAccount() {
        Sleep(700);
        system("cls");
        cout << "\n|------- Delete  driver account ------------|" << endl;

        // Prompt the admin to enter the driverId of the account to be deleted
        int userId;
        cout << "\nEnter the Driver Id of the account to be deleted: ";
        cin >> userId;


        ifstream infile(DRIVER);
        if (!infile) {
            cerr << "Error: could not open file " << DRIVER << endl;
            return;
        }

        // Read the contents of the file into memory
        vector<string> lines;
        string line;
        getline(infile, line);  // read and ignore the column names
        while (getline(infile, line)) {
            lines.push_back(line);
        }
        infile.close();

        // Delete the desired row from the data in memory
        bool found = false;
        for (auto it = lines.begin(); it != lines.end(); it++) {
            stringstream ss(*it);
            string field;
            getline(ss, field, ',');
            int rowUserId = stoi(field);
            if (rowUserId == userId) {
                lines.erase(it);
                found = true;
                break;
            }
        }

        // Overwrite the input file with the updated data
        if (found) {
            ofstream outfile(DRIVER);
            outfile << "DriverId,Name,Email,PhoneNumber,LicenseNumber,Car License Plate,Password" << endl;
            for (auto it = lines.begin(); it != lines.end(); it++) {
                outfile << *it << endl;
            }
            outfile.close();
            cout << "Driver account with driver Id " << userId << " has been deleted." << endl;
        }
        else {
            cout << "Error: Driver account with driver Id " << userId << " not found." << endl;
        }


    }

};

void handleRegistration(Admin& admin) {
    Sleep(700);
    system("cls");
    cout << "+----------------------------------------+" << endl;
    cout << "|     REGISTER FOR A NEW MEMBER          |" << endl;
    cout << "+----------------------------------------+" << endl;
    cout << "\nPlease select your member type:\n";
    cout << "\n1. Register  Customer" << "\n";
    cout << "2. Register  Driver" << "\n";
    int choice;
    while (true) {
        cout << "Enter your choice (1-2): ";
        cin >> choice;

        if (cin.fail() || choice < 1 || choice > 2) {
            cout << "Invalid input. Please enter a number between 1 and 2." << endl;
            cin.clear();
            cin.ignore(10000, '\n'); // ignore any remaining input in the buffer
        }
        else {
            break;
        }
    }
    switch (choice) {
    case 1:
        admin.registerCustomer();
        break;
    case 2:
        admin.registerDriver();
        break;
    default:
        cout << "Invalid choice. Please try again." << endl;
        break;
    }

};

void handletologin(Customer& customer, Driver& driver) {
    Sleep(700);
    system("cls");
    cout << "+---------------------------------+" << endl;
    cout << "|         User Login              |" << endl;
    cout << "+---------------------------------+" << endl;
    cout << "\nPlease select your member type:\n";
    cout << "1. Login as Customer\n";
    cout << "2. Login as Driver\n";
    int choice;
    while (true) {
        cout << "Enter your choice (1-2): ";
        cin >> choice;

        if (cin.fail() || choice < 1 || choice > 2) {
            cout << "Invalid input. Please enter a number between 1 and 2." << endl;
            cin.clear();
            cin.ignore(10000, '\n'); // ignore any remaining input in the buffer
        }
        else {
            break;
        }
    }
    switch (choice) {
    case 1:
        customer.loginCustomer();
        break;
    case 2:
        driver.loginDriver();
        break;
    default:
        cout << "Invalid choice. Please try again." << endl;
        break;
    }
};

int main()
{
    Customer customer;
    Driver driver;
    Admin admin;
    
    do {
        Sleep(800);
        system("cls");
        cout << "+-----------------------------------+" << endl;
        cout << "|    WELCOME TO OUR TAXI BOOKING    |" << endl;
        cout << "+-----------------------------------+" << endl;
        cout << "\n1.Login as Admin" << endl;
        cout << "2.Login as User" << endl;
        cout << "3.Register New Account" << endl;
        cout << "4.For Exit " << endl;
        int choice;
        while (true) {
            cout << "Enter your choice (1-4): ";
            cin >> choice;

            if (cin.fail() || choice < 1 || choice > 4) {
                cout << "Invalid input. Please enter a number between 1 and 4." << endl;
                cin.clear();
                cin.ignore(10000, '\n'); // ignore any remaining input in the buffer
            }
            else {
                break;
            }
        }
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
    } while (true);

    return 0;
}
