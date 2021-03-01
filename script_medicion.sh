make # Compilamos
rm medidas.csv # Limpiamos el fichero de resultados
lista_c="4 8 20 40"
lista_f="768 2304 8192 24576 98304 147456 393216 786432 384 1152 4096 12288 49152 73728 196608 393216 154 461 1638 4915 19661 29491 78643 157286 77 230 819 2458 9830 14746 39322 78643"
#lista_c="4 8"
#lista_f="20 40"
for c in $lista_c;
do
    for f in $lista_f;
    do
        for id_prueba in {1..50};
        do
            echo "Ejecutando prueba con C=$c F=$f"
            eval "./codigo.out $c $f $id_prueba"
        done
    done
done