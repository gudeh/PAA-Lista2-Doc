/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
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

struct node {
    bool visited=false;
     int distance=INT_MAX;
     node* previous=NULL;
     int id=0;
    set<node*> conexoes;
//public:
//    void 
};


//node* findNode(vector< int> param, int id){
//    for(int i=0;i<param.size();param++)
//    {
//        if(param[i]==id)
//    }
//}

vector<int> primeiroExercicio(vector<int> centrais,vector<pair<int,int> > adjacencias, int origem, int destino){
    //Inicializando grafo
    map<int,node> my_graph;
    cout<<my_graph.size()<<endl;
    for (vector<int>::iterator it=centrais.begin();it!=centrais.end();it++)
    {
        node node_inst;
        node_inst.id=*it;
        my_graph.insert(pair<int,node>(*it,node_inst));
    }
    
    //aplicando conexoes aos elementos do grafo
    for(int i=0;i<adjacencias.size();i++)
    {
        node node_inst;
        my_graph.find(adjacencias[i].first)->second.conexoes.insert(&my_graph.find(adjacencias[i].second)->second);
        my_graph.find(adjacencias[i].second)->second.conexoes.insert(&my_graph.find(adjacencias[i].first)->second);
    }
    cout<<my_graph.size()<<endl;
    //realizar BFS
    
//    my_graph.find(origem)->second.visited=true;
    queue<node*> my_queue;
    my_graph.find(origem)->second.distance=0;
    my_queue.push(&my_graph.find(origem)->second);
    node* front;
    while(!my_queue.empty())
    {
        
        front=my_queue.front();
        my_queue.pop();
        cout<<"front:"<<front->id<<endl;
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
    
    cout<<"resultado:"<<my_graph.find(destino)->second.distance<<endl;
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
    //https://www.youtube.com/watch?v=pkKErJOu3KQ&feature=youtu.be ~2:00:00
    //return vetor com menor numero de passagens entre origem e destino
}
/*
 * 
 */
int main(int argc, char** argv) {
    vector<int> centrais_exemplo={1,2,3,4,5,23,35,50};
    vector<pair<int,int> > adjacencias_exemplo={pair<int,int>(2,3),pair<int,int>(4,5),pair<int,int>(2,4),pair<int,int>(5,23),pair<int,int>(2,4)};
    
    primeiroExercicio(centrais_exemplo,adjacencias_exemplo,3,4);
    return 0;
}


