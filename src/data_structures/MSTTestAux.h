#ifndef TEST_AUX_H_
#define TEST_AUX_H_

#include "Graph.h"
#include <random>
#include <map>
#include <set>

using namespace std;

template <class T>
bool isSpanningTree(const std::vector<Vertex<T> *> &res);

template <class T>
double spanningTreeCost(const std::vector<Vertex<T> *> &res);

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

template <class T>
double spanningTreeCost(const std::vector<Vertex<T> *> &res){
    double ret = 0;
    for(const Vertex<T> *v: res){
        if(v->getPath() == nullptr) continue;
        const Vertex<T> *u = v->getPath()->getOrig();
        for(const auto e: u->getAdj()){
            if(e->getDest()->getInfo() == v->getInfo()){
                ret += e->getWeight();
                break;
            }
        }
    }
    return ret;
}



#endif //TEST_AUX_H_
