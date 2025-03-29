// Copyright 2022 UNN-IASR
#include "Automata.h"
#include <map>
#include <utility>
#include <string>

Coffee_machine::Coffee_machine() {
    state = State::off;
    current_cash = 0;
    earned_cash = 0;
}

std::string Coffee_machine::AddPosition(const std::string name,
     const unsigned int price) {
    if (state == State::admin) {
        if (menu.count(name) <= 0) {
            menu.insert({name, price});
            return "The drink was successfully added to the vending machine";
        } else {
            return "Such a drink is already in the vending machine!";
        }
    } else {
        return "You're not an administrator";
    }
}

std::string Coffee_machine::DeletePosition(const std::string name) {
    if (state == State::admin) {
        if (menu.count(name) > 0) {
            menu.erase(name);
            return
            "The product was successfully removed from the vending machine";
        } else {
            return "There is no such drink in the vending machine!";
        }
    } else {
        return "You're not an administrator";
    }
}

int Coffee_machine::On() {
    if (state == State::off) {
        state = State::wait;
    }
    return 0;
}

int Coffee_machine::Off() {
    if (state == State::wait) {
        state = State::off;
    }
    return 0;
}

std::map<std::string, unsigned int> Coffee_machine::GetMenu() {
    return menu;
}

std::string Coffee_machine::Choice(const std::string name) {
    if (state == State::wait) {
        if (name == std::string(adminPassword)) {
            state = State::admin;
            return "You have switched to the administrator mode";
        }
        if (menu.count(name) > 0) {
            state = State::check;
            selected_drink = name;
            return "The drink has been successfully selected, make the payment";
        } else {
            return "There is no such drink in the vending machine!";
        }
    } else {
        return "The machine went out of standby mode";
    }
}

int Coffee_machine::Cancel() {
    if (state == State::check || state == State::admin) {
        state = State::wait;
        int change = current_cash;
        current_cash = 0;
        selected_drink = "";
        return change;
    }
    return 0;
}

std::string Coffee_machine::Coin(int money) {
    if (state == State::check) {
        current_cash += money;
        return "The money is credited to the current account";
    } else {
        return "It's not time to make a payment yet";
    }
}

int Coffee_machine::GetCash() {
    return current_cash;
}

int Coffee_machine::GetEarnedMoney() {
    if (state == State::admin) {
        return earned_cash;
    }
    return 0;
}

std::pair<std::string, unsigned int> Coffee_machine::Ready_to_cook() {
    if (state == State::check) {
        if (current_cash >= menu[selected_drink]) {
            state = State::cook;
            int change = Finish();
            return std::make_pair(
                "The drink has been successfully prepared, get your change",
                 change);
        } else {
            return std::make_pair(
                std::string(
                    "You have not deposited enough funds, deposit another $")
                 + std::to_string(menu[selected_drink] - current_cash)
                  + std::string("units of currency"), 0);
        }
    } else {
        return std::make_pair("The drink has not been selected yet", 0);
    }
}

std::string Coffee_machine::GetState() {
    return StateToString[state];
}

int Coffee_machine::Finish() {
    int change = current_cash - menu[selected_drink];
    current_cash -= menu[selected_drink];
    earned_cash += menu[selected_drink];
    selected_drink = "";
    state = State::wait;
    return change;
}
