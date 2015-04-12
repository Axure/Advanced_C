



// What is the standard process of tokenization?

// Directly do it is the pratice of primary school students. It is nothing wrong though ^_^



// If the tree is binary, we can use a recursion to evaluate it...

// e.g.

// The hardest part is the priority..

int evaluate(pTreeNode root);
int calculate(char symbol, int left_operand, int right_operand);

int evaluate(pTreeNode root) {
	if (root->pLeft == NULL) return root->value;
	else return calculate(root->symbol, evaluate(root->pLeft), evaluate(root->pRight));
	// How to optimize the cache used for this program? Mayebe we need to use a static cache? STL map may be used 233?
	// No.. A binary tree needs no optimization as there is no repeated visit to any node.

}

int calculate(char symbol, int left_operand, int right_operand) {

}