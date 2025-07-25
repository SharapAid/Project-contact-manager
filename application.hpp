#pragma once
#include <iostream>
#include <string>
#include <iomanip>
#include <vector>
#include <numeric>
#include <limits>

enum class state{
    MENU,
    ADD_CONTACT,
    SHOW_CONTACT,
    FIND_CONTACT,
    CHANGE_CONTACT,
    DELETE_CONTACT,
    EXIT
};

class Application{
private:
    ContactManager m_manager;
    state m_state;

    void EnterChoise(int& choise);
    void EnterId(int& id);
    void EnterName(std::string& name);
    void EnterCogname(std::string& cogname);
    void EnterNumber(std::string& number);
    void EnterEmail(std::string& email);

    int stateMenu();
    void stateAddContact();
    void stateShowContact();
    void stateFindContact();
    void stateChangeContact();
    void stateDeleteContact();

    void updataState();
public:
    Application() : m_state(state::MENU) {}

    void setState(const state& state){m_state = state;}
    state getState()const {return m_state;}

    void Run();
};