#include <stdlib.h>
#include <stdio.h>

#define NMAX 50000		/* peut etre modifie si necessaire */



/*
generation_aleatoire
Donnees : t : tableau d'entiers de taille > n, n : entier > 0
Resultat : les valeurs t[0..n-1] ont ete initialisees avec n valeurs aleatoires
           prises dans [0,2147483647] selon une loi uniforme.
Pre-condition : le generateur aleatoire doit avoir ete initialise avec "srand"
*/

void generation_aleatoire(int t[], int n) {
  int i ;

  for (i=0 ; i<n ; i++) {
	  t[i] = rand() ;
  } ;
}

/*
generation_aleatoire_non_uniforme
Donnees : t : tableau d'entiers de taille > n, n : entier > 0
Resultat : les valeurs t[0..n-1] ont ete initialisees avec n valeurs aleatoires
           prises dans [0,2147483647].
Pre-condition : le generateur aleatoire doit avoir ete initialise avec "srand"
*/
void generation_aleatoire_non_uniforme(int t[], int n) {
  int i;
  int x = 0;

  for (i=0; i < n; i++) {
    t[i] = x;
    x = x + ((rand() % 10) - 2);
  }
}

/*
tri_insertion
Donnees : t : tableau d'entiers de taille > n, n : entier > 0
Resultat : le tableau t est trie en ordre croissant
*/
void tri_insertion(int t[], int n) {
  int i,j,f=0; // f : compteur de comparaisons :)
  int Clef;

  for(i=1; i < n; i++) {
    
    Clef = t[i];
    
    j = i - 1;
    
    /* Decalage des valeurs du tableau */
    while((j >= 0) && (t[j] > Clef)) {
      t[j+1] = t[j];
      j = j - 1;
      f++; // Compteur de comparaisons :D
      printf("f = %d\n", f); // Affichage du nombre de comparaisons :v
    }
    /* insertion de la clef */
    t[j+1] = Clef;
  }
}

/*
tri_segmentation
Donnees : t : tableau d'entiers de taille > n, n : entier > 0
Resultat : le tableau t est trie en ordre croissant
*/
void tri_segmentation(int t[], int n) {
  /* A completer */
}



void lancer_mesures() {

  unsigned int germe ;
  int T[NMAX];
  int N;

  printf("Valeur du germe pour la fonction de tirage aleatoire ? ") ;
  scanf("%d", &germe) ;
  srand(germe) ;

  do {
  	printf("Valeur de N ? ") ;
  	scanf("%d", &N) ;
  } while (N<1 || N > NMAX) ;

  generation_aleatoire(T, N) ; /* initialisation du tableau T */
  tri_insertion(T, N) ;	/* tri de T */
}
