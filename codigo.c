#include <stdlib.h>
#include <stdio.h>
#include <pmmintrin.h>
#include <time.h>

#define LINEA_CACHE 64 // Bytes que hay en una línea caché

void escribir_resultado(int id_prueba, int C, int F, clock_t tiempo)
{
    FILE *fp;

    fp = fopen("medidas.csv", "a");
    if (fp)
    {
        fprintf(fp, "%d;%d;%d;%ld\n", id_prueba, C, F, tiempo);
        fclose(fp);
    }
}

int main(int argc, char **argv)
{
    int i, j, swap, swap_i, C, F, id_prueba;
    clock_t inicio, fin;
    double **M;
    int *ind;
    double red[10];
    double suma, media;

    if (argc != 4)
    {
        fprintf(stderr, "Formato del comando: %s [C] [F] [ID de prueba]", argv[0]);
        exit(EXIT_FAILURE);
    }

    C = atoi(argv[1]);
    F = atoi(argv[2]);
    id_prueba = atoi(argv[3]);

    srand(clock());

    ind = malloc(F * sizeof(int));

    for (i = 0; i < F; i++)
    { // Inicializamos los elementos del vector a 0, 1, 2, ...
        ind[i] = i;
    }

    for (i = 0; i < F * 5; i++)
    { // Barajamos los elementos del vector. Recorremos dos veces el vector, haciendo intercambios de forma aleatoria.
        swap_i = rand() % F;
        swap = ind[i % F];
        ind[i % F] = ind[swap_i];
        ind[swap_i] = swap;
    }

    M = (double **)_mm_malloc(F * sizeof(double *), LINEA_CACHE);
    for (i = 0; i < F; i++)
    { // Reservamos la memoria de cada fila de la matriz, e inicializamos los valores de la fila
        M[i] = (double *)malloc(C * sizeof(double));
        for (j = 0; j < C; j++)
        {
            M[i][j] = ((double)rand() / RAND_MAX);
        }
    }

    inicio = clock();

    for (i = 0; i < 10; i++)
    {
        suma = 0;
        for (j = 0; j < F; j++)
        {
            suma = suma + M[ind[j]][0];
        }
        red[i] = suma;
    }

    fin = clock();

    printf("RED: ");
    for (int i = 0; i < 10; i++)
    {
        printf("%lf  ", red[i]);
    }

    media = 0;
    for (i = 0; i < 10; i++)
    {
        media = media + red[i];
    }

    media = media / 10.0;

    printf("\nMedia: %lf\n", media);

    for (i = 0; i < F; i++)
    { // Liberamos la memoria
        free(M[i]);
    }
    _mm_free(M);
    free(ind);

    escribir_resultado(id_prueba, C, F, fin - inicio);

    exit(EXIT_SUCCESS);
}