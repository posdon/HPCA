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

/* gprof valgrind */

using namespace std;

int main(int argc, char *argv[]){

    if(argc<2){
        cerr<<"Error syntaxe : -h for more information"<<endl;
        exit(EXIT_FAILURE);
    }

    if(argc<3){
        string valueFirst = argv[1];
        if(!valueFirst.compare("-h")){
            cerr<<endl<<endl<<
            "***************************Help menu***************************"<<endl<<endl<<
            "Minimum syntaxe : ./hpca <INPUT_DATA> <OUTPUT_VECTORS>"<<endl<<endl<<
            "Option : "<<endl<<
			"	-P [i]	: building context with the i previous words of the current word (default value : 1)"<<endl<<
            "	-N [j]	: building context with the next j words of the current word (default value : 1)"<<endl<<
            "	--ngram [n]	: contexts of n-grams (default value : 1)"<<endl<<
            "	-cutOff [s]	: doesn't count contexts with a probability of occurencies inferior at s (default value : 0)"<<endl<<
            "	-L [m]	: vectors have a dimension of 1*m for each word (default value : 100)"<<endl<<endl<<endl;
            exit(EXIT_FAILURE);
        }else{
            cerr<<"Error syntaxe : -h for more information"<<endl;
            exit(EXIT_FAILURE);
        }
    }

    if(argc>2){
        string textInput = argv[1];
        string textOutput = argv[2];

        Traitement mainApp = Traitement(textInput,textOutput);
        for(int i=3;i<argc;i++){
            string valueArg = argv[i];
            if(!valueArg.compare("--ngram")){
                i++;
                if(i<argc){
                    mainApp.setNgram(atoi(argv[i]));
                }else{
                    cerr<<"Error syntaxe : -h for more information"<<endl;
                    exit(EXIT_FAILURE);
                }
            }
            if(!valueArg.compare("-cutOff")){
                i++;
                if(i<argc){
                    mainApp.setSeuil(atof(argv[i]));
                }else{
                    cerr<<"Error syntaxe : -h for more information"<<endl;
                    exit(EXIT_FAILURE);
                }
            }
            if(!valueArg.compare("-P")){
                i++;
                if(i<argc){
                    mainApp.setNbMotPrev(atoi(argv[i]));
                }else{
                    cerr<<"Error syntaxe : -h for more information"<<endl;
                    exit(EXIT_FAILURE);
                }
            }
            if(!valueArg.compare("-N")){
                i++;
                if(i<argc){
                    mainApp.setNbMotSucc(atoi(argv[i]));
                }else{
                    cerr<<"Error syntaxe : -h for more information"<<endl;
                    exit(EXIT_FAILURE);
                }
            }
            if(!valueArg.compare("-L")){
                i++;
                if(i<argc){
                    mainApp.setEigenLength(atoi(argv[i]));
                }else{
                    cerr<<"Error syntaxe : -h for more information"<<endl;
                    exit(EXIT_FAILURE);
                }
            }
        }
        cerr<<"Welcome on Hellinger PCA Manager From CALL"<<endl<<endl<<"Converting : "+textInput+" To : "+textOutput<<endl<<"It can take some time, so you can make some coffee. Enjoy yourself !"<<endl<<endl;
        mainApp.mainFunction();
    }
}
