
#include <stdio.h>
#include <stdlib.h>

#define TAM 20

int cuantas_piezas(int);
int rectificable(float, float);
int rechazada(float, float);

void cargar_piezas(float *, int);
int contar(int (*)(float, float), float, float *, int);
float* reserva_memoria(int);
void segrega(int (*)(float, float), float, float *, int, float *);
void mostrar_piezas(const char *, float *, int);

int main(void) {
	float diametros[TAM] = {0};
	int n;
	float max = 12;
	float min = 10;
	
	n = cuantas_piezas(TAM);
	cargar_piezas(diametros, n);
	
	int n_rectificar = contar(rectificable, max, diametros, n);
	float *p_rectificables = reserva_memoria(n_rectificar);
	segrega(rectificable, max, diametros, n, p_rectificables);
	
	int n_rechazar = contar(rechazada, min, diametros, n);
	float *p_rechazadas = reserva_memoria(n_rechazar);
	segrega(rechazada, min, diametros, n, p_rechazadas);
	
	mostrar_piezas("rectificables", p_rectificables, n_rectificar);
	mostrar_piezas("rechazadas", p_rechazadas, n_rechazar);
	
	free(p_rectificables);
	free(p_rechazadas);
	
	return 0;
}
void cargar_piezas(float *p, int n) {
	float aux;
	for (int i = 0; i < n; i++) {
		do {
			printf("Ingrese diámetro de pieza %d: ", i);
			scanf("%f", &aux);
			if (aux <= 0) {
				printf("Error: El diámetro debe ser positivo.\n");
			}
		} while (aux <= 0);
		
		*(p + i) = aux;
	}
}
int contar(int (*criterio)(float, float), float valor, float *p, int n) {
	int contador = 0;
	for (int i = 0; i < n; i++) {
		if (criterio(*(p + i), valor) == 1) {
			contador++;
		}
	}
	return contador;
}
float* reserva_memoria(int n) {
	int cantidad = (n == 0) ? 1 : n; 
	float *ptr = (float *) malloc(cantidad * sizeof(float));
	
	if (ptr == NULL) {
		printf("Error fatal: No se pudo reservar memoria.\n");
		exit(1);
	}
	return ptr;
}
void segrega(int (*criterio)(float, float), float valor, float *p, int n, float *q) {
	int j = 0;
	for (int i = 0; i < n; i++) {
		if (criterio(*(p + i), valor) == 1) {
			*(q + j) = *(p + i);
			j++;
		}
	}
}
void mostrar_piezas(const char *mensaje, float *p, int n) {
	printf("\nPiezas %s:\n", mensaje);
	for (int i = 0; i < n; i++) {
		printf("Diámetro: %.2f\n", *(p + i));
	}
}
int cuantas_piezas(int max) {
	int n;
	do {
		printf("Cuantas piezas ingresara? ");
		scanf("%d", &n);
	} while (n < 0 || n > max);
	return n;
}
int rectificable(float diametro, float valor) {
	if (diametro > valor) return 1;
	else return 0;
}
int rechazada(float diametro, float valor) {
	if (diametro < valor) return 1;
	else return 0;
}
