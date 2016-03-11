#include <fst/fstlib.h>
#include <fstream>

using namespace fst;

//haut, bas, jeton
int main(int argc, char *argv[]){	

	//affectation de la SymbolTable passee en parametre
	string nomFichier= argv[1];
	string nomFichierTrace= argv[2];
	string nomFichierTracePropre = "Propre.txt";
	bool pasEcoute;
		
	SymbolTable *syms = SymbolTable::ReadText(nomFichier);
	
	ifstream lesTraces(nomFichierTrace);
	ofstream lesTracesPropres(nomFichierTracePropre);
	
	if(lesTraces){
		string mot;
		int i =1;
		while(!lesTraces.eof()){
			lesTraces >> mot;
			
			if(i % 3 ==0){
			
				int64 key = syms->Find(mot);
			
				if (key ==-1){
					cout << "le label " << mot << " n'est pas trouvé dans le modèle de tâches " << endl;
					cout << "Voulez vous que cette trace ne soit pas écoutée ? (oui=1/non=0)";
					cin >> pasEcoute;
					cout << pasEcoute <<endl;
					if(pasEcoute){
						lesTracesPropres << "eps" <<" " << endl;
					}
					else{
						cout << "Voyez le modèle de tâches, il doit lui manquer une tâche" << endl;
						lesTracesPropres << mot <<" " << endl;
					}
				}
				else {
					lesTracesPropres << mot <<" " << endl;
					
				}
			}
			else{
				lesTracesPropres << mot <<" ";
			}
			i++;
		}
		
	}
	else{
		cout << "ERREUR: Impossible d'ouvrir le fichier." << endl;
	}
	
	//lesTracesPropres.fluch();
	lesTracesPropres.close();
	return 0;
}