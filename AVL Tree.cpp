#include<stdio.h>
#include<stdlib.h>

struct node {
	int data; 
	int height; 
	struct node *left = NULL;
	struct node *right = NULL; 
};

struct node *root = NULL; 

struct node *createNode(int value) {
	struct node *newNode = (struct node *)malloc(sizeof(struct node)); 
	newNode->data = value; 
	newNode->height = 1; 
	newNode->left = NULL; 
	newNode->right = NULL; 
	
	return newNode; 
}

int height (struct node *curr) {
	if (curr == NULL) return 0; 
	else return curr->height; 
}

int max (int a, int b) {
	return (a > b) ? a : b; 
}

int getBalance (struct node *curr) {
	if (curr == NULL) return 0; 
	else return height(curr->left) - height(curr->right); 
}

int updateHeight(struct node *curr) {
	return max(height(curr->left), height(curr->right)) + 1; 
}

struct node *leftRotate(struct node *curr) {
	struct node *a = curr->right; 
	struct node *b = a->left; 
	
	a->left = curr; 
	curr->right = b; 
	
	curr->height = updateHeight(curr);  
	a->height = updateHeight(a);
	return a; 
}

struct node *rightRotate(struct node *curr) {
	struct node *a = curr->left; 
	struct node *b = a->right; 
	
	a->right = curr; 
	curr->left = b; 
	
	curr->height = updateHeight(curr); 
	a->height = updateHeight(a);
	
	return a;  
}

struct node *searching(struct node *curr, int value) {
	if (curr == NULL) return NULL; 
	
	if (value < curr->data) return searching(curr->left, value); 
	else if (value > curr->data) return searching(curr->right, value); 
	else if (value == curr->data) return curr; 
}

struct node *insertNode(struct node *curr, int value) {
	if (curr == NULL) return (createNode(value)); 
	
	if (value < curr->data) {
		curr->left = insertNode(curr->left, value); 
	}
	else if (value > curr->data) {
		curr->right = insertNode(curr->right, value);
	}
	else return curr; 
	
	curr->height = updateHeight(curr); 
	
	int balance = getBalance(curr); 
	
	if (balance > 1 && value < curr->left->data) {
		return rightRotate(curr); 
	}
	
	if (balance < -1 && value > curr->right->data) {
		return leftRotate(curr); 
	}
	
	if (balance > 1 && value > curr->left->data) {
		curr->left = leftRotate(curr->left); 
		return rightRotate(curr); 
	}
	
	if (balance < -1 && value < curr->right->data) {
		curr->right = rightRotate(curr->right);
		return leftRotate(curr); 
	}
	
	return curr; 
}

int delExist = 1; 

struct node *getPredecessor(struct node *curr) {
	struct node *temp = curr->left; 
	while (temp->right != NULL) {
		temp = temp->right; 
	}
	return temp; 
}

struct node *deleteNode(struct node *curr, int value) {
	if (curr == NULL) {
		delExist = 0; 
		return NULL;
	}
	
	if (value < curr->data) {
		curr->left = deleteNode(curr->left, value); 
	}
	else if (value > curr->data) {
		curr->right = deleteNode(curr->right, value); 
	}
	else {
		if (curr->left == NULL && curr->right == NULL) {
			free(curr); 
		}
		else if (curr->left == NULL) {
			return curr->right;
		}
		else if (curr->right == NULL) {
			return curr->left; 
		}
		else {
			struct node *temp = getPredecessor(curr); 
			curr->data = temp->data; 
			curr->left = deleteNode(curr->left, temp->data); 
		}
	}
	
	curr->height = updateHeight(curr); 
	int balance = getBalance(curr); 
	
//	if (balance > 1 && height(curr->left->left) - height(curr->left->right) < 0) {
//		curr->left = leftRotate(curr->left); 
//		return rightRotate(curr); 
//	}
//	else if (balance < -1 && height(curr->right->left) - height(curr->right->right) > 0) {
//		curr->right = rightRotate(curr->right); 
//		return leftRotate(curr); 
//	}
//	else if (balance > 1) {
//		return rightRotate(curr); 
//	}
//	else if (balance < -1) {
//		return leftRotate(curr); 
//	}

	if (balance > 1 && getBalance(curr->left) >= 0) {
		return rightRotate(curr); 
	}
	
	if (balance < -1 && getBalance(curr->right) <= 0) {
		return leftRotate(curr); 
	}
	
	if (balance > 1 && getBalance(curr->left) < 0) {
		curr->left = leftRotate(curr->left);
		return rightRotate(curr);
	}
	
	if (balance < -1 && getBalance(curr->right) < 0) {
		curr->right = rightRotate(curr->right);
		return leftRotate(curr);
	}
	
	return curr; 
}

void inorder(int level, struct node *curr) {
	if (curr->left != NULL) inorder(level+1, curr->left);
	printf("Level: %d - Data: %d - Height: %d\n", level, curr->data, curr->height); 
	if (curr->right != NULL) inorder(level+1, curr->right);
}

int main() {
	root = insertNode(root, 30);
    root = insertNode(root, 20);
    root = insertNode(root, 50);
    root = insertNode(root, 10);
    root = insertNode(root, 35);
    root = insertNode(root, 100);
    root = insertNode(root, 33);
    inorder(0,root);
    printf("\n");

    root = deleteNode(root, 30);
    inorder(0,root);
    
	return 0; 
}
