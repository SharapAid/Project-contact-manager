#pragma once
#include <iostream>
#include <vector>
#include <string>
#include <sqlite3.h>


using RowData = std::vector<std::string>;
using QueryResult = std::vector<RowData>;

class DataBaseManager{
private:
    sqlite3* m_db;
    std::string m_lastError;
    std::string m_dbPath;

    static int callback(void* data, int count, char** values, char** columnNames);

public:
    explicit DataBaseManager(const std::string& dbPath);

    ~DataBaseManager();

    bool execute(const std::string& sqlQuery);

    QueryResult query(const std::string& sqlQuery);

    std::string getLastError() const;
};