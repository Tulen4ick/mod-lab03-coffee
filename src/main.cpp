// Copyright 2022 UNN-IASR
#include "Automata.h"

int main() {
    Coffee_machine machine = Coffee_machine();
    machine.On();
    machine.Choice("12345678");
    machine.AddPosition("cappuccino", 120);
    machine.AddPosition("latte", 130);
    machine.DeletePosition("latte");
    machine.AddPosition("vanilla raff", 150);
    machine.Cancel();
    machine.GetState();
    machine.GetMenu();
    machine.Choice("vanilla raff");
    machine.Coin(120);
    machine.Ready_to_cook();
    machine.Coin(50);
    machine.Ready_to_cook();
}