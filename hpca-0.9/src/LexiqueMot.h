#ifndef LEXIQUEMOT_H_INCLUDED
#define LEXIQUEMOT_H_INCLUDED
#include <string>
#include <unordered_map>
#include <iostream>
#include <vector>
using namespace std;

class LexiqueMot{

    private:
    unordered_map<string,int> mapMot;
    int derniereCle;    //pour créer des clés int différents par mot

    public:
    const unordered_map<string,int> getMapMot();
    const int getDerniereCle();

    void ajouter(string mot);   //ajoute un mot au lexique et incremente derniereCle
    int containsKey(string mot);    //retourne 1 si la map contient cette cle
    int containsValue(int id);  //retourne 1 si la map contient cette valeur
    string getKey(int id);  //retourne le string associé à la valeur int
    int getValue(string key);   //retourne le int associé à la clé string
    LexiqueMot();
};

#endif // LEXIQUEMOT_H_INCLUDED
