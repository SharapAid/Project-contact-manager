#include "contact.hpp"
#include "databasemanager.hpp"
#include "contactmanager.hpp"
#include "application.hpp"

ContactManager::ContactManager(): m_data_manager("contact.db"){
    std::string sqlCreateTable = R"(
        CREATE TABLE IF NOT EXISTS CONTACT(
            ID INTEGER PRIMARY KEY AUTOINCREMENT,
            NAME TEXT NOT NULL,
            COGNAME TEXT DEFAULT '',
            NUMBER_PHONE TEXT NOT NULL, 
            EMAIL TEXT DEFAULT ''
        );
    )";

    if(!m_data_manager.execute(sqlCreateTable)) {
        std::cerr<<"Error creating table: "<<m_data_manager.getLastError()<<std::endl;
    }
}

bool ContactManager::addContact(const Contact& contact){
    std::string name = contact.getName();
    std::string cogname = contact.getCogname();
    std::string number = contact.getNumberPhone();
    std::string email = contact.getEmail();
    std::string sqlInsertData = "INSERT INTO CONTACT(NAME, COGNAME, NUMBER_PHONE, EMAIL) VALUES('"
                            + name + "', '"
                            + cogname + "', '"
                            + number + "', '"
                            + email + "');";

    if(!m_data_manager.execute(sqlInsertData)){
        std::cerr << "Data insertion error: "<<m_data_manager.getLastError()<< std::endl;
        return false;
    }
    return true;
}

std::vector<Contact> ContactManager::getAllContacts(){
    std::string sqlSelectData = "SELECT ID, NAME, COGNAME, NUMBER_PHONE, EMAIL FROM CONTACT;";
    QueryResult results = m_data_manager.query(sqlSelectData);
    std::vector<Contact> all_contacts;
    if(results.empty() && !m_data_manager.getLastError().empty()){
        std::cerr<< "Data sampling error: "<< m_data_manager.getLastError()<< std::endl;
        return {};
    } 
    else{
        for(const auto& row : results){
            if(row.size() < 5){
                std::cerr<<"Error: Not enough columns in query result row."<< std::endl;
                continue;
            }

            int id = std::stoi(row[0]);
            std::string name = row[1];
            std::string cogname = row[2];
            std::string number_phone = row[3];
            std::string email = row[4];

            Contact new_contact(id, name, cogname, number_phone, email);
            
            all_contacts.push_back(new_contact);
        }
    }
    return all_contacts;
}


Contact ContactManager::getContactById(int id){
    std::string str_id = std::to_string(id);
    std::string sqlSelectData = "SELECT ID, NAME, COGNAME, NUMBER_PHONE, EMAIL FROM CONTACT WHERE ID = " + str_id + ";";
    QueryResult results = m_data_manager.query(sqlSelectData);
    if(results.empty() && !m_data_manager.getLastError().empty()){
        std::cerr<< "Data sampling error: "<< m_data_manager.getLastError()<< std::endl;
        return Contact();
    }
    if(results.empty()){
        std::cout<< "Contact whis ID "<<id<<" not faund."<< std::endl;
        return Contact();
    }
    const auto& row = results[0];

    if(row.size() < 5){
        std::cerr<< "Error: Not enough columns in query result row for ID"<<id<<std::endl;
        return Contact();
    }

    int contact_id = std::stoi(row[0]);
    std::string name = row[1];
    std::string cogname = row[2];
    std::string number_phone = row[3];
    std::string email = row[4];

    return Contact(contact_id, name, cogname, number_phone, email);
}

bool ContactManager::updateContact(const Contact& contact){
    std::string str_id = std::to_string(contact.getId());
    std::string name = contact.getName();
    std::string cogname = contact.getCogname();
    std::string number = contact.getNumberPhone();
    std::string email = contact.getEmail();
    std::string sqlUpdateData = "UPDATE CONTACT SET NAME = '" + name + "', COGNAME = '" + cogname + "', NUMBER_PHONE = '" + number + "', EMAIL = '" + email + "' WHERE ID = "+ str_id +";";
    if (!m_data_manager.execute(sqlUpdateData)) {
        std::cerr << "Data update error: " << m_data_manager.getLastError() << std::endl;
        return false;
    }
    return true;
}

bool ContactManager::deleteContact(int id){
    std::string str_id = std::to_string(id);
    std::string sqlDeleteData = "DELETE FROM CONTACT WHERE ID = " + str_id + ";";
    if(!m_data_manager.execute(sqlDeleteData)){
        std::cerr<<"Error in delete data: "<<m_data_manager.getLastError()<< std::endl;
        return false;
    }
    return true;
}