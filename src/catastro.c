/*
 * catastro.c
 *
 *  Created on: 16 jun. 2022
 *      Author: nico
 */
#include <stdio.h>
#include <stdlib.h>
#include "censista.h"
#include "vivienda.h"
#include "arraysChar.h"
#include "utn.h"
#include <string.h>
#include <ctype.h>

int cargarCatastro(eCatastro* catastros, int tam, int* idActual, int* posCargadas)
{
	int ret = -1;
	char localidad[20];
	int manzana;
	int parcela;

	if(catastros != NULL && idActual != NULL && posCargadas != NULL)
	{
		do
		{
			if(*posCargadas == tam)
			{
				printf("\nNo hay mas espacios disponibles.\n");
				break;
			}

			if(pedirNombre(localidad, "\nIngrese el nombre de la lacalidad: ") == -1)
			{
				break;
			}
			if(pedirNumero(&manzana, "\nIngrese la manzana: ",  "\nError.\n",1,200) == -1)
			{
				break;
			}
			if(pedirNumero(&parcela, "\nIngrese la parcela: ",  "\nError.\n",1,3000) == -1)
			{
				break;
			}

			agregarCatastro(catastros, tam, manzana, localidad, parcela, idActual, posCargadas);
			(*idActual)++;

		}while(utn_confirmar("\n¿Desea continuar? s/n ", "\nRespuesta invalida.\n", 3) == 1);
		ret = 0;
	}
	return ret;
}

int agregarCatastro(eCatastro* catastros, int tam, int manzana, char* localidad, int parcela, int* id, int* posCargadas)
{
	int ret = -1;
	int pos;

	if(catastros != NULL && tam > 0 && localidad != NULL && id > 0 && posCargadas != NULL && manzana > 0 && parcela > 0)
	{
		pos = buscarCatastroLibre(catastros, tam);
		if(pos != -1)
		{
			(*(catastros+pos)).isEmpty = 0;
			(*(catastros+pos)).idCatastro = *id;
			strncpy((*(catastros+pos)).localidad,localidad,sizeof((*(catastros+pos)).localidad));
			(*(catastros+pos)).parcela = parcela;
			(*(catastros+pos)).manzana = manzana;
			*posCargadas = *posCargadas +1;
		}
		ret = 0;
	}

	return ret;
}

int buscarCatastroLibre(eCatastro* catastros, int tam)
{
	int ret = -1;
	int i;

	if(catastros != NULL && tam > 0)
	{
		for(i = 0; i < tam; i++)
		{
			if((*(catastros+i)).isEmpty == 1)
			{
				ret = i;
				break;
			}
		}
	}
	return ret;
}

int bajaCatastro(eCatastro* catastros, int tam, int* posCargadas, int idActual)
{
	int ret = -1;
	int pos;
	int id;

	if(catastros != NULL && tam > 0 && posCargadas != NULL && idActual > 0)
	{
		if(utn_getNumero(&id, "\nIngrese id del catastro: ", "\nNo se encontró el id.\n", 1, idActual, 3) == 0)
		{
			pos = buscarIdCatastro(catastros, tam, id);
			if(pos != -1)
			{
				if(utn_confirmar("\n¿Está seguro? s/n\n", "\nRespuesta no valida.\n", 3) == 1)
				{
					(*(catastros+pos)).isEmpty = 1;
					ret = 0;
					*posCargadas = *posCargadas -1;
				}
			}
		}
	}

	return ret;
}

int buscarIdCatastro(eCatastro* catastros, int tam, int id)
{
	int ret = -1;
	int i;

	if(catastros != NULL && tam > 0 && id > 0)
	{
		for(i=0; i<tam; i++)
		{
			if((*(catastros+i)).idCatastro == id)
			{
				ret = i;
			}
		}
	}
	return ret;
}

void mostrarCatastro(eCatastro catastro)
{
	printf("\n %-20s %-10d %-10d %-10d\n",catastro.localidad,catastro.manzana,catastro.parcela,catastro.idCatastro);
}

int listarCatastros(eCatastro* catastros, int tam)
{
	int ret = -1;
	int i;

	if(catastros != NULL && tam > 0)
	{
		printf("\n*********************************************************\n");
		printf(" %-20s %-10s %-10s %-10s\n","LOCALIDAD","MANZANA","PARCELA","ID");
		for(i = 0; i < tam; i++)
		{
			if((*(catastros+i)).isEmpty == 0)
			{
				mostrarCatastro(*(catastros+i));
			}
		}
		printf("\n*********************************************************\n");
		ret = 0;
	}

	return ret;
}

int modificarCatastro(eCatastro* catastros, int tam, int idActual)
{
	int ret = -1;
	int pos;
	int id = -1;
	int res;
	int campo;
	int numero;
	char localidad[20];

	if(catastros != NULL && tam > 0 && idActual > 0)
	{
		utn_getNumero(&id, "\nIngrese el id del catastro: ", "\nNo se encontró el id.\n", 1, idActual, 3);
		pos = buscarIdCatastro(catastros, tam, id);

		if(pos != -1)
		{
			res = utn_getNumero(&campo, "\nIngrese campo a modificar: \n1 - localidad.\n2 - manzana.\n3 - parcela. ", "\nError.\n", 1, 3, 3);
			if(!res)
			{
				ret = 0;
				switch(campo)
				{
					case 1:
						if(pedirNombre(localidad, "\nIngrese la localidad: ") == 0)
						{
							strncpy((*(catastros+pos)).localidad,localidad,sizeof((*(catastros+pos)).localidad));
							printf("\nSe guardaron los cambios.\n");
						}
						break;
					case 2:
						if(pedirNumero(&numero, "\nIngrese la manzana: ",  "\nError.\n",1,200) == 0)
						{
							(*(catastros+pos)).manzana = numero;
							printf("\nSe guardaron los cambios.\n");
						}
						break;
					case 3:
						if(pedirNumero(&numero, "\nIngrese la parcela: ",  "\nError.\n",1,3000) == 0)
						{
							(*(catastros+pos)).parcela = numero;
							printf("\nSe guardaron los cambios.\n");
						}
						break;
				}
			}
		}
		else
		{
			printf("\nNo se encontro el id.\n");
		}
	}
	return ret;
}

int ordenarCatastros(eCatastro* catastros, int tam)
{
	int ret = -1;
	int i;
	int max = tam -1;
	int bandera;
	eCatastro aux;
	int res;

	if(catastros != NULL && tam > 0)
	{
		do
		{
			bandera = 0;
			for(i = 0; i < max; i++)
			{
				res = strcmp((*(catastros+i)).localidad,(*(catastros+i+1)).localidad);
				if(res > 0)
				{
					bandera = 1;
					aux = *(catastros+i);
					*(catastros+i) = *(catastros+i+1);
					*(catastros+i+1) = aux;
				}
			}
			max--;
		}while(bandera);
		ret = 0;
	}

	return ret;
}

int retornarIdPorLocalidad(eCatastro* catastros, int tam, char* localidad)
{
	int ret = -1;
	int i;
	if(catastros != NULL && tam > 0 && localidad != NULL)
	{
		*(localidad+0) = toupper(*(localidad+0));
		for(i = 0; i < tam; i++)
		{
			if(strcmp((*(catastros+i)).localidad,localidad) == 0)
			{
				ret = (*(catastros+i)).idCatastro;
				break;
			}
		}
	}
	return ret;
}
