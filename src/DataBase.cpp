#include "DataBase.hpp"

DataBase::DataBase(std::string name)
{
    //ctor
    rc = sqlite3_open(name.c_str() , &db);
    //create a database or open a link to it
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

DataBase::DataBase(DataBase&& other)            //move constructor
    :DataBase(this->_name)
{
    swap(*this, other);
}

DataBase& DataBase::operator=(DataBase other)  //copy assignment
{
    swap(*this, other); // (2)
    return *this;
}
DataBase::~DataBase()
{
    //dtor
    // finalize the last statement to prevent memory leaks,
    // should not be used and is a harmless no op in this case
    sqlite3_finalize(stmt);

    // close the database
    sqlite3_close(db);
}

int DataBase::callback(void *NotUsed, int argc, char **argv, char **azColName)
{
    // call back function to use with execute commands,
    // prints the output
    int i;
    for(i = 0; i<argc; i++)
        {
            printf("%s = %s\n", azColName[i], argv[i] ? argv[i] : "NULL");
        }
    printf("\n");
    return 0;
}

void DataBase::execute(std::string sql)
{
    // prepare, repeat until done and finalize a statment
    // for debugging or insertions mostly
    rc = sqlite3_exec(db, sql.c_str(), callback, 0, &zErrMsg);
    if (rc != SQLITE_OK)
    {
        fprintf(stderr, "SQL error: %s\n", zErrMsg);
        sqlite3_free(zErrMsg);
    }
}

void DataBase::prepare(std::string statement)
{
    sqlite3_finalize(stmt); //cleans up the last statement, SHOULD be redundant

    rs = sqlite3_prepare_v2(db, statement.c_str(),-1, &stmt,NULL);
    // string is converterd to c string since these are not automatically interchanged to save memory
}

void DataBase::step()
{
    // take one step for a prepared statement
    // rs stores the row
    // also readies the output, see Below
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

void DataBase::finalize()
{
    sqlite3_finalize(stmt);
    //clear up the last statement
}

// Below
int DataBase::GetDatatype(int i)
{
    // checks what the datatype is of the last step
    datatype = sqlite3_column_type(stmt,i);
    return datatype;
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
