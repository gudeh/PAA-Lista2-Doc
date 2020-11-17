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
#include <algorithm>
#include <map>

using namespace std;

vector<vector<vector<int> > > n_matrices;


struct item{
    int id;
    int peso;
    int lucro;
};

int opt(vector<item> itens_restantes,vector<float> capacidade_atual){
    int total_cap=0; for(auto x:capacidade_atual) total_cap+=x;
//    cout<<"total cap:"<<total_cap<<", item list size:"<<itens_restantes.size();
//    for(int h=0;h<capacidade_atual.size();h++)
//        cout<<",truck:"<<h<<">"<<capacidade_atual[h]; cout<<endl;
    if(itens_restantes.size()==0 || total_cap<=0)
    {
//        if(itens_restantes.size()==0)
//            cout<<"ITEM LIST EMPTY";
//        else
//            cout<<"NO SIZE AVAILABLE";
//        cout<<"- RETURNING 0<<<<."<<endl;
        return 0;
    }
    else
    {
        item current=itens_restantes[0];
        vector<int> rets;
        //checando se o item a ser inserido cabe em algum caminhao.
        bool fit=false; int ret=0;
        for(int i=0;i<capacidade_atual.size();i++)
        {
            vector<item> item_aux; item_aux=itens_restantes;
            if(current.peso>capacidade_atual[i])
            {
                item_aux.erase(item_aux.begin());
                ret=opt(item_aux,capacidade_atual);
//                cout<<"OUT->current.peso:"<<current.peso<<"truck[i]:"<<capacidade_atual[i]<<endl;
//                cout<<"-----RET1:"<<ret<<endl<<endl;
//                return ret;
                
                n_matrices[i][capacidade_atual[i]][current.id]=ret;
            }
            //caso o item caiba no caminhao em index
            else
            {
                vector<float> cap_aux=capacidade_atual;
                cap_aux[i]=cap_aux[i]-current.peso;
                item_aux.erase(item_aux.begin());
                ret=max(current.lucro+opt(item_aux,cap_aux),
                        opt(item_aux,capacidade_atual));
//                cout<<"IN->current.peso:"<<current.peso<<",truck[i]:"<<capacidade_atual[i]<<endl;
//                cout<<"-----RET2:"<<ret<<endl<<endl;
//                return ret;
                
//                cout<<"i:"<<i<<",cap[i]:"<<capacidade_atual[i]<<",id:"<<current.id<<endl;
//                cout<<n_matrices.size()<<"|"<<n_matrices[i].size()<<"|"<<n_matrices[i][capacidade_atual[i]].size()<<endl;
                n_matrices[i][capacidade_atual[i]][current.id]=ret;
            }
            rets.push_back(ret);
        }
        ret=0;
        for(auto x:rets)
        {
            if(x>ret)
                ret=x;
        }
        return ret;
    }
}


//Retorno: os itens que não foram entregues (vector) e o lucro perdido (int).
pair<vector<int>,int> exercicioDois(vector<float> capacidade_caminhoes, vector< int> peso_itens, vector< int> lucro_itens)
{   
    int aux=0; float auxf=0;
    cout<<"Numero de caminhoes:"<<capacidade_caminhoes.size()<<endl<<"\tCapacidade total:";     for(auto x : capacidade_caminhoes)  auxf+=x;    cout<<auxf<<endl<<endl;
    cout<<"Numero de itens:"<<peso_itens.size()<<endl<<"\tPeso total:"; aux=0;  for(auto x : peso_itens)        aux+=x; cout<<aux<<endl;
    cout<<"\tLucro de todos itens:";   aux=0;  for(auto x : lucro_itens)        aux+=x; cout<<aux<<endl;
    
    //Inicializando matriz para memorizacao
    vector<int> aux1(peso_itens.size()+1,0);
    for(int x=0;x<capacidade_caminhoes.size();x++)
    {
        vector<vector<int> > aux2(capacidade_caminhoes[x]+1,aux1);
        n_matrices.push_back(aux2);
    }
    cout<<n_matrices.size()<<"|"<<n_matrices[0].size()<<"|"<<n_matrices[0][2].size()<<endl;
    vector<item> all_items;
    for(int x=0;x<peso_itens.size();x++)
    {
        item item_obj;
        item_obj.id=x;
        item_obj.peso=peso_itens[x];
        item_obj.lucro=lucro_itens[x];
        all_items.push_back(item_obj);
    }
    int ret=0;
    ret=opt(all_items,capacidade_caminhoes);
    cout<<">>RETORNO:"<<ret<<endl;
    for(auto x:n_matrices)
    {
        for(auto y:x)
        {
            for(auto z:y)
                cout<<z<<",";
            cout<<endl;
        }
        cout<<endl;
    }
}



int main(int argc, char** argv) {
    
//    vector<float> capacidades={3,5};
//    vector< int> pesos={5,7,10},lucros={5,7,10};
    
    vector<float> capacidades={90,100};
    vector< int> pesos={18, 9, 23, 20, 59, 61, 70, 75, 76, 30},
                lucros={78, 35, 89, 36, 94, 75, 74, 79, 80, 16};


    
    if(pesos.size() == lucros.size())
        exercicioDois(capacidades,pesos,lucros);
    else
        cout<<"INVALID INPUT!"<<endl;
    return 0;
}

