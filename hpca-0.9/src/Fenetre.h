#ifndef FENETRE_H_INCLUDED
#define FENETRE_H_INCLUDED
#include <iostream>
#include <string>
#include <unordered_map>
#include <vector>
#include "LexiqueMot.h"
#include "LexiqueContext.h"
#include "PseudoMatrice.h"
using namespace std;

class Fenetre{

private:
    int nbMotPrev; //Nombre de mot précédent la mot courant
    vector<string> fenetreString ; //Fenetre contenant les mots lus sous forme symbolique
    vector<int> fenetreInt ; //Fenetre contenant les mots lus sous forme numérique (cf LexiqueMot)
    int idMot;  //id du mot courant dans le lexique mot
    int nbMotSucc; //Nombre de mot suivant la mot courant
    int ngram; //méthode de ngram

    public:
    const int getTailleFenetre();
    const int getIdMot();
    const int getPlaceMot();
    const int getNbMotPrev();
    const int getNbMotSucc();
    const int getNgram();
    const vector<string> getFenetreString();
    const vector<int> getFenetreInt();
    void setFenetreString(vector<string> slitLine);

    Fenetre(int nbMotPrev,int nbMotSucc,int ngram);
    Fenetre();
    void addLexiqueMot(LexiqueMot& lexiqueMot);
    void convert(LexiqueMot& lMot,LexiqueContext& lContext,PseudoMatrice& element);
};




#endif // FENETRE_H_INCLUDED
