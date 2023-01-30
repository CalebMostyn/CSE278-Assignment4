// Copywrite 2022
// CGI for Used Car Web Application
// Facilitates authentication for existing users
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

// Retreives username and password from
// both client and SQL table, comparing
// to login a user
int main()
{
    //  POST results
    map<string, string> Get;
    initializePost(Get);

    // Username and password from user
    string username = Get["username"];
    string password = Get["password"];

    // Connecting to mySQL
    mysqlpp::Connection conn(false);
    if (conn.connect("cse278", "localhost", "cse278", "MonSepM1am1"))
    {
        // Pulls user data from user if exists
        mysqlpp::Query query = conn.query();
        query << "SELECT * FROM mostyncrUsers WHERE username='" + username + "';";
        query.parse();
        mysqlpp::StoreQueryResult result = query.store();

        // Checks if result is returned
        if (result)
        {
            // Checks if username exists in table
            if (result.num_rows() > 0)
            {
                // Compare password to password in table
                if (password == (string)result[0]["password"])
                {
                    // Successful authentication
                    // redirects user to main.html
                    cout << "Content-type: text/html" << endl
                         << endl;
                    cout << "<html><head><meta http-equiv=\"refresh\" content=\"0;"
                    cout << " URL=main.html#" + username + "\"></head>" << endl;
                }
                else
                {
                    // Unsuccessful authentication
                    // redirects user back to login.html
                    cout << "Content-type: text/html" << endl
                         << endl;
                    cout << "<html><head><meta http-equiv=\"refresh\" content=\"0;"
                    cout << " URL=index.html\"></head>" << endl;
                }
            }
            else
            {
                // No such username
                // redirects user back to login.html
                cout << "Content-type: text/html" << endl
                     << endl;
                cout << "<html><head><meta http-equiv=\"refresh\" content=\"0;"
                cout << " URL=index.html#\"></head>" << endl;
            }
        }
        else
        {
            // Query failed
            // redirects user back to login.html
            cout << "Content-type: text/html" << endl
                 << endl;
            cout << "<html><head><meta http-equiv=\"refresh\" content=\"0;"
            cout << " URL=index.html\"></head>" << endl;
        }
    }
    else
    {
        // Connection failed
        // redirects user back to login.html 
        cout << "Content-type: text/html" << endl
             << endl;
        cout << "<html><head><meta http-equiv=\"refresh\" content=\"0;"
        cout << " URL=index.html\"></head>" << endl;
    }
}
