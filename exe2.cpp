/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   newmain.cpp
 * Author: vinic
 *
 * Created on 14 de novembro de 2020, 22:52
 */

#include <cstdlib>
#include <iostream>
#include <vector>
#include <queue>
#include <climits>

using namespace std;

const int INF = INT_MAX;
typedef pair<int, int> my_pair;

//funcao recursiva auxiliar para printar os vertices do menor caminho
void tracking_path(vector<int> parent, int v) {
    if(parent[v] == -1) {
        return;
    }
    tracking_path(parent, parent[v]);
    cout << " -> " << v;
}

//imprime a solucao do problema
void print_shortest_path(int source, int destination, int cost, vector<int> parent) {
    cout << "Origem: "  << source << endl; 
    cout << "Destino: " << destination << endl;
    cout << "Custo: " << cost << endl;
    cout << "Caminho: " << source;
    tracking_path(parent, destination);
    cout << endl;
}

//funcao dijkstra para calcular o menor custo da viagem
//recebe a lista de adjacencias do grafo, o numero de vertices, a origem e o destino
void dijkstra(vector<pair<my_pair, double>> adj[], int V, int source, int destination) {
    vector<int> dist; //vector para armazenar as distancias ate cada vertice
    dist.assign(V, INF);
    vector<bool> visited; //vetor de bool para armazenar se um vertice ja foi visitado ou nao
    visited.assign(V, false);
    vector<int> parent; //armazenar os vertices que compoem o menor custo da viagem
    parent.assign(V, -1);
    priority_queue<my_pair, vector<my_pair>, greater<my_pair>> my_pq; //fila de prioridades para armazenar os custos e os vertices (utilizando min-heap)

    //inicializa o custo da origem (distancia) com 0 e insere a origem na fila de prioridades
    dist[source] = 0;
    my_pq.push({0, source});

    //enquanto a fila de prioridades nao estiver vazia, ira repetir ate as distancias serem verificadas
    while(!my_pq.empty()) { 
        int u = my_pq.top().second; //retorna o vertice que esta no topo da fila de prioridades
        my_pq.pop(); //retira da fila de prioridade o pair com menor distancia
        if(visited[u]) {
            continue;
        }
        visited[u] = true;
        if(u == destination) { //se o vertice que esta sendo analisado eh o destino
            print_shortest_path(source, destination, dist[u], parent);
            return;
        }
        for(auto e : adj[u]) { 
            my_pair vertex_weight = e.first; //primeiro campo é o pair {vertice, distancia}
            double toll = e.second; //segundo campo é o valor do pedagio
            int v = vertex_weight.first, w = vertex_weight.second;
            if(dist[v] > dist[u] + w + toll) { //relaxamento: verifica se existe um caminho de menor custo do que o armazenado em dist atual
                dist[v] = dist[u] + w + toll;
                parent[v] = u; //atribui para o vertice o seu antecessor que compoe o menor caminho
                my_pq.push({dist[v], v}); //adiciona na fila de prioridades o novo custo atualizado e o vertice v
            }
        }
    }
}

int main() {
    int V = 5;
    vector<pair<my_pair, double>> adj[V];
    
    /*double fuel_price = 4;
    double driving_range = 10;
    double vehicle_cost = driving_range * fuel_price; */

    //adicionando na lista de adjacencias os vertices com seus respectivos vizinhos e distancias e o valor do pedagio de cada vertice
    adj[0].push_back({{1, 10}, 0});
    adj[0].push_back({{4, 100}, 0});
    adj[0].push_back({{3, 30}, 0});
    adj[1].push_back({{2, 50}, 7});
    adj[2].push_back({{4, 10}, 6});
    adj[3].push_back({{2, 20}, 8});
    adj[3].push_back({{4, 60}, 8});
    adj[4].push_back({{4, 0}, 750}); //OBS: tem que considerar tambem o pedagio para entrar na ultima cidade, mas nao ta pegando esse valor

    //chamada para calcular o menor caminho passando a lista de adjacencias, o numero de vertices do grafo, a origem e o destino
    dijkstra(adj, V, 0, 4);

    return 0;
}