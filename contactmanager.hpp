#pragma once
#include <iostream>
#include <string>
#include <vector>
#include <sqlite3.h>

class ContactManager{
private:
    DataBaseManager m_data_manager;
public: 
    ContactManager();

    bool addContact(const Contact& contact);
    std::vector<Contact> getAllContacts();
    Contact getContactById(int id);
    bool updateContact(const Contact& contact);
    bool deleteContact(int id);
};
