#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#include <stdint.h>
#include <assert.h>
#include "labo.h"

/*
* Creer un Noeud, assigner lui la valeur de data, faite un memset 0 sur adj, visited a faux, len a 0, 
* allouer de la memoire pour le QNode et assurer vous de mettre la propiete prev de QNode a NULL.
* Retourner ensuite le pointeur vers le Node.
*/
Node* create_node(void* data) 
{
	Node n;

	n.data = data; 
	memset(n.adj, 0, sizeof(uint8_t)*UINT8_MAX);
	n.visited = 0;
	n.len = 0;
	n.revPath = allocate(sizeof(QNode));
	n.revPath->prev = NULL;

	return &n;
}

/*
* Ajouter le node dans la liste d'adjacence de root.
*/
void add_adjacent_node(Node* root, Node* node) 
{

}

/*
* Programmer l'algorithme de depth first search afin de trouver la cle. 
* Pour programmer cet algorithme, vous avez besoins d'une pile/stack, sa definition est fourni.
* La Stack devrait contenir la liste en ordre inverse de celle parcouru. 
* i.e. si le chemin est A -> B -> C la stack avec son pop devrait retourner C -> B -> A
*/

int dfs(Node* root[], int len, Node* curr, void* key, Stack* s) {}

/*
* Programmer l'algorithme de breath first search afin de trouver la cle. 
* Pour programmer cet algorithme, vous avez besoins d'une file/queue, sa definition est fourni.
* La Stack devrait contenir la liste en ordre du chemin parcouru. 
* i.e. si le chemin est A -> B -> C la stack avec son pop devrait retourner A -> B -> C
*/

int bfs(Node* root[], void* key, Stack* s) {}

