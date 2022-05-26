/*
 * censista.h
 *
 *  Created on: 20 may. 2022
 *      Author: nico
 */

#ifndef CENSISTA_H_
#define CENSISTA_H_

typedef struct
{
	int legajo;
	char nombre[20];
	int edad;
	char telefono[10];
	int isEmpty;
}eCensista;

#endif /* CENSISTA_H_ */

/**
 * recibe un id por parametro y lo busca en un array de censistas
 * @param censistas puntero a array de tipo censista
 * @param tam tamaño del array
 * @param id id del sencista a buscar
 * @return retorna -1 en caso de error, la posicion del censista dentro del array si se encuentra
 */
int buscarIdCensista(eCensista* censistas, int tam, int id);
/**
 * recibe un array de censistas y muestra una lista de todos los censistas
 * @param censistas puntero a array de censistas
 * @param tam tamaño del array
 * @return retorna -1 si hay un error, 0 si todo sale bien
 */
int listarCensistas(eCensista* censistas, int tam);
/**
 * recibe un censista y muestra por pantalla sus datos
 * @param censista censista a mostrar
 */
void mostrarCensista(eCensista censista);
/**
 * carga los datos de un censista
 * @param censistas puntero a array de censistas
 * @param tam tamaño del array
 * @param idActual id actual de censistas
 * @param posCargadas numero de posiciones actualmente cargadas en un array de censistas
 * @return retorna -1 en caso de error, 0 si todo sale bien
 */
int cargarCensista(eCensista* censistas, int tam, int* idActual, int* posCargadas);
/**
 * pide un numero de telefono y lo valida
 * @param telefono puntero a char, telefono
 * @return retorna -1 en caso de error, 0 si todo sale bien
 */
int pedirTelefono(char* telefono);
/**
 * agrega un censista al array de censistas
 * @param censistas  puntero a array de censistas
 * @param tam tamaño del array
 * @param telefono puntero a char, telefono del censista
 * @param nombre puntero a char, nombre del censista
 * @param edad edad del censista
 * @param id id maximo actual de censista
 * @param posCargadas numero de posiciones cargadas en el array
 * @return retorna -1 en caso de error, 0 si todo sale bien
 */
int agregarCensista(eCensista* censistas, int tam, char* telefono, char* nombre, int edad, int* id, int* posCargadas);
/**
 * busca una posicion libre en un array de tipo censista
 * @param censistas puntero a array de censistas
 * @param tam tamaño del array
 * @return retorna -1 en caso de error o la posicion libre si la encuentra
 */
int buscarCensistaLibre(eCensista* censistas, int tam);
/**
 * pide un id al usuario y realiza una baja logica al censista con ese id
 * @param censistas puntero a array de censistas
 * @param tam tamaño del array
 * @param posCargadas numero de posiciones cargadas en el array
 * @param idActual id maximo actual de censista
 * @return retorna -1 en caso de error, 0 si todo sale bien
 */
int bajaCensista(eCensista* censistas, int tam, int* posCargadas, int idActual);
/**
 * pide un id al usuarioy modifica un campo de la persona con ese id
 * @param censistas puntero a array de censistas
 * @param tam tamaño del array
 * @param idActual id maximo actual de censista
 * @return retorna  -1 en caso de error, 0 si todo sale bien
 */
int modificarCensista(eCensista* censistas, int tam, int idActual);
/**
 * inicializa un array de censistas
 * @param censistas puntero a array de censistas
 * @param tam tamaño del array
 * @return retorna -1 en caso de error, 0 si todo sale bien
 */
int inicializarCensista(eCensista* censistas, int tam);

