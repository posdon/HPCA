#ifndef LEXIQUECONTEXT_H_INCLUDED
#define LEXIQUECONTEXT_H_INCLUDED
#include <string>
#include <iostream>
#include <vector>
#include <unordered_map>
using namespace std;

class LexiqueContext{

private:
    unordered_map<int, vector<int> >  mapContext;
    int derniereCle;
    vector<int> tabOccContext;
    int nbOccContext;

public:
    const unordered_map<int, vector<int> >& getMapContext();
    int getDerniereCle() const;
    const vector<int>& getTabOccContext() const;
    int getNbOccContext() const;
    void setTabOccContextAt(int value, int atNumber);

    void ajouter(const vector<int>& context);   //ajoute un context au lexique et incremente derniereCle
    bool containsValue(const vector<int>& context) const;    //retourne 1 si la map contient ce context
    bool containsKey(int id) const;  //retourne 1 si la map contient cette valeur
    const vector<int>& getValue(int id) const;  //retourne le context associé à la valeur int
    int getKey(const vector<int>& context) const;   //retourne le int associé à la clé context
    LexiqueContext();
};

#endif // LEXIQUECONTEXT_H_INCLUDED
