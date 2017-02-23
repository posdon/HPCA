#include "PseudoMatrice.h"
using namespace std;

PseudoMatrice::PseudoMatrice(){
}

/* Getters and Setters */

const unordered_map<int,unordered_map<int, int> > PseudoMatrice::getMapPseudoMatrice(){
    return mapPseudoMatrice;
}

const unordered_map<int,int> PseudoMatrice::getMapValuePseudoMatrice(int id){
    return mapPseudoMatrice.at(id);
}


/* Navigation Map */

//Rend 1 si context est clé de la grande map
bool PseudoMatrice::containsContext(int context) const{
    unordered_map< int ,unordered_map<int,int> >::const_iterator it = this->mapPseudoMatrice.find(context);
        return (it!=mapPseudoMatrice.end());
}

//Rend 1 si mot est clé de la petite map. La petite map étant la valeure de la clé context de la grosse map
bool PseudoMatrice::containsMot(int context,int mot) const{
    unordered_map<int,int>::const_iterator it = this->mapPseudoMatrice.at(context).find(mot);
        return (it!=mapPseudoMatrice.at(context).end());
}

//Incrémente la valeure de la clé mot dans la petite map. La petite map étant la valeur de la clé context dans la grosse map.
void PseudoMatrice::ajouter(int context,int mot){
    mapPseudoMatrice[context][mot]+=1;
}

