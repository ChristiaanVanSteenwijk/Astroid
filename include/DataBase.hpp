#ifndef DATABASE_H
#define DATABASE_H

#include <string>
#include <cstdio>
#include <iostream>
#include "sqlite3.h"

// Based on the tutorial from https://www.tutorialspoint.com/sqlite/sqlite_c_cpp.htm on c++ interface
class DataBase
{
    public:
     //   DataBase();
        DataBase(std::string name = "default.db");
        friend void swap(DataBase& first, DataBase& second);
        DataBase& operator=(DataBase other); //copy assignment
        DataBase(const DataBase&)=default;
        DataBase(DataBase&& other);  //move constructor
        ~DataBase();

        //void execute(char* query);
        void execute(std::string query);

        void prepare(std::string Statement);
        void step(); // does not include a for loop
        void finalize();

        int GetDatatype(int i);
        const unsigned char* column_string(int i);
        int column_int(int i);
        int64_t column_int64(int i);

        static int callback(void *NotUsed, int argc, char **argv, char **azColName);

    protected:    // designed this as a potential base for more advanced shells
        std::string _name;      // name of the database
        sqlite3 *db;            // pointer to the database
        // didn't use a smart pointer because this requires a defined destructor and that's in this shell itself
        sqlite3_stmt* stmt;     //sql statement or command
        char *zErrMsg = 0;      // error message
        int rc;
        int rs;                 //ReSult from a statement if applicable notably prepare and step
        char *sql;
        int datatype =0;

};

#endif // DATABASE_H
