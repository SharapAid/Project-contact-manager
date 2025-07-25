#include "databasemanager.hpp"
#include <sstream>

DataBaseManager::DataBaseManager(const std::string& dbPath)
    : m_db(nullptr), m_dbPath(dbPath){
    int rc = sqlite3_open(m_dbPath.c_str(), &m_db);
    if(rc != SQLITE_OK){
        m_lastError = "Do not open BD: " + std::string(sqlite3_errmsg(m_db));
        if(m_db){
            sqlite3_close(m_db);
            m_db = nullptr;
        }
        std::cerr<<"Error in DatabaseManager constructor: "<<m_lastError<<std::endl;
    } 
    else{
        std::cout<<"Data base open: "<<m_dbPath<< std::endl;
    }
}

DataBaseManager::~DataBaseManager(){
    if(m_db){
        sqlite3_close(m_db);
        std::cout<<"Data base close: "<< m_dbPath<<std::endl;
    }
}

bool DataBaseManager::execute(const std::string& sqlQuery){
    char* zErrMsg = 0;
    int rc = sqlite3_exec(m_db, sqlQuery.c_str(), 0, 0, &zErrMsg);

    if(rc != SQLITE_OK){
        m_lastError = "Request execution error '" + sqlQuery + "': " + std::string(zErrMsg);
        std::cerr << "Error in DatabaseManager::execute: " << m_lastError << std::endl;
        sqlite3_free(zErrMsg);
        return false;
    }
    return true;
}

QueryResult DataBaseManager::query(const std::string& sqlQuery){
    QueryResult results;
    char* zErrMsg = 0;

    int rc = sqlite3_exec(m_db, sqlQuery.c_str(), callback, &results, &zErrMsg);

    if(rc != SQLITE_OK){
        m_lastError = "Request execution error '" + sqlQuery + "': " + std::string(zErrMsg);
        std::cerr << "Error in DatabaseManager::query: " << m_lastError << std::endl;
        sqlite3_free(zErrMsg);
        return {};
    }
    return results;
}

int DataBaseManager::callback(void* data, int count, char** values, char** columnNames){
    QueryResult* results = static_cast<QueryResult*>(data);
    RowData row;
    for (int i = 0; i < count; i++) {
        row.push_back(values[i] ? values[i] : "NULL");
    }
    results->push_back(row);
    return 0;
}

std::string DataBaseManager::getLastError() const{
    return m_lastError;
}

