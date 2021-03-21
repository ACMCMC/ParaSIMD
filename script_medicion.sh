#!/bin/bash
make # Compilamos
rm medidas_red1.csv # Limpiamos el fichero de resultados
touch medidas_red1.csv
echo 'ID_PRUEBA,C,F,L,T_TOTAL,T_POR_ACCESO' > medidas_red1.csv # Cabecera del fichero
rm medidas_red2.csv # Limpiamos el fichero de resultados
touch medidas_red2.csv
echo 'ID_PRUEBA,C,F,L,T_TOTAL,T_POR_ACCESO' > medidas_red2.csv # Cabecera del fichero
lista_c="4 8 12 16 20 30 40 50 60" 
lista_l="384 1152 4096 12288 49152 73728 196608 393216 786432"
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
            eval "./codigo_1.out $c $f $l $id_prueba"
            eval "./codigo_2.out $c $f $l $id_prueba"
        done
    done
done