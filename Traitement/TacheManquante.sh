#/usr/bash


echo "Début du processus de détection de tâches manquantes et suppression de bruit (étape 2)"

#demande les informations pour executer le programme de transformation
echo "fichier de symbols prendre pour l'affichage (format .syms) ?"
echo "Attention : votre fichier de symbol doit nécessairement avoir eps 0 en première ligne et R 1 en seconde ligne"
read noml

echo "fichier de traces (.txt) ? "
read trace

#compile le programme cpp de detection : remplacer les chemin pour mettre ceux où se trouve la librairie openFst
g++ -std=c++11 -I ../../../EvaluationMaquetteMdT/VerifMaquettesMdTCogtool/testCpp/openfst-1.5.0/src/include TacheManquante.cpp -L ../../../EvaluationMaquetteMdT/VerifMaquettesMdTCogtool/testCpp/openfst-1.5.0/src/lib -lfst -o myapp

#revenir ici

./myapp $noml $trace

#Supprime tous les epsilon de la trace
fstcompile --isymbols=$noml ----acceptor Propre.txt | fstarcsort > Propre.fst
fstrmepsilon Propre.fst Scenario.fst

fstprint --isymbols=$noml --osymbols=$noml Scenario.fst
	
echo "Fin du processus de detection"
echo "Les traces qui n'ont pas été trouvé dans le modèle de tâches et que vous avez choisi de garder sont des oublis dans le modèle de tâches, il faut modifier le modèle de tâches et recommencer la procédure"
