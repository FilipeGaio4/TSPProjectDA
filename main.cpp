//
// Created by leodr on 02/05/2024.
//


#include <iostream>
#include <string>
#include <chrono>
#include "src/data_structures/Graph.h"
#include "src/Menu.h"

using namespace std;


int main() {
    string option;
    ManagementSystem system;
    Menu temp(system);
    while(true) {
        cout << "Welcome to our TSP algorithm" << endl;
        cout << "Which data structure would you like to use?" << endl;
        cout << "1. Toy Graphs\n2. Real World Graphs\n3. Extra Fully Connected Graphs" << endl;
        cin >> option;
        auto start = chrono::high_resolution_clock::now();
        if (option == "1") {
            while(true) {
                cout << "Which Toy Graph do you want to use?" << endl;
                cout << "1. Shipping\n2. Stadiums\n3. Tourism" << endl;
                cin >> option;
                if (option == "1") {
                    cout << "Shipping Graph" << endl;
                    system.toyGraphs("shipping");
                    break;
                } else if (option == "2") {
                    cout << "Stadiums Graph" << endl;
                    system.toyGraphs("stadiums");
                    break;
                } else if (option == "3") {
                    cout << "Tourism Graph" << endl;
                    system.toyGraphsExtra();
                    break;
                } else {
                    cout << "Invalid option" << endl;
                    temp.enterToContinue();
                }
            }
        } else if (option == "2") {
            while(true) {
                cout << "Which Real World Graph you want to use?" << endl;
                cout << "1. Graph 1\n2. Graph 2\n3. Graph 3" << endl;
                cin >> option;
                if (option == "1") {
                    cout << "Graph 1" << endl;
                    system.readGraps(option);
                    break;
                } else if (option == "2") {
                    cout << "Graph 2" << endl;
                    system.readGraps(option);
                    break;
                } else if (option == "3") {
                    cout << "Graph 3" << endl;
                    system.readGraps(option);
                    break;
                } else {
                    cout << "Invalid option" << endl;
                    temp.enterToContinue();
                }
            }
        } else if (option == "3") {
            while(true) {
                cout << "Which Extra Fully Connected Graph do you want to use?" << endl;
                cout << "1. 25 Nodes" << endl;
                cout << "2. 50 Nodes" << endl;
                cout << "3. 75 Nodes" << endl;
                cout << "4. 100 Nodes" << endl;
                cout << "5. 200 Nodes" << endl;
                cout << "6. 300 Nodes" << endl;
                cout << "7. 400 Nodes" << endl;
                cout << "8. 500 Nodes" << endl;
                cout << "9. 600 Nodes" << endl;
                cout << "10. 700 Nodes" << endl;
                cout << "11. 800 Nodes" << endl;
                cout << "12. 900 Nodes" << endl;
                cin >> option;
                if (option == "1") {
                    cout << "25 Nodes" << endl;
                    system.extraFullyConnectedGraphs(25);
                    break;
                } else if (option == "2") {
                    cout << "50 Nodes" << endl;
                    system.extraFullyConnectedGraphs(50);
                    break;
                } else if (option == "3") {
                    cout << "75 Nodes" << endl;
                    system.extraFullyConnectedGraphs(75);
                } else if (option == "4") {
                    cout << "100 Nodes" << endl;
                    system.extraFullyConnectedGraphs(100);
                    break;
                } else if (option == "5") {
                    cout << "200 Nodes" << endl;
                    system.extraFullyConnectedGraphs(200);
                    break;
                } else if (option == "6") {
                    cout << "300 Nodes" << endl;
                    system.extraFullyConnectedGraphs(300);
                    break;
                } else if (option == "7") {
                    cout << "400 Nodes" << endl;
                    system.extraFullyConnectedGraphs(400);
                    break;
                } else if (option == "8") {
                    cout << "500 Nodes" << endl;
                    system.extraFullyConnectedGraphs(500);
                    break;
                } else if (option == "9") {
                    cout << "600 Nodes" << endl;
                    system.extraFullyConnectedGraphs(600);
                    break;
                } else if (option == "10") {
                    cout << "700 Nodes" << endl;
                    system.extraFullyConnectedGraphs(700);
                    break;
                } else if (option == "11") {
                    cout << "800 Nodes" << endl;
                    system.extraFullyConnectedGraphs(800);
                    break;
                } else if (option == "12") {
                    cout << "900 Nodes" << endl;
                    system.extraFullyConnectedGraphs(900);
                    break;
                } else {
                    cout << "Invalid option" << endl;
                    temp.enterToContinue();
                }
            }
        } else {
            cout << "Invalid option" << endl;
            temp.enterToContinue();
            continue;
        }
        auto finish = chrono::high_resolution_clock::now();
        chrono::duration<double> elapsed = finish - start;
        cout << "Time to read files: " << elapsed.count() << endl;
        break;
    }
    Menu menu(system);

    menu.start();
    return 0;
}