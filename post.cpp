// Copywrite 2022
// CGI for Used Car Web Application
// Submits Car information to SQL table
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

// Retreives textbox entries of car information
// and submits them to the Cars table.
int main()
{

    // POST results
    map<string, string> Get;
    initializePost(Get);

    // Retreiving all the information from client
    std::string make = Get["make"];
    std::string model = Get["model"];
    std::string mileage = Get["mileage"];
    std::string price = Get["price"];
    std::string year = Get["year"];
    std::string description = Get["description"];
    std::string username = Get["username"];

    // Connecting to mySQL
    mysqlpp::Connection conn(false);
    if (conn.connect("cse278", "localhost", "cse278", "MonSepM1am1"))
    {

        mysqlpp::SimpleResult result;

        // Checks all entries are unique
        if (make != "Make of Car" && model != "Model of Car"
            && mileage != "Mileage of Car" && year != "Year of Car" && price != "Price of Car"
            && description != "Short Description of Car")
        {
            // Inserts all relevent data
            mysqlpp::Query query = conn.query();
            query << "INSERT INTO mostyncrCars (username, make, model, mileage, description, year, price)"
                + " VALUES ('" + username + "', '" + make + "', '" + model + "', '" + mileage + "', '"
                + description + "', '" + year + "', '" + price + "');";
            query.parse();
            result = query.execute();
        }
        if (result)
        {
            // Successful post
            // redirects user to main.html
            cout << "Content-type: text/html" << endl
                 << endl;
            cout << "<html><head><meta http-equiv=\"refresh\" content=\"0; URL=main.html#"
                + username + "\"></head>" << endl;
        }
        else
        {
            // Query failed
            // redirects user back to post.html
            cout << "Content-type: text/html" << endl
                 << endl;
            cout << "<html><head><meta http-equiv=\"refresh\" content=\"0; URL=post.html#"
                + username + "\"></head>" << endl;
        }
    }
    else
    {
        // Connection failed
        // redirects user back to post.html
        cout << "Content-type: text/html" << endl
             << endl;
        cout << "<html><head><meta http-equiv=\"refresh\" content=\"0; URL=post.html#"
            + username + "\"></head>" << endl;
    }
}
