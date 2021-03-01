make # Compilamos
rm medidas.csv # Limpiamos el fichero de resultados
lista_c="4 8 20 40"
lista_l="384 1152 4096 12288 49152 73728 196608 393216"
#lista_c="4 8"
#lista_f="20 40"
for c in $lista_c;
do
    for l in $lista_l;
    do
        f=$(bc <<< "scale=2; (64/(8*$c))*$l")
        f=$(echo "$f" | awk '{printf("%.0f\n", $1)}')
        for id_prueba in {1..100};
        do
            echo "Ejecutando prueba con C=$c L=$l F=$f"
            eval "./codigo.out $c $f $id_prueba"
        done
    done
done