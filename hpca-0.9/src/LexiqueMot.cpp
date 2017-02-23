#include "LexiqueMot.h"
using namespace std;

LexiqueMot::LexiqueMot(){
    this->derniereCle=0;
}

/* Getters and Setters */

const unordered_map<string, int> LexiqueMot::getMapMot(){
    return mapMot;
}

const int LexiqueMot::getDerniereCle(){
    return derniereCle;
}


/* Navigation Map */

//Ajoute mot dans la map
void LexiqueMot::ajouter(string mot){
    if(!containsKey(mot)){
        mapMot[mot]=derniereCle;
        derniereCle++;
    }
}

//Retourne 1 si mot est clé dans la map
int LexiqueMot::containsKey(string mot){
    unordered_map<string,int>::const_iterator it = this->mapMot.find(mot);
        return (it!=mapMot.end());
}

//Retourne 1 si id est valeur dans la map
int LexiqueMot::containsValue(int id){
    for ( auto it = mapMot.begin(); it != mapMot.end(); ++it ){
        if(it->second==id){
            return 1;
        }
    }
    return 0;
}
//Rend la clé de la valeur id de la map
string LexiqueMot::getKey(int id){
    for ( auto it = mapMot.begin(); it != mapMot.end(); ++it ){
        if(it->second==id){
            return it->first;
        }
    }
    cerr << "id mot non attribue" << endl;
    return "";
}

//Rend la valeur de la clé key de la map
int LexiqueMot::getValue(string key){
    return mapMot.at(key);
}
