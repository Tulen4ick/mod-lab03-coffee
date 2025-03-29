// Copyright 2022 UNN-IASR
#ifndef INCLUDE_AUTOMATA_H_
#define INCLUDE_AUTOMATA_H_
#include <string>
#include <vector>
#include <iostream>
#include <map>
#include <utility>

enum class State { off, wait, check, cook, admin };

std::map<State, std::string> StateToString = {
    {State::off, "off"},
    {State::wait, "wait"},
    {State::check, "check"},
    {State::cook, "cook"},
    {State::admin, "admin"}
};

class Coffee_machine {
 public:
    Coffee_machine();
    std::string AddPosition(const std::string name, const unsigned int price);
    std::string DeletePosition(const std::string name);
    int On();
    int Off();
    std::map<std::string, unsigned int> GetMenu();
    std::string Choice(const std::string name);
    int Cancel();
    std::string Coin(int money);
    int GetCash();
    int GetEarnedMoney();
    std::pair<std::string, unsigned int> Ready_to_cook();
    std::string GetState();
 private:
    State state;
    std::map<std::string, unsigned int> menu;
    int current_cash;
    int earned_cash;
    std::string selected_drink;
    std::string admin_password;
    int Finish();
};
#endif // INCLUDE_AUTOMATA_H_
