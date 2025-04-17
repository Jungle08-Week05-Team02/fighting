//////////////////////////////////////////////////////////////////////////////////

/* CE1007/CZ1007 Data Structures
Lab Test: Section C - Stack and Queue Questions
Purpose: Implementing the required functions for Question 6 */

//////////////////////////////////////////////////////////////////////////////////

#include <stdio.h>
#include <stdlib.h>

#define MIN_INT -1000

//////////////////////////////////////////////////////////////////////////////////

typedef struct _listnode
{
	int item;
	struct _listnode *next;
} ListNode;	// You should not change the definition of ListNode

typedef struct _linkedlist
{
	int size;
	ListNode *head;
} LinkedList;	// You should not change the definition of LinkedList


typedef struct stack{
	LinkedList ll;
} Stack; // You should not change the definition of stack

///////////////////////// function prototypes ////////////////////////////////////

// You should not change the prototypes of these functions
void removeUntil(Stack *s, int value);

void push(Stack *s, int item);
int pop(Stack *s);
int peek(Stack *s);
int isEmptyStack(Stack *s);
void removeAllItemsFromStack(Stack *s);

void printList(LinkedList *ll);
void removeAllItems(LinkedList *ll);
ListNode * findNode(LinkedList *ll, int index);
int insertNode(LinkedList *ll, int index, int value);
int removeNode(LinkedList *ll, int index);

//////////////////////////// main() //////////////////////////////////////////////

int main()
{
	int c, i;
	c = 1;

	LinkedList ll;
	Stack s;

	// Initialize the linked list as an empty linked list
	ll.head = NULL;
	ll.size = 0;

	// Initalize the stack as an empty stack
	s.ll.head = NULL;
	s.ll.size = 0;

	printf("1: Insert an integer into the stack:\n");
	printf("2: Remove values until the given value;\n");
	printf("0: Quit:\n");


	while (c != 0)
	{
		printf("Please input your choice(1/2/0): ");
		scanf("%d", &c);

		switch (c)
		{
		case 1:
			printf("Input an integer that you want to insert into the stack: ");
			scanf("%d", &i);
			push(&s, i);
			printf("The resulting stack is: ");
			printList(&(s.ll));
			break;
		case 2:
		    printf("Enter an integer value in stack to remove values until that value: ");
			scanf("%d", &i);
			removeUntil(&s,i); // You need to code this function
			printf("The resulting stack after removing values until the given value: ");
			printList(&(s.ll));
			removeAllItemsFromStack(&s);
			removeAllItems(&ll);
			break;
		case 0:
			removeAllItemsFromStack(&s);
			removeAllItems(&ll);
			break;
		default:
			printf("Choice unknown;\n");
			break;
		}

	}

	return 0;
}

////////////////////////////////////////////////////////////

void removeUntil(Stack *s, int value)
{
	/* add your code here */
	// 주어진 값이 스택에서 처음 나올 때까지 pop을 반복한다.
	// 해당 값이 스택의 top에 오도록 만들며, 그 이후는 남겨둔다.
	// 값이 스택에 없다면 스택이 완전히 비워진다.

	// 원래 작성했던 코드
	// Use-after-free 가능성 : cur = cur->next로 이동한 뒤 pop(s) 호출하면, 이전에 이동했던 cur가 가리키던 메모리가 해제됨
	// 스택의 top과 cur가 비동기 : cur는 순차적으로 따라가지만, pop(s)은 s->ll.head를 바로 변경하니까, cur는 실제 상태와 다르게 엉뚱한 노드를 따라갈 수 있음
	// 실행 환경에 따라 세그폴트 : 테스트 환경에서는 우연히 잘 돌아갈 수 있지만, 조금만 복잡한 입력이나 최적화 상황에서는 예외가 발생할 수 있음
	// if (s == NULL || s->ll.head == NULL) return;
	// ListNode *cur = s->ll.head;
	// while (cur != NULL && cur->item != value){
	// 	cur = cur->next;
	// 	pop(s);
	// }

	// 매번 pop 전후의 head 상태를 동기화된 상태에서 직접 확인하고 더 이상 노드를 직접 추적할 필요도 없기 때문에 가장 안전하고 예측 가능한 방식
	// 외부 포인터 쓰지 말고 , s->ll.head 기준으로 매번 상태를 확인하며 pop() 하는 방식으로 수정하는 게 좋음
	if (s == NULL || s->ll.head == NULL) return;
    while (!isEmptyStack(s) && peek(s) != value) {
        pop(s);
    }
}

//////////////////////////////////////////////////////////////////////////////////

void removeAllItemsFromStack(Stack *s)
{
	if (s == NULL)
		return;
	while (s->ll.head != NULL)
	{
		pop(s);
	}
}


void removeAllItems(LinkedList *ll)
{
	ListNode *cur = ll->head;
	ListNode *tmp;

	while (cur != NULL){
		tmp = cur->next;
		free(cur);
		cur = tmp;
	}
	ll->head = NULL;
	ll->size = 0;
}

/////////////////////////////////////////////////////////////////////////////////////////

void push(Stack *s, int item)
{
	insertNode(&(s->ll), 0, item);
}

int pop(Stack *s)
{
	int item;
	if (s->ll.head != NULL)
	{
		item = ((s->ll).head)->item;
		removeNode(&(s->ll), 0);
		return item;
	}
	else
		return MIN_INT;
}

int peek(Stack *s){
    if(isEmptyStack(s))
        return MIN_INT;
    else
        return ((s->ll).head)->item;
}

int isEmptyStack(Stack *s)
{
	if ((s->ll).size == 0)
		return 1;
	else
		return 0;
}


void printList(LinkedList *ll){

	ListNode *cur;
	if (ll == NULL)
		return;

	cur = ll->head;
	if (cur == NULL)
		printf("Empty");
	while (cur != NULL)
	{
		printf("%d ", cur->item);
		cur = cur->next;
	}
	printf("\n");
}

ListNode * findNode(LinkedList *ll, int index){

	ListNode *temp;

	if (ll == NULL || index < 0 || index >= ll->size)
		return NULL;

	temp = ll->head;

	if (temp == NULL || index < 0)
		return NULL;

	while (index > 0){
		temp = temp->next;
		if (temp == NULL)
			return NULL;
		index--;
	}

	return temp;
}

int insertNode(LinkedList *ll, int index, int value){

	ListNode *pre, *cur;

	if (ll == NULL || index < 0 || index > ll->size + 1)
		return -1;

	// If empty list or inserting first node, need to update head pointer
	if (ll->head == NULL || index == 0){
		cur = ll->head;
		ll->head = malloc(sizeof(ListNode));
		if (ll->head == NULL)
		{
			exit(0);
		}
		ll->head->item = value;
		ll->head->next = cur;
		ll->size++;
		return 0;
	}


	// Find the nodes before and at the target position
	// Create a new node and reconnect the links
	if ((pre = findNode(ll, index - 1)) != NULL){
		cur = pre->next;
		pre->next = malloc(sizeof(ListNode));
		if (pre->next == NULL)
		{
			exit(0);
		}
		pre->next->item = value;
		pre->next->next = cur;
		ll->size++;
		return 0;
	}

	return -1;
}


int removeNode(LinkedList *ll, int index){

	ListNode *pre, *cur;

	// Highest index we can remove is size-1
	if (ll == NULL || index < 0 || index >= ll->size)
		return -1;

	// If removing first node, need to update head pointer
	if (index == 0){
		cur = ll->head->next;
		free(ll->head);
		ll->head = cur;
		ll->size--;
		return 0;
	}

	// Find the nodes before and after the target position
	// Free the target node and reconnect the links
	if ((pre = findNode(ll, index - 1)) != NULL){

		if (pre->next == NULL)
			return -1;

		cur = pre->next;
		pre->next = cur->next;
		free(cur);
		ll->size--;
		return 0;
	}

	return -1;
}
