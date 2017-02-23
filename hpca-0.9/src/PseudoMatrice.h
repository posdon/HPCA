#ifndef PSEUDOMATRICE_H_INCLUDED
#define PSEUDOMATRICE_H_INCLUDED
#include <string>
#include <iostream>
#include <unordered_map>
#include <new>
#include "LexiqueMot.h"
#include "LexiqueContext.h"
#include <vector>
using namespace std;

class PseudoMatrice{

    private:
    unordered_map< int ,unordered_map<int,int> > mapPseudoMatrice; //hashmap(context , hashmap(mot,itération) )

    public:
    const unordered_map<int,unordered_map<int, int> > getMapPseudoMatrice();
    const unordered_map<int,int> getMapValuePseudoMatrice(int id);
    void ajouter(int mot,int context);
    bool containsContext(int context) const;
    bool containsMot(int context,int mot) const;
    PseudoMatrice();

    protected:
};

#endif // PSEUDOMATRICE_H_INCLUDED
