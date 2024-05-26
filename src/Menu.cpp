//
// Created by leodr on 02/05/2024.
//

#include "Menu.h"
#include <iostream>
#include <iomanip>
#include <string>
#include <limits>
#include <chrono>
#include "Colors.h"
using namespace std;



void Menu::enterToContinue() {
    cout << TC_WHITE << BC_RED << "PRESS ENTER TO CONTINUE" << TC_RESET << BC_RESET << endl;
    string z;
    cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
    getline(cin, z);
}

Menu::Menu(ManagementSystem system) : system(std::move(system)) {};

void Menu::start() {
    cout<<"Starting Menu"<<endl;
    Graph<int> network = system.getNetwork();
    int edgeCount= 0;

    cout<<"Nodes amount: "<<network.getVertexSet().size()<<endl;
    for(auto vertex : network.getVertexSet()){
        edgeCount += vertex.second->getAdj().size();
    }
    cout<<"Edges amount: "<<edgeCount<<endl;

    enterToContinue();

    while (true) {
        cout << "Welcome." << endl << "What are you looking for \n" << endl;
        cout << "1) Backtracking" << endl;
        cout << "2) Triangular Approximation" << endl;
        cout << "3) Nearest Neighbour" << endl;
        cout << "4) Real World TSP" << endl;
        cout << "0) Return" << endl;
        
        string temp;
        cin >> temp;
        if (temp == "0") return;
        else if (temp == "1") {
            bool progress;
            cout << "Would you like to see the progress" << endl;
            cout << "1) Yes" << endl;
            cout << "0) No (default)" << endl;
            cin >> temp;
            if (temp == "1") progress = true;
            else progress = false;
            system.backtracking(progress);
        }
        else if (temp == "2"){
            vector<int> path;
            auto start = chrono::high_resolution_clock::now();
            double length = system.calculateTriangular(path);
            auto finish = chrono::high_resolution_clock::now();
            chrono::duration<double> elapsed = finish - start;
            for (auto i = 0; i < path.size()-1; i++){
                cout << path[i] << " -> ";
            }
            cout << path.back()<< endl;
            cout << "Length of the path : " << fixed << setprecision(2) << length << endl
                << "Elapsed time : " << setprecision(5) << elapsed.count() << endl << endl;
            cout<<"Path size: "<<path.size()<<endl;

        }
        else if (temp == "3"){
            vector<int> path;
            auto start = chrono::high_resolution_clock::now();
            double length = system.nearestNeighbour(path, 0);
            auto finish = chrono::high_resolution_clock::now();
            chrono::duration<double> elapsed = finish - start;
            for (auto i = 0; i < path.size()-1; i++){
                cout << path[i] << " -> ";
            }
            cout << path.back()<< endl;
            cout << "Length of the path : " << fixed << setprecision(2) << length << endl
                << "Elapsed time : " << setprecision(5) << elapsed.count() << endl << endl;
            cout<<"Path size: "<<path.size()<<endl;

        }
        else if(temp=="4"){
            while(true) {
                cout << "What's the starting point?" << endl;
                cout << "Choose a number between 0 and " << network.getVertexSet().size() - 1 << endl;
                cin>>temp;
                if(stoi(temp) >= 0 && stoi(temp) < network.getVertexSet().size()) break;
                else cout<<"Invalid start point"<<endl;
            }
            vector<int> path;
            auto start = chrono::high_resolution_clock::now();
            double length = system.realWorldTSP(path, stoi(temp));
            auto finish = chrono::high_resolution_clock::now();
            chrono::duration<double> elapsed = finish - start;
            for (auto i = 0; i < path.size()-1; i++){
                cout << path[i] << " -> ";
            }
            cout << path.back()<< endl;
            cout << "Length of the path : " << fixed << setprecision(2) << length << endl
                 << "Elapsed time : " << setprecision(5) << elapsed.count() << endl << endl;
            cout<<"Path size: "<<path.size()<<endl;
        }
    }
}
