#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#include <stdint.h>
#include <assert.h>

#include "labo.h"


/*
* Creer une matrice d'adjacence. Mettre len a 0. Mettre max_size a max_nodes.
* Allouer de la memoire pour le max de noeud specifier i.e. pour graph->nodes.
* Pour chaque noeud de graph->nodes mettre le cost et path_from a UINT8_MAX et
* visited a 0.
* Pour adjGraph, allouer une quantiter de int* relatif a la valeur de max_nodes.
* Dans chaque int* allouer un tableau de int relatif a la valeur max_nodes.
* A chaque index de adjGraph mettez son cout a 0.
* Retourner le graph creer.
*/
AdjMatrix* create_graph(size_t max_nodes)
{
	AdjMatrix* graph = allocate(sizeof(AdjMatrix));

	graph->len = 0;
	graph->max_size = max_nodes;
	graph->nodes = allocate(max_nodes * sizeof(Node));
	graph->adjGraph = allocate(max_nodes * sizeof(int*));

	for (size_t i = 0; i < max_nodes; i++) {
		graph->nodes[i].cost = UINT8_MAX;
		graph->nodes[i].path_from = UINT8_MAX;
		graph->nodes[i].visited = 0;
	}
	for (size_t i = 0; i < max_nodes; i++) {
		graph->adjGraph[i] = allocate(max_nodes * sizeof(int));
		for (size_t j = 0; j < max_nodes; j++) {
			graph->adjGraph[i][j] = 0;
		}
	}
	return graph;
}

/*
* Creer un node, lui attribuer le data et l'ajouter dans la matrice d'adjacence.
*/
void add_node(AdjMatrix* graph, void* data)
{
	Node* newNode = (Node*)malloc(sizeof(Node));

	newNode->data = data;
	newNode->cost = UINT8_MAX;
	newNode->path_from = UINT8_MAX;
	newNode->visited = 0;

	graph->nodes[graph->len] = *newNode;
	graph->len++;
}

/*
* Ajouter un lien dans la matrice d'adjacence, d'un noeud a l'autre noeud, en specifiant le cout y etant relier.
*/
void add_edge(AdjMatrix* graph, int fromNode, int toNode, uint8_t cost)
{
	graph->adjGraph[fromNode][toNode] = cost;
}

/*
* Implementer l'algorithme de dijkstra.
*/
void dijkstra(AdjMatrix* graph, int startNodeIndex, int endNodeIndex, Stack* solvedPath)
{
	uint8_t* distances = (uint8_t*)malloc(graph->len * sizeof(uint8_t));
	for (int i = 0; i < graph->len; i++) {
		distances[i] = UINT8_MAX;
	}

	distances[startNodeIndex] = 0;

	Queue q;
	queue_init(&q);
	queue_push(&q, &graph->nodes[startNodeIndex]);

	int* prev = (int*)malloc(graph->len * sizeof(int));
	for (int i = 0; i < graph->len; i++) {
		prev[i] = -1;
	}

	while (q.count > 0) {
		Node* curr = (Node*)queue_pop(&q);
		if (curr == &graph->nodes[endNodeIndex]) {
			int nodeIndex = endNodeIndex;
			while (nodeIndex != startNodeIndex) {
				stack_push(solvedPath, &graph->nodes[nodeIndex]);
				nodeIndex = prev[nodeIndex];
			}
			stack_push(solvedPath, &graph->nodes[startNodeIndex]);
			break;
		}
		for (int i = 0; i < graph->len; i++) {
			if (graph->adjGraph[curr - graph->nodes][i] > 0) {
				int newDistance = distances[curr - graph->nodes] + graph->adjGraph[curr - graph->nodes][i];
				if (newDistance < distances[i]) {
					distances[i] = newDistance;
					prev[i] = curr - graph->nodes;
					queue_push(&q, &graph->nodes[i]);
				}
			}
		}
	}
}