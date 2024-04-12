#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "labo.h"

Stack stack_init(size_t max_size) {
	Stack s;
	s.max = max_size;
	s.top = -1;
	s.elements = allocate(sizeof(void*) * s.max);
	return s;
}

void stack_push(Stack* s, void* element) {
	if (s->max != s->top + 1) {
		s->top++;
		s->elements[s->top] = element;
	}
}

void* stack_pop(Stack* s) {
	if (s->top > -1) {
		void* elem = s->elements[s->top];
		s->elements[s->top] = NULL;
		--s->top;
		return elem;
	}
	return NULL;
}
void queue_init(Queue* q) {
	q->next = q->prev = NULL;
	q->count = 0;
}
void queue_push(Queue* q, void* data) {
	QNode* n = allocate(sizeof(QNode));
	n->data = data;
	n->prev = n->next = NULL;
	if (q->prev == NULL) {
		q->prev = q->next = n;
	}
	else {
		QNode* temp = q->next;
		q->next = temp->prev = n;
		n->next = temp;
	}
}
void* queue_pop(Queue* q) {
	if (q->prev != NULL) {
		QNode* temp = q->prev;
		if(temp->prev != NULL)
			temp->prev->next = NULL;
		q->prev = temp->prev;
		q->count++;
		return temp->data;
	}
	return NULL;
}

#define HEAP_SIZE 2048 * 2048 * 4
static uint8_t* heap = NULL;
static size_t heap_top = 0;
void* allocate(size_t size) {
	size_t old_top = heap_top;
	heap_top += size;
	assert(heap_top <= HEAP_SIZE);
	return &heap[old_top];
}

int main(int argc, char** argv) {
	heap = (uint8_t*)malloc(HEAP_SIZE);
	assert(heap != NULL);
	
	printf("-----FIRST-----\n");

	AdjMatrix* graph = create_graph(10);
	
	{
		Vector2 pos = { .x = 1.0,.y = 3.0 };
		add_node(graph, "A", pos);//0
		add_edge(graph, 0, 3, 10);
		add_edge(graph, 0, 2, 5);
		add_edge(graph, 0, 1, 2);
	}
	
	{
		Vector2  pos = { .x = 0.0,.y = 5.0 };
		add_node(graph, "B",pos);//1
		//add_edge(graph, 1, 3, 3);
		add_edge(graph, 1, 3, 8);
		add_edge(graph, 1, 2, 2);
	}
	
	{
		Vector2  pos = { .x = 3.0,.y = 5.0 };
		add_node(graph, "C",pos);//2
		add_edge(graph, 2, 3, 5);
		add_edge(graph, 2, 4, 3);
	}

	{
		Vector2 pos = { .x = 9.0,.y = 11.0 };
		add_node(graph, "D",pos);//3
		//add_edge(graph, 3, 4, 1);
		add_edge(graph, 3, 4, 8);
		add_edge(graph, 3, 5, 2);
	}
	
	{
		Vector2  pos = { .x = 5.0,.y = 7.0 };
		add_node(graph, "E",pos);//4
		add_edge(graph, 4, 3, 8);
		add_edge(graph, 4, 5, 2);
	}

	{
		Vector2  pos = { .x = 10.0,.y = 15.0 };
		add_node(graph, "F",pos);//5
	}

	{
		Vector2  pos = { .x = -3.0,.y = 5.0 };
		add_node(graph, "G", pos);//6
		add_edge(graph, 6, 7, 5);
		add_edge(graph, 6, 8, 3);
	}

	{
		Vector2 pos = { .x = -9.0,.y = 11.0 };
		add_node(graph, "H", pos);//7
		add_edge(graph, 3, 4, 1);
		add_edge(graph, 7, 8, 8);
		add_edge(graph, 7, 9, 2);
	}

	{
		Vector2  pos = { .x = -5.0,.y = 7.0 };
		add_node(graph, "I", pos);//8
		add_edge(graph, 8, 7, 8);
		add_edge(graph, 8, 9, 2);
	}

	{
		Vector2  pos = { .x = -10.0,.y = 15.0 };
		add_node(graph, "J", pos);//9
	}
	

	Stack s = stack_init(6);
	Queue tq;
	queue_init(&tq);

	astar(graph, 0, 5, &s);
	Node* n = stack_pop(&s);
	queue_push(&tq, n);
	while (n != NULL) {
		printf("      %s", (char*)n->data);
		n = stack_pop(&s);
		if (n != NULL) {
			queue_push(&tq, n);
			printf(" ->");
		}
	}
	printf("\n");
	n = queue_pop(&tq);
	while (n != NULL) {
		printf("cost: %i | ", n->cost);
		n->path_from = UINT8_MAX;
		n->cost = UINT8_MAX;
		n->visited = 0;
		n = queue_pop(&tq);
	}
	printf("\n");

	printf("-----SECOND-----\n");
	build_groups(graph);
	astar(graph, 0, 6, &s);
	if (s.top != -1 || graph->nodes[0].graph_group == graph->nodes[6].graph_group) {
		printf("La Stack n'est pas vide mais il n'y a pas de chemin entre A et G.\nTu as potentiellement un probleme avec ta fonction build_groups\n");
	}
	else {
		printf("Tu as potentiellement bien programmer build_groups\n");
	}

	printf("-----THIRD-----\n");
	astar(graph, 6, 9, &s);
	n = stack_pop(&s);
	queue_push(&tq, n);
	while (n != NULL) {
		printf("      %s", (char*)n->data);
		n = stack_pop(&s);
		if (n != NULL) {
			queue_push(&tq, n);
			printf(" ->");
		}
	}
	printf("\n");
	n = queue_pop(&tq);
	while (n != NULL) {
		printf("cost: %i | ", n->cost);
		n->path_from = UINT8_MAX;
		n->cost = UINT8_MAX;
		n->visited = 0;
		n = queue_pop(&tq);
	}
	printf("\n");

	return 0;
}
