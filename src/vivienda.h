/*
 * vivienda.h
 *
 *  Created on: 20 may. 2022
 *      Author: nico
 */

#ifndef VIVIENDA_H_
#define VIVIENDA_H_

#include "censista.h"
#include "catastro.h"

typedef struct
{
	int idVivienda;
	char calle[25];
	int cantPersonas;
	int cantHabitaciones;
	int tipoVivienda;
	int legajoCensista;
	int idCatastro;
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
int cargarVivienda(eVivienda* viviendas, eCensista* censistas, eCatastro* catastros, int tamViv, int tamCen, int tamCat, int* idActual);
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
int agregarVivienda(eVivienda* viviendas,char* calle,int personas,int habitaciones,int idCensista, int idCatastro, int tipo,int tam,int* idActual);
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
void mostrarVivienda(eVivienda vivienda, char* tipo, char* censista, eCatastro catastro);
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

/**
 *pide al usuario el id del catastro y valida que exista
 * @param id id del catastro
 * @param catastros array de catastros
 * @param tam tamaño del array
 * @return retorna -1 si hubo error, 0 si todo ok
 */
int pedirCatatastro(int* id, eCatastro* catastros, int tam);
/**
 *pide al usuario una opcion e informa lo seleccionado
 * @param viviendas array de viviendas
 * @param tamViv tamaño del array de viviendas
 * @param censistas array de censistas
 * @param tamCen tamaño del array de censistas
 * @param catastros array de catastros
 * @param tamCat tamaño del array de catastros
 * @param tipos array de tipos de viviendas
 * @param tamTip tamaño del array de tipos
 * @return retorna -1 si hubo un error, 0 si todo ok
 */
int informar(eVivienda* viviendas, int tamViv, eCensista* censistas, int tamCen, eCatastro* catastros, int tamCat, eTipoVivienda* tipos, int tamTip);
/**
 * recorre un array de viviendas e informa la cantidad de viviendas que hay del tipo seleccionado
 * @param viviendas array de viviendas
 * @param tamViv tamaño del array de viviendas
 * @param idTipo id del tipo de vivienda a contar
 * @return retorna -1 si hubo error, >= 0 si todo ok
 */
int cantidadCensadaPorTipo(eVivienda* viviendas, int tamViv, int idTipo);
/**
 * informa la cantidad de viviendas censadas de cierto tipo y localidad seleccionados
 * @param viviendas array de viviendas
 * @param catastros array de catastros
 * @param tamViv tamaño del array de viviendas
 * @param tamCat tamaño del array de catastros
 * @param idTipo id del tipo de vivienda a contar
 * @param localidad id de la localidad
 * @return retorna -1 si hubo un error, >= 0 si todo ok
 */
int cantidadCensadaPorTipoYLocalidad(eVivienda* viviendas, eCatastro* catastros, int tamViv, int tamCat, int idTipo, int localidad);
/**
 *recorre un array de viviendas e informa la cantidad de viviendas que hay de la localidad seleccionada
 * @param viviendas array de viviendas
 * @param catastros array de catastros
 * @param tamViv tamaño del array de viviendas
 * @param tamCat tamaño del array de catastros
 * @param localidad id de la localidad
 * @return retorna -1 si hubo un error, >= 0 si todo ok
 */
int cantidadCensadaPorLocalidad(eVivienda* viviendas, eCatastro* catastros, int tamViv, int tamCat, int localidad);

/**
 * recibe un puntero a funcion y lista todas las viviendas
 * @param viviendas array de viviendas
 * @param tamViv tamaño del array de viviendas
 * @param censistas array de censistas
 * @param tamCen tamaño del array de censistas
 * @param catastros array de catastros
 * @param tamCat tamaño del array de catastros
 * @param tipos array de tipos de viviendas
 * @param tamTip tamaño del array de tipos
 * @param pFunc puntero a funcion
 * @param num numero a dar como parametro de la funcion
 * @return retorna -1 si hubo un error, 0 si todo ok
 */
int listarViviendas(eVivienda* viviendas, int tamViv, eCensista* censistas, int tamCen, eCatastro* catastros, int tamCat, eTipoVivienda* tipos, int tamTip, int (*pFunc)(eVivienda,int),int num);
/**
 * valida que una vivienda sea del tipo dado como parametro
 * @param vivienda vivienda a validar
 * @param tipo id del tipo de vivienda a validar
 * @return retorna 1 si la validacion fue correcta, 0 si no lo fue
 */
int validarTipo(eVivienda vivienda, int tipo);
/**
 * valida el campo legajoCensista de una vivienda dado como parametro
 * @param vivienda vivienda a validar
 * @param id id del censista a validar
 * @return retorna 1 si la validacion fue correcta, 0 si no lo fue
 */
int validarCensista(eVivienda vivienda, int id);
/**
 *valida el campo idcatastro de una vivienda dado como parametro
 * @param vivienda vivienda a validar
 * @param id id del catastro a validar
 * @return retorna 1 si la validacion fue correcta, 0 si no lo fue
 */
int validarLocalidad(eVivienda vivienda, int id);
/**
 *valida el campo isempty de una vivienda dado como parametro
 * @param vivienda vivienda a validar
 * @param empty valor del campo isEmpty a validar
 * @return retorna 1 si la validacion fue correcta, 0 si no lo fue
 */
int validarEmpty(eVivienda vivienda, int empty);
