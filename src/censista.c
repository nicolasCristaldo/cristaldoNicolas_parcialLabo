/*
 * censista.c
 *
 *  Created on: 20 may. 2022
 *      Author: nico
 */
#include <stdio.h>
#include <stdlib.h>
#include "censista.h"
#include "vivienda.h"
#include "arraysChar.h"
#include "utn.h"
#include <string.h>

int inicializarCensista(eCensista* censistas, int tam)
{
	int ret = -1;
	int i;

	if(censistas != NULL && tam > 0)
	{
		for(i=0;i<tam;i++)
		{
			(censistas+i)->isEmpty = 1;
		}
		ret = 0;
	}

	return ret;
}

int buscarIdCensista(eCensista* censistas, int tam, int id)
{
	int ret = -1;
	int i;

	if(censistas != NULL && tam > 0 && id > 0)
	{
		for(i=0; i<tam; i++)
		{
			if((censistas+i)->legajo == id)
			{
				ret = i;
			}
		}
	}
	return ret;
}

int listarCensistas(eCensista* censistas, int tam)
{
	int ret = -1;
	int i;

	if(censistas != NULL && tam > 0)
	{
		printf("\n*********************************************************\n");
		printf(" %-20s %-15s %-10s %-10s\n","NOMBRE","TELEFONO","EDAD","LEGAJO");
		for(i = 0; i < tam; i++)
		{
			if((censistas+i)->isEmpty == 0)
			{
				mostrarCensista(*(censistas+i));
			}
		}
		printf("\n*********************************************************\n");
		ret = 0;
	}

	return ret;
}

void mostrarCensista(eCensista censista)
{
	printf("\n %-20s %-15s %-10d %-10d\n",censista.nombre,censista.telefono,censista.edad,censista.legajo);
}

int cargarCensista(eCensista* censistas, int tam, int* idActual, int* posCargadas)
{
	int ret = -1;
	char nombre[20];
	char telefono[10];
	int edad;

	if(censistas != NULL && idActual != NULL && posCargadas != NULL)
	{
		do
		{
			if(*posCargadas == tam)
			{
				printf("\nNo hay mas espacios disponibles.\n");
				break;
			}

			if(pedirNombre(nombre, "\nIngrese el nombre del censista: ") == -1)
			{
				break;
			}
			if(pedirNumero(&edad, "\nIngrese la edad del censista: ",  "\nError.\n",18,64) == -1)
			{
				break;
			}
			if(pedirTelefono(telefono) == -1)
			{
				break;
			}

			agregarCensista(censistas, tam, telefono, nombre, edad, idActual, posCargadas);
			(*idActual)++;

		}while(utn_confirmar("\n¿Desea continuar? s/n ", "\nRespuesta invalida.\n", 3) == 1);
		ret = 0;
	}
	return ret;
}

int pedirTelefono(char* telefono)
{
	int ret = -1;

	if(telefono != NULL)
	{
		do
		{
			if(utn_getTelefono(telefono, "\nIngrese numero de telefono: ", "\nError.\n",8, 10, 3) == 0)
			{
				ret = 0;
				break;
			}
		}while(utn_confirmar("\n¿Volver a intentar? s/n\nSi la respuesta es no, se perderán los datos ","\nRespuesta invalida.\n",3)== 1);
	}

	return ret;
}

int agregarCensista(eCensista* censistas, int tam, char* telefono, char* nombre, int edad, int* id, int* posCargadas)
{
	int ret = -1;
	int pos;

	if(censistas != NULL && tam > 0 && telefono != NULL && nombre != NULL && edad >= 18 && edad <= 64 && id > 0 && posCargadas != NULL)
	{
		pos = buscarCensistaLibre(censistas, tam);
		if(pos != -1)
		{
			(censistas+pos)->isEmpty = 0;
			(censistas+pos)->legajo = *id;
			strncpy((censistas+pos)->nombre,nombre,sizeof((censistas+pos)->nombre));
			strncpy((censistas+pos)->telefono,telefono,sizeof((censistas+pos)->telefono));
			(censistas+pos)->edad = edad;
			*posCargadas = *posCargadas +1;
		}
		ret = 0;
	}

	return ret;
}

int buscarCensistaLibre(eCensista* censistas, int tam)
{
	int ret = -1;
	int i;

	if(censistas != NULL && tam > 0)
	{
		for(i = 0; i < tam; i++)
		{
			if((censistas+i)->isEmpty == 1)
			{
				ret = i;
				break;
			}
		}
	}
	return ret;
}

int bajaCensista(eCensista* censistas, int tam, int* posCargadas, int idActual)
{
	int ret = -1;
	int pos;
	int id;

	if(censistas != NULL && tam > 0 && posCargadas != NULL && idActual > 0)
	{
		if(utn_getNumero(&id, "\nIngrese legajo del censista: ", "\nNo se encontró el legajo.\n", 1, idActual, 3) == 0)
		{
			pos = buscarIdCensista(censistas, tam, id);
			if(pos != -1)
			{
				if(utn_confirmar("\n¿Está seguro? s/n\n", "\nRespuesta no valida.\n", 3) == 1)
				{
					(censistas+pos)->isEmpty = 1;
					ret = 0;
					*posCargadas = *posCargadas -1;
				}
			}
		}
	}

	return ret;
}

int modificarCensista(eCensista* censistas, int tam, int idActual)
{
	int ret = -1;
	int pos;
	int id = -1;
	int res;
	int campo;
	int numero;
	char nombre[20];

	if(censistas != NULL && tam > 0 && idActual > 0)
	{
		utn_getNumero(&id, "\nIngrese el id del censista: ", "\nNo se encontró el id.\n", 1, idActual, 3);
		pos = buscarIdCensista(censistas, tam, id);

		if(pos != -1)
		{
			res = utn_getNumero(&campo, "\nIngrese campo a modificar: \n1 - Nombre.\n2 - Telefono.\n3 - edad. ", "\nError.\n", 1, 3, 3);
			if(!res)
			{
				ret = 0;
				switch(campo)
				{
					case 1:
						if(pedirNombre(nombre, "\nIngrese el nombre: ") == 0)
						{
							strncpy((censistas+pos)->nombre,nombre,sizeof((censistas+pos)->nombre));
							printf("\nSe guardaron los cambios.\n");
						}
						break;
					case 2:
						if(pedirTelefono(nombre) == 0)
						{
							strncpy((censistas+pos)->telefono,nombre,sizeof((censistas+pos)->telefono));
							printf("\nSe guardaron los cambios.\n");
						}
						break;
					case 3:
						if(pedirNumero(&numero, "\nIngrese la edad: ",  "\nError.\n",18,64) == 0)
						{
							(censistas+pos)->edad = numero;
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
