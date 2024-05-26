//
// Created by leodr on 02/05/2024.
//

#include "ManagementSystem.h"
#include <iostream>
#include <sstream>
#include "Colors.h"
#include "data_structures/Graph.h"
#include "data_structures/MutablePriorityQueue.h"
#include <filesystem>
#include <cmath>
#include <map>
#include <set>
#include <algorithm>
#include <cfloat>

using namespace std;

#ifndef DATASET_DIR
#define DATASET_DIR "."  // Default to current directory if OUTPUT_DIR is not defined
#endif


void ManagementSystem::readGraps(string name) {
    readNodes(string(DATASET_DIR) + "/Real-world-Graphs/graph" + name + "/nodes.csv");
    readEdgesFiles("graph" + name);
}

void ManagementSystem::extraFullyConnectedGraphs(int i) {
    readNodes(i);
    readEdges(string(DATASET_DIR) + "/Extra_Fully_Connected_Graphs/edges_" + to_string(i) + ".csv");

}

void ManagementSystem::toyGraphs(string name) {
    ifstream file(string(DATASET_DIR) + "/Toy-Graphs/" + name + ".csv");
    int src, dest;
    string ssrc, sdest, sweight;
    double weight;
    if (!file) {
        cerr << "Failed to open file\n";
        exit(EXIT_FAILURE);
    }

    string line;
    getline(file, line); //ignore the header
    while (getline(file, line)) {
        istringstream iss(line);
        getline(iss, ssrc, ',');
        getline(iss, sdest, ',');
        getline(iss, sweight, '\r');


        src = stoi(ssrc);
        dest = stoi(sdest);
        weight = stod(sweight);


        if (network.findVertex(src) == nullptr) {
            network.addVertex(src);
        }
        if (network.findVertex(dest) == nullptr) {
            network.addVertex(dest);
        }
        network.addEdge(src, dest, weight);
        network.addEdge(dest, src, weight);
    }
}

void ManagementSystem::toyGraphsExtra() {
    ifstream file(string(DATASET_DIR) + "/Toy-Graphs/tourism.csv");
    int src, dest;
    string ssrc, sdest, sweight, nsrc, ndest;
    double weight;
    if (!file) {
        cerr << "Failed to open file\n";
        exit(EXIT_FAILURE);
    }

    string line;
    getline(file, line); //ignore the header
    while (getline(file, line)) {
        istringstream iss(line);
        getline(iss, ssrc, ',');
        getline(iss, sdest, ',');
        getline(iss, sweight, ',');
        getline(iss, nsrc, ',');
        getline(iss, ndest, '\r');


        src = stoi(ssrc);
        dest = stoi(sdest);
        weight = stod(sweight);

        Vertex<int> *v = network.findVertex(src);
        if (v == nullptr) {
            network.addVertex(src);
            v = network.findVertex(src);
            v->setName(nsrc);
        }

        v = network.findVertex(dest);
        if (v == nullptr) {
            network.addVertex(dest);
            v = network.findVertex(dest);
            v->setName(ndest);
        }
        network.addEdge(src, dest, weight);
        network.addEdge(dest, src, weight);
    }

}

void ManagementSystem::readNodes(int i) {
    ifstream file(string(DATASET_DIR) + "/Extra_Fully_Connected_Graphs/nodes.csv");
    int id;
    string slat, slon, sid;
    double lat, lon;
    if (!file) {
        cerr << "Failed to open file\n";
        exit(EXIT_FAILURE);
    }

    string line;
    getline(file, line); //ignore the header
    for (int j = 0; j < i; j++) {
        getline(file, line);
        istringstream iss(line);
        getline(iss, sid, ',');
        getline(iss, slon, ',');
        getline(iss, slat, '\r');
        id = stoi(sid);
        lat = stod(slat);
        lon = stod(slon);
        network.addVertex(id);
        Vertex<int> *v = network.findVertex(id);
        v->setLatitude(lat);
        v->setLongitude(lon);
    }

}


void ManagementSystem::readEdges(std::string path) {
    ifstream file(path);
    int src, dest;
    string ssrc, sdest, sweight;
    double weight;
    if (!file) {
        cerr << "Failed to open file\n";
        exit(EXIT_FAILURE);
    }

    string line;
    getline(file, line); //ignore the header
    while (getline(file, line)) {
        istringstream iss(line);
        getline(iss, ssrc, ',');
        getline(iss, sdest, ',');
        getline(iss, sweight, '\r');
        src = stoi(ssrc);
        dest = stoi(sdest);
        weight = stod(sweight);
        network.addEdge(src, dest, weight);
        network.addEdge(dest, src, weight);
    }
}


void ManagementSystem::readNodes(string path) {
    ifstream file(path);
    int id;
    string slat, slon, sid;
    double lat, lon;
    if (!file) {
        cerr << "Failed to open file\n";
        exit(EXIT_FAILURE);
    }

    string line;
    getline(file, line); //ignore the header
    while (getline(file, line)) {
        istringstream iss(line);
        getline(iss, sid, ',');
        getline(iss, slon, ',');
        getline(iss, slat, '\r');
        id = stoi(sid);
        lat = stod(slat);
        lon = stod(slon);
        network.addVertex(id);
        Vertex<int> *v = network.findVertex(id);
        v->setLatitude(lat);
        v->setLongitude(lon);
    }

}

void ManagementSystem::readEdgesFiles(string name) {
    readEdges(string(DATASET_DIR) + "/Real-world-Graphs/" + name + "/edges.csv");
}

int ManagementSystem::countEdgeFilesInDir(string path) {
    int fileCount = 0;
    for (const auto &entry: std::filesystem::directory_iterator(path)) {
        if (is_regular_file(entry) && entry.path().filename().string().rfind("edges", 0) == 0) {
            fileCount++;
        }
    }
    return fileCount;
}

const Graph<int> &ManagementSystem::getNetwork() const {
    return network;
}

void ManagementSystem::setNetwork(const Graph<int> &network) {
    ManagementSystem::network = network;
}

void ManagementSystem::setDisatnce(double distance) {
    best_distance = distance;
}

double ManagementSystem::getDistance() const {
    return best_distance;
}

void ManagementSystem::setPath(list<int> path) {
    best_path = path;
}

list<int> ManagementSystem::getPath() const {
    return best_path;
}

void printPath(const list<int> &path) {
    bool first_element = true;
    for (const int &i: path) {
        if (!first_element) cout << " -> ";
        else first_element = false;
        cout << i;
    }
}

void ManagementSystem::backtracking(const bool progress) {
    for (auto v: network.getVertexSet()) v.second->setVisited(false);
    double distance = 0;
    setDisatnce(distance);
    list<int> path = {};
    setPath(path);
    Vertex<int> *start_v = network.findVertex(0);
    auto start = chrono::high_resolution_clock::now();
    backtrack(start_v, path, distance, progress);
    auto finish = chrono::high_resolution_clock::now();
    chrono::duration<double> elapsed = finish - start;

    cout << endl << "Shortest path: ";
    printPath(getPath());
    cout << endl << "Distance: " << fixed << setprecision(2) << getDistance() << endl
        << "Elapsed time : " << setprecision(5) << elapsed.count() << endl << endl;
}

void ManagementSystem::backtrack(Vertex<int> *v, list<int> path, double distance, const bool progress) {
    v->setVisited(true);
    path.push_back(v->getInfo());
    best_distance = getDistance();
    bool connection_to_origin = false;
    double distance_to_origin;

    if (progress) {
        printPath(path);
        cout << endl;
    }

    for (auto e: v->getAdj()) {
        Vertex<int> *v_dest = e->getDest();
        if (v_dest->getInfo() == 0) {
            connection_to_origin = true;
            distance_to_origin = e->getWeight();
        }
        if (!v_dest->isVisited()) {
            double test_distance = distance + e->getWeight();
            if ((best_distance == 0 || test_distance < best_distance)) backtrack(v_dest, path, test_distance, progress);
            else if (progress) {
                list<int> failed_path = path;
                failed_path.push_back(v_dest->getInfo());
                cout << "Failed: ";
                printPath(failed_path);
                cout << " Distance: " << test_distance << endl;
            }
        }
    }

    distance += distance_to_origin;
    if (path.size() == network.getNumVertex() && connection_to_origin) {
        if (best_distance == 0 || distance < best_distance) {
            path.push_back(0);
            if (progress) {
                printPath(path);
                cout << endl << "New distance: " << distance << endl;
            }
            setDisatnce(distance);
            setPath(path);
        } else if (progress) {
            path.push_back(0);
            cout << "Failed: ";
            printPath(path);
            cout << " Distance: " << distance << endl;
        }
    }

    v->setVisited(false);
}

void ManagementSystem::mst() {
    MutablePriorityQueue<Vertex<int>> queue;

    for (auto vertex: network.getVertexSet()) {
        vertex.second->setPath(nullptr);
        vertex.second->setVisited(false);
        vertex.second->setPrimDist(9999999999);
        queue.insert(vertex.second);
        //inicializar double e progress a falso se for preciso
    }

    auto start = network.findVertex(0);
    start->setPrimDist(0);
    queue.decreaseKey(start);

    while (!queue.empty()) {
        auto v = queue.extractMin();
        v->setVisited(true);
        for (auto edge: v->getAdj()) {
            auto w = edge->getDest();
            if (!w->isVisited() && edge->getWeight() < w->getPrimDist()) {
                Edge<int> *prevPath = w->getPath();
                w->setPrimDist(edge->getWeight());
                w->setPath(edge);
                queue.decreaseKey(w);
                //por a true double e progress
            }
        }
    }


}

double haversineDistance(double latitude1, double longitude1, double latitude2, double longitude2) {

    double lat1_rad = latitude1 * M_PI / 180.0;
    double long1_rad = longitude1 * M_PI / 180.0;
    double lat2_rad = latitude2 * M_PI / 180.0;
    double long2_rad = longitude2 * M_PI / 180.0;

    double delta_latitude = lat2_rad - lat1_rad;
    double delta_longitude = long2_rad - long1_rad;

    double sin_half_delta_latitude = sin(delta_latitude / 2.0);
    double sin_half_delta_longitude = sin(delta_longitude / 2.0);

    double a = sin_half_delta_latitude * sin_half_delta_latitude +
               cos(lat1_rad) * cos(lat2_rad) * sin_half_delta_longitude * sin_half_delta_longitude;

    double c = 2.0 * atan2(sqrt(a), sqrt(1.0 - a));

    // Radius of the Earth in meters
    const double earth_radius_meters = 6371000.0;

    return earth_radius_meters * c;
}
template <class T>
bool isSpanningTree(const std::vector<Vertex<T> *> &res){
    std::map<int, std::set<int> > adj;
    for(const Vertex<T> *v: res) {
        adj[v->getInfo()];
        if (v->getPath() != nullptr) {
            Vertex<T> *u = v->getPath()->getOrig();
            adj[u->getInfo()].emplace(v->getInfo());
            adj[v->getInfo()].emplace(u->getInfo());
        }
    }

    std::queue<int> q;
    std::set<int> visited;
    q.push(res.at(0)->getInfo());
    while(!q.empty()){
        int u = q.front(); q.pop();
        if(visited.count(u)) continue;
        visited.emplace(u);
        for(const int &v: adj.at(u)){
            q.emplace(v);
        }
    }

    for(const Vertex<T> *v: res)
        if(!visited.count(v->getInfo())) return false;
    return true;
}

double ManagementSystem::calculateTriangular(vector<int> &path) { //refactor
    double totalDistance = 0;
    auto startVertex = network.findVertex(0);
    int count = 0;

    mst(); //make the mst
    //cout << isSpanningTree(network.getVertexSet());

    for (auto vertex : network.getVertexSet()) {
        vertex.second->setVisited(false);
    }

    dfsMst(startVertex, path, count);

    path.push_back(0);//backs to start to finish loop

    for (size_t i = 0; i < path.size() - 1; i++) {
        auto v = network.findVertex(path[i]);
        auto w = network.findVertex(path[i + 1]);
        auto e = v->findEdge(w->getInfo());
        if (e == nullptr) { // if no edge haversine
            totalDistance += haversineDistance(v->getLatitude(), v->getLongitude(), w->getLatitude(), w->getLongitude());
        } else {
            totalDistance += e->getWeight();
        }
    }

    return totalDistance;
}

void ManagementSystem::dfsMst(Vertex<int>* vertex, std::vector<int>& path, int& count) {
    vertex->setVisited(true);
    path.push_back(vertex->getInfo());
    for (auto edge : vertex->getAdj()) {
        auto dest = edge->getDest();
        if (!dest->isVisited() && edge == dest->getPath()) {
            dfsMst(dest, path, count);
        }
    }
}

double ManagementSystem::nearestNeighbour(vector<int> &path, int id) {
    for (auto v : network.getVertexSet()){
        v.second->setVisited(false);
    }
    path.clear();
    Vertex<int> * atual = network.findVertex(id);
    Vertex<int> * first = atual;
    if (atual == nullptr) return -1;
    double size = network.getNumVertex();
    double distance = 0;
    path.push_back(id);
    atual->setVisited(true);
    int countVisited = 0; //Numero de vertices visitados so far

    Vertex<int> * nextVertex = atual; // inicializar a atual para caso a primeira iteracao n tenha edges

    while (countVisited < size - 1){
        double minDist = 99999999;
        for (auto e : atual->getAdj()){
            if (!e->getDest()->isVisited() && e->getWeight() < minDist){
                minDist = e->getWeight();
                nextVertex = e->getDest();
            }
        }
        if (atual == nextVertex){
            minDist = findNearest(atual, nextVertex);
        }
        distance += minDist;
        atual = nextVertex;
        countVisited++;
        path.push_back(atual->getInfo());
        atual->setVisited(true);

    }
    distance += haversineDistance(atual->getLatitude(), atual->getLongitude(), first->getLatitude(), first->getLongitude());
    path.push_back(0);
    return distance;
}

double ManagementSystem::findNearest(Vertex<int> *atual, Vertex<int> *&nextVertex) {
    double minDist = 999999999;
    double distance;
    for (auto vertex : network.getVertexSet()){
        if (!vertex.second->isVisited() && vertex.second != atual){
            distance = haversineDistance(atual->getLatitude(), atual->getLongitude(), vertex.second->getLatitude(), vertex.second->getLatitude());
            if (distance < minDist){
                minDist = distance;
                nextVertex = vertex.second;
            }
        }
    }
    return minDist;
}




double ManagementSystem::dijkstra(Vertex<int> *source, Vertex<int> *dest, vector<int> &path) {
    // Initialize the distance to all vertices to infinity and the distance to the source to 0
    double res=0;
    for (auto v : network.getVertexSet()) {
        v.second->setPrimDist(99999999);
        v.second->setPath(nullptr); // clear previous paths
        v.second->setProcessing(false);
    }
    source->setPrimDist(0);

    // Create a priority queue and insert all vertices
    MutablePriorityQueue<Vertex<int> > q;
    q.insert(source);

    while (!q.empty()) {
        // Extract the vertex with the minimum distance
        auto u = q.extractMin();
        u->setProcessing(true);

        // Stop if we reached the destination
        if (u == dest) break;

        // For each adjacent vertex of u
        for (auto edge : u->getAdj()) {
            Vertex<int> *v = edge->getDest();
            int newDist = u->getPrimDist() + edge->getWeight();

            // If a shorter path to v is found
            if (!v->isProcessing() && newDist < v->getPrimDist()) {
                v->setPrimDist(newDist);
                v->setPath(edge); // set the path to reach v
                q.insert(v);
            }
        }
    }

    // Reconstruct the shortest path from source to dest
    path.clear();
    Vertex<int> *v = dest;
    while (v != nullptr) {
        path.push_back(v->getInfo()); // assuming getInfo returns the int or the int's identifier
        auto edge = v->getPath();
        if (edge == nullptr) break;
        res+=edge->getWeight();
        if(edge->getOrig()== nullptr){
            cout<<"error";
        }
        v = edge->getOrig();
    }
    std::reverse(path.begin(), path.end());
    return res;
}


double ManagementSystem::realWorldTSP(vector<int> &path, int start) {
    double result = 0;

    cout<<path.size()<<endl;
    auto v=network.findVertex(int(start));
    for( auto vertex : network.getVertexSet()){
        vertex.second->setVisited(false);
    }
    int numVertex = network.getNumVertex();
    cout<<numVertex<<endl;
    int current=1;
    path.push_back(start);
    while(current < numVertex){
        v->setVisited(true);
        double  minimum=DBL_MAX;
        auto next=v;
        for( auto edge: v->getAdj()){
            if(edge->getDest()->isVisited()==false && edge->getWeight() < minimum){
                next=edge->getDest();
                minimum=edge->getWeight();
            }
        }
        if(next != v){
            result+=minimum;
            path.push_back(next->getInfo());
            current++;
            v=next;
        }
        else{
            for( auto ver : network.getVertexSet()){
                if(ver.second->isVisited()==false){
                    path.push_back(ver.second->getInfo());
                    vector<int> dummyVector;
                    result+=dijkstra(v, ver.second, dummyVector);

                    v=ver.second;
                    current++;
                    break;
                }
            }
        }
    }
    return result;
}