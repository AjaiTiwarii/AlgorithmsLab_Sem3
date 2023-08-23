// Q1. Write a C/C++ program to convert a Binary Search Tree to a Max-Heap containing the same
// elements. In this Max-Heap, all the values in the left subtree of a node should be less than all the
// values in the right subtree of the node.
#include <stdio.h>
#include <stdlib.h>

struct Node {
    int data;
    struct Node* left;
    struct Node* right;
};

struct Node* getNode(int data) {
    struct Node* newNode = (struct Node*)malloc(sizeof(struct Node));
    newNode->data = data;
    newNode->left = newNode->right = NULL;
    return newNode;
}

void inorderTraversal(struct Node* root, int* arr, int* i) {
    if (root == NULL)
        return;

    inorderTraversal(root->left, arr, i);
    arr[(*i)++] = root->data;
    inorderTraversal(root->right, arr, i);
}

void posttoBST(struct Node* root, int* arr, int* i) {
    if (root == NULL)
        return;

    posttoBST(root->left, arr, i);
    posttoBST(root->right, arr, i);

    root->data = arr[(*i)++];
}

void Maxheap(struct Node* root) {
    int arr[100]; 
    int i = 0;
    inorderTraversal(root, arr, &i);

    i = 0;
    posttoBST(root, arr, &i);
}

void postorderTraversal(struct Node* root) {
    if (!root)
        return;

    postorderTraversal(root->left);
    postorderTraversal(root->right);
    printf("%d ", root->data);
}
void inorder(struct Node* root) {
    if (!root)
        return;

    inorder(root->left);
    printf("%d ", root->data);
    inorder(root->right);
    
}

int main() {
    struct Node* root = getNode(4);
    root->left = getNode(2);
    root->right = getNode(6);
    root->left->left = getNode(1);
    root->left->right = getNode(3);
    root->right->left = getNode(5);
    root->right->right = getNode(7);

    Maxheap(root);
    printf("inorder Traversal of Tree:\n");
    inorder(root);
    return 0;
}


// Q2. Write a C/C++ program to convert a Binary Search Tree (BST) to a Binary Tree (BT) such that
// every key of the original BST is changed to key plus sum of all greater keys in BST.

#include<stdio.h>
#include<stdlib.h>

struct node
{
    struct node *left;
    int data;
    struct node *right;
};

struct node *newnode(int data)
{
    struct node* new = (struct node*)malloc(sizeof(struct node));
    new->data=data;
    new->left=NULL;
    new->right=NULL;
    return new;
}

struct node *insert(struct node *root, int data)
{
	if(root==NULL)
	{
		return newnode(data);
	}
	else if(data<root->data)
	{
		root->left=insert(root->left,data);
	
	}
	else
	{
		root->right=insert(root->right,data);
	}
	return root;


}


void addnode(struct node *root, int *sum_ptr)
{
    if (root == NULL)
        return;
 
    addnode(root->right, sum_ptr);
    *sum_ptr = *sum_ptr + root->data;
    root->data = *sum_ptr;
    addnode(root->left, sum_ptr);
}

void addGreaterVal(struct node *root)
{
    int sum = 0;
    addnode(root, &sum);
}


void inorder(struct node *t)
{  
	if(t)
	{
		inorder(t->left);
		printf("%d ",t->data);
		inorder(t->right);
	}
	
}
// void preorder(struct node *t)
// {  
// 	if(t)
// 	{	
// 		printf("%d ",t->data);
// 		preorder(t->left);
// 		preorder(t->right);
// 	}
	
// }
// void postorder(struct node *t)
// {  
// 	if(t)
// 	{
// 		postorder(t->left);
// 		postorder(t->right);
// 		printf("%d ",t->data);
// 	}
	
// }

int main()
{

	struct node *root=NULL;
	root = insert(root,5);
	root = insert(root,2);
	root = insert(root,1);
	root = insert(root,3);
	root = insert(root,8);
	root = insert(root,7);
	root = insert(root,9);
	
	
	
	
    
    printf("In-order=");
    inorder(root);
    printf("\n");
    
    addGreaterVal(root);
 
	printf("In-order=");
    inorder(root);
    printf("\n");

	return 0;

}