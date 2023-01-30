// Copywrite 2022
// CGI for Used Car Web Application
// Creates a webpage for viewing all cars
// from a specified city
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

// Creates a unique page for all cars
// from a specified city
// Displays a table for cars information
int main()
{
    // POST results
    map<string, string> Get;
    initializePost(Get);

    // Retreiving city to search for
    std::string city = Get["city"];
    std::string username = Get["username"];

    // Connecting to mySQL
    mysqlpp::Connection conn(false);
    if (conn.connect("cse278", "localhost", "cse278", "MonSepM1am1"))
    {

        mysqlpp::StoreQueryResult result;

        // Ensures city value is entered
        if (city != "City")
        {
            // Retreives seller and car information
            mysqlpp::Query query = conn.query();
            query << "SELECT * FROM mostyncrUserInfo INNER JOIN mostyncrCars ON"
                + " mostyncrCars.username=mostyncrUserInfo.username WHERE city ='" + city + "';";
            query.parse();
            result = query.store();
        }
        if (result)
        {
            // Query successful, creates table of all cars

            // Header
            cout << "Content-type: text/html" << endl
                 << endl;
            cout << "<html><head><meta charset=\"UTF-8\"><title>Local Used Cars</title>";
            cout << "<link rel=\"stylesheet\" href=\"css/style6.css\" media=\"screen\" ";
            cout << "type=\"text/css\" /></head><body><html lang=\"en-US\"><head>";
            cout << "<meta charset=\"utf-8\"><title>Login</title><link rel=\"stylesheet\" ";
            cout << "href=\"http://fonts.googleapis.com/css?family=Open+Sans:400,700\"></head>";
            cout << endl;
            cout << "<table border = 25 width = 1000><tr><th>Cars in " + city;
            cout << "</th></tr><tr><th>Make of Car</th><th>Model of Car</th><th>Mileage of Car</th>";
            cout << "<th>Year of Car</th><th>Price of Car</th><th>Description of Car</th>";
            cout << "<th>ID of Car</th></tr>" << endl;

            for (int i = 0; i < result.num_rows(); i++)
            {
                // Prints each piece of info
                cout << "<tr><td>" << result[i]["make"] << "</td>" << endl;
                cout << "<td>" << result[i]["model"] << "</td>" << endl;
                cout << "<td>" << result[i]["mileage"] << "</td>" << endl;
                cout << "<td>" << result[i]["year"] << "</td>" << endl;
                cout << "<td>" << result[i]["price"] << "</td>" << endl;
                cout << "<td>" << result[i]["description"] << "</td>" << endl;
                cout << "<td>" << result[i]["id"] << "</td></tr>" << endl;
            }
            cout << "</table>" << endl;
        }
        else
        {
            // Query failed
            // Redirects user back to search.html
            cout << "Content-type: text/html" << endl
                 << endl;
            cout << "<html><head><meta http-equiv=\"refresh\" content=\"0;";
            cout << " URL=search.html#" + username + "\"></head>" << endl;
        }
    }
    else
    {
        // Connection failed
        // Redirects user back to search.html
        cout << "Content-type: text/html" << endl
             << endl;
        cout << "<html><head><meta http-equiv=\"refresh\" content=\"0;";
        cout << " URL=search.html#" + username + "\"></head>" << endl;
    }
}
