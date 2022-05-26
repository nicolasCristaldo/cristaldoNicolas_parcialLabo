/*
 * utn.c
 *
 *  Created on: 9 abr. 2022
 *      Author: nicolas cristaldo
 */

#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <string.h>
#include "arraysChar.h"

static int esRespuestaValida(char* cadena);
static int getRespuesta(void);
static int getInt(int* pResultado);
static int getFloat(float* fResultado);
static int getNombre(char* cResultado, int min, int max);
static int getAlfanumerico(char* cResultado, int min, int max);
static int getTel(char* cResultado, int min, int max);
static int esNombre(char* cadena);
static int esNumerica(char* cadena);
static int esFlotante(char* cadena);
static int esAlfanumerica(char* cadena);
static int esTel(char* cadena);
static int myGets(char* cadena, int longitud);

static int getInt(int* pResultado)
{
	int ret = -1;
	char buffer[2000];

	if(myGets(buffer,sizeof(buffer))==0 && esNumerica(buffer))
	{
		*pResultado = atoi(buffer);
		ret = 0;
	}
	return ret;
}

static int getFloat(float* fResultado)
{
	int ret = -1;
	char buffer[2000];

	if(myGets(buffer,sizeof(buffer))==0 && esFlotante(buffer))
	{
		*fResultado = atof(buffer);
		ret = 0;
	}
	return ret;
}

static int getNombre(char* cResultado, int min, int max)
{
	int ret = -1;
	char buffer[2000];

	if(myGets(buffer,sizeof(buffer))==0 && esNombre(buffer))
	{
		if(strlen(buffer) >= min && strlen(buffer) <= max)
		{
			strncpy(cResultado,buffer,max);
			ret = 0;
		}
	}
	return ret;
}

static int getAlfanumerico(char* cResultado, int min, int max)
{
	int ret = -1;
	char buffer[2000];

	if(myGets(buffer,sizeof(buffer))==0 && esAlfanumerica(buffer))
	{
		if(strlen(buffer) >= min && strlen(buffer) <= max)
		{
			strncpy(cResultado,buffer,max);
			ret = 0;
		}
	}
	return ret;
}

static int getRespuesta(void)
{
	int ret = -1;
	char buffer[2000];

	if(myGets(buffer,sizeof(buffer))==0)
	{
		ret = esRespuestaValida(buffer);
	}
	return ret;
}

static int esNumerica(char* cadena)
{
	int ret = 1;
	int i = 0;

	if(cadena[i] == '-')
	{
		i = 1;
	}
	for(; cadena[i] != '\0'; i++)
	{
		if(cadena[i] > '9' || cadena[i] < '0')
		{
			ret = 0;
			break;
		}
	}
	return ret;
}

static int esFlotante(char* cadena)
{
	int ret = 1;
	int i = 0;
	int flag = 0;

	if(cadena[i] == '-')
	{
		i = 1;
	}

	for(; cadena[i] != '\0'; i++)
	{
		if(cadena[i] > '9' || cadena[i] < '0')
		{
			if(cadena[i] == '.' && flag == 0)
			{
				flag++;
			}
			else
			{
				ret = 0;
				break;
			}
		}
	}
	return ret;
}

static int esNombre(char* cadena)
{
	int ret = 1;
	if(esLetraConEspacio(cadena) == 0)
	{
		ret = 0;
	}
	return ret;
}

static int esAlfanumerica(char* cadena)
{
	int ret = 1;
	int res;

	esAlfanumerico(&res,cadena);

	if(res == 0)
	{
		ret = 0;
	}
	return ret;
}

static int esRespuestaValida(char* cadena)
{
	int ret = -1;

	if((cadena[0] == 's'|| cadena[0] == 'S') && strlen(cadena) == 1)
	{
		ret = 1;
	}
	else if((cadena[0] == 'n'|| cadena[0] == 'N') && strlen(cadena) == 1)
	{
		ret = 0;
	}

	return ret;
}

static int myGets(char* cadena, int longitud)
{
	fflush(stdin);
	fgets(cadena, longitud, stdin);

	cadena[strlen(cadena)-1] = '\0';
	return 0;
}

int utn_getNumero(int* pResultado,char* mensaje,char* mensajeError,int minimo,int maximo,int reintentos)
{
	int ret = -1;
	int num;

	if(pResultado != NULL && mensaje != NULL && mensajeError != NULL && minimo <= maximo && reintentos >= 0)
	{
		do
		{
			printf(mensaje);
			if(getInt(&num) == 0 && num >= minimo && num <= maximo)
			{
				*pResultado = num;
				ret = 0;
				break;
			}
			reintentos--;
			printf("%s",mensajeError);
		}while(reintentos >= 0);
	}

	return ret;
}


int utn_getFlotante(float* fResultado,char* mensaje,char* mensajeError,int minimo,int maximo,int reintentos)
{
	int ret = -1;
	float num;

	if(fResultado != NULL && mensaje != NULL && mensajeError != NULL && minimo <= maximo && reintentos >= 0)
	{
		do
		{
			printf(mensaje);
			if(getFloat(&num) == 0 && num >= minimo && num <= maximo)
			{
				*fResultado = num;
				ret = 0;
				break;
			}
			reintentos--;
			printf("%s",mensajeError);
		}while(reintentos >= 0);
	}

	return ret;
}

int utn_getNombre(char* cResultado,char* mensaje,char* mensajeError,int minimo,int maximo,int reintentos)
{
	int ret = -1;
	char cadena[maximo];

	if(cResultado != NULL && mensaje != NULL && mensajeError != NULL && minimo <= maximo && reintentos >= 0)
	{
		do
		{
			printf(mensaje);
			if(getNombre(cadena, minimo, maximo) == 0)
			{
				strncpy(cResultado,cadena,maximo);
				ret = 0;
				break;
			}
			reintentos--;
			printf("%s",mensajeError);
		}while(reintentos >= 0);
	}

	return ret;
}

int utn_getAlfanumerico(char* cResultado,char* mensaje,char* mensajeError,int minimo,int maximo,int reintentos)
{
	int ret = -1;
	char cadena[maximo];

	if(cResultado != NULL && mensaje != NULL && mensajeError != NULL && minimo <= maximo && reintentos >= 0)
	{
		do
		{
			printf(mensaje);
			if(getAlfanumerico(cadena, minimo, maximo) == 0)
			{
				strncpy(cResultado,cadena,maximo);
				ret = 0;
				break;
			}
			reintentos--;
			printf("%s",mensajeError);
		}while(reintentos >= 0);
	}

	return ret;
}

int utn_confirmar(char* mensaje,char* mensajeError,int reintentos)
{
	int ret = -1;

	if(mensaje != NULL && mensajeError != NULL && reintentos >= 0)
	{
		do
		{
			printf(mensaje);
			ret = getRespuesta();
			if(ret == 0 || ret == 1)
			{
				break;
			}
			reintentos--;
			printf("%s",mensajeError);
		}while(reintentos >= 0);
	}

	return ret;
}

int utn_getTelefono(char* cResultado,char* mensaje,char* mensajeError,int minimo,int maximo,int reintentos)
{
	int ret = -1;
	char cadena[maximo];

	if(cResultado != NULL && mensaje != NULL && mensajeError != NULL && minimo <= maximo && reintentos >= 0)
	{
		do
		{
			printf(mensaje);
			if(getTel(cadena, minimo, maximo) == 0)
			{
				strncpy(cResultado,cadena,maximo);
				ret = 0;
				break;
			}
			reintentos--;
			printf("%s",mensajeError);
		}while(reintentos >= 0);
	}

	return ret;
}

static int getTel(char* cResultado, int min, int max)
{
	int ret = -1;
	char buffer[2000];

	if(myGets(buffer,sizeof(buffer))==0 && esTel(buffer) == 0)
	{
		if(strlen(buffer) >= min && strlen(buffer) <= max)
		{
			strncpy(cResultado,buffer,max);
			ret = 0;
		}
	}
	return ret;
}

static int esTel(char* cadena)
{
	int ret = -1;
	int res;

	res = esTelefono(cadena);

	if(res == 0)
	{
		ret = 0;
	}
	return ret;
}
