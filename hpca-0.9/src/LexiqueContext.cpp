#include "LexiqueContext.h"
#include <string>
#include <unordered_map>
#include <iostream>
#include <vector>
using namespace std;

LexiqueContext::LexiqueContext(): derniereCle(0), nbOccContext(0){

}

/* Getters and Setters */

const unordered_map<int, vector<int> >& LexiqueContext::getMapContext(){
    return mapContext;
}

int LexiqueContext::getDerniereCle() const{
    return derniereCle;
}

const vector<int>& LexiqueContext::getTabOccContext() const{
    return tabOccContext;
}

 int LexiqueContext::getNbOccContext() const{
    return nbOccContext;
}

void LexiqueContext::setTabOccContextAt(int value, int atNumber){
    tabOccContext[atNumber]=value;
}

/* Navigation Map */

//Ajoute context à la map
void LexiqueContext::ajouter(const vector<int>& context){
    
	if(!containsValue(context)){
        tabOccContext.push_back(1);
        mapContext[derniereCle]=context;
        derniereCle++;
    }
    else{
        tabOccContext[getKey(context)]++;
    }
    nbOccContext++;
}

//Rend 1 si context est valeure de la map
bool LexiqueContext::containsValue(const vector<int>& context) const{
    for (const auto& it : mapContext ){
        if(it.second==context){
            return true;
        }
    }
    return false;
}

//Rend 1 si id est clé de la map
bool LexiqueContext::containsKey(int id) const{
    unordered_map<int,vector<int>>::const_iterator it = this->mapContext.find(id);
    return (it!=mapContext.end());
}

//Rend la clé de la valeur context de la map
int LexiqueContext::getKey(const vector<int>& context)const{
    for ( auto it = mapContext.begin(); it != mapContext.end(); ++it ){
        if(it->second==context){
            return it->first;
        }
    }
    cerr << "id context non attribue" << endl;
}

//Rend la valeur de la clé key dans la map
const vector<int>& LexiqueContext::getValue(int key)const{
    return mapContext.at(key);
}
