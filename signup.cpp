// Copywrite 2022
// CGI for Used Car Web Application
// Allows user to create a new account
// Author: Caleb Mostyn

#define MYSQLPP_MYSQL_HEADERS_BURIED
#include <mysql++/mysql++.h>
#include <unistd.h>
#include <stdlib.h>
#include <string>
#include <iostream>
#include <map>
#include "getpost.h"

using std::cin;
using std::cout;
using std::endl;
using std::string;

// Retreives relevent user info
// and submits it to database
int main()
{
    // POST results
    map<string, string> Get;
    initializePost(Get);

    // Retreiving relevent user info
    std::string username = Get["username"];
    std::string password = Get["password"];
    std::string email = Get["email"];
    std::string city = Get["city"];
    std::string phoneNumber = Get["phoneNumber"];

    // Connecting to mySQL
    mysqlpp::Connection conn(false);
    if (conn.connect("cse278", "localhost", "cse278", "MonSepM1am1"))
    {

        mysqlpp::SimpleResult result1;
        mysqlpp::SimpleResult result2;

        // Checks for unique entries for user data
        if (username != "Username" && password != "Password" && email != "Email Address"
            && city != "City" && phoneNumber != "Phone Number")
        {
            // Inserting new user info to authentication table
            mysqlpp::Query query1 = conn.query();
            query1 << "INSERT INTO mostyncrUsers VALUES ('" + username + "', '" + password + "');";
            query1.parse();
            result1 = query1.execute();

            // Inserting user info into info table
            mysqlpp::Query query2 = conn.query();
            query2 << "INSERT INTO mostyncrUserInfo VALUES ('" + username + "', '" + email + "', '" + city + "', '" + phoneNumber + "');";
            query2.parse();
            result2 = query2.execute();
        }
        if (result1 && result2)
        {
            // Successful account creation
            // Redirects user to main.html
            cout << "Content-type: text/html" << endl
                 << endl;
            cout << "<html><head><meta http-equiv=\"refresh\" content=\"0;";
            cout << " URL=main.html#" + username + "\"></head>" << endl;
        }
        else
        {
            // Unssuccessful account creation
            // Redirects user back to signup.html
            cout << "Content-type: text/html" << endl
                 << endl;
            cout << "<html><head><meta http-equiv=\"refresh\" content=\"0;";
            cout << " URL=signup.html#1\"></head>" << endl;
        }
    }
    else
    {
        // Connection failed
        // Redirects user back to signup.html
        cout << "Content-type: text/html" << endl
             << endl;
        cout << "<html><head><meta http-equiv=\"refresh\" content=\"0;";
        cout << " URL=signup.html#1\"></head>" << endl;
    }
}
