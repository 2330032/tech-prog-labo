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
	Node* n = (Node*)malloc(sizeof(Node));

	n->data = data;
	memset(n->adj, 0, sizeof(uint8_t) * UINT8_MAX);
	n->visited = 0;
	n->len = 0;
	n->revPath = allocate(sizeof(QNode));
	n->revPath->data = n;
	n->revPath->prev = NULL;

	return n;
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
	if (curr == NULL)
	{
		for (int i = 0; i < len; i++)
		{
			Node* n = root[1];
			int result = dfs(root, len, root[i], key, s);

			if (result)
			{
				return result;
			}
		}
		return 0;
	}
	else
	{
		curr->visited = 1;
		stack_push(s, curr);
		if (curr->data == key)
		{
			return 1;
		}
		for (int j = 0; j < curr->len; j++)
		{
			Node* n = curr->adj[j];
			if (!n->visited)
			{
				int result = dfs(root, len, n, key, s);
				if (result)
				{
					return result;
				}
			}
		}
		stack_pop(s);
		return 0;
	}
}

/*
* Programmer l'algorithme de breath first search afin de trouver la cle.
* Pour programmer cet algorithme, vous avez besoins d'une file/queue, sa definition est fourni.
* La Stack devrait contenir la liste en ordre du chemin parcouru.
* i.e. si le chemin est A -> B -> C la stack avec son pop devrait retourner A -> B -> C
* La fonction doit retourner le nombre de node visiter
*/

int bfs(Node* root[], void* key, Stack* s)
{
	Queue q;
	queue_init(&q);
	queue_push(&q, root[0]);

	while (q.prev != NULL)
	{
		Node* n = queue_pop(&q);
		int end = 0;
		for (int i = 0; i < n->len; i++)
		{
			Node* n_adj = n->adj[i];
			if (!n_adj->visited)
			{
				n_adj->visited = 1;
				queue_push(&q, n_adj);
				n_adj->revPath->prev = n->revPath;
			}
			if (n_adj->data == key)
			{
				end = 1;
				break;
			}
		}
		if (end) 
		{
			break;
		}
	}
	Node* lastNode = q.next->data;
	stack_push(s, lastNode);
	QNode* nq = lastNode->revPath->prev;
	while (nq != NULL) 
	{
		lastNode = nq->data;
		stack_push(s, lastNode);
		nq = lastNode->revPath->prev;
	}
	return s->top;
}