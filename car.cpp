// Copywrite 2022
// CGI for Used Car Web Application
// Creates a webpage for viewing a car
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

// Creates a unique page for a car,
// designated by the client.
// Displays a table for car information
// and seller information.
int main()
{
    // POST results
    map<string, string> Get;
    initializePost(Get);

    // ID number for Car to view
    string id = Get["id"];

    // Connecting to mySQL
    mysqlpp::Connection conn(false);
    if (conn.connect("cse278", "localhost", "cse278", "MonSepM1am1"))
    {

        mysqlpp::StoreQueryResult result;

        // Aggregates data about selected car and seller
        mysqlpp::Query query = conn.query();
        query << "SELECT * FROM mostyncrUserInfo INNER JOIN mostyncrCars "
            + "ON mostyncrCars.username=mostyncrUserInfo.username WHERE id ='" + id + "';";
        query.parse();
        result = query.store();
        
        // Creates a new page if results returned
        if (result)
        {
            // Header
            cout << "Content-type: text/html" << endl
                 << endl;
            cout << "<html><head><meta charset=\"UTF-8\"><title>Local Used Cars</title>"
                + "<link rel=\"stylesheet\" href=\"css/style6.css\" media=\"screen\" type=\"text/css\" />"
                + "</head><body><html lang=\"en-US\"><head><meta charset=\"utf-8\"><title>Login</title>"
                + "<link rel=\"stylesheet\" href=\""
                + "http://fonts.googleapis.com/css?family=Open+Sans:400,700\"></head>";
            cout << endl;
            
            // Table containing car info
            cout << "<table border = 25 width = 1000><tr><th>Car from "; 
            cout << result[0]["username"];
            cout << "</th></tr><tr><th>Make of Car</th><th>Model of Car</th>";
            cout << "<th>Mileage of Car</th><th>Year of Car</th><th>Price of Car</th>";
            cout << "<th>Description of Car</th></tr>" << endl;
            cout << "<tr><td>" << result[0]["make"] << "</td>" << endl;
            cout << "<td>" << result[0]["model"] << "</td>" << endl;
            cout << "<td>" << result[0]["mileage"] << "</td>" << endl;
            cout << "<td>" << result[0]["year"] << "</td>" << endl;
            cout << "<td>" << result[0]["price"] << "</td>" << endl;
            cout << "<td>" << result[0]["description"] << "</td></tr>" << endl;
            cout << "</table>" << endl;

            // Table containing seller info
            cout << "<table border = 25 width = 1000><tr><th>"; 
            cout << result[0]["username"]; 
            cout << "'s Contact Info</th></tr><tr><th>Email Address</th>";
            cout << "<th>Phone Number</th></tr>" << endl;
            cout << "<tr><td>" << result[0]["email"] << "</td>" << endl;
            cout << "<td>" << result[0]["phoneNumber"] << "</td></tr>" << endl;
            cout << "</table>" << endl;

            cout << "</body>" << endl;
        }
        else
        {
            // Query failed
            // Redirect user back to search.html
            cout << "Content-type: text/html" << endl
                 << endl;
            cout << "<html><head><meta http-equiv=\"refresh\" content=\"0;"
            cout << " URL=search.html\"></head>" << endl;
        }
    }
    else
    {
        // Connection failed
        // Redirect user back to search.html
        cout << "Content-type: text/html" << endl
             << endl;
        cout << "<html><head><meta http-equiv=\"refresh\" content=\"0;"
        cout << " URL=search.html\"></head>" << endl;
    }
}
