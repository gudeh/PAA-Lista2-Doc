/*
 * Primeiro exercicio da lista 2 da discilpina de Projeto e Analise de Algoritmos
 */

/* 
 * File:   main.cpp
 * Author: gudeh
 *
 * Created on November 6, 2020, 6:34 PM
 */

#include <cstdlib>
#include <vector>
#include <set>
#include <map>
#include <iostream>
#include <utility>
#include <climits>
#include <queue>

using namespace std;

//estrutura que armazena informacoes de cada nodo do grafo
struct node {
    bool visited=false;
     int distance=INT_MAX;
     node* previous=NULL;
     int id=0;
     //Cada nodo possui um set com ponteiros para nodos que conectam a este nodo.
     //O container SET garante que não haverão repetições entre os elementos,
     //além de providenciar acesso a membros com complexidade temporal aceitavel.
    set<node*> conexoes;
};

printQueue(queue<node*> Q){
    cout<<"my queue:";
        while(!Q.empty()){
		cout<<" "<<Q.front()->id;
		Q.pop();
	}
        cout<<endl;
}

//Funcao que resolve o primeiro exercicio, a chamada dela é feita na main
vector<int> primeiroExercicio(vector<int> centrais,vector<pair<int,int> > adjacencias, int origem, int destino){
    //Inicializando grafo a partir dos parametros informados.
    //O grafo é armazenado em formato de hash, ou seja a estrtura MAP do C++.
    //As chaves serão os IDs dos nodos que referenciam aos próprios nodos (struct acima).
    map<int,node> my_graph;
    for (vector<int>::iterator it=centrais.begin();it!=centrais.end();it++)
    {
        node node_inst;
        node_inst.id=*it;
        my_graph.insert(pair<int,node>(*it,node_inst));
    }
    
    //Aplicando conexoes aos elementos do grafo
    for(int i=0;i<adjacencias.size();i++)
    {
        node node_inst;
        my_graph.find(adjacencias[i].first)->second.conexoes.insert(&my_graph.find(adjacencias[i].second)->second);
        my_graph.find(adjacencias[i].second)->second.conexoes.insert(&my_graph.find(adjacencias[i].first)->second);
    }
    
    //Inicializando fila, ja incluindo o primeiro elemento (origem)
    queue<node*> my_queue;
    my_graph.find(origem)->second.distance=0;
    my_graph.find(origem)->second.visited=true;
    my_queue.push(&my_graph.find(origem)->second);
    node* front;
    //Realizando processos de BFS com fila e grafo
    while(!my_queue.empty())
    {
        front=my_queue.front();
        my_queue.pop();
        cout<<"front:"<<front->id<<", queue size:"<<my_queue.size()<<endl;
        printQueue(my_queue);
        for(set<node*>::iterator it=front->conexoes.begin();it!=front->conexoes.end();it++)
        {
            if((*it)->visited==false)
            {
                (*it)->visited=true;
                (*it)->distance=front->distance+1;
                (*it)->previous=front;
                my_queue.push(*it);
            }
        }
    }
    for(map<int,node>::iterator it=my_graph.begin();it!=my_graph.end();it++)
        cout<<"node:"<<it->first<<"-->"<<"visited:"<<it->second.visited<<", dist:"<<it->second.distance<<endl;//<<", previous:"<<it->second.previous->id<<endl;
    cout<<"distancia resultante:"<<my_graph.find(destino)->second.distance<<endl;
    
    //Montando vetor com menor caminho encontrado, para retorno da funcao.
    node* checker=&my_graph.find(destino)->second;
    vector<int> ret;
    while(checker->id!=origem)
    {
        ret.push_back(checker->id);
        checker=checker->previous;
    }
    ret.push_back(origem);
    for(int i=ret.size()-1;i>=0;i--)
        cout<<ret[i]<<","; cout<<endl;
    return ret;
}
/*
 * 
 */
int main(int argc, char** argv) {
//    vector<int> centrais_exemplo={1,2,3,4,5,23,35,50};
//    vector<pair<int,int> > adjacencias_exemplo={pair<int,int>(2,3),pair<int,int>(4,5),pair<int,int>(2,4),pair<int,int>(5,23),pair<int,int>(2,4)};
    
    //Os IDs dos nodos e as adjacencias devem ser explicitamente expostas com os vectors: centrais_exemplo e adjacencias_exemplo, 
    //no qual são enviados como parâmetro para a função que resolve o exercicio 1.
    //O programa foi testado empiracamente com diferentes combinações de conexões e parece estar funcionando como deveria.
    vector<int> centrais_exemplo={1,2,3,4,5,6};
    vector<pair<int,int> > adjacencias_exemplo={pair<int,int>(1,2),pair<int,int>(1,3),pair<int,int>(1,4),pair<int,int>(3,4),pair<int,int>(4,6),pair<int,int>(3,5),pair<int,int>(6,5)};
    primeiroExercicio(centrais_exemplo,adjacencias_exemplo,1,5);
    return 0;
}


