/*
 * vivienda.c
 *
 *  Created on: 20 may. 2022
 *      Author: nico
 */
#include <stdio.h>
#include <stdlib.h>
#include "vivienda.h"
#include "utn.h"
#include "censista.h"
#include "catastro.h"
#include <string.h>

int pedirCensista(int* id, eCensista* censistas, int tam)
{
	int ret = -1;

	if(id != NULL && censistas != NULL && tam > 0)
	{
		do
		{
			utn_getNumero(id, "\nIngrese id del censista: ", "\nError.\n",1, 250000, 3);

			if(buscarIdCensista(censistas, tam, *id) == -1)
			{
				printf("\nNo se encontró el id.\n");
			}
			else
			{
				ret = 0;
				printf("\nSe encontró el id.\n");
				break;
			}
		}while(utn_confirmar("\n¿Volver a intentar? s/n\nSi la respuesta es no, se perderán los datos ","\nRespuesta invalida.\n",3)== 1);
	}
	return ret;
}

int pedirCatastro(int* id, eCatastro* catastros, int tam)
{
	int ret = -1;

	if(id != NULL && catastros != NULL && tam > 0)
	{
		do
		{
			utn_getNumero(id, "\nIngrese id del catastro: ", "\nError.\n",1, 250000, 3);

			if(buscarIdCatastro(catastros, tam, *id) == -1)
			{
				printf("\nNo se encontró el id.\n");
			}
			else
			{
				ret = 0;
				printf("\nSe encontró el id.\n");
				break;
			}
		}while(utn_confirmar("\n¿Volver a intentar? s/n\nSi la respuesta es no, se perderán los datos ","\nRespuesta invalida.\n",3)== 1);
	}
	return ret;
}

int pedirNumero(int* numero, char* mensaje, char* mensajeError,int min, int max)
{
	int ret = -1;

	if(numero != NULL && mensaje != NULL && mensajeError != NULL && min < max)
	{
		do
		{
			if(utn_getNumero(numero, mensaje, mensajeError,min, max, 3) == 0)
			{
				ret = 0;
				break;
			}
		}while(utn_confirmar("\n¿Volver a intentar? s/n\nSi la respuesta es no, se perderán los datos ","\nRespuesta invalida.\n",3)== 1);
	}
	return ret;
}

int pedirNombre(char* nombre, char* mensaje)
{
	int ret = -1;

	if(nombre != NULL && mensaje != NULL)
	{
		do
		{
			if(utn_getNombre(nombre, mensaje, "\nError.\n",3, 25, 3) == 0)
			{
				ret = 0;
				break;
			}
		}while(utn_confirmar("\n¿Volver a intentar? s/n\nSi la respuesta es no, se perderán los datos ","\nRespuesta invalida.\n",3)== 1);
	}
	return ret;
}

int inicializarVivienda(eVivienda* viviendas, int tam)
{
	int ret = -1;
	int i;

	if(viviendas != NULL && tam > 0)
	{
		for(i=0;i<tam;i++)
		{
			(*(viviendas+i)).isEmpty = 1;
		}
		ret = 0;
	}

	return ret;
}

int cargarVivienda(eVivienda* viviendas, eCensista* censistas, eCatastro* catastros, int tamViv, int tamCen, int tamCat, int* idActual)
{
	int ret = -1;
	char calle[25];
	int personas;
	int habitaciones;
	int legCensista;
	int idCatastro;
	int tipo;

	if(viviendas != NULL && tamViv > 0 && idActual != NULL && tamCen > 0 && catastros != NULL && tamCat > 0)
	{
		if(pedirNombre(calle, "\nIngrese el nombre de la calle: ") == -1)
		{
			return ret;
		}
		if(pedirNumero(&personas, "\nIngrese la cantidad de personas: ",  "\nError.\n",1,20) == -1)
		{
			return ret;
		}
		if(pedirNumero(&habitaciones, "\nIngrese la cantidad de habitaciones: ",  "\nError.\n",1,25) == -1)
		{
			return ret;
		}
		if(pedirNumero(&tipo,"\nIngrese el tipo de vivienda:\n1 - CASA.\n2 - DEPARTAMENTO\n3 - CASILLA\n4 - RANCHO.\n",
				"\nError.\n",1,4)==-1)
		{
			return ret;
		}

		listarCensistas(censistas, tamCen);
		if(pedirCensista(&legCensista, censistas, tamCen) == -1)
		{
			return ret;
		}
		listarCatastros(catastros, tamCat);
		if(pedirCatastro(&idCatastro, catastros, tamCat) == -1)
		{
			return ret;
		}

		if(agregarVivienda(viviendas,calle,personas,habitaciones,legCensista,idCatastro,tipo,tamViv,idActual) == 0)
		{
			(*idActual)++;
			printf("\nSe cargó correctamente la vivienda.\n");
			ret = 0;
		}
	}

	return ret;
}

int agregarVivienda(eVivienda* viviendas,char* calle,int personas,int habitaciones,int idCensista, int idCatastro, int tipo,int tam,int* idActual)
{
	int ret = -1;
	int posicion;

	if(viviendas != NULL && tam > 0 && idActual != NULL && calle != NULL && habitaciones > 0 && idCensista > 0 && idCatastro > 0 && tipo > 0 && personas > 0)
	{
		posicion = buscarLibre(viviendas, tam);
		if(posicion != -1)
		{
			//(*(viviendas+posicion)).isEmpty = 0;
			(*(viviendas+posicion)).isEmpty = 0;
			(*(viviendas+posicion)).idVivienda = *idActual;
			strncpy((*(viviendas+posicion)).calle,calle,sizeof((*(viviendas+posicion)).calle));
			(*(viviendas+posicion)).cantHabitaciones = habitaciones;
			(*(viviendas+posicion)).cantPersonas = personas;
			(*(viviendas+posicion)).tipoVivienda = tipo;
			(*(viviendas+posicion)).legajoCensista = idCensista;
			(*(viviendas+posicion)).idCatastro = idCatastro;
			ret = 0;
		}
		else
		{
			printf("\nNo hay espacios libres.\n");
		}
	}
	return ret;
}

int buscarLibre(eVivienda* viviendas, int tam)
{
	int ret = -1;
	int i;

	if(viviendas != NULL && tam > 0)
	{
		for(i = 0; i < tam; i++)
		{
			if((*(viviendas+i)).isEmpty == 1)
			{
				ret = i;
				break;
			}
		}
	}
	return ret;
}

int buscarIdVivienda(eVivienda* viviendas, int tam, int id)
{
	int ret = -1;
	int i;

	if(viviendas != NULL && tam > 0 && id > 0)
	{
		for(i = 0; i < tam; i++)
		{
			if(((*(viviendas+i)).idVivienda == id) && ((*(viviendas+i)).isEmpty == 0))
			{
				ret = i;
				break;
			}
		}
		if(ret == -1)
		{
			printf("\nNo se encontró el id.\n");
		}
	}
	return ret;
}

int modificarVivienda(eVivienda* viviendas, int tam, int idActual)
{
	int ret= -1;
	int res;
	int campo;
	int pos;
	char calle[25] = "";
	int id;
	int numero;

	if(viviendas != NULL && tam > 0 && idActual > 0)
	{
		res = utn_getNumero(&id, "\nIngrese el id de la vivienda: ", "\nError.\n", 1, idActual, 3);
		if(!res)
		{
			pos = buscarIdVivienda(viviendas, tam, id);

			if(pos != -1)
			{
				res = utn_getNumero(&campo, "\nIngrese campo a modificar: \n1 - Calle.\n2 - Cantidad de personas.\n"
						"3 - cantidad de habitaciones.\n4 - Tipo de vivienda.", "\nError.\n", 1, 4, 3);
				if(!res)
				{
					switch(campo)
					{
						case 1:
							if(pedirNombre(calle, "\nIngrese el nombre de la calle: ") == 0)
							{
								strncpy((*(viviendas+pos)).calle,calle,sizeof((*(viviendas+pos)).calle));
								ret = 0;
								printf("\nSe guardaron los cambios.\n");
							}
							break;
						case 2:
							if(pedirNumero(&numero, "\nIngrese la cantidad de personas: ",  "\nError.\n",1,20) == 0)
							{
								(*(viviendas+pos)).cantPersonas = numero;
								ret = 0;
								printf("\nSe guardaron los cambios.\n");
							}
							break;
						case 3:
							if(pedirNumero(&numero, "\nIngrese la cantidad de habitaciones: ",  "\nError.\n",1,25) == 0)
							{
								(*(viviendas+pos)).cantHabitaciones = numero;
								ret = 0;
								printf("\nSe guardaron los cambios.\n");
							}
							break;
						case 4:
							if(pedirNumero(&numero,"\nIngrese el tipo de vivienda: \n1 - CASA.\n2 - DEPARTAMENTO\n3 - CASILLA\n4 - "
									"RANCHO.\n","\nError.\n",1,4) == 0)
							{
								(*(viviendas+pos)).tipoVivienda = numero;
								ret = 0;
								printf("\nSe guardaron los cambios.\n");
							}
							break;
					}
				}
			}
		}
	}
	return ret;
}

int darDeBaja(eVivienda* viviendas, int tam, int idActual)
{
	int ret = -1;
	int pos;
	int id;
	int res;

	if(viviendas != NULL && tam > 0 && idActual > 0)
	{
		res = utn_getNumero(&id, "\nIngrese el id de la vivienda: ", "\nError.\n", 1, idActual, 3);
		if(!res)
		{
			pos = buscarIdVivienda(viviendas, tam, id);
			if(pos != -1)
			{
				if(utn_confirmar("\n¿Está seguro? s/n\n", "\nRespuesta no valida.\n", 3) == 1)
				{
					(*(viviendas+pos)).isEmpty = 1;
					printf("\nSe eliminó la vivienda correctamente.\n");
					ret = 0;
				}
			}
		}
	}

	return ret;
}

void mostrarVivienda(eVivienda vivienda, char* tipo, char* censista, eCatastro catastro)
{
	printf("\n %-25s %-15d %-15d %-10d %-18s %-18s %-20s %-10d %-10d\n",vivienda.calle,vivienda.cantPersonas,vivienda.cantHabitaciones
			,vivienda.idVivienda,tipo,censista,catastro.localidad,catastro.manzana,catastro.parcela);
}

int ordenarViviendas(eVivienda* viviendas, int tam)
{
	int ret = -1;
	int i;
	int max = tam -1;
	int bandera;
	eVivienda aux;
	int res;

	if(viviendas != NULL && tam > 0)
	{
		do
		{
			bandera = 0;
			for(i = 0; i < max; i++)
			{
				res = strcmp((*(viviendas+i)).calle,(*(viviendas+i+1)).calle);
				if(res > 0)
				{
					bandera = 1;
					aux = *(viviendas+i);
					*(viviendas+i) = *(viviendas+i+1);
					*(viviendas+i+1) = aux;
				}
				else if(res == 0 && (*(viviendas+i)).cantPersonas > (*(viviendas+i+1)).cantPersonas)
				{
					bandera = 1;
					aux = *(viviendas+i);
					*(viviendas+i) = *(viviendas+i+1);
					*(viviendas+i+1) = aux;
				}
			}
			max--;
		}while(bandera);
		ret = 0;
	}

	return ret;
}

int buscarIdTipo(eTipoVivienda* tipos, int tam, int id)
{
	int ret = -1;
	int i;

	if(tipos != NULL && tam > 0 && id > 0)
	{
		for(i=0; i<tam; i++)
		{
			if((*(tipos+i)).idTipo == id)
			{
				ret = i;
			}
		}
	}
	return ret;
}

int informar(eVivienda* viviendas, int tamViv, eCensista* censistas, int tamCen, eCatastro* catastros, int tamCat, eTipoVivienda* tipos, int tamTip)
{
	int ret = -1;
	int num;
	int (*pFuncion)(eVivienda, int);
	char localidad[25];
	if(viviendas != NULL && tamViv > 0 && censistas != NULL && tamCen > 0 && tipos != NULL && tamTip > 0 && catastros != NULL && tamCat > 0)
	{
		if(utn_getNumero(&num, "\nInformar:\n1- Elegir tipo de vivienda y mostrar datos.\n2- Elegir localidad y mostrar datos."
				"\n3- Cantidad de viviendas censadas en la localidad de Avellaneda."
				"\n4- mostrar todas las viviendas que censó  un censista.\n5- Cantidad de viviendas de tipo “casa” censadas.\n"
				"6- Cantidad de viviendas de tipo “departamento” de la localidad de Lanús.\n", "\nError.\n", 1, 6, 6) == 0)
		{
			switch(num)
			{
				case 1:
					pFuncion = validarTipo;
					if(pedirNumero(&num,"\nIngrese el tipo de vivienda:\n1 - CASA.\n2 - DEPARTAMENTO\n3 - CASILLA\n4 - RANCHO.\n",
											"\nError.\n",1,4)==0)
					{
						listarViviendas(viviendas, tamViv, censistas, tamCen, catastros, tamCat, tipos, tamTip, pFuncion, num);
					}
					break;
				case 2:
					pFuncion = validarLocalidad;
					if(pedirNombre(localidad, "\nIngrese el nombre de la localidad: ") == 0)
					{
						num = retornarIdPorLocalidad(catastros, tamCat, localidad);
						if(num > -1)
						{
							listarViviendas(viviendas, tamViv, censistas, tamCen, catastros, tamCat, tipos, tamTip, pFuncion, num);
						}
					}
					break;
				case 3:
					cantidadCensadaPorLocalidad(viviendas,catastros,tamViv, tamCat, 1000);
					break;
				case 4:
					pFuncion = validarCensista;
					listarCensistas(censistas, tamCen);
					if(pedirCensista(&num, censistas, tamCen) == 0)
					{
						listarViviendas(viviendas, tamViv, censistas, tamCen, catastros, tamCat, tipos, tamTip, pFuncion, num);
					}
					break;
				case 5:
					cantidadCensadaPorTipo(viviendas, tamViv, 1);
					break;
				case 6:
					cantidadCensadaPorTipoYLocalidad(viviendas, catastros, tamViv, tamCat, 2, 1001);
					break;
			}
		}
	}
	return ret;
}

int cantidadCensadaPorTipo(eVivienda* viviendas, int tamViv, int idTipo)
{
	int ret = -1;
	int i;
	if(viviendas != NULL && tamViv > 0 && idTipo > 0)
	{
		ret = 0;
		for(i = 0; i < tamViv; i++)
		{
			if((*(viviendas+i)).tipoVivienda == idTipo)
			{
				ret++;
			}
		}
		printf("\nCantidad de viviendas de tipo %d censadas: %d\n",idTipo,ret);
	}
	return ret;
}

int cantidadCensadaPorTipoYLocalidad(eVivienda* viviendas, eCatastro* catastros, int tamViv, int tamCat, int idTipo, int localidad)
{
	int ret = -1;
	int i;
	int pos;
	if(viviendas != NULL && catastros != NULL && tamCat > 0 && tamViv > 0 && idTipo > 0)
	{
		ret = 0;
		for(i = 0; i < tamViv; i++)
		{
			if((*(viviendas+i)).tipoVivienda == idTipo && (*(viviendas+i)).idCatastro == localidad)
			{
				ret++;
			}
		}
		pos = buscarIdCatastro(catastros, tamCat, localidad);
		printf("\nCantidad de viviendas de tipo %d censadas en %s: %d\n",idTipo,(*(catastros+pos)).localidad,ret);
	}
	return ret;
}

int cantidadCensadaPorLocalidad(eVivienda* viviendas, eCatastro* catastros, int tamViv, int tamCat, int localidad)
{
	int ret = -1;
	int i;
	int pos;
	if(viviendas != NULL && catastros != NULL && tamCat > 0 && tamViv > 0)
	{
		ret = 0;
		for(i = 0; i < tamViv; i++)
		{
			if((*(viviendas+i)).idCatastro == localidad)
			{
				ret++;
			}
		}
		pos = buscarIdCatastro(catastros, tamCat, localidad);
		printf("\nCantidad de viviendas censadas en %s: %d\n",(*(catastros+pos)).localidad,ret);
	}
	return ret;
}

int listarViviendas(eVivienda* viviendas, int tamViv, eCensista* censistas, int tamCen, eCatastro* catastros, int tamCat, eTipoVivienda* tipos, int tamTip, int (*pFunc)(eVivienda,int),int num)
{
	int ret = -1;
	int i;
	int posNombre;
	int posTipo;
	int posCatastro;

	if(viviendas != NULL && tamViv > 0 && censistas != NULL && tamCen > 0 && tipos != NULL && tamTip > 0 && catastros != NULL && tamCat > 0 && num >= 0 && pFunc != NULL)
	{
		ordenarViviendas(viviendas, tamViv);
		printf("\n***************************************************************************************************************************************************\n");
		printf(" %-25s %-15s %-15s %-10s %-18s %-18s %-20s %-10s %-10s\n","CALLE","PERSONAS","HABITACIONES","ID","TIPO VIVIENDA","CENSISTA","LOCALIDAD","MANZANA","PARCELA");
		for(i = 0; i < tamViv; i++)
		{
			if(pFunc(*(viviendas+i),num) == 1)
			{
				posCatastro = buscarIdCatastro(catastros, tamCat, (*(viviendas+i)).idCatastro);
				posNombre = buscarIdCensista(censistas, tamCen, (*(viviendas+i)).legajoCensista);
				posTipo = buscarIdTipo(tipos, tamTip, (*(viviendas+i)).tipoVivienda);
				mostrarVivienda(*(viviendas+i), (*(tipos+posTipo)).descripcion, (*(censistas+posNombre)).nombre,*(catastros+posCatastro));
				ret = 0;
			}
		}
		printf("\n******************************************************************************************************************************************************\n");
	}

	return ret;
}

int validarTipo(eVivienda vivienda, int tipo)
{
	int ret = 0;

	if(tipo > 0 && tipo < 5)
	{
		if(vivienda.tipoVivienda == tipo && vivienda.isEmpty == 0)
		{
			ret = 1;
		}
	}
	return ret;
}

int validarCensista(eVivienda vivienda, int id)
{
	int ret = 0;

	if(vivienda.legajoCensista == id && vivienda.isEmpty == 0)
	{
		ret = 1;
	}
	return ret;
}

int validarLocalidad(eVivienda vivienda, int id)
{
	int ret = 0;

	if(vivienda.idCatastro == id && vivienda.isEmpty == 0)
	{
		ret = 1;
	}
	return ret;
}

int validarEmpty(eVivienda vivienda, int empty)
{
	int ret = 0;
	if(vivienda.isEmpty == empty)
	{
		ret = 1;
	}
	return ret;
}












































































/*
int mostrarCensistaPorViviendas(eCensista* censistas, eVivienda* viviendas,eTipoVivienda* tipos, int tamV, int tamC, int tamT)
{
	int ret = -1;
	int i;
	int j;
	int posTipo;

	if(censistas != NULL && viviendas != NULL  && tamC> 0 && tamV > 0 && tamT > 0)
	{
		ret = 0;
		for(i = 0; i < tamC; i++)
		{
			if((*(censistas+i)).isEmpty == 0)
			{
				mostrarCensista(*(censistas+i));
				printf("\n");
				for(j = 0; j < tamV; j++)
				{
					if((*(viviendas+j)).legajoCensista == (*(censistas+i)).legajo && (*(viviendas+j)).isEmpty == 0)
					{
						posTipo = buscarIdTipo(tipos, tamT, (*(viviendas+j)).tipoVivienda);
						mostrarVivienda(*(viviendas+j), (*(tipos+posTipo)).descripcion, (*(censistas+i)).nombre);
						printf("\n");
					}
				}
			}
		}
	}
	return ret;
}

int censisitaConMasCensos(eCensista* censistas, eVivienda* viviendas, int tamV)
{
	int ret = -1;
	int i;
	int a = 0;
	int b = 0;
	int c = 0;
	if(censistas != NULL && viviendas != NULL && tamV > 0)
	{
		ret = 0;

		for(i = 0; i < tamV; i++)
		{
			if((*(viviendas+i)).legajoCensista == (*(censistas+0)).legajo)
			{
				a++;
			}
			else if((*(viviendas+i)).legajoCensista == (*(censistas+1)).legajo)
			{
				b++;
			}
			else
			{
				c++;
			}
		}

		if(a > b && a > c)
		{
			mostrarCensista(*(censistas+0));
		}
		else if(b > c)
		{
			mostrarCensista(*(censistas+1));
		}
		else
		{
			mostrarCensista(*(censistas+2));
		}
	}
	return ret;
}*/
