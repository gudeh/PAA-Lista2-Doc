/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   exe2.cpp
 * Author: vinic
 *
 * Created on 14 de novembro de 2020, 22:38
 */

#include <cstdlib>
#include <iostream>
#include <vector>
#include <queue>

using namespace std;
  
const int V = 5;
const int INF = 1e9;
typedef pair<int, int> my_pair;

//imprime a solucao do problema -> implementar para mostrar o caminho dos vertices percorridos
void print_shortest_path(int source, int destination, int cost) {
    cout << "Origem: "  << source << endl; 
    cout << "Destino: " << destination << endl;
    cout << "Custo: " << cost << endl;
    //cout << "Caminho: " << endl;
}

//funcao dijkstra para calcular o menor caminho
//recebe a lista de adjacencias do grafo, o numero de vertices, a origem e o destino
void dijkstra(vector<my_pair> adj[], int V, int source, int destination) {
    vector<int> dist; //vector para armazenar a menor distancia (custo) ate cada vertice
    dist.assign(V, INF);
    vector<bool> visited; //vetor de bool para armazenar se um vertice ja foi visitado ou nao
    visited.assign(V, false);
    vector<int> parent; //armazenar os vertices que compoem o menor caminho
    parent.assign(V, -1);
    priority_queue<my_pair, vector<my_pair>, greater<my_pair>> my_pq; //fila de prioridades para armazenar os custos e os vertices (utilizando min-heap)

    //inicializa o custo da origem com 0 e insere a origem na fila de prioridades
    dist[source] = 0;
    my_pq.push({0, source});

    //enquanto a fila de prioridades nao estiver vazia, ira repetir ate as distancias serem verificadas
    while(!my_pq.empty()) { 
        int u = my_pq.top().second; //retorna o vertice que esta no topo da fila de prioridades
        int cost = my_pq.top().first; //retorna o custo que esta no topo da fila
        my_pq.pop(); //retira da fila de prioridade o pair com menor custo
        if(visited[u]) {
            continue;
        }
        visited[u] = true;
        if(u == destination) { //se o vertice que esta sendo analisado eh o destino
            print_shortest_path(source, destination, cost);
            return;
        }
        //percorre a lista de adjacencias
        for(auto e : adj[u]) { 
            int v = e.first, w = e.second; 
            if(dist[v] > dist[u] + w) { //relaxamento: verifica se existe um caminho menor do que o armazenado em dist atual
                dist[v] = dist[u] + w;
                parent[v] = u; //atribui para o vertice o seu antecessor que compoe o menor caminho
                my_pq.push({dist[v], v}); //adiciona na fila de prioridades a nova dist atualizada (custo) e o vertice v
            }
        }
    }
}

int main() {
    vector<my_pair> adj[V];
    
    //adicionando na lista de adjacencias os vertices com seus respectivos vizinhos e distancias
    adj[0].push_back({1, 1});
    adj[0].push_back({4, 10});
    adj[0].push_back({3, 3});
    adj[1].push_back({2, 5});
    adj[2].push_back({4, 1});
    adj[3].push_back({2, 2});
    adj[3].push_back({4, 6});
    
    //chamada para calcular o menor caminho passando a lista de adjacencias, o numero de vertices do grafo, a origem e o destino
    dijkstra(adj, V, 0, 4);

    return 0;
}