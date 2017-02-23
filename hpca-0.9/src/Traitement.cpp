#include "Traitement.h"

Traitement::Traitement(){
    this->inputText="test.txt";
    this->outputText="outPut.txt";
    this->eigenLength=100;                //Taille des vecteurs des mots
    this->nbMotPrev=1;                    //Nombre de mot précédent le mot suivant dans la fenêtre
    this->nbMotSucc=1;                    //Nombre de mot suivant le mot courant dans la fenêtre
    this->seuil=0;                        //Seuil de rejet pour les contextes pas assez observés
    this->ngram=1;                        //Nombre de gram lors de la lecture
}

Traitement::Traitement(const string& input, const string& output){
    this->inputText=input;
    this->outputText=output;
    this->eigenLength=100;                //Taille des vecteurs des mots
    this->nbMotPrev=1;                    //Nombre de mot précédent le mot suivant dans la fenêtre
    this->nbMotSucc=1;                    //Nombre de mot suivant le mot courant dans la fenêtre
    this->seuil=0;                        //Seuil de rejet pour les contextes pas assez observés
    this->ngram=1;                        //Nombre de gram lors de la lecture
}



/* Getters and Setters */

int Traitement::getNbMotPrev(){
    return nbMotPrev;
}

int Traitement::getNgram(){
    return ngram;
}

int Traitement::getNbMotSucc(){
    return nbMotSucc;
}

int Traitement::getEigenLength(){
    return eigenLength;
}

float Traitement::getSeuil(){
    return seuil;
}

void Traitement::setEigenLength(int egL){
    if(egL>0){
        this->eigenLength=egL;
    }else{
        cerr<<"Error 42 : value must be positive not null. Default value assigned : 100"<<endl;
    }
}

void Traitement::setSeuil(float s){
    if(s<=1&&s>=0){
        this->seuil=s;
    }else{
        cerr<<"Error 42 : value must be contained between 0 and 1. Default value assigned : 0"<<endl;
    }
}

void Traitement::setNgram(int ng){
    if(ng>0){
        this->ngram=ng;
    }else{
        cerr<<"Error 42 : value must be positive not null. Default value assigned : 1"<<endl;
    }
}

void Traitement::setNbMotPrev(int nbPrev){
    if(nbPrev>=0){
        this->nbMotPrev=nbPrev;
    }else{
        cerr<<"Error 42 : value must be positive. Default value assigned : 1"<<endl;
    }
}

void Traitement::setNbMotSucc(int nbSucc){
    if(nbSucc>=0){
        this->nbMotSucc=nbSucc;
    }else{
        cerr<<"Error 42 : value must be positive. Default value assigned : 1"<<endl;
    }
}

void Traitement::readTexte(LexiqueMot& lexiqueMotTest,LexiqueContext& lexiqueContextTest,PseudoMatrice& pseudoMatriceTest){
    Fenetre fenetreTest(nbMotPrev,getNbMotSucc(),getNgram());
    std::string line;                   //Ligne courante du fichier

    ifstream fichier(inputText, ios::in);  //ouverture du fichier en lecture
     if(!fichier){
        cerr << "Impossible d'ouvrir le fichier !" << endl;
        exit(EXIT_FAILURE);
    }

    /* Parcours et lecture du fichier */
    while(std::getline( fichier, line )){
        string word;
        vector<string> splitLine;
        istringstream iss (line);
        while(iss>>word){
            splitLine.push_back(word);
        }
        fenetreTest.setFenetreString(splitLine);
        fenetreTest.convert(lexiqueMotTest,lexiqueContextTest,pseudoMatriceTest);
    }
    /* Fermeture fichier */
    fichier.close();
}

void Traitement::testRead(LexiqueMot& lexiqueMotTest,LexiqueContext& lexiqueContextTest){
    for(int i=0;i<lexiqueMotTest.getDerniereCle();i++){
        cerr<< "Lexique Mot : Mot numero: " << i << " => " << lexiqueMotTest.getKey(i)<<endl;
    }
    cerr<< endl;

    for(int h=0;h<lexiqueContextTest.getDerniereCle();h++){
        cerr<< "Lexique Contexte : Contexte numero: " << h << " => ";
            for(int j=0;j<(int)lexiqueContextTest.getValue(h).size();j++){
                cerr<< " " << lexiqueMotTest.getKey(lexiqueContextTest.getValue(h).at(j));
            }
        cerr<<endl;
    }
   cerr<<endl;
}

int Traitement::parcoursSeuil(LexiqueContext& lexiqueContextTest){
    int nbRejetContext=0;
    for(unsigned int i=0;i<lexiqueContextTest.getTabOccContext().size();i++){
        double probaContext = lexiqueContextTest.getTabOccContext().at(i)/static_cast<float>(lexiqueContextTest.getNbOccContext());
        /*Si notre contexte n'a pas un poids suffisant parmis tous les contextes : écrase le nombre d'occurence de ce contexte à zéro et le qualifie de Rejet*/
        if(probaContext<seuil){
            lexiqueContextTest.setTabOccContextAt(-1,i);
            nbRejetContext++;
        }
    }
    return nbRejetContext;
}

void Traitement::writeTexte(LexiqueMot& lexiqueMotTest,LexiqueContext& lexiqueContextTest,const Eigen::MatrixXf& embedding) const{
    cerr<<"Debut d'écriture du texte"<<endl;
    ofstream fich(outputText, ios::out | ios::trunc);
        if(fich)
        {
            for(int li=0;li<embedding.rows();li++){
                fich<<lexiqueMotTest.getKey(li+1);
                for(int co=0;co<embedding.cols();co++){
                    fich<<" "<<embedding(li,co);
                }
                fich<<endl;
            }

            fich.close();
        }
        else{
            cerr << "Impossible d'ouvrir le fichier !" << endl;
        }
    cerr<<"Fin d'écriture du texte"<<endl;
}




void Traitement::remplissageMatrice(LexiqueContext& lexiqueContextTest, PseudoMatrice& pseudoMatriceTest, Eigen::MatrixXf& matrice){
    cerr<<"Debut du remplissage de la matrice"<<endl;
    int decalage=0;
    for(unsigned int i=0;i<lexiqueContextTest.getTabOccContext().size();i++){
        if(lexiqueContextTest.getTabOccContext()[i]<0){
                //Cas où le nombre d'occurences de ce contexte a été écrasé -> Contexte rejeté, on a un décalage qui augmente de un
            decalage++;
        }else{
            //Cas où le nombre le contexte est à insérer dans la matrice
            for(const auto& tab : pseudoMatriceTest.getMapValuePseudoMatrice(i)){
                matrice(tab.first,i-decalage)=sqrt(tab.second/static_cast<float>(lexiqueContextTest.getTabOccContext()[i]));
            }

        }
    }
    cerr<<"Fin du remplissage de la matrice"<<endl<<endl;
}

int Traitement::mainFunction(){
    /* Initialisation */
    Eigen::MatrixXf matrice(1,1);       //Matrice finale
    LexiqueMot lexiqueMotTest;          //Lexique affiliant chaque mot à un entier ID
    LexiqueContext lexiqueContextTest;  //Lexique affiliant chaque contexte (représenté comme un tableau d'entier ID de mots) à un entier ID
    PseudoMatrice pseudoMatriceTest;    //Map ayant pour clé l'entier ID d'un contexte et en valeur une map, ayant pour clé l'entier ID d'un mot et en valeur le nombre de fois que ce mot est le mot courant du contexte associé


    int nbMot;                          //Nombre total de mots (mise à jour après lecture)
    int nbContext;                      //Nombre total de contextes ((mise à jour après lecture)
    lexiqueMotTest.ajouter("__");       //Ajout du caractère __ signifiant l'empalcement du mot courant dans un contexte

    /* Ouverture du fichier */
    readTexte(lexiqueMotTest,lexiqueContextTest,pseudoMatriceTest);


    /* Test de lecture */
    //empty

    /*Mise à jour des valeurs*/
    nbMot = lexiqueMotTest.getDerniereCle();
    nbContext = lexiqueContextTest.getDerniereCle();

    /*Parcours de seuil*/
    int nbRejetContext = parcoursSeuil(lexiqueContextTest);

    /* Test résultat : vérification des tailles des fichiers test avec taille des lexiques et matrice */
    cerr<< "Nombre de mots dans lexique et matrice (mot 0 compté) : " << nbMot <<endl;
    cerr<< "Nombre de contextes dans lexique : " << nbContext <<endl;
    cerr<< "Nombre de contextes dans matrice : " << nbContext-nbRejetContext <<endl;
    cerr<< "Taille finale de la matrice : " << eigenLength <<endl;
    cerr<<endl;

    /*Mise à jour de la taille de notre matrice*/
    cerr<<"Debut du resize"<<endl;
    matrice.resize(nbMot,(nbContext-nbRejetContext));
    cerr<<"Fin du resize"<<endl<<endl;

    /*Remplissage matrice*/
    remplissageMatrice(lexiqueContextTest, pseudoMatriceTest,matrice);

    /* PCA */
    cerr<<"Debut de la PCA"<<endl;
    Eigen::MatrixXf cov = matrice.adjoint() * matrice;
    Eigen::SelfAdjointEigenSolver<Eigen::MatrixXf> eig(cov);
    cerr<<"Fin de la PCA"<<endl<<endl;


    /* Troncage des dernières colonnes pour obtenir une matrice de taille : nbMot*eigenLength */
    cerr<<"Debut du troncage"<<endl;
    Eigen::MatrixXf embedding = eig.eigenvectors().rightCols(eigenLength);
	cerr<<"Fin du troncage"<<endl<<endl;


    /* Ouverture et écriture du fichier final */
    writeTexte(lexiqueMotTest,lexiqueContextTest,embedding);

    return 0;
}
