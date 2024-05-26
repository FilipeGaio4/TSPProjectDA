//
// Created by leodr on 02/05/2024.
//

#ifndef TSPPROJECTDA_MANAGEMENTSYSTEM_H
#define TSPPROJECTDA_MANAGEMENTSYSTEM_H


#include <string>
#include <list>
#include "data_structures/Graph.h"

using namespace std;

/** Classe que define um objeto do tipo ManagementSystem.
 *  Um objeto desta classe tem 3 membros privados.
 *  Um grafo do tipo int que representa a rede de pontos a ser visitados.
 *  Duas vari'aveis do tipo double e list<int> para ajudar a fazer backtracking
 */
class ManagementSystem {

public:
    /** Função que chama as funções que leem os ficheiros Real-world-Graphs.
     * @param name número do grafo escolhido.
    */
    void readGraps(string name);

    /** Função que chama as funções que leem os ficheiros Extra_Fully_Connected_Graphs.
     * @param i número de nodes.
    */
    void extraFullyConnectedGraphs(int i);

    /** Função que lê o ficheiro tourism.csv.
     * 
    */
    void toyGraphsExtra();

    /** Função que lê shipping.csv ou stadiums.csv.
     *  @param name nome do ficheiro
    */
    void toyGraphs(string name);

    /** Função que lê o ficheiro de nodes dos Extra_Fully_Connected_Graphs.
     *  @param i número de nodes
    */
    void readNodes(int i);
    /** Função que lê o ficheiro de nodes dos Real-world-Graphs.
     *  @param path path do ficheiro
    */
    void readNodes(string path);

    /** Função que lê os ficheiros de edges dos Extra_Fully_Connected_Graph e dos Real-world-Graphs.
     *  @param path path do ficheiro
    */
    void readEdges(string path);

    /** Função que chama readEdges para ler todos os ficheiros de edges dos Real-world-Graphs.
     *  @param name pasta dos ficheiros
    */
    void readEdgesFiles(string name);

    /** Função que conta o número de ficheiros de edges dos Real-world-Graphs.
     *  @param path path da pasta
     *  @return número de ficheiros de edges do grafo selecionado
    */
    int countEdgeFilesInDir(string path);

    /** Função que inicia o backtracking.
     *  @param progress true para ver o progresso do backtracking
    */
    void backtracking(const bool progress);

    /** Função recursiva que faz backtracking.
     *  Complexidade temporal: O(V² + E).
     *  @param v vértice a ser analisado
     *  @param path percurso até ao vértice
     *  @param distance distância do percurso percorrido até ao vértice
     *  @param progress true para ver o progresso do backtracking
    */
    void backtrack(Vertex<int>* v, list<int> path, double distance, const bool progress);

    /** Funçao que permite alterar o valor best_distance.
     * @param network novo valor.
    */
    void setDisatnce(double distance);

    /** Função que retorna o valor best_distance.
     * @return valor best_distance.
    */
    double getDistance() const;

    /** Funçao que permite alterar a lista best_path.
     * @param path nova lista.
    */
    void setPath(list<int> path);

    /** Funçao que cria uma mst.
     *
    */
    void mst();

    /** Função que retorna a lista best_path.
     * @return lista best_path.
    */
    list<int> getPath() const;
private:
    Graph<int> network; ///<Grafo que representa a rede de pontos a ser visitados.
    double best_distance; ///<Valor com a melhor distância alcançada durante o backtracking.
    list<int> best_path; ///<Lista com o melhor percurso encontrado durante o backtracking.
public:
    /** Funçao que retorna o grafo network.
     * @return grafo network.
    */
    const Graph<int> &getNetwork() const;

    /** Funçao que permite alterar o grafo network.
     * @param network novo grafo network.
    */
    void setNetwork(const Graph<int> &network);

    /** Funçao que faz dfs pela mst.
     *  Complexidade temporal: O(V+E).
     * @param vertex vértice a ser analisado
     * @param path variável onde é armasenado o percurso calculado
    */
    void dfsMst(Vertex<int> *vertex, vector<int> &path, int &count);

    /** Função que calcula o melhor percurso usando Triangular Approximation Heuristic.
     *  Complexidade temporal: O(1).
     *  @param path variável onde é armasenado o percurso calculado
    */
    double calculateTriangular(vector<int> &path);
    /** Função que calcula o percurso ao ir sempre para o vertex mais próximo. Se não houver edge verifica haversine para todos os não visitados
     * Complexidade temporal: O(V^2 * E).
     * @param path variável onde é armasenado o percurso calculado
     * @param id variável onde começa o path
     * @return distancia do path
     */
    double nearestNeighbour(vector<int> &path, int id);

    /** Função que calcula o vertex mais proximo usando haversine (auxiliar function Nearest Neigbour)
     * @return distancia ate ao mais proximo vertex
     */
    double findNearest(Vertex<int> *atual, Vertex<int> *&nextVertex);

    /**
     * @brief Executa o algoritmo de Dijkstra para encontrar o caminho mais curto entre dois vértices.
     * Complexidade temporal: O(E * log(V)).
     *
     * Esta função calcula o caminho mais curto de um vértice de origem para um vértice de destino
     * num grafo. Utiliza o algoritmo de Dijkstra para determinar o caminho e retorna a
     * distância total desse caminho. O próprio caminho é armazenado no vetor fornecido.
     *
     * @param source Um ponteiro para o vértice de origem.
     * @param dest Um ponteiro para o vértice de destino.
     * @param path Uma referência para um vetor onde o caminho resultante será armazenado. O caminho
     * será uma sequência de índices de vértices desde a origem até ao destino.
     * @return A distância total do caminho mais curto desde a origem até ao destino.
     */
    double dijkstra(Vertex<int> *source, Vertex<int> *dest, vector<int> &path);

    /** Função que calcula o percurso ao ir sempre para o vertex mais próximo. Se não houver edge usa dijkstra para encontrar o caminho mais próximo mesmo que repita vertices
     * Complexidade temporal: O(V^2 * E^2 * log(V)).
     * @param path variável onde é armasenado o percurso calculado
     * @param id variável onde começa o path
     * @return distancia do path
     */
    double realWorldTSP(vector<int> &path, int start);
};


#endif //TSPPROJECTDA_MANAGEMENTSYSTEM_H
