#pragma once

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <math.h>

#include <stdint.h>
#include <assert.h>
#include "labo.h"


/*
* Creer une matrice d'adjacence. Mettre len a 0. Mettre max_size a max_nodes.
* Allouer de la memoire pour le max de noeud specifier i.e. pour graph->nodes.
* Pour chaque noeud de graph->nodes mettre le cost, graph_group et path_from a UINT8_MAX et visited a 0.
* Pour adjGraph, allouer une quantiter de int* relatif a la valeur de max_nodes.
* Dans chaque int* allouer un tableau de int relatif a la valeur max_nodes.
* A chaque index de adjGraph mettez son cout a 0. 0 indique qu'il n'y a pas d'adjacence.
* Retourner le graph creer.
*/
AdjMatrix* create_graph(size_t max_nodes) {
	AdjMatrix* graph = (AdjMatrix*)allocate(sizeof(AdjMatrix));

	graph->len = 0;
	graph->max_size = max_nodes;
	graph->nodes = (Node*)allocate(max_nodes * sizeof(Node));
	graph->adjGraph = (int**)allocate(max_nodes * sizeof(int*));

	for (size_t i = 0; i < max_nodes; i++) {
		graph->nodes[i].cost = UINT8_MAX;
		graph->nodes[i].graph_group = UINT8_MAX;
		graph->nodes[i].path_from = UINT8_MAX;
		graph->nodes[i].visited = 0;
	}

	for (size_t i = 0; i < max_nodes; i++) {
		graph->adjGraph[i] = (int*)allocate(max_nodes * sizeof(int));
		for (size_t j = 0; j < max_nodes; j++) {
			graph->adjGraph[i][j] = 0;
		}
	}
	return graph;
}

/*
* Creer un node, lui attribuer le data, la position et l'ajouter dans la matrice d'adjacence.
*/
void add_node(AdjMatrix* graph, void* data, Vector2 pos) {
	Node* newNode = (Node*)allocate(sizeof(Node));

	newNode->data = data;
	newNode->position = pos;
	newNode->cost = UINT8_MAX;
	newNode->graph_group = UINT8_MAX;
	newNode->path_from = UINT8_MAX;
	newNode->visited = 0;

	graph->nodes[graph->len] = *newNode;
	graph->len++;
}

/*
* Ajouter un lien dans la matrice d'adjacence, d'un noeud a l'autre noeud,
* en specifiant le cout y etant relier.
*/
void add_edge(AdjMatrix* graph, int fromNode, int toNode, uint8_t cost) {
	graph->adjGraph[fromNode][toNode] = cost;
}

/*
* Construire les groupes de nodes. Faire l'algorithme qui determine l'association entre noeud.
*/
void build_groups(AdjMatrix* graph) {
	uint8_t current_group = 0;
	Stack stack = stack_init(graph->len);

	for (size_t i = 0; i < graph->len; i++) {
		if (graph->nodes[i].graph_group == UINT8_MAX) {
			stack_push(&stack, &graph->nodes[i]);

			while (stack.top >= 0) {
				Node* current = (Node*)stack_pop(&stack);
				current->graph_group = current_group;

				for (size_t j = 0; j < graph->len; j++) {
					if (graph->adjGraph[current - graph->nodes][j] > 0 &&
						graph->nodes[j].graph_group == UINT8_MAX) {
						stack_push(&stack, &graph->nodes[j]);
					}
				}
			}
			current_group++;
		}
	}
}

/*
* Implementer l'algorithme A*.
* Lorsqu'il n'y a aucun chemin entre deux node, la Stack doit être vide.
*/
void astar(AdjMatrix* graph, int startNodeIndex, int endNodeIndex, Stack* solvedPath) {
	uint8_t* distances = (uint8_t*)malloc(graph->len * sizeof(uint8_t));
	for (int i = 0; i < graph->len; i++) {
		distances[i] = UINT8_MAX;
	}
	distances[startNodeIndex] = 0;

	int* prev = (int*)malloc(graph->len * sizeof(int));
	for (int i = 0; i < graph->len; i++) {
		prev[i] = -1;
	}

	Queue openSet;
	queue_init(&openSet);
	queue_push(&openSet, &graph->nodes[startNodeIndex]);
	while (openSet.count > 0) {

		Node* current = (Node*)queue_pop(&openSet);

		if (current == &graph->nodes[endNodeIndex]) {
			int nodeIndex = endNodeIndex;
			while (nodeIndex != startNodeIndex) {
				stack_push(solvedPath, &graph->nodes[nodeIndex]);
				nodeIndex = prev[nodeIndex];
			}
			stack_push(solvedPath, &graph->nodes[startNodeIndex]);
			break;
		}

		for (int i = 0; i < graph->len; i++) {
			if (graph->adjGraph[current - graph->nodes][i] > 0) {
				Node* neighbor = &graph->nodes[i];
				uint8_t tentative_gScore = distances[current - graph->nodes] + graph->adjGraph[current - graph->nodes][i];

				if (tentative_gScore < distances[i]) {
					prev[i] = current - graph->nodes;
					distances[i] = tentative_gScore;

					double dx = neighbor->position.x - graph->nodes[endNodeIndex].position.x;
					double dy = neighbor->position.y - graph->nodes[endNodeIndex].position.y;
					double heuristic = sqrt(dx * dx + dy * dy); //pythagoras

					queue_push(&openSet, neighbor);
				}
			}
		}
	}
}