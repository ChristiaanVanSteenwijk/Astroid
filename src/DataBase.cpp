#include "DataBase.hpp"

DataBase::DataBase(std::string name)
{
    //ctor
    rc = sqlite3_open(name.c_str() , &db);
    _name = name;

    if( rc )
    {
      fprintf(stderr, "Can't open database: %s\n", sqlite3_errmsg(db));
    }
    else
   {
      fprintf(stderr, "Opened database successfully\n");
   }
}

DataBase::~DataBase()
{
    //dtor
    sqlite3_finalize(stmt);
    sqlite3_close(db);
}

int DataBase::callback(void *NotUsed, int argc, char **argv, char **azColName)
{
    int i;
    for(i = 0; i<argc; i++)
        {
            printf("%s = %s\n", azColName[i], argv[i] ? argv[i] : "NULL");
        }
    printf("\n");
    return 0;
}
/*
void DataBase::execute(char* sql)
{
    rc = sqlite3_exec(db, sql, callback, 0, &zErrMsg);
    if (rc != SQLITE_OK)
    {
        fprintf(stderr, "SQL error: %s\n", zErrMsg);
        sqlite3_free(zErrMsg);
    }
}
*/
void DataBase::execute(std::string sql)
{
    rc = sqlite3_exec(db, sql.c_str(), callback, 0, &zErrMsg);
    if (rc != SQLITE_OK)
    {
        fprintf(stderr, "SQL error: %s\n", zErrMsg);
        sqlite3_free(zErrMsg);
    }
}

void DataBase::prepare(std::string statement)
{
    rs = sqlite3_prepare_v2(db, statement.c_str(),-1, &stmt,NULL);
}

void DataBase::finalize()
{
    sqlite3_finalize(stmt);
}

void DataBase::step()
{
    for(;;){
    rs = sqlite3_step(stmt);
    if (rs == SQLITE_DONE){
        break;
    }
    else if (rs != SQLITE_ROW){
        std::cout << "error in reading sensore with error No: " << rs;
        break;
    }}
}

void DataBase::column(int i)
{
    datatype = sqlite3_column_type(stmt,i);
}

int DataBase::column_int(int i)
{
    return sqlite3_column_int(stmt,i);
}

int64_t DataBase::column_int64(int i)
{
    return sqlite3_column_int64(stmt,i);
}

const unsigned char* DataBase::column_string(int i)
{
    return sqlite3_column_text(stmt,i);
    //return sName(reinterpret_cast<char*>(text));
}
