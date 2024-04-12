#pragma once

#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#include <stdint.h>
#include <assert.h>
#include "labo.h"

/*
* Creer une HashTable,
* assigner lui la valeur max_size,
* allouer de la memoire pour la quantiter de d'information possible dans la liste data.
* Pour chaque index du tableau data, assigner la valeur NULL.
* Retourner ensuite le pointeur vers le HashTable.
*/
HashTable* create_hashtable(size_t max_size) {
	HashTable* hashtable = (HashTable*)allocate(sizeof(HashTable));
	hashtable->max_size = max_size;
	hashtable->data = (void**)allocate(max_size * sizeof(void*));

	for (size_t i = 0; i < max_size; i++) {
		hashtable->data[i] = NULL;
	}
	return hashtable;
}

/*
* Implementer la fonction de hashing tel que vu en classe. Retourner l'index
*/
size_t hash(char* key, size_t max) {
	size_t hash = 0;

	for (size_t i = 0; key[i] != '\0'; i++) {
		hash = (hash + key[i]) % max;
	}
	return hash;
}

/*
* Ajouter la cle dans le hashtable avec la valeur donner.
* Si l'operation reussi retourner 1. 
* Si jamais il y a deja une valeur dans le tableau retourner 0.
*/
int add_kv(HashTable* table, char* key, void* data) {
	size_t i = hash(key, table->max_size);

	if (table->data[i] == NULL) {
		table->data[i] = data;
		return 1; 
	}
	return 0;
}

/*
* Si jamais la cle se retrouve dans le tableau, 
* on assigne la valeur du tableau a NULL et on retourne la valeur qu'il y avait dans le tableau.
* Sinon, on retourne NULL.
*/
void* del_kv(HashTable* table, char* key) {
	size_t i = hash(key, table->max_size);
	
	if (table->data[i] != NULL) {
		void* temp = table->data[i];
		table->data[i] = NULL;
		return temp;
	}
	return NULL;
}

/*
* Si jamais la cle se retrouve dans le tableau,
* on retourne la valeur qu'il y avait dans le tableau.
* Sinon, on retourne NULL.
*/
void* get_value(HashTable* table, char* key) {
	size_t i = hash(key, table->max_size);

	if (table->data[i] != NULL) {
		return table->data[i];
	}
	return NULL;
}