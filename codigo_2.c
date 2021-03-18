#include <stdlib.h>
#include <stdio.h>
#include <pmmintrin.h>
#include <time.h>

#define LINEA_CACHE 64 // Bytes que hay en una línea caché

static unsigned cyc_hi = 0;
static unsigned cyc_lo = 0;
/* Set *hi and *lo to the high and low order bits of the cycle counter.
 Implementation requires assembly code to use the rdtsc instruction. */
void access_counter(unsigned *hi, unsigned *lo)
{
    asm("rdtsc; movl %%edx,%0; movl %%eax,%1" /* Read cycle counter */
        : "=r"(*hi), "=r"(*lo)                /* and move results to */
        : /* No input */                      /* the two outputs */
        : "%edx", "%eax");
}

/* Record the current value of the cycle counter. */
void start_counter()
{
    access_counter(&cyc_hi, &cyc_lo);
}

/* Return the number of cycles since the last call to start_counter. */
double get_counter()
{
    unsigned ncyc_hi, ncyc_lo;
    unsigned hi, lo, borrow;
    double result;

    /* Get cycle counter */
    access_counter(&ncyc_hi, &ncyc_lo);

    /* Do double precision subtraction */
    lo = ncyc_lo - cyc_lo;
    borrow = lo > ncyc_lo;
    hi = ncyc_hi - cyc_hi - borrow;
    result = (double)hi * (1 << 30) * 4 + lo;
    if (result < 0)
    {
        fprintf(stderr, "Error: counter returns neg value: %.0f\n", result);
    }
    return result;
}

void escribir_resultado(int id_prueba, int C, int F, int L, double tiempo, double tiempo_por_acceso)
{
    FILE *fp;

    fp = fopen("medidas_red2.csv", "a");
    if (fp)
    {
        fprintf(fp, "%d,%d,%d,%d,%lf,%lf\n", id_prueba, C, F, L, tiempo, tiempo_por_acceso);
        fclose(fp);
    }
}

int main(int argc, char **argv)
{
    int i, j, k, C, F, L, id_prueba;
    double tiempo;
    double **M;
    int *ind;
    double red[10];
    double suma, media;
    size_t salto_linea_cache;
    double num_accesos;

    if (argc != 5)
    {
        fprintf(stderr, "Formato del comando: %s [C] [F] [L] [ID de prueba]", argv[0]);
        exit(EXIT_FAILURE);
    }

    C = atoi(argv[1]);
    F = atoi(argv[2]);
    L = atoi(argv[3]);
    id_prueba = atoi(argv[4]);

    srand(clock());

    salto_linea_cache = LINEA_CACHE / (sizeof(double)); // La cantidad que tenemos que avanzar dentro de la matriz

    ind = malloc(F * sizeof(int)); // El vector de índices se puede reservar con malloc()

    for (i = 0; i < F; i++)
    { // Inicializamos los elementos del vector a 0, 1, 2, ...
        ind[i] = i;
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

    start_counter();

    for (i = 0; i < 10; i++)
    {
        suma = 0;
        for (j = 0; j < F; j++)
        {
            for (k = 0; k < C; k+=salto_linea_cache) {
                suma = suma + M[ind[j]][k]; // Al cambiar de línea, empezamos de nuevo en k=0
            }
        }
        red[i] = suma;
    }

    tiempo = get_counter();

    printf("Resultados de la reducción: ");
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

    num_accesos = (10.0*((double)(F*(1 + ((C-1)/salto_linea_cache)))));

    escribir_resultado(id_prueba, C, F, L, tiempo, tiempo / num_accesos);

    exit(EXIT_SUCCESS);
}