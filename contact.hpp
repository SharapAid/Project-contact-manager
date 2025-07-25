#pragma once
#include <iostream>
#include <string>

class Contact{
private:
    int m_id;
    std::string m_name;
    std::string m_cogname;
    std::string m_number_phone;
    std::string m_email;
public:
    Contact(int id, const std::string& name, const std::string& cogname, const std::string& number, const std::string& email);

    Contact();

    int getId()const {return m_id;}
    std::string getName()const {return m_name;}
    std::string getCogname()const {return m_cogname;}
    std::string getNumberPhone()const {return m_number_phone;}
    std::string getEmail()const {return m_email;}

    void setName(const std::string& name){m_name = name;}
    void setCogname(const std::string& cogname){m_cogname = cogname;}
    void setNumber(const std::string& number){m_number_phone = number;}
    void setEmail(const std::string& email){m_email = email;}

    std::string ToString() const;
};