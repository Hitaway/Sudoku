# Sudoku

Pour l'éxecution sur Windows et Linux je me suis servis du logiciel CodeBlocks que je vous invite à installer

#Pour l'éxecution sur Mac taper les commandes
g++ -o exe Sudoku_Mac_Linux.cpp <br/>
./exe

exemple de grille à saisir rapidement pour jouer: 
1ere grille: 005019008006570032008604507902007150000090000017400209409706800720081600800240700<br/>
2eme grille: 040300001109267300563000000200001609805603204406900007000000158001859403300002070<br/>

#Description du jeu:
 MENU:<br/>
			 1.Reinitialiser grille		=> initialise tout les cases de la grille à 0<br/>
			 2.Saisi precise			=> initialise une case en fonction de la ligne et colonne<br/>
			 3.Saisi rapide 			=> Saisir les 81 nombres de la grille à la suite, 0 correspond a une case vide<br/>
			 4.Resoudre le Sudoku 		=> Résoud le sudoku<br/>
			 5.Debloquer une case 		=> Débloque une case aléatoirement dans la grille<br/>
			 0.Stop 					=> Arrête le jeu<br/>