#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>
#include <time.h>

#define MAX_STRING 45

int lineas(FILE* fp) {
  int lineas = 0;
  char c;
  for (c = getc(fp); c != EOF; c = getc(fp)) {
    if (c == '\n')
      lineas++;
  }
  rewind(fp);
  return lineas;
}

void archivo_a_array(FILE *fp, char **arr, int l) {
  size_t s = 0, tam;
  for(int i = 0; i < l; i++) {
    arr[i] = NULL;
    tam = getline(&arr[i], &s, fp);
    arr[i][tam - 2] = '\0';
  }
}

void archivo_personas(char **nombres, int cantN, char **paises, int cantP) {
  int cant;
  printf("Cuantas personas quiere generar? ");
  scanf("%d", &cant);

  char *salida = malloc(sizeof(char)*MAX_STRING);
  printf("Ingrese el nombre del archivo donde guardar las personas: ");
  scanf("%s", salida);

  FILE *fp = fopen(salida, "w");
  for(int i = 0; i < cant; i++) {
    int nombre = random()%cantN;
    int edad = random()%100 + 1;
    int pais = random()%cantP;

    fprintf(fp, "%s, %d, %s\n", nombres[nombre], edad, paises[pais]);
  }
  fclose(fp);
}

void liberar_strings(char **arr, int cant) {
  for(int i = 0; i < cant; i++)
    free(arr[i]);
}

int main(int argc, char const *argv[]) {
  char *nombres = malloc(sizeof(char)*MAX_STRING);
  char *paises = malloc(sizeof(char)*MAX_STRING);
  FILE *fileN, *fileP;

  if (argc > 1)  {
    strcpy(nombres, argv[1]);
    strcpy(paises, argv[2]);
  } else {
    printf("Por favor, ingrese el nombre del archivo de los nombres: ");
    scanf("%[^\n]s",nombres);

    printf("Ahora ingrese el nombre del archivo de los paises: ");
    scanf("%[^\n]s",paises);
  }

  fileN = fopen(nombres, "r");
  for (;fileN == NULL, fileN = fopen(nombres, "r")) {
    printf("ERROR: No se encuentra el archivo. Ingrese un nombre valido: ");
    scanf("%s", nombres);
  }
  free(nombres);
  int cantN = lineas(fileN);
  char **arrN = malloc(sizeof(char*)*cantN);
  archivo_a_array(fileN, arrN, cantN);
  fclose(fileN);

  fileP = fopen(paises, "r");
  for (fileP == NULL, fileP = fopen(paises, "r")) {
    printf("ERROR: No se encuentra el archivo. Ingrese un nombre valido: ");
    scanf("%s", paises);
  }
  free(paises);
  int cantP = lineas(fileP);
  char **arrP = malloc(sizeof(char*)*cantP);
  archivo_a_array(fileP, arrP, cantP);
  fclose(fileP);

  archivo_personas(arrN, cantN, arrP, cantP);

  liberar_strings(arrN, cantN);
  free(arrN);
  liberar_strings(arrP, cantP);
  free(arrP);
  return 0;
}
