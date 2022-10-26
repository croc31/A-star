#include <iostream>
#include <string>
#include <vector>
#include <algorithm>
#include <list>
#include <vector>
using namespace std;
 
/**
 * Auto-generated code below aims at helping you parse
 * the standard input according to the problem statement.
 **/
typedef struct Aresta Aresta;
typedef struct Node {
    int value;
    int heuristic;//h()
    int min_cost = 0;//g()
    bool fechado = false;
    list<Aresta*> *adj_list;
} Node;

struct Aresta {
    int value;
    Node* inicio;
    Node* fim;
};
vector<Node*> controle;
vector<Node*> saida;

bool ComparaNode (const Node* first, const Node* second)
{
    if((first->min_cost + first->heuristic) != (second->min_cost + second->heuristic)){
        return (first->min_cost + first->heuristic) < (second->min_cost + second->heuristic);
    }else{
        return ( first->value < second->value );
    }
}
void AEstrela(int start, int end){
    list<Node*> abertos;
    list<Node*> fechados;
    bool caminhoEncontrado = false;
    abertos.push_back(controle[start]);
    //inicio da arvore
    // caminhoFinal.nodeAtual = controle[start];
    // Arvore nodeArvoreAtual;
    while(!caminhoEncontrado){
        Node* nodeAtual = abertos.front();
        abertos.pop_front();
        //fechando o node
        nodeAtual->fechado = true;
        list<Aresta*> *adj_listAtual = nodeAtual->adj_list;
        //percorrendo as arestas de nodeAtual
        for (list<Aresta*>::iterator i = adj_listAtual->begin(); 
        i != adj_listAtual->end(); i++) 
        {
            // acrescentando o nó na lista aberta e calculando o custo f minimo
            if(((*i)->fim != nodeAtual && !(*i)->fim->fechado) ){
                abertos.push_back((*i)->fim);
                if((*i)->fim->min_cost == 0 || (*i)->value + (*i)->inicio->min_cost < (*i)->fim->min_cost){
                (*i)->fim->min_cost = (*i)->value + (*i)->inicio->min_cost;

                }
                // cerr << (*i)->fim->min_cost << " = " << (*i)->value
                //     << " + " << (*i)->inicio->min_cost << "\n" << endl;
            }else if(((*i)->inicio != nodeAtual && !(*i)->inicio->fechado)){
                abertos.push_back((*i)->inicio);
                (*i)->inicio->min_cost = (*i)->value + (*i)->fim->min_cost;
                // cerr << (*i)->inicio->min_cost << " = " << (*i)->value
                //     << " + " << (*i)->fim->min_cost << "\n" << endl;
            }
        }
        //ordenando os nós
        abertos.sort(ComparaNode);
        abertos.unique();
        //teste de fim de ciclo
        if(nodeAtual == controle[end]){
            caminhoEncontrado = true;
        }
        //SAIDA
        cout << nodeAtual->value << " " << 
        (nodeAtual->min_cost + nodeAtual->heuristic) << endl;
    }
}

int main()
{
    int n; // the total number of nodes in the level, including the gateways
    int e; //the number of links
    int s; //start node
    int g; //end node
    cin >> n >> e >> s >> g; cin.ignore();
    //cerr << n << " " << e << " " << s << " " << g << endl; 
    //    cerr << "primeira entrada"<< endl;
    for (int i = 0; i < n; i++) {
        int heuristic;
        cin >> heuristic; cin.ignore();
       // cerr << i << " " << heuristic << endl;
        Node* nodeAux = (Node*)malloc(sizeof(Node));
        nodeAux->value = i;
        nodeAux->heuristic = heuristic;
        nodeAux->min_cost = 0;
        nodeAux->adj_list = new list<Aresta*>[e];
        //cout << nodeAux->adj_list.size() << endl;
        controle.push_back(nodeAux);
    }
   
    //cerr << "tamanho do vetor " <<vetor.size() << endl;
    for (int i = 0; i < e; i++) {
        int x; // x and y defines a link between these nodes
        int y;
        int c; // c is the heuristic cost to g
        cin >> x >> y >> c; cin.ignore();
        //cerr<< x << " " << y << " " << c << endl;
        Aresta *arestaAux = (Aresta*)malloc(sizeof(Aresta));
        arestaAux->value = c;
        arestaAux->fim = controle[x];
        arestaAux->inicio = controle[y];
        controle[x]->adj_list->push_back(arestaAux);
        controle[y]->adj_list->push_back(arestaAux);
        
    }
    // cerr << "criou as arestas"<< endl;
   AEstrela(s, g);
 
    //cout << "0 33" << endl;
}

