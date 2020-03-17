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
        void Execute(std::string query);
        void RunFile(std::string filename);

        void Prepare(std::string Statement);
        void Finalize();

        void Step();
        void Column(int i);
        const unsigned char* Column_string(int i);
        int Column_int(int i);
        int64_t Column_int64(int i);

        static int Callback(void *Data, int argc, char **argv, char **azColName);

    protected:
        std::string _name, _line, _command;
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
