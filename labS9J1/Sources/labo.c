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
	root->adj[root->len++] = node;
}

/*
* Programmer l'algorithme de depth first search afin de trouver la cle. 
* Pour programmer cet algorithme, vous avez besoins d'une pile/stack, sa definition est fourni.
* La Stack devrait contenir la liste en ordre inverse de celle parcouru. 
* i.e. si le chemin est A -> B -> C la stack avec son pop devrait retourner C -> B -> A
*/

int dfs(Node* root[], int len, Node* curr, void* key, Stack* s) 
{
	//1 - Push 1st node on stack
	int i = 0;
	stack_push(s, root[i]);

	//2 - mark as visited
	root[i]->visited = 1;

	//3 - for first edge
	 
		//3.1 - Verify if edge leads to key
		
			//3.1.1 - if yes, return 1;
			//break;
			 
		//3.2 - Verify if node is visited
		 
			//3.2.1 - if yes, move to next edge
			
			//3.2.2 - Verify if there is a next edge and if it is visited
			 
			//3.2.3 - If no next or if visited, pop node
			
		 //3.3 - else, push node to stack
		
		 //3.4 -  loop back to 3
}

/*
* Programmer l'algorithme de breath first search afin de trouver la cle. 
* Pour programmer cet algorithme, vous avez besoins d'une file/queue, sa definition est fourni.
* La Stack devrait contenir la liste en ordre du chemin parcouru. 
* i.e. si le chemin est A -> B -> C la stack avec son pop devrait retourner A -> B -> C
*/

int bfs(Node* root[], void* key, Stack* s) 
{
	//1 - Push 1st node to queue

	//2 - While (queue != empty)
	
		//2.1 - pop queue
		
		//2.2 - if popped node == key, break;
		
		//2.3 - Push root.adj
		 
		//2.4 - Mark all adj as visited
		 
			//2.4.1 - assign adj.prev to curr.node
			 
		//2.5 - Loop
		
	//3 - Reconstruct
}

