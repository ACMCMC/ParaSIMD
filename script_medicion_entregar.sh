#!/bin/bash
make # Compilamos
rm medidas_red1.csv # Limpiamos el fichero de resultados
echo 'ID_PRUEBA,C,F,L,T_TOTAL,T_POR_ACCESO' > medidas_red1.csv # Cabecera del fichero
rm medidas_red2.csv # Limpiamos el fichero de resultados
echo 'ID_PRUEBA,C,F,L,T_TOTAL,T_POR_ACCESO' > medidas_red2.csv # Cabecera del fichero
lista_c="4 8 20 40" # Valores de C para probar
lista_l="384 1152 4096 12288 49152 73728 196608 393216" # Valores de L para probar
for id_prueba in {1..50}; # Repetimos las pruebas 50 veces
do
    echo "=========== ID DE PRUEBA: $id_prueba ==========="
    for c in $lista_c; # Para cada valor de C...
    do
        for l in $lista_l; # Recorremos todos los valores de L...
        do
        f=$(bc <<< "scale=2; (64/(8*$c))*$l") # Calculamos el numero de filas que se corresponden con ese valor de L
        f=$(echo "$f" | awk '{printf("%.0f\n", $1)}') # Eliminamos los decimales
            echo "Ejecutando prueba con C=$c L=$l F=$f" # Información por pantalla
            eval "./codigo_1.out $c $f $l $id_prueba" # Ejecutamos el primer experimento
            eval "./codigo_2.out $c $f $l $id_prueba" # Ejecutamos el segundo experimento
        done
    done
done