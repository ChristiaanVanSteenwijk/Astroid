#ifndef DATABASE_H
#define DATABASE_H

#include <memory>
#include <string>
#include <cstdio>
#include <iostream>
#include <fstream>

#include "sqlite3.h"

class DataBase
{
    public:
        DataBase(std::string name = "database.ldb"); //Ctor
        friend void swap(DataBase& first, DataBase& second);    //swap

        DataBase(DataBase& other);             //Copy Ctor
        DataBase& operator=(DataBase& other); //copy assignment

        DataBase(DataBase&& other);       //move constructor
        DataBase& operator=(DataBase&&); //move assignment

        ~DataBase();

        //void execute(char* query);
        void execute(std::string query);
        void RunFile(std::string filename);

        void prepare(std::string Statement);
        void finalize();

        void step();
        void column(int i);
        const unsigned char* column_string(int i);
        int column_int(int i);
        int64_t column_int64(int i);

        static int callback(void *Data, int argc, char **argv, char **azColName);

    protected:
        std::string _name, line;
        sqlite3* db;
        sqlite3_stmt* stmt;
        char* zErrMsg = 0;
        int rc;
        int rs;
        char* sql;
        int datatype =0;

        std::ifstream myfile;

};

#endif // DATABASE_H
