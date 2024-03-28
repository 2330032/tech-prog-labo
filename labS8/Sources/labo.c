#include "labo.h"
#include <stdint.h>
#include <assert.h>
#include <stdio.h>
#include <limits.h>


static long long fib_memo[0x7ffffff];


/*
* Programmer l'algorithme de fibonacci.
* Commencer par faire l'algorithme de base et par la suite ajouter la memoization.
* Faire attention lorsque vous utilisez un type pour une variable qui represente un nombre, 
* int ne depasse pas 2^31-1 ou 2,147,483,647
*/
long long fibonacci(int n) {
	if (fib_memo[1] == 0) 
	{
		memset(fib_memo, -1, sizeof(long long) * 0x7ffffff);
	}
	if (n <= 1) {
		return n;
	}

	if (fib_memo[n] == -1) 
	{
		fib_memo[n] = fibonacci(n - 1) + fibonacci(n - 2);
		return fib_memo;
	}
	else
	{
		return fib_memo[n];
	}
}

/*
* Creer un Noeud, assigner lui la valeur de data, mettre ses references a NULL et retourner le noeud.
*/
TreeNode* tree_create_node(void* data) {
	TreeNode t;
	t.data = data;
	t.left = NULL;
	t.right = NULL;

	return &t;
}

/*
* Ajouter le noeud  node dans la propriete left ou right qui est NULL de root.
* On priorise de gauche a droite. Si right et left son NULL on le met dans left.
* Si jamais aucun des noeuds est NULL, ajouter rien.
*/
void tree_add_node(TreeNode* root, TreeNode* node) {
	if (root->left == NULL) 
	{
		root->left = node;
	}
	else if (root->left != NULL && root->right == NULL) 
	{
		root->right = node;
	}
	else if (root->left != NULL && root->right != NULL) 
	{
		return 0;
	}
}

/*
* Programmer l'algorithme de depth first search afin de trouver la cle.
* Pour programmer cet algorithme, vous avez besoins d'une pile/stack, ca definition est fourni.
*/
int dfs(TreeNode* root, void* key)
{
	Stack s = stack_init(sizeof(TreeNode));

}

/*
* Programmer l'algorithme de breath first search afin de trouver la cle.
* Pour programmer cet algorithme, vous avez besoins d'une file/queue, ca definition est fourni.
*/
int bfs(TreeNode* root, void* key)
{

}