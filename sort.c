#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include "glist.h"

#define MAX_STRING 45

typedef struct {
  char* nombre;
  int edad;
  char* lugarDeNacimiento; // pais o capital
} Persona;

void print_persona(void *dato) {
  Persona *p = (Persona *) dato;
  printf("%s, %d, %s\n", p->nombre, p->edad, p->lugarDeNacimiento);
}

GList glist_personas(char* archivo) {
  GList lista = glist_crear();

  FILE *fp = fopen(archivo, "r");
  for (; fp == NULL; fp = fopen(archivo, "r")) {
    printf("ERROR: No se encuentra el archivo. Ingrese un nombre valido: ");
    scanf("%[^\n]s", archivo);
  }

  char *buf = malloc(sizeof(char)*100);
  size_t s = 0;
  char c;
  while(!(feof(fp))) {
    Persona *p = malloc(sizeof(Persona));
    puts("alloc");
    p->nombre = malloc(sizeof(char)*MAX_STRING);
    puts("alloc");
    p->lugarDeNacimiento = malloc(sizeof(char)*MAX_STRING);
    puts("alloc");

		int tam = getline(&buf, &s, fp), i = 0;

    for (c = buf[0]; i < tam-1 && c != ','; i++, c = buf[i]) {
      p->nombre[i] = c;
    }
    p->nombre[i] = '\0';
    puts("nombre");

    i += 2;
    int j = i;
    char* edad = malloc(sizeof(char)*4);
    for (c = buf[i]; i < tam-1 && c != ','; i++, c = buf[i]) {
      edad[i - j] = c;
    }
    edad[i] = '\0';
    p->edad = atoi(edad);
    free(edad);
    puts("edad");

    i += 2;
    j = i;
    for (c = buf[i]; i < tam-1; i++, c = buf[i]) {
      p->lugarDeNacimiento[i - j] = c;
    }
    p->lugarDeNacimiento[i] = '\0';
    puts("pais");

    lista = glist_agregar_inicio(lista, (void*) p);
    puts("agregar");
    print_persona(p);
	}

  fclose(fp);
  free(buf);
  return lista;
}

int main(int argc, char const *argv[]) {
  char *archivo = malloc(sizeof(char)*MAX_STRING);

  if (argc > 1) {
    strcpy(archivo, argv[1]);
  } else {
    printf("Por favor, ingrese el nombre del archivo de las personas: ");
    scanf("%[^\n]s",archivo);
  }

  GList personas = glist_personas(archivo);
  glist_recorrer(personas, print_persona);

  glist_destruir(personas);
  free(archivo);
  return 0;
}
