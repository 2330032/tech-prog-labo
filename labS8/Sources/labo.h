#include <stdint.h>
#include <assert.h>

void* allocate(size_t size);

typedef struct {
	void** elements;
	int top;
	size_t max;
} Stack;

Stack stack_init(size_t max_size);
void stack_push(Stack* s, void* element);
void* stack_pop(Stack* s);


typedef struct Node Node;
typedef struct TreeNode TreeNode;

typedef struct TreeNode {
	void* data;
	TreeNode* left;
	TreeNode* right;
}TreeNode;

typedef struct Node {
	void* data;
	Node* prev;
	Node* next;
	size_t count;
}Queue;

void queue_init(Queue* q);
void queue_push(Queue* q, void* data);
void* queue_pop(Queue* q);

long long fibonacci(int n);

TreeNode* tree_create_node(void* data);

void tree_add_node(TreeNode* root, TreeNode* node);

int dfs(TreeNode* root, void* key);

int bfs(TreeNode* root, void* key);