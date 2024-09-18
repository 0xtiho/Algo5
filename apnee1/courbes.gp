# Script Gnuplot pour tracer les résultats du tri par insertion avec génération aléatoire
set title "Tri Segmentation"
set xlabel "Taille du tableau (N)"
set ylabel "Nombre moyen de comparaisons"
set grid

# Type de sortie (PNG par exemple)
set terminal pngcairo size 1024,768 enhanced font 'Arial,10'
set output 'courbe_Segmen1.png'

# Tracer la courbe à partir du fichier
plot "segmentation_non_uniforme.txt" using 1:2 with linespoints title "Insertion"

# Fermer le fichier de sortie
set output
