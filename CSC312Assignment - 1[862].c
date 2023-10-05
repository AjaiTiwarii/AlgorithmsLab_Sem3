//  Ques1 - checking for balanced paranthesis expression using stack

#include <stdio.h>
#include <stdlib.h>

struct node
{
    char data;
    struct node *next;
} *start = NULL, *top = NULL;

void push(char x)
{
    struct node *newnode = (struct node *)malloc(sizeof(struct node));
    newnode->next = NULL;
    newnode->data = x;
    if (start == NULL)
    {
        start = newnode;
        top=start;
    }
    else
    {
        top = start;
        while (top->next != NULL)
            top = top->next;
        top->next = newnode;
        top = top->next;
    }
}

char pop()
{
    if (top == NULL)
    {
        //printf("Stack underflow\n");
        return '\0';
    }
    else if (top != start)
    {
        char value;
        struct node *p = start;
        while (p->next != top)
            p = p->next;
        value = top->data;
        p->next = NULL;
        free(top);
        top = p;
        return value;
    }
    else
    {
        char value = start->data;
        free(start);
        start=NULL;
        top=NULL;
        return value;
    }
}

int main(){
    int n=50,flag=0;
    char *exp;
    exp = (char *)malloc(n * sizeof(char));
    printf("enter the expression = ");
    scanf("%s",exp);
    while(*exp!='\0'){
        if(*exp == '[' || *exp == '(' || *exp == '{'){
            push(*exp);
        }
        if(*exp ==')'){
            char c = pop();
            if(c!='(' || c=='\0'){
                flag=1;
                printf("The given expression has unmatched paranthesis\n");
                break;
            }
        }
        if(*exp ==']'){
            char c = pop();
            if(c!='[' || c=='\0'){
                flag=1;
                printf("The given expression has unmatched paranthesis\n");
                break;
            }
        }
        if(*exp=='}'){
            char c = pop();
            if(c!='{' || c=='\0'){
                flag=1;
                printf("The given expression has unmatched paranthesis\n");
                break;
            }
        }
        exp++;
    }
    if(flag==0){
        if(top==NULL) printf("the given expression has balanced paranthesis");
        else printf("the given expression has unbalanced paranthesis");
    }

    return 0;
}




// Ques 2 - palindrome checking program using stack and queue


// #include <stdio.h>
// #include <stdlib.h>
// #include <string.h>

// struct QueueNode
// {
//     char data;
//     struct QueueNode *next;
// };
// struct StackNode
// {
//     char data;
//     struct StackNode *next;
// };
// struct Queue
// {
//     struct QueueNode *front;
//     struct QueueNode *rear;
// };

// struct QueueNode *createQueueNode(char data)
// {
//     struct QueueNode *newNode = (struct QueueNode *)malloc(sizeof(struct QueueNode));
//     if (newNode == NULL)
//     {
//         printf("Memory allocation error.\n");
//         exit(EXIT_FAILURE);
//     }
//     newNode->data = data;
//     newNode->next = NULL;
//     return newNode;
// }

// struct Queue *createQueue()
// {
//     struct Queue *queue = (struct Queue *)malloc(sizeof(struct Queue));
//     if (queue == NULL)
//     {
//         printf("Memory allocation error.\n");
//         exit(EXIT_FAILURE);
//     }
//     queue->front = NULL;
//     queue->rear = NULL;
//     return queue;
// }

// int isQueueEmpty(struct Queue *queue)
// {
//     return queue->front == NULL;
// }

// void enqueue(struct Queue *queue, char data)
// {
//     struct QueueNode *newNode = createQueueNode(data);
//     if (isQueueEmpty(queue))
//     {
//         queue->front = queue->rear = newNode;
//     }
//     else
//     {
//         queue->rear->next = newNode;
//         queue->rear = newNode;
//     }
// }

// char dequeue(struct Queue *queue)
// {
//     if (isQueueEmpty(queue))
//     {
//         printf("Queue is empty.\n");
//         exit(EXIT_FAILURE);
//     }
//     struct QueueNode *temp = queue->front;
//     char data = temp->data;
//     queue->front = queue->front->next;
//     if (queue->front == NULL)
//     {
//         queue->rear = NULL;
//     }
//     free(temp);
//     return data;
// }

// struct StackNode *createStackNode(char data)
// {
//     struct StackNode *newNode = (struct StackNode *)malloc(sizeof(struct StackNode));
//     if (newNode == NULL)
//     {
//         printf("Memory allocation error.\n");
//         exit(EXIT_FAILURE);
//     }
//     newNode->data = data;
//     newNode->next = NULL;
//     return newNode;
// }

// int isStackEmpty(struct StackNode *top)
// {
//     return top == NULL;
// }

// void push(struct StackNode **top, char data)
// {
//     struct StackNode *newNode = createStackNode(data);
//     newNode->next = *top;
//     *top = newNode;
// }

// char pop(struct StackNode **top)
// {
//     if (isStackEmpty(*top))
//     {
//         printf("Stack is empty.\n");
//         exit(EXIT_FAILURE);
//     }
//     struct StackNode *temp = *top;
//     char data = temp->data;
//     *top = temp->next;
//     free(temp);
//     return data;
// }

// int isPalindrome(char *str)
// {
//     struct Queue *Q1 = createQueue();
//     struct StackNode *S = NULL;

//     int len = strlen(str);
//     for (int i = 0; i < len; i++)
//     {
//         char ch = str[i];
//         enqueue(Q1, ch);
//         push(&S, ch);
//     }

//     while (!isQueueEmpty(Q1) && !isStackEmpty(S))
//     {
//         char q_ch = dequeue(Q1);
//         char s_ch = pop(&S);
//         if (q_ch != s_ch)
//         {
//             return 0;
//         }
//     }
//     return isQueueEmpty(Q1) && isStackEmpty(S);
// }

// int main()
// {
//     char input[100];
//     printf("Enter a string: ");
//     scanf("%s", input);

//     if (isPalindrome(input))
//     {
//         printf("The input string is a palindrome");
//     }
//     else
//     {
//         printf("The input string is not a palindrome");
//     }

//     return 0;
// }