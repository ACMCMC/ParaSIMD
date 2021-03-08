#!/bin/bash
make # Compilamos
rm medidas.csv # Limpiamos el fichero de resultados
touch medidas.csv
echo 'ID_PRUEBA,C,F,T_TOTAL,T_POR_ACCESO' > medidas.csv
lista_c="4 8 16 20 40 60 100 128"
lista_l="384 1152 4096 12288 49152 73728 196608 393216"
#lista_c="4 8"
#lista_f="20 40"
for id_prueba in {1..50};
do
    echo "=========== ID DE PRUEBA: $id_prueba ==========="
    for c in $lista_c;
    do
        for l in $lista_l;
        do
        f=$(bc <<< "scale=2; (64/(8*$c))*$l")
        f=$(echo "$f" | awk '{printf("%.0f\n", $1)}')
            echo "Ejecutando prueba con C=$c L=$l F=$f"
            eval "./codigo.out $c $f $id_prueba"
        done
    done
done