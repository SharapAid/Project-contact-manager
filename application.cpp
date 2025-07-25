#include "contact.hpp"
#include "databasemanager.hpp"
#include "contactmanager.hpp"
#include "application.hpp"

void Application::EnterChoise(int& choise){
    std::cout<<"Enter your choise: ";
    std::cin>>choise;
    while(std::cin.fail() || choise > 5 || choise < 0){
        std::cerr<<"Error the choice must be between 0 and 5 and must not contain letters\n";
        std::cin.clear();
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
        std::cout<<"Enter your choise: ";
        std::cin>>choise;
    }
    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
}

void Application::EnterId(int& id){
    std::cout<<"Enter id of contact: ";
    std::cin>>id;
    while(std::cin.fail() || id < 0){
        std::cerr<<"Error the choice must not be 0 and must not contain letters\n";
        std::cin.clear();
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
        std::cout<<"Enter id of contact: ";
        std::cin>>id;
    }
    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
}

void Application::EnterName(std::string& name){
    std::cout<<"Enter name of contact: ";
    std::getline(std::cin, name);
    while(name == ""){
        std::cerr<<"The name field cannot be empty\n";
        std::cin.clear();
        std::cout<<"Enter name of contact: ";
        std::getline(std::cin, name);
    }
}

void Application::EnterCogname(std::string& cogname){
    std::cout<<"Enter cogname of contact: ";
    std::getline(std::cin, cogname);
}

void Application::EnterNumber(std::string& number){
    std::cout<<"Enter number of contact: ";
    std::getline(std::cin, number);
    bool is_number = false;
    while(!is_number || number == ""){
        is_number = true;
        for(const auto& letter : number){
            if(int(letter) < 48 || int(letter) > 57){
                is_number = false;
                break;
            }
        }
        if(!is_number || number == ""){
            std::cerr<<"The number field cannot be empty and cannot contain letters\n";
            std::cin.clear();
            std::cout<<"Enter number of contact: ";
            std::getline(std::cin, number);
        }
    }
}

void Application::EnterEmail(std::string& email){
    std::cout<<"Enter email of contact: ";
    std::getline(std::cin, email);
}

void Application::stateAddContact(){
    std::cout<<"___________________ADD CONTACT_________________\n";
    std::string name;
    std::string cogname;
    std::string number;
    std::string email;
    EnterName(name);
    EnterCogname(cogname);
    EnterNumber(number);
    EnterEmail(email);
    Contact new_contact(0, name, cogname, number, email);
    m_manager.addContact(new_contact);
    setState(state::MENU);
}

void Application::stateShowContact(){
    std::cout<<"___________________SHOW CONTACT_________________\n";
    std::vector<Contact> list = m_manager.getAllContacts();
    if(!list.empty()){
        for(const auto& element : list){
            std::cout<<"ID: "<<element.getId()<<" ,NAME: "<<element.getName()<<" ,COGNAME:"<<element.getCogname()<<" ,NUMBER PHON: "<<element.getNumberPhone()<<" ,EMAIL: "<<element.getEmail()<<'\n';
        }
    }
    else{
        std::cout<<"Contact list is empty!\n";
    }
    setState(state::MENU);
}

void Application::stateFindContact(){
    std::cout<<"___________________CHANGE CONTACT_________________\n";
    int id = 0;
    EnterId(id);
    Contact find_contact = m_manager.getContactById(id);
    if(find_contact.getName() == ""){
        std::cout<<"Contact with this id not found'\n";
    }
    else{
        std::cout<<"ID: "<<find_contact.getId()<<" ,NAME: "<<find_contact.getName()<<" ,COGNAME:"<<find_contact.getCogname()<<" ,NUMBER PHON: "<<find_contact.getNumberPhone()<<" ,EMAIL: "<<find_contact.getEmail()<<'\n';
    }
    setState(state::MENU);
}

void Application::stateChangeContact(){
    std::cout<<"________________CHANGE CONTACT_______________\n";
    int id = 0;
    EnterId(id);
    Contact find_contact = m_manager.getContactById(id);
    if(find_contact.getName() == ""){
        std::cout<<"Contact with this id not found'\n";
    }
    else{
        std::string name;
        std::string cogname;
        std::string number;
        std::string email;
        EnterName(name);
        EnterCogname(cogname);
        EnterNumber(number);
        EnterEmail(email);
        find_contact.setName(name);
        find_contact.setCogname(cogname);
        find_contact.setNumber(number); 
        find_contact.setEmail(email);
        bool is_change = m_manager.updateContact(find_contact);
        if(is_change){
            std::cout<<"Contact: "<<name<<" is change!\n";
        }
        else{
            std::cout<<"Error in change contact!\n";
        }
    }
    setState(state::MENU);
}
    
void Application::stateDeleteContact(){
    std::cout<<"__________________DELETE CONTACT_________________\n";
    int id = 0;
    EnterId(id);
    bool is_delete = m_manager.deleteContact(id);
    if(is_delete){
        std::cout<<"Contact whis id "<<id<<" is delete!\n";
    }
    else{
        std::cout<<"Failed to delete contact\n";
    }
    setState(state::MENU);
}

int Application::stateMenu(){
    int choise = -1;
    std::cout<<"___________________MENU_______________\n";
    std::cout<<"What you whant to do?\n"
             <<"0 - Exit,'\n"
             <<"1 - Add new contact,\n"
             <<"2 - Show all contact,\n"
             <<"3 - Find contact,\n"
             <<"4 - Change contact\n"
             <<"5 - Delete contact.\n";
    EnterChoise(choise);
    return choise;
}

void Application::updataState(){
    int choise = stateMenu(); 
    switch (choise){
        case 0:
            setState(state::EXIT);
            break;
        case 1:
            setState(state::ADD_CONTACT);
            break;
        case 2:
            setState(state::SHOW_CONTACT);
            break;
        case 3:
            setState(state::FIND_CONTACT);
            break;
        case 4:
            setState(state::CHANGE_CONTACT);
            break;
        case 5:
            setState(state::DELETE_CONTACT);
            break;
    }
}

void Application::Run(){
    while(true){
        switch (m_state){
            case state::MENU:
                updataState();
                break;
            case state::ADD_CONTACT:
                stateAddContact();
                break;
            case state::SHOW_CONTACT:
                stateShowContact();
                break;
            case state::FIND_CONTACT:
                stateFindContact();
                break;
            case state::CHANGE_CONTACT:
                stateChangeContact();
                break;
            case state::DELETE_CONTACT:
                stateDeleteContact();
                break;
            case state::EXIT:
                break;
        }
        if(m_state == state::EXIT){
            break;
        }
    }
}