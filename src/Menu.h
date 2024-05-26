//
// Created by leodr on 02/05/2024.
//

#ifndef TSPPROJECTDA_MENU_H
#define TSPPROJECTDA_MENU_H


#include "ManagementSystem.h"

class Menu {
private:
    ManagementSystem system;
public:
    explicit Menu(ManagementSystem system);
    void start();
    void enterToContinue();
};


#endif //TSPPROJECTDA_MENU_H
