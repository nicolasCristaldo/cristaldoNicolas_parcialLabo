/*
 * vivienda.h
 *
 *  Created on: 20 may. 2022
 *      Author: nico
 */

#ifndef VIVIENDA_H_
#define VIVIENDA_H_

#include "censista.h"

typedef struct
{
	int idVivienda;
	char calle[25];
	int cantPersonas;
	int cantHabitaciones;
	int tipoVivienda;
	int legajoCensista;
	int isEmpty;
}eVivienda;

typedef struct
{
	int idTipo;
	char descripcion[20];
}eTipoVivienda;

#endif /* VIVIENDA_H_ */

/**
 * inicializa el campo isEmpty
 * @param viviendas puntero a array de viviendas
 * @param tam tamaño del array
 * @return retorna 0 si todo sale vien, -1 si hubo error
 */
int inicializarVivienda(eVivienda* viviendas, int tam);
/**
 *carga una vivienda y llama a agregarVivienda para que la agregue al array
 * @param viviendas puntero a array de viviendas
 * @param censistas puntero a array de censistas
 * @param tamViv tamaño del array de viviendas
 * @param tamCen tamaño del array de censistas
 * @param idActual puntero a int, id actual de la vivienda
 * @return retorna -1 en caso de error, 0 si todo sale bien
 */
int cargarVivienda(eVivienda* viviendas, eCensista* censistas, int tamViv, int tamCen, int* idActual);
/**
 * agrega una vivienda cargada a un array de viviendas
 * @param viviendas puntero a array de viviendas
 * @param calle array de caracteres, nombre de la calle
 * @param personas cantidad de personas
 * @param habitaciones cantidad de habitaciones
 * @param idCensista legajo del censista
 * @param tipo tipo de vivienda
 * @param tam tamaño del array de viviendas
 * @param idActual puntero a int, id actual de las viviendas
 * @return retorna -1 en caso de error, 0 si todo salio bien
 */
int agregarVivienda(eVivienda* viviendas,char* calle,int personas,int habitaciones,int idCensista, int tipo,int tam,int* idActual);
/**
 * busca un espacio libre en un array de viviendas
 * @param viviendas puntero a array de viviendas
 * @param tam tamaño del array
 * @return si encuentra una posicion libre retorna su posicion en el array, -1 en caso contrario
 */
int buscarLibre(eVivienda* viviendas, int tam);
/**
 * pide un id y lo busca dentro del array de viviendas
 * @param viviendas puntero a array de viviendas
 * @param tam tamaño del array
 * @param id id a buscar
 * @return retorna la posicion del array si se encuentra, retorna -1 si hubo un error
 */
int buscarIdVivienda(eVivienda* viviendas, int tam, int id);
/**
 * modifica un campo de una viviendaseleccionada
 * @param viviendas puntero a array de viviendas
 * @param tam tamaño del array
 * @param idActual id maximo actual
 * @return retorna 0 si todo sale bien, -1 si hubo un error
 */
int modificarVivienda(eVivienda* viviendas, int tam, int idActual);
/**
 * pide un nombre al usuario, pasa por referencia el nombre cargado
 * @param nombre puntero a char, nombre a pedir
 * @param mensaje puntero a char, mensaje para pedir el nombre
 * @return retorna 0 si todo sale bien, -1 si no se pudo cargar una calle
 */
int pedirNombre(char* calle, char* mensaje);
/**
 * pide un numero al usuario, pasa por referencia el valor del numero cargado
 * @param numero puntero a int, numero a cargar
 * @param mensaje array de char, mensaje
 * @param mensajeError array de char, mensaje de error
 * @param min numero minimo admitido
 * @param max numero maximo admitido
 * @return retorna 0 si todo sale bien, -1 si error
 */
int pedirNumero(int* numero, char* mensaje, char* mensajeError,int min,int max);
/**
 * pide al usuario el numero de legajo del censista y valida que exista
 * @param id puntero a int, id del censista
 * @param censistas puntero a array de censistas
 * @param tam tamaño del array
 * @return retorna -1 si hubo un error, 0 si se pudo cargar correctamente
 */
int pedirCensista(int* id, eCensista* censistas, int tam);
/**
 * pide el id de la vivienda a traves de la funcion buscarIdvivienda y realiza una baja logica
 * @param viviendas puntero a array de viviendas
 * @param tam tamaño del array
 * @param idActual id maximo actual
 * @return retorna 0 si todo sale bien, -1 en caso de error
 */
int darDeBaja(eVivienda* viviendas, int tam, int idActual);
/**
 * muestra por pantalla unavivienda
 * @param vivienda vivienda a mostrar
 * @param tipo puntero a array de caracteres, tipo de vivienda
 * @param censista puntero a array de caracteres, nombre del censista
 */
void mostrarVivienda(eVivienda vivienda, char* tipo, char* censista);
/**
 * lista todas las viviendascargadas
 * @param viviendas puntero a array de viviendas
 * @param tamViv tamaño del array de viviendas
 * @param censistas puntero a array de censistas
 * @param tamCen tamaño del array de censistas
 * @param tipos puntero a array de tipos de casas
 * @param tamTip tamaño del array de tipos
 * @return retorna 0 si todo salio bien, -1 en caso de error
 */
int listarVivienda(eVivienda* viviendas, int tamViv, eCensista* censistas, int tamCen, eTipoVivienda* tipos, int tamTip);
/**
 * ordena un array de viviendas por nombre de calle y ante la igualdad, por cantidad de personas
 * @param viviendas puntero a array de viviendas
 * @param tam tamaño del array
 * @return retorna 0 si todo salio bien, -1 en caso de error
 */
int ordenarViviendas(eVivienda* viviendas, int tam);
/**
 * recibe el id de un tipo de casa y valida que se encuentre
 * @param tipos puntero a array de tipos de casas
 * @param tam tamaño del array
 * @param id id a validar
 * @return retorna -1 en caso de error, la posicion en el array donde se encuentra el id si todo sale bien
 */
int buscarIdTipo(eTipoVivienda* tipos, int tam, int id);

int mostrarCensistaPorViviendas(eCensista* censistas, eVivienda* viviendas,eTipoVivienda* tipos, int tamV, int tamC, int tamT);

int censisitasConMasCensos(eCensista* censistas, eVivienda* viviendas, int tamV);
