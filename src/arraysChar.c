/*
 * arraysChar.c
 *
 *  Created on: 26 abr. 2022
 *      Author: nico
 */
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int esTelefono(char* tel)
{
	int ret = -1;
	int i;

	if(tel != NULL)
	{
		ret = 0;

		for(i = 0; (tel[i] != '\0'); i++)
		{
			if(i != 4)
			{
				if((tel[i] < '0' || tel[i] > '9') || (tel[i] == '-'))
				{
					ret = -1;
					break;
				}
			}
			else
			{
				if((tel[i] != '-'))
				{
					ret = -1;
					break;
				}
			}
		}
	}
	return ret;
}

int esAlfanumerico(int* resultado, char alfanum[])
{
	int ret = -1;
	int res = 1;
	int i;

	if(resultado != NULL && alfanum != NULL)
	{
		ret = 1;

		for(i = 0; alfanum[i] != '\0'; i++)
		{
			if((alfanum[i] < '0' || alfanum[i] > '9') && (alfanum[i] < 'A' || alfanum[i] > 'Z') && (alfanum[i] < 'a' || alfanum[i] > 'z'))
			{
				res = 0;
				break;
			}
		}
	}
	*resultado = res;
	return ret;
}

int esLetraConEspacio(char *pResultado)
{
	int ret = 0;
	int i;

	if(pResultado != NULL)
	{
		ret = 1;

		for(i=0; pResultado[i]!='\0'; i++)
		{
			if(pResultado[0] == ' ' || pResultado[i+1] == '\0')
			{
				if(pResultado[i] == ' ')
				{
					ret = 0;
					break;
				}
			}

			if((pResultado[i] < 'a' || pResultado[i] > 'z') && (pResultado[i] < 'A' || pResultado[i] > 'Z') && pResultado[i] != ' ')
			{
				ret = 0;
				break;
			}
		}
	}

	return ret;
}

int esSoloLetra(char *pResultado)
{
	int ret = 0;
	int i;

	if(pResultado != NULL)
	{
		ret = 1;

		for(i=0; pResultado[i]!='\0'; i++)
		{
			if((pResultado[i] < 'a' || pResultado[i] > 'z') && (pResultado[i] < 'A' || pResultado[i] > 'Z'))
			{
				ret = 0;
				break;
			}
		}
	}

	return ret;
}
