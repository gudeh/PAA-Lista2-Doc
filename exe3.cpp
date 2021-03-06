/*
 * Este código resolve o terceiro problema da Lista 2 da disciplina de Projeto
 * e Analise de Algoritmos.
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
#include <set>

using namespace std;

//Estrutura utilizada para armazenar de maneira intuitivamente as 
//informações de cada item.
struct item{
    int id;
    int peso;
    int lucro;
};

//A função recursiva OPT foi adaptada para o problema em questão.
//Seu retorno é um par com um inteiro informando o lucro obtido até o momento e 
//um vetor com os itens que compõem este lucro.
//As entradas da função se da por dois vetores: um para os itens e outro para os 
//caminhões que ainda não foram processados.
pair<int,vector<item> > opt(vector<item> itens_restantes,vector<float> capacidade_atual){
    int total_cap=0; for(auto x:capacidade_atual) total_cap+=x;
    vector<item> selected;
//Caso base: se não há mais itens a serem analisados, ou os caminhoes nao possuem
//mais espaço, retorna lucro 0 e uma lista vazia de itens.
    if(itens_restantes.size()==0 || total_cap<=0)
        return pair<int,vector<item> >(0,selected);
//Se não for o caso, se processa o primeiro item do vetor de entrada.
    else
    {
        item current=itens_restantes[0];
        //vetor auxiliar para armazenar e comparar os lucros que serão obtidos.
        vector<pair<int,vector<item> > >  rets;
        int ret=0;
        //Se insere o primeiro item em cada caminhão.
        for(int i=0;i<capacidade_atual.size();i++)
        {
            vector<item> item_aux; item_aux=itens_restantes;
            pair<int,vector<item> > solut,solut2;
            selected.clear();
            //Caso o caminhao i nao tenha capacidade, é feito uma chamada recursiva
            //desconsiderando o item atual
            if(current.peso>capacidade_atual[i])
            {
                item_aux.erase(item_aux.begin());
                solut=opt(item_aux,capacidade_atual);
                ret=get<0>(solut);
                selected=get<1>(solut);
            }
            //Caso haja espaço no caminhao i, o valor máximo de retorno entre uma
            //chamada considerando o item sendo carregado e outra sem o item.
            else
            {
                vector<float> cap_aux=capacidade_atual;
                cap_aux[i]=cap_aux[i]-current.peso;
                 item_aux.erase(item_aux.begin());
                 solut=opt(item_aux,cap_aux);
                 solut2=opt(item_aux,capacidade_atual);
                 int aux1=current.lucro+get<0>(solut), 
                         aux2=get<0>(solut2);
                 ret=max(aux1,aux2);
                if(aux1>=aux2)
                {
                    selected=get<1>(solut);
                    selected.push_back(current);
                }
                else                   
                    selected=get<1>(solut2);
            }
            rets.push_back(pair<int,vector<item> > (ret,selected));
        }
        ret=0;  selected.clear();
        //Escolhendo o caminhao que apresentou o melhor lucro para retorno.
        for(auto x:rets)
        {
            if(get<0>(x)>ret)
            {
                ret=get<0>(x);
                selected=get<1>(x);
            }
        }
        return pair<int,vector<item> >(ret,selected);
    }
}


void exercicioDois(vector<float> capacidade_caminhoes, vector< int> peso_itens, vector< int> lucro_itens)
{   
    int todo_lucro=0,todo_peso=0; float auxf=0;
    cout<<"Numero de caminhoes:"<<capacidade_caminhoes.size()<<endl<<"\tCapacidade total:";     for(auto x : capacidade_caminhoes)  auxf+=x;    cout<<auxf<<endl<<endl;
    cout<<"Numero de itens:"<<peso_itens.size()<<endl<<"\tPeso total:"; todo_peso=0;  for(auto x : peso_itens)        todo_peso+=x; cout<<todo_peso<<endl;
    cout<<"\tLucro de todos itens:";   todo_lucro=0;  for(auto x : lucro_itens)        todo_lucro+=x; cout<<todo_lucro<<endl;
    
    vector<item> all_items;
    //Montando structures a partir dos dados de entrada.
    for(int x=0;x<peso_itens.size();x++)
    {
        item item_obj;
        item_obj.id=x;
        item_obj.peso=peso_itens[x];
        item_obj.lucro=lucro_itens[x];
        all_items.push_back(item_obj);
    }
    int ret=0; pair<int,vector<item> > solution;
    solution=opt(all_items,capacidade_caminhoes);
    ret=get<0>(solution);
    cout<<endl<<"ITENS SELECIONADOS PARA ENTREGA:"<<endl;
    cout<<"  ids:";for(int u=0;u<get<1>(solution).size();u++)
        cout<<get<1>(solution)[u].id<<","; cout<<endl;
    cout<<"pesos:";for(int u=0;u<get<1>(solution).size();u++)
        cout<<get<1>(solution)[u].peso<<","; cout<<endl;
    cout<<"lucro:";for(int u=0;u<get<1>(solution).size();u++)
        cout<<get<1>(solution)[u].lucro<<","; cout<<endl;
    cout<<"Lucro otimo:"<<ret<<endl<<endl;    
    vector<item> remain=get<1>(solution);
    cout<<"ITENS QUE FICARAM DE FORA DA ENTREGA:"<<endl;
    for(int x=0;x<remain.size();x++)
    {
        for(int y=0;y<all_items.size();y++)
        {
            if(all_items[y].id==remain[x].id)
            {
                all_items.erase(all_items.begin()+y);
                break;
            }
        }
    }
    cout<<"  ids:";for(auto x:all_items)
        cout<<x.id<<","; cout<<endl;
    cout<<"pesos:";for(auto x:all_items)
        cout<<x.peso<<","; cout<<endl;
    cout<<"lucro:";for(auto x:all_items)
        cout<<x.lucro<<","; cout<<endl;
        cout<<"Lucro perdido:"<<todo_lucro-get<0>(solution)<<endl;
}


int main(int argc, char** argv) {
//    vector<float> capacidades={10,20};
//    vector< int> pesos={5,7,10,20,10},lucros={5,7,10,20,10};
    
    //Definindo valores de entrada para o problema.
    vector<float> capacidades={90,100};
    vector< int> pesos={ 59, 61, 70, 75, 76, 30, 18,9, 23, 20},
                lucros={ 94, 75, 74, 79, 80, 16, 78,35, 89, 36};
  
    //Chamada da função recursiva que resolve o problema.
    if(pesos.size() == lucros.size())
        exercicioDois(capacidades,pesos,lucros);
    else
        cout<<"INVALID INPUT!"<<endl;
    return 0;
}

