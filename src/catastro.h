/*
 * catastro.h
 *
 *  Created on: 16 jun. 2022
 *      Author: nico
 */

#ifndef CATASTRO_H_
#define CATASTRO_H_

typedef struct
{
	int idCatastro;
	char localidad[25];
	int manzana;
	int parcela;
	int isEmpty;
}eCatastro;

#endif /* CATASTRO_H_ */
/**
 *
 * @param catastros
 * @param tam
 * @param idActual
 * @param posCargadas
 * @return
 */
int cargarCatastro(eCatastro* catastros, int tam, int* idActual, int* posCargadas);
/**
 *
 * @param catastros
 * @param tam
 * @param manzana
 * @param localidad
 * @param parcela
 * @param id
 * @param posCargadas
 * @return
 */
int agregarCatastro(eCatastro* catastros, int tam, int manzana, char* localidad, int parcela, int* id, int* posCargadas);
/**
 *
 * @param catastros
 * @param tam
 * @return
 */
int buscarCatastroLibre(eCatastro* catastros, int tam);
/**
 *
 * @param catastros
 * @param tam
 * @param id
 * @return
 */
int buscarIdCatastro(eCatastro* catastros, int tam, int id);
/**
 *
 * @param catastros
 * @param tam
 * @param posCargadas
 * @param idActual
 * @return
 */
int bajaCatastro(eCatastro* catastros, int tam, int* posCargadas, int idActual);
/**
 *
 * @param catastro
 */
void mostrarCatastro(eCatastro catastro);
/**
 *
 * @param catastros
 * @param tam
 * @return
 */
int listarCatastros(eCatastro* catastros, int tam);
/**
 *
 * @param catastros
 * @param tam
 * @param idActual
 * @return
 */
int modificarCatastro(eCatastro* catastros, int tam, int idActual);
/**
 *
 * @param catastros
 * @param tam
 * @return
 */
int ordenarCatastros(eCatastro* catastros, int tam);
/**
 *
 * @param catastros
 * @param tam
 * @param localidad
 * @return
 */
int retornarIdPorLocalidad(eCatastro* catastros, int tam, char* localidad);
