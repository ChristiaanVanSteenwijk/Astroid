#ifndef DATABASE_H
#define DATABASE_H

#include <string>
#include <cstdio>
#include <iostream>
#include "sqlite3.h"

class DataBase
{
    public:
     //   DataBase();
        DataBase(std::string name = "database");
        ~DataBase();

        //void execute(char* query);
        void execute(std::string query);

        void prepare(std::string Statement);
        void finalize();

        void step();
        void column(int i);
        const unsigned char* column_string(int i);
        int column_int(int i);
        int64_t column_int64(int i);

        static int callback(void *NotUsed, int argc, char **argv, char **azColName);

    protected:
    private:
        std::string _name;
        sqlite3 *db;
        sqlite3_stmt* stmt;
        char *zErrMsg = 0;
        int rc;
        int rs;
        char *sql;
        int datatype =0;

};

#endif // DATABASE_H
