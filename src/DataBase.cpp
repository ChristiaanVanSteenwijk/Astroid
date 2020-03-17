#include "DataBase.hpp"

DataBase::DataBase(std::string name):
    _name(name)
{
    //ctor
    rc = sqlite3_open(name.c_str() , &db);
   // _name = name;

    if( rc )
      fprintf(stderr, "Can't open database: %s\n", sqlite3_errmsg(db));

    else
      fprintf(stderr, "Opened database successfully\n");

}

DataBase::~DataBase()
{
    //dtor
    sqlite3_finalize(stmt);
    sqlite3_close(db);
}

void swap(DataBase& first, DataBase& second)
{
        // enable ADL (not necessary in our case, but good practice)
        using std::swap;

        // the two objects are effectively swapped
        swap(first._name, second._name);
        swap(first.db, second.db);
        swap(first.stmt, second.stmt);
        swap(first.zErrMsg, second.zErrMsg);
        swap(first.rc, second.rc);
        swap(first.rs, second.rs);
        swap(first.sql, second.sql);
        swap(first.datatype, second.datatype);
}

DataBase::DataBase(DataBase& other)  // passed by value
{
     swap(*this, other); // nothrow swap
}

DataBase& DataBase::operator=(DataBase& other)  //copy assignment
{
    swap(*this, other); // (2)
    return *this;
}

DataBase::DataBase(DataBase&& other)            //move constructor
    :DataBase(this->_name)
{
    swap(*this, other);
}

DataBase& DataBase::operator=(DataBase&& other)  //move assignment
  //  :DataBase(this->_name)
{
    swap(*this, other); // (2)
    return *this;
}

int DataBase::Callback(void *Data, int argc, char **argv, char **azColName)
{
    int i;
    for(i = 0; i<argc; i++)
        printf("%s = %s\n", azColName[i], argv[i] ? argv[i] : "NULL");

    printf("\n");
    return 0;
}

void DataBase::Execute(std::string _input)
{
    rc = sqlite3_exec(db, _input.c_str(), Callback, 0, &zErrMsg);
    if (rc != SQLITE_OK)
    {
        fprintf(stderr, "SQL error: %s\n", zErrMsg);
        sqlite3_free(zErrMsg);
    }
}

void DataBase::RunFile(std::string filename)
{
    myfile.open(filename.c_str());
    if (myfile.is_open())
    {
        while ( getline (myfile, _line) )
            _command+=_line;

        myfile.close();
        Execute(_command.c_str());
    }
    else std::cout << "Unable to open file";
}

void DataBase::Prepare(std::string statement)
{
    rs = sqlite3_prepare_v2(db, statement.c_str(),-1, &stmt,NULL);
}

void DataBase::Finalize()
{
    sqlite3_finalize(stmt);
}

void DataBase::Step()
{
    rs = sqlite3_step(stmt);
    if (rs == SQLITE_DONE)
    {
        return;
    }
    else if (rs != SQLITE_ROW)
    {
        std::cout << "error in reading sensor with error No: " << rs;
        return;
    }
}

void DataBase::Column(int i)
{
    datatype = sqlite3_column_type(stmt,i);
}

int DataBase::Column_int(int i)
{
    return sqlite3_column_int(stmt,i);
}

int64_t DataBase::Column_int64(int i)
{
    return sqlite3_column_int64(stmt,i);
}

const unsigned char* DataBase::Column_string(int i)
{
    return sqlite3_column_text(stmt,i);
    //return sName(reinterpret_cast<char*>(text));
}
