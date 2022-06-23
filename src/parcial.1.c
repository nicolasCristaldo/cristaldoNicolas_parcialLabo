/*nicolas cristaldo
 */

#include <stdio.h>
#include <stdlib.h>
#include "censista.h"
#include "vivienda.h"
#include "utn.h"
#include "catastro.h"

#define TAM_V 5
#define TAM_C 3
#define TAM_T 4
#define TAM_CAT 5

int main(void) {
	setbuf(stdout, NULL);
	int idActual = 20000;
	int posCargadas = 0;
	char letraSeleccionada;
	int res;
	eCensista censistas[TAM_C]= {{100, "Ana", 34, "1203-2345",0},
							{101, "Juan", 24, "4301-54678",0},
							{102, "Sol", 47, "5902-37487",0}};
	eTipoVivienda tipos[TAM_T] = {{1,"Casa"},{2,"Departamento"},{3,"Casilla"},{4,"Rancho"}};
	eCatastro catastros[TAM_CAT] = {{1000, "Avellaneda", 28, 1540}, {1001, "Lanus", 43, 1789}, {1002, "Quilmes", 32, 1624},
									{1003, "La Plata", 67, 1677},{1004, "Lomas de Zamora", 32, 1923}};
	eVivienda viviendas[TAM_V];

	inicializarVivienda(viviendas, TAM_V);

	int (*pFuncion)(eVivienda, int);
	do
	{
		res = utn_getNombre(&letraSeleccionada, "Elija una opcion: \nA - ALTA.\nB - MODIFICAR.\nC - BAJA.\nD - LISTAR VIVIENDAS."
				"\nE - LISTAR CENSISTAS.\nF - LISTAR CATASTROS POR NOMBRE.\nG - INFORMAR.\n", "\nCaracter invalido\n", 1, 1, 3);
		if(!res)
		{
			switch(letraSeleccionada)
			{
				case 'a':
				case 'A':
					if(posCargadas < TAM_V)
					{
						if(!cargarVivienda(viviendas, censistas, catastros, TAM_V, TAM_C, TAM_CAT, &idActual))
						{
							posCargadas++;
						}
					}
					else
					{
						printf("\nNo hay lugares disponibles.\n");
					}
					break;
				case 'b':
				case 'B':
					if(posCargadas > 0)
					{
						modificarVivienda(viviendas, TAM_V, idActual);
					}
					else
					{
						printf("\nNo hay viviendas cargadas.\n\n");
					}
					break;
				case 'c':
				case 'C':
					if(posCargadas > 0)
					{
						if(darDeBaja(viviendas, TAM_V, idActual) == 0)
						{
							posCargadas--;
						}
					}
					else
					{
						printf("\nNo hay viviendas cargadas.\n\n");
					}
					break;
				case 'd':
				case 'D':
					if(posCargadas > 0)
					{
						pFuncion = validarEmpty;
						listarViviendas(viviendas, TAM_V, censistas, TAM_C, catastros, TAM_CAT, tipos, TAM_T, pFuncion, 0);
					}
					else
					{
						printf("\nNo hay viviendas cargadas.\n\n");
					}
					break;
				case 'e':
				case 'E':
					listarCensistas(censistas, TAM_C);
					break;
				case 'f':
				case 'F':
					ordenarCatastros(catastros, TAM_CAT);
					listarCatastros(catastros, TAM_CAT);
					break;
				case 'g':
				case 'G':
					if(posCargadas > 0)
					{
						informar(viviendas, TAM_V, censistas, TAM_C, catastros, TAM_CAT, tipos, TAM_T);
					}
					break;
			}
		}

	}while(1);

	return EXIT_SUCCESS;
}
