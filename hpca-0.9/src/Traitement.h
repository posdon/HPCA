#ifndef TRAITEMENT_INCLUDED
#define TRAITEMENT_INCLUDED
#include "Fenetre.h"
#include "LexiqueContext.h"
#include "LexiqueMot.h"
#include "PseudoMatrice.h"
#include "Traitement.h"
#include <iostream>
#include <fstream>
#include <unordered_map>
#include <new>
#include "Eigen-3.2.8/Eigen/Dense"
#include <math.h>
#include <sstream>

typedef Eigen::MatrixXf Matrice;

using namespace std;

class Traitement{

private:

    int eigenLength;                  //Taille des vecteurs des mots
    int nbMotPrev;                    //Nombre de mot précédent le mot suivant dans la fenêtre
    int nbMotSucc;                    //Nombre de mot suivant le mot courant dans la fenêtre
    float seuil;                      //Seuil de rejet pour les contextes pas assez observés
    int ngram;                        //Nombre de gram lors de la lecture
    string inputText;
    string outputText;

    public:
    int getEigenLength();
    float getSeuil();
    int getNgram();
    int getNbMotPrev();
    int getNbMotSucc();

    void setEigenLength(int egL);
    void setSeuil(float s);
    void setNgram(int ng);
    void setNbMotPrev(int nbPrev);
    void setNbMotSucc(int nbSucc);

    void readTexte(LexiqueMot& lexiqueMotTest,LexiqueContext& lexiqueContextTest,PseudoMatrice& pseudoMatriceTest);
    void testRead(LexiqueMot& lexiqueMotTest,LexiqueContext& lexiqueContextTest);
    int parcoursSeuil(LexiqueContext& lexiqueContextTest);
    void writeTexte(LexiqueMot& lexiqueMotTest,LexiqueContext& lexiqueContextTest,const Matrice& embedding) const;
    void remplissageMatrice(LexiqueContext& lexiqueContextTest, PseudoMatrice& pseudoMatriceTest,Eigen::MatrixXf& matrice);
    int mainFunction();

    Traitement();
    Traitement(const string& input, const string& output);
};





#endif // TRAITEMENT_INCLUDED
