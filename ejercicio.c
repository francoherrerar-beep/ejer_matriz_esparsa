
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

typedef struct {
    int fila;
    int col;
    double valor;
} ElementoEsparso;

void generar_matriz(char nombre[], int filas, int columnas) {
    FILE *archivo;
    int total, cantidad, i, j, pos, aux;
    int *valores, *posiciones;

    total = filas * columnas;
    cantidad = total * 5 / 100;

    valores = (int *)calloc(total, sizeof(int));
    posiciones = (int *)malloc(total * sizeof(int));

    if (valores == NULL || posiciones == NULL) {
        printf("Error al reservar memoria.\n");
        free(valores);
        free(posiciones);
        exit(1);
    }

    for (i = 0; i < total; i++) {
        posiciones[i] = i;
    }

    for (i = 0; i < cantidad; i++) {
        pos = i + rand() % (total - i);

        aux = posiciones[i];
        posiciones[i] = posiciones[pos];
        posiciones[pos] = aux;

        valores[posiciones[i]] = rand() % 9 + 1;
    }

    archivo = fopen(nombre, "w");

    if (archivo == NULL) {
        printf("Error al crear el archivo.\n");
        free(valores);
        free(posiciones);
        exit(1);
    }

    fprintf(archivo, "%d %d\n", filas, columnas);

    for (i = 0; i < filas; i++) {
        for (j = 0; j < columnas; j++) {
            if (valores[i * columnas + j] != 0) {
                fprintf(archivo, "%d %d %d\n", i, j,
                        valores[i * columnas + j]);
            }
        }
    }

    fclose(archivo);
    free(valores);
    free(posiciones);
}

void convertir_binario(char nombre_txt[], char nombre_bin[]) {
    FILE *txt, *bin;
    ElementoEsparso e;
    int filas, columnas;

    txt = fopen(nombre_txt, "r");

    if (txt == NULL) {
        printf("Error al abrir el archivo de texto.\n");
        exit(1);
    }

    bin = fopen(nombre_bin, "wb");

    if (bin == NULL) {
        printf("Error al crear el archivo binario.\n");
        fclose(txt);
        exit(1);
    }

    if (fscanf(txt, "%d %d", &filas, &columnas) != 2) {
        printf("Error al leer las dimensiones.\n");
        fclose(txt);
        fclose(bin);
        exit(1);
    }

    while (fscanf(txt, "%d %d %lf",
                  &e.fila, &e.col, &e.valor) == 3) {
        fwrite(&e, sizeof(ElementoEsparso), 1, bin);
    }

    fclose(txt);
    fclose(bin);
}

