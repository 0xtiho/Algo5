#include <stdlib.h>
#include <stdio.h>
#include <time.h>

#define NMAX 500000		/* peut etre modifie si necessaire */
#define XMAX 500000		/* peut etre modifie si necessaire */



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

/*resultats_
tri_insertion
Donnees : t : tableau d'entiers de taille > n, n : entier > 0
Resultat : le tableau t est trie en ordre croissant
*/
int tri_insertion(int t[], int n) {
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
      // printf("f = %d\n", f); // Affichage du nombre de comparaisons :v
    }
    /* insertion de la clef */
    t[j+1] = Clef;
  }
  return f; // Retourner le nombre de comparaisons :v
}

/*
tri_segmentation
Donnees : t : tableau d'entiers de taille > n, n : entieris > 0
Resultat : le tableau t est trie en ordre croissant
*/
void swap(int *a, int *b) {
    int temp = *a;
    *a = *b;
    *b = temp;
}
int partitionner(int t[], int min, int max, int *compteur) {
    int pivot = t[(min + max) / 2]; // choisir le pivot au milieu
    int i = min;
    int j = max;

    while (i <= j) {
        while (t[i] < pivot) {
            i++;
            (*compteur)++; // incrémenter le compteur de comparaison
        }
        while (t[j] > pivot) {
            j--;
            (*compteur)++; // incrémenter le compteur de comparaison
        }

        if (i <= j) {
            swap(&t[i], &t[j]); // echanger les éléments
            i++;
            j--;
        }
    }
    return i; // retourner la position du pivot
}

/*
tri_rapide
Donnees : t : tableau d'entiers, low : indice de début, high : indice de fin
Resultat : trie le tableau t en utilisant l'algorithme du tri rapide
*/
void tri_rapide(int t[], int min, int max, int *compteur) {
    if (min < max) {
        int pivote_i = partitionner(t, min, max, compteur); // partitionner le tableau
        tri_rapide(t, min, pivote_i - 1, compteur);  // tri de la partie gauche
        tri_rapide(t, pivote_i, max, compteur);  // tri de la partie droite
    }
}


int tri_segmentation(int t[], int n) {
    int compteur;
    tri_rapide(t, 0, n - 1,&compteur); // Appel au tri rapide
    return compteur; // Retourner le nombre de comparaisons :v
}

void executer_tri(int choix_generation, int choix_tri, int T[], int N[], int Nb_N, int X, char *nom_fichier) {
    FILE *fichier = fopen(nom_fichier, "w");
    if (fichier == NULL) {
        printf("Erreur d'ouverture du fichier %s.\n", nom_fichier);
        return;
    }

    float Fmoy; // Nombre moyen de comparaisons

    for (int i = 0; i < Nb_N; i++) {
        Fmoy = 0;
        clock_t debut = clock(); // Début du chronomètre

        for (int j = 0; j < X; j++) {
            // Génération des valeurs selon le choix de l'utilisateur
            if (choix_generation == 1) {
                generation_aleatoire(T, N[i]);
            } else {
                generation_aleatoire_non_uniforme(T, N[i]);
            }

            // Tri selon le choix de l'utilisateur
            if (choix_tri == 1) {
                Fmoy += tri_insertion(T, N[i]);
            } else {
                Fmoy += tri_segmentation(T, N[i]);
            }
        }

        clock_t fin = clock();
        double chrono = (double)(fin - debut) / CLOCKS_PER_SEC;

        // affichage et écriture dans le fichier
        printf("N = %d, Comparaisons = %f, Temps = %f secondes\n", N[i], Fmoy / X, chrono);
        fprintf(fichier, "%d %f\n", N[i], Fmoy / X);
    }

    fclose(fichier);
}

void lancer_mesures() {

  unsigned int germe ;
  int T[NMAX];
  int N[] = {100, 1000, 5000, 10000, 25000, 50000, 70000, 100000}; // valeurs de N à tester :)
  int Nb_N = 8; // nombre de valeurs de N à tester :)
  int X; // nombre de fois à exécuter le tri :v
  int choix_tri, choix_gen, mode_comp; // choix de l'utilisateur :v
  float Fmoy; // nombre de comparaisons :v
  germe = 3; // valeur (pour que ca soit plus rapide pour moi) du germe :v
  srand(germe) ;
    // choix du type de génération aléatoire
   printf("Veuillez entrer combien de fois vous voulez exécuter le tri : ");
    do {
        scanf("%d", &X);
    } while (X < 1 || X > XMAX);
    
    printf("Choisissez le mode :\n1 - Choix manuel (génération et tri)\n2 - Mode comparaison (toutes les combinaisons)\n");
    scanf("%d", &mode_comp);
    
    if (mode_comp == 1) {
        // choix manuel
        printf("Choisissez le type de génération :\n1 - Génération aléatoire\n2 - Génération non uniforme\n");
        scanf("%d", &choix_gen);
        
        printf("Choisissez le type de tri :\n1 - Tri par insertion\n2 - Tri par segmentation\n");
        scanf("%d", &choix_tri);
        FILE *fichier = fopen("resultat_choix.txt", "w");
        if (fichier == NULL) {
            printf("Erreur d'ouverture du fichier.\n");
            return;
        }

        for (int i = 0; i < Nb_N; i++) {
            Fmoy = 0;
            clock_t debut = clock();

            for (int j = 0; j < X; j++) {
                if (choix_gen == 1) {
                    generation_aleatoire(T, N[i]);
                } else {
                    generation_aleatoire_non_uniforme(T, N[i]);
                }

                if (choix_tri == 1) {
                    Fmoy += tri_insertion(T, N[i]);
                } else {
                    Fmoy += tri_segmentation(T, N[i]);
                }
            }
            
            clock_t fin = clock();
            double chrono = (double)(fin - debut) / CLOCKS_PER_SEC;
            printf("temps d'execution = %f\n", chrono);
            printf("nombre de comparaisons = %f\n", Fmoy);
            fprintf(fichier, "%d %f\n", N[i], Fmoy / X);
        }
        fclose(fichier);
    } else {
        const char* noms_fichiers[4] = {
            "insertion_aleatoire.txt",
            "insertion_non_uniforme.txt",
            "segmentation_aleatoire.txt",
            "segmentation_non_uniforme.txt"
        };

        for (int combi = 0; combi < 4; combi++) {
            FILE *fichier = fopen(noms_fichiers[combi], "w");
            if (fichier == NULL) {
                printf("Erreur d'ouverture du fichier %s.\n", noms_fichiers[combi]);
                continue;
            }

            for (int i = 0; i < Nb_N; i++) {
                Fmoy = 0;
                clock_t debut = clock();

                for (int j = 0; j < X; j++) {
                    if (combi % 2 == 0) {
                        generation_aleatoire(T, N[i]);
                    } else {
                        generation_aleatoire_non_uniforme(T, N[i]);
                    }
                    if (combi / 2 == 0) {
                        Fmoy += tri_insertion(T, N[i]);
                    } else {
                        Fmoy += tri_segmentation(T, N[i]);
                    }
                }

                clock_t fin = clock();
                double chrono = (double)(fin - debut) / CLOCKS_PER_SEC;
                printf("Combi %d - temps d'execution = %f\n", combi, chrono);
                fprintf(fichier, "%d %f\n", N[i], Fmoy / X);
            }
            fclose(fichier);
        }
    }
}
