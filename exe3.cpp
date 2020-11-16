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

using namespace std;

/*
 * 
 */
struct item{
    int id;
    int peso;
    int lucro;
};

int opt(vector<item> itens_restantes, vector<float> capacidade_atual){
    cout<<"OPT CALL!"<<endl;
    //caso base
    
    int total_cap=0; for(auto x:capacidade_atual) total_cap+=x;
    if(itens_restantes.size()==0 || total_cap<=0)
    {
        cout<<"Returning 0."<<endl;
        return 0;
    }
    else
    {
        cout<<"else"<<endl;
        item current=itens_restantes[0];
        //checando se o item a ser inserido cabe em algum caminhao.
        bool fit=false; int index=0,ret=0;
        for(int i=0;i<capacidade_atual.size();i++)
        {
            if(current.peso<capacidade_atual[i])
            {
                index=i;
                fit=true;
                break;
            }
        }
        //caso o item nao caiba
        if(!fit)
        {
            itens_restantes.erase(itens_restantes.begin());
            ret=opt(itens_restantes,capacidade_atual);
            //TODO: guardar lucro perdido
        }
        //caso o item caiba no caminhao em index
        else
        {
            //TODO: peso negativo?
            vector<float> cap_aux=capacidade_atual;
            cap_aux[index]=cap_aux[index]-current.peso;
            itens_restantes.erase(itens_restantes.begin());
            ret=max(current.lucro+opt(itens_restantes,cap_aux),
                    opt(itens_restantes,capacidade_atual));
        }
        return ret;
    }
}

//Retorno: os itens que não foram entregues (vector) e o lucro perdido (int).
pair<vector<int>,int> exercicioDois(vector<float> capacidade_caminhoes, vector<unsigned int> peso_itens, vector<unsigned int> lucro_itens)
{   
    int aux=0; float auxf=0;
    cout<<"Numero de caminhoes:"<<capacidade_caminhoes.size()<<endl<<"\tCapacidade total:";     for(auto x : capacidade_caminhoes)  auxf+=x;    cout<<auxf<<endl<<endl;
    cout<<"Numero de itens:"<<peso_itens.size()<<endl<<"\tPeso total:"; aux=0;  for(auto x : peso_itens)        aux+=x; cout<<aux<<endl;
    cout<<"\tLucro de todos itens:";   aux=0;  for(auto x : lucro_itens)        aux+=x; cout<<aux<<endl;
    
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
    cout<<"RETORNO:"<<ret<<endl;
}



int main(int argc, char** argv) {
    
    vector<float> capacidades={10,15};
    vector<unsigned int> pesos={10,10,10,10,10},lucros={1,2,3,4,5};
    
    if(pesos.size() == lucros.size())
        exercicioDois(capacidades,pesos,lucros);
    else
        cout<<"INVALID INPUT!"<<endl;
    return 0;
}

