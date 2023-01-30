// Copywrite 2022
// CGI for Used Car Web Application
// Removes Car information from SQL Table
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

// Attempts to delete a car from the table
// based on a provided ID number
int main()
{

    // POST results
    map<string, string> Get;
    initializePost(Get);

    // Retreives supplied ID to delete and username
    std::string id = Get["id"];
    std::string username = Get["username"];

    // Connecting to mySQL
    mysqlpp::Connection conn(false);
    if (conn.connect("cse278", "localhost", "cse278", "MonSepM1am1"))
    {
        // Only performs delete if username matches current user
        mysqlpp::SimpleResult result;
        mysqlpp::Query query = conn.query();
        query << "DELETE FROM mostyncrCars WHERE id =" + id + " AND username = '" + username + "';";
        query.parse();
        result = query.execute();

        if (result)
        {
            // Successful remove
            // redirects user to main.html
            cout << "Content-type: text/html" << endl
                 << endl;
            cout << "<html><head><meta http-equiv=\"refresh\" content=\"0; URL=main.html#"
                + username + "\"></head>" << endl;
        }
        else
        {
            // Query failed
            // redirects user back to remove.html
            cout << "Content-type: text/html" << endl
                 << endl;
            cout << "<html><head><meta http-equiv=\"refresh\" content=\"0; URL=remove.html#"
                + username + "\"></head>" << endl;
        }
    }
    else
    {
        // Connection failed
        // redirects user back to remove.html
        cout << "Content-type: text/html" << endl
             << endl;
        cout << "<html><head><meta http-equiv=\"refresh\" content=\"0; URL=remove.html#"
            + username + "\"></head>" << endl;
    }
}
