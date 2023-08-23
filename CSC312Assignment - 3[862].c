#include <stdio.h>
#include <stdlib.h>

struct node
{
    int data;
    struct node *left;
    struct node *right;
}*root = NULL;
struct node* ptr = NULL;

struct node* createNode(int item) {
    struct node* newNode = (struct node*)malloc(sizeof(struct node));
    newNode->data = item;
    newNode->left = NULL;
    newNode->right = NULL;
    return newNode;
}

struct node* createBST(struct node* root, int item) {
    struct node* newNode = createNode(item);
    if (root == NULL) {
        root = newNode;
        return root;
    }

    struct node* current = root;
    struct node* parent = NULL;

    while (current != NULL) {
        parent = current;
        if (item < current->data) {
            current = current->left;
        } else {
            current = current->right;
        }
    }

    if (item < parent->data) {
        parent->left = newNode;
    } else {
        parent->right = newNode;
    }

    return root;
}

void inorderTraversal(struct node* root) {
    if (root != NULL) {
        inorderTraversal(root->left);
        printf("%d ", root->data);
        inorderTraversal(root->right);
    }
}


void smallestbst(struct node* root) {
    if (root == NULL) {
        printf("Tree is empty\n");
        return;
    }

    if (root->left == NULL) {
        printf("Smallest element is: %d\n", root->data);
        return;
    }

    smallestbst(root->left);
}


void largestbst(struct node* root){
    if (root == NULL) {
        printf("Tree is empty\n");
        return;
    }

    if (root->right == NULL) {
        printf("largest element is: %d\n", root->data);
        return;
    }

    largestbst(root->right);
}


struct node* minValueNode(struct node* node) {
    struct node* current = node;
    while (current && current->left != NULL) {
        current = current->left;
    }
    return current;
}


struct node* deleteNode(struct node* root, int key) {
    if (root == NULL) {
        return root;
    }

    if (key < root->data) {
        root->left = deleteNode(root->left, key);
    } else if (key > root->data) {
        root->right = deleteNode(root->right, key);
    } else {
        if (root->left == NULL) {
            struct node* temp = root->right;
            free(root);
            return temp;
        } else if (root->right == NULL) {
            struct node* temp = root->left;
            free(root);
            return temp;
        }

        struct node* temp = minValueNode(root->right);
        root->data = temp->data;
        root->right = deleteNode(root->right, temp->data);
    }
    return root;
}

void inorderArray(struct node *root,int *a,int *index)
{
    if(root!=NULL){
        inorderArray(root->left,a,index);
        a[(*index)++] = root->data;
        inorderArray(root->right,a,index);
    }
}

void searchanodebst(int *a,int item)
{
    int found=0,pos;
    for(int i=0;i<8;i++)
    {
        if(a[i]==item)
        {
         found=1;
         pos=i;
         break;
        }
    }
    if(found==1)
     printf("Element %d item present at index %d",item,pos);
    else
     printf("Element %d not present ",item);
}


int main() {
    int x, item;
    int a[20], index = 0;
    do {
        printf("\n1. Create a binary search tree\n");
        printf("2. Find the smallest element\n");
        printf("3. Find the largest element\n");
        printf("4. Search a node in the BST\n");
        printf("5. Deleting a node from the BST\n");
        printf("6. Inorder traversal\n");
        printf("7. Exit from the program\n");
        printf("Enter your option: ");
        scanf("%d", &x);

        switch (x) {
            case 1:
                printf("Enter -1 to terminate\n");
                printf("Enter the data item: ");
                scanf("%d", &item);
                while (item != -1) {
                    root = createBST(root, item);
                    printf("Enter the data item: ");
                    scanf("%d", &item);
                }
                printf("\nBinary tree is created\n");
                break;

            case 2:
                
                smallestbst(root);
                break;

            case 3:
                
                largestbst(root);
                break;


            case 4:
                printf("Which element you want to search: ");
                scanf("%d", &item);
                inorderArray(root,a,&index);
                searchanodebst(a, item);
                break;

            case 5:
                printf("Which element you want to delete");
                scanf("%d", &item);
                root = deleteNode(root, item);
                break;

            case 6:
                if (root == NULL)
                    printf("\nIn-order Traversal: Binary tree is empty\n");
                else {
                    printf("\nIn-order Traversal:\n");
                    inorderTraversal(root);
                    printf("\n");
                }
                break;

            case 7:
                printf("Exiting the program.\n");
                break;

            default:
                printf("Invalid option\n");
        }
    } while (x != 7);

    return 0;
}





