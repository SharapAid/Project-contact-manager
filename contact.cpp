#include "contact.hpp"
#include "databasemanager.hpp"
#include "contactmanager.hpp"
#include "application.hpp"

Contact::Contact()
    :m_id(0), m_name(""), m_cogname(""), m_number_phone(""), m_email("")
{

}

Contact::Contact(int id, const std::string& name, const std::string& cogname, const std::string& number, const std::string& email)
    : m_id(id), m_name(name), m_cogname(cogname), m_number_phone(number), m_email(email)
{

}

std::string Contact::ToString() const{
    return "ID: " + std::to_string(getId()) + " ,NAME: " + getName() + " ,COGNAME: " + getCogname() + " ,NUMBER PHONE: " + getNumberPhone() + " ,EMAIL: " + getEmail() + ".";
}