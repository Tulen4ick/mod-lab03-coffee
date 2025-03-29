// Copyright 2022 GHA Test Team

#include <gtest/gtest.h>
#include "Automata.h"
#include <string>
#include <utility>

TEST(AutomataTest, InitialStateOFF) {
    Coffee_machine machine = Coffee_machine();
    ASSERT_EQ(StateToString[State::off], machine.GetState());
}

TEST(AutomataTest, CantDepositMoneyWhileOff) {
    Coffee_machine machine = Coffee_machine();
    machine.Coin(1);
    ASSERT_EQ(StateToString[State::off], machine.GetState());
    ASSERT_EQ(0, machine.GetCash());
}

TEST(AutomataTest, CantChoseWhileOff) {
    Coffee_machine machine = Coffee_machine();
    machine.Choice("12345678");
    ASSERT_EQ(StateToString[State::off], machine.GetState());
}

TEST(AutomataTest, CantCookWhileDrinkNotChosen) {
    Coffee_machine machine = Coffee_machine();
    machine.On();
    machine.Ready_to_cook();
    ASSERT_EQ(StateToString[State::wait], machine.GetState());
}

TEST(AutomataTest, CantChooseWhileDrinksNotLoaded) {
    Coffee_machine machine = Coffee_machine();
    machine.On();
    machine.Choice("latte");
    ASSERT_EQ(StateToString[State::wait], machine.GetState());
}

TEST(AutomataTest, AdminCantChooseDrink) {
    Coffee_machine machine = Coffee_machine();
    machine.On();
    machine.Choice("12345678");
    machine.AddPosition("latte", 130);
    machine.Choice("latte");
    ASSERT_EQ(StateToString[State::admin], machine.GetState());
}

TEST(AutomataTest, CantCookWhileNotDepositeEnoughMoney) {
    Coffee_machine machine = Coffee_machine();
    machine.On();
    machine.Choice("12345678");
    machine.AddPosition("cappuccino", 120);
    machine.Cancel();
    machine.Choice("cappuccino");
    machine.Coin(1);
    machine.Ready_to_cook();
    ASSERT_EQ(StateToString[State::check], machine.GetState());
}

TEST(AutomataTest, CantDeleteNonExistentDrink) {
    Coffee_machine machine = Coffee_machine();
    machine.On();
    machine.Choice("12345678");
    std::string answer = machine.DeletePosition("latte");
    ASSERT_EQ("There is no such drink in the vending machine!", answer);
}

TEST(AutomataTest, CannotCancelWhenOff) {
    Coffee_machine machine = Coffee_machine();
    machine.Cancel();
    ASSERT_EQ(StateToString[State::off], machine.GetState());
}

TEST(AutomataTest, OffFromWaitState) {
    Coffee_machine machine = Coffee_machine();
    machine.On();
    machine.Off();
    ASSERT_EQ(StateToString[State::off], machine.GetState());
}

TEST(AutomataTest, MachineIsOn) {
    Coffee_machine machine = Coffee_machine();
    machine.On();
    ASSERT_EQ(StateToString[State::wait], machine.GetState());
}

TEST(AutomataTest, CantOffFromCheckState) {
    Coffee_machine machine = Coffee_machine();
    machine.On();
    machine.Choice("12345678");
    machine.AddPosition("latte", 120);
    machine.Cancel();
    machine.Choice("latte");
    machine.Off();
    ASSERT_EQ(StateToString[State::check], machine.GetState());
}

TEST(AutomataTest, ReturnChangeIfCancel1) {
    Coffee_machine machine = Coffee_machine();
    machine.On();
    machine.Choice("12345678");
    machine.AddPosition("latte", 120);
    machine.Cancel();
    machine.Choice("latte");
    int change = machine.Cancel();
    ASSERT_EQ(0, change);
}

TEST(AutomataTest, ReturnChangeIfCancel2) {
    Coffee_machine machine = Coffee_machine();
    machine.On();
    machine.Choice("12345678");
    machine.AddPosition("latte", 120);
    machine.Cancel();
    machine.Choice("latte");
    machine.Coin(100);
    int change = machine.Cancel();
    ASSERT_EQ(100, change);
}

TEST(AutomataTest, SuccessfullyPreparedDrink) {
    Coffee_machine machine = Coffee_machine();
    machine.On();
    machine.Choice("12345678");
    machine.AddPosition("latte", 120);
    machine.Cancel();
    machine.Choice("latte");
    machine.Coin(130);
    std::pair<std::string, unsigned int> answer = machine.Ready_to_cook();
    ASSERT_EQ(std::make_pair(
        "The drink has been successfully prepared, get your change",
         10), answer);
}
