/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   exe3.cpp
 * Author: gudeh
 *
 * Created on November 15, 2020, 4:53 PM
 */

#include <cstdlib>
#include <vector>
#include <iostream>

using namespace std;

/*
 * 
 */
struct item{
    int id;
    int peso;
    int lucro;
};

int opt(item to_load, vector<item> itens_restantes){
    
}

//Retorno: os itens que não foram entregues (vector) e o lucro perdido (int).
pair<vector<int>,int> exercicioDois(vector<float> capacidade_caminhoes, vector<unsigned int> peso_itens, vector<unsigned int> lucro_itens)
{   
    int aux=0; float auxf=0;
    cout<<"Numero de caminhoes:"<<capacidade_caminhoes.size()<<endl<<"\tCapacidade total:";     for(auto x : capacidade_caminhoes)  auxf+=x;    cout<<auxf<<endl<<endl;
    cout<<"Numero de itens:"<<peso_itens.size()<<endl<<"\tPeso total:"; aux=0;  for(auto x : peso_itens)        aux+=x; cout<<aux<<endl;
    cout<<"\tLucro de todos itens:";   aux=0;  for(auto x : lucro_itens)        aux+=x; cout<<aux<<endl;
    
    vector<item> all_itens;
    for(int x=0;x<peso_itens.size();x++)
    {
        item item_obj;
        item_obj.id=x;
        item_obj.peso=peso_itens[x];
        item_obj.lucro=lucro_itens[x];
        all_itens.push_back(item_obj);
    }
        
    
    
    
    
    
//    opt();
}
int main(int argc, char** argv) {
    
    vector<float> capacidades={11,14};
    vector<unsigned int> pesos={3,3,4,4,5,7},lucros={1,2,3,4,5,10};
    
    if(pesos.size() == lucros.size())
        exercicioDois(capacidades,pesos,lucros);
    else
        cout<<"INVALID INPUT!"<<endl;
    return 0;
}

