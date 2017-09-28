//////////////////////////////////////////////////////////////////////////////////

/* CE1007/CZ1007 Data Structures
2016/17 S1
Author and Lab Group: WU WEIJIE FSP2
Program name: FSP2_WU WEIJEI
Date: 13 November 2016
Purpose: Implementing the required functions for Assignment 1 (Question 4)*/

//////////////////////////////////////////////////////////////////////////////////

#include <stdio.h>
#include <stdlib.h>

//////////////////////////////////////////////////////////////////////////////////

typedef struct _bstnode {
	int item;
	struct _bstnode *left;
	struct _bstnode *right;
} BSTNode;   // You should not change the definition of BSTNode

typedef struct _stackNode {
	BSTNode *item;
	struct _stackNode *next;
}StackNode; // You should not change the definition of StackNode

typedef struct _stack
{
	StackNode *top;
}Stack; // You should not change the definition of Stack

		///////////////////////// function prototypes ////////////////////////////////////

		// This is for question 4. You should not change the prototypes of these functions
void insertBSTNode(BSTNode **node, int value);
void printPostOrderIterative(BSTNode *root);

// You may use the following functions or you may write your own
void push(Stack *stack, BSTNode *node);
BSTNode * pop(Stack *s);
BSTNode * peek(Stack *s);
int isEmpty(Stack *s);
void removeAll(BSTNode **node);
//void getstack(Stack *s, BSTNode *root);

///////////////////////////// main() /////////////////////////////////////////////

int main()
{
	int c, i;

	//Initialize the Binary Search Tree as an empty Binary Search Tree
	BSTNode *root;
	c = 1;
	root = NULL;

	printf("1:Insert an integer into the binary search tree;\n");
	printf("2:Print the post-order traversal of the binary search tree;\n");
	printf("0:Quit;\n");


	while (c != 0)
	{
		printf("Please input your choice(1/2/0): ");
		scanf("%d", &c);

		switch (c)
		{
		case 1:
			printf("Input an integer that you want to insert into the Binary Search Tree: ");
			scanf("%d", &i);
			insertBSTNode(&root, i);
			break;
		case 2:
			printf("The resulting post-order traversal of the binary search tree is: ");
			printPostOrderIterative(root); // You need to code this function
			printf("\n");
			break;
		case 0:
			removeAll(&root);
			break;
		default:
			printf("Choice unknown;\n");
			break;
		}

	}

	return 0;
}

//////////////////////////////////////////////////////////////////////////////////

void insertBSTNode(BSTNode **node, int value) {
	if (*node == NULL)
	{
		*node = malloc(sizeof(BSTNode));

		if (*node != NULL) {
			(*node)->item = value;
			(*node)->left = NULL;
			(*node)->right = NULL;
		}
	}
	else
	{
		if (value < (*node)->item)
		{
			insertBSTNode(&((*node)->left), value);
		}
		else if (value >(*node)->item)
		{
			insertBSTNode(&((*node)->right), value);
		}
		else
			return;
	}
}

//////////////////////////////////////////////////////////////////////////////////


void printPostOrderIterative(BSTNode *root)
{
	/* add your code here */
	Stack s1,s2;							// Declare stack1 and stack2

	BSTNode *temp;							// Create a temporary BSTNode pointer

	s1.top = NULL;							// Initialise stack1
	s2.top = NULL;							// Initialise stack2

	if (!isEmpty(&s1))						// Check if the stack1 is empty
		removeAll(&s1);						// If no, clear the stack1

	push(&s1, root);						// Push the root to stack1
	
	while (!isEmpty(&s1))					// Check if the top of the stack1 is empty
	{
		temp = pop(&s1);					// Pop the top of the stack1 to the temp pointer
		push(&s2, temp);					// Push the temp to the stack2;

		if (temp->left)						// Check if the left branch is empty
			push(&s1, temp->left);			// Push the left branch address to the stack1
		
		if (temp->right)					// Check if the right branch is empty
			push(&s1, temp->right);			// Push the right branch address to the stack1
	}
	while (!isEmpty(&s2))					// Check if the top of stack2 is empty
	{		
		printf("%d ", pop(&s2)->item);		// If no, print out the value by pop from stack2
	}
}

//void printPostOrderIterative(BSTNode *root)
//{
//	/* add your code here */
//
//	Stack s1,s2;									// declare stack1,and stack2 variables
//
//	s1.top = NULL;									// initialise the s1
//	s2.top = NULL;									// initialise the s2
//	
//	getstack(&s1, root);							// call getstack functon
//
//	while (s1.top!= NULL)							// check if the stack1 is empty
//	{
//		push(&s2, pop(&s1));						//pop the address from stack1 and push it to stack2 to form a reversed order. 
//	}
//
//	while (s2.top !=NULL)							// check if the stack2 is empty
//	{
//		printf ("\n s2 is %d ",pop(&s2)->item);		// print out the value pop from the stack2
//	}
//
//}
//
//void getstack(Stack *s, BSTNode *root)			// using post-order to stock the value in the stack1
//{
//	if (root == NULL) return;						// check if the root is empty
//	
//	getstack(s, root->left);						// recursive way to checking each nodes left and right
//	getstack(s, root->right);
//
//	push(s, root);									// push the value to the stack. 
//}

//////////////////////////////////////////////////////////////////////////////////

void push(Stack *stack, BSTNode *node) 
{
	StackNode *temp;

	temp = malloc(sizeof(StackNode));

	if (temp == NULL)
		return;
	temp->item = node;

	if (stack->top == NULL)
	{
		stack->top = temp;
		temp->next = NULL;
	}
	else
	{
		temp->next = stack->top;
		stack->top = temp;
	}
}


BSTNode* pop(Stack * s)
{
	StackNode *temp, *t;
	BSTNode * ptr;
	ptr = NULL;

	t = s->top;
	if (t != NULL)
	{
		temp = t->next;
		ptr = t->item;

		s->top = temp;
		free(t);
		t = NULL;
	}

	return ptr;
}

BSTNode* peek(Stack * s)
{
	StackNode *temp;
	temp = s->top;
	if (temp != NULL)
		return temp->item;
	else
		return NULL;
}

int isEmpty(Stack *s)
{
	if (s->top == NULL)
		return 1;
	else
		return 0;
}


void removeAll(BSTNode **node)
{
	if (*node != NULL)
	{
		removeAll(&((*node)->left));
		removeAll(&((*node)->right));
		free(*node);
		*node = NULL;
	}
}