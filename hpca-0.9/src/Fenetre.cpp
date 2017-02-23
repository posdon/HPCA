#include "Fenetre.h"
using namespace std;

Fenetre::Fenetre(){
}

Fenetre::Fenetre(int nbMotPrev,int nbMotSucc,int ngram){
    this->nbMotPrev=nbMotPrev;
    this->nbMotSucc=nbMotSucc;
    this->ngram=ngram;
}

/* Getters and Setters */

void Fenetre::setFenetreString(vector<string> splitLine){
    this->fenetreString=splitLine;
}

const int Fenetre::getTailleFenetre(){
    return nbMotPrev+nbMotSucc+1;
}

const int Fenetre::getIdMot(){
    return idMot;
}

const int Fenetre::getPlaceMot(){
    return nbMotPrev;
}

const int Fenetre::getNbMotPrev(){
    return nbMotPrev;
}

const int Fenetre::getNgram(){
    return ngram;
}

const int Fenetre::getNbMotSucc(){
    return nbMotSucc;
}

const vector<string> Fenetre::getFenetreString(){
    return fenetreString;
}

const vector<int> Fenetre::getFenetreInt(){
    return fenetreInt;
}

/* Cores functions */
void Fenetre::addLexiqueMot(LexiqueMot& lexiqueMot){
    for(int i=0;i<fenetreString.size();i++){
        lexiqueMot.ajouter(fenetreString[i]);
        fenetreInt.push_back(lexiqueMot.getMapMot().at(fenetreString[i]));
    }
}

//Converti notre fenetreString en fenetreInt et enregistre les mots et context dans le lexique
void Fenetre::convert(LexiqueMot& lexiqueMot,LexiqueContext& lexiqueContext,PseudoMatrice& pseudoMatrix){
    /*Traitement des données*/

    /*Reset de la fenetreInt*/
    fenetreInt.clear();
    /*Ajout de chaque mot dans le lexique mot et convertion de la fenêtre*/
    addLexiqueMot(lexiqueMot);

    //¨Pour chaque mot de notre ligne
    for(int i=0;i<fenetreInt.size();i++){

        /*Sauvegarde de la valeur du mot courant*/
        idMot=fenetreInt[i];

        //Pour chaque mot "voisin"
        for(int j=-nbMotPrev;j<nbMotSucc;j++){
            if(i+j>=0&&i+j<fenetreInt.size()){

                vector<int> result;
                //Pour chaque n-gram
                for(int n=0;n<ngram;n++){
                    if(i+j+n<fenetreInt.size()&&n==0){
                        if(j!=0){
                            result.push_back(fenetreInt[i+j+n]);

                           /*Ajout du contexte dans le lexique*/
                            lexiqueContext.ajouter(result);

                            /*Ajout du couple dans la pseudo matrice*/
                            pseudoMatrix.ajouter(lexiqueContext.getKey(result),idMot);
                        }else{
                            result.push_back(lexiqueMot.getValue("__"));
                        }
                    }else{
                        if(i+j+n<fenetreInt.size()&&n!=0){
                            if(j+n==0){
                                result.push_back(lexiqueMot.getValue("__"));
                            }else{
                                result.push_back(fenetreInt[i+j+n]);
                            }
                            /*Ajout du contexte dans le lexique*/
                            lexiqueContext.ajouter(result);

                            /*Ajout du couple dans la pseudo matrice*/
                            pseudoMatrix.ajouter(lexiqueContext.getKey(result),idMot);
                        }
                    }
                }
            }
        }
    }
}

