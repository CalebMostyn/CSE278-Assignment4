// Copywrite 2022
// CGI for Used Car Web Application
// Facilitates SQL updates to user information
// Author: Caleb Mostyn

#define MYSQLPP_MYSQL_HEADERS_BURIED
#include <mysql++/mysql++.h>
#include <unistd.h>
#include <stdlib.h>
#include <string>
#include <iostream>
#include <map>
#include "getpost.h"

using std::cout;
using std::cin;
using std::endl;
using std::string;

// Retreives information from a dropdown
// selection as well as a textbox
// to update information in the relevent
// SQL table.
int main()
{
    // POST results
    map<string, string> Get;
    initializePost(Get);

    // Dropdown selection for detail to change
    string selection = Get["dropdown"];
    // New value for selected option
    string text = Get["text"];
    // Client username
    string username = Get["username"];

    // Connecting to mySQL
    mysqlpp::Connection conn(false);
    if (conn.connect("cse278", "localhost", "cse278", "MonSepM1am1"))
    {

        mysqlpp::SimpleResult result;

        // Checks if value was entered for updated details
        if (text != "Update Account")
        {
            // Seperate SQL queries for password and user info,
            // as they are in different tables
            if (selection == "password")
            {
                // Password update
                mysqlpp::Query query = conn.query();
                query << "UPDATE mostyncrUsers SET password = '" + text
                    + "' where username = '" + username + "';";
                query.parse();
                result = query.execute();
            }
            else
            {
                // Info update
                mysqlpp::Query query = conn.query();
                query << "UPDATE mostyncrUserInfo SET " + selection + " = '" + text
                    + "' where username = '" + username + "';";
                query.parse();
                result = query.execute();
            }
        }
        if (result)
        {
            // Redirect user to main page if update successful
            cout << "Content-type: text/html" << endl
                 << endl;
            cout << "<html><head><meta http-equiv=\"refresh\" content=\"0; URL=main.html#"
                + username + "\"></head>" << endl;
        }
        else
        {
            // Query failed
            // Redirect user back to account.html
            cout << "Content-type: text/html" << endl
                 << endl;
            cout << "<html><head><meta http-equiv=\"refresh\" content=\"0; URL=account.html#"
                + username + "\"></head>" << endl;
        }
    }
    else
    {
        // Connection failed
        // Redirect user back to account.html
        cout << "Content-type: text/html" << endl
             << endl;
        cout << "<html><head><meta http-equiv=\"refresh\" content=\"0; URL=account.html#"
            + username + "\"></head>" << endl;
    }
}
