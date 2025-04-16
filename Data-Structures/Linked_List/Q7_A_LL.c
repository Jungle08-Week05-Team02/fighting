//////////////////////////////////////////////////////////////////////////////////

/* CE1007/CZ1007 Data Structures
Lab Test: Section A - Linked List Questions
Purpose: Implementing the required functions for Question 7 */

//////////////////////////////////////////////////////////////////////////////////

#include <stdio.h>
#include <stdlib.h>

//////////////////////////////////////////////////////////////////////////////////

typedef struct _listnode
{
	int item;
	struct _listnode *next;
} ListNode;			// You should not change the definition of ListNode

typedef struct _linkedlist
{
	int size;
	ListNode *head;
} LinkedList;			// You should not change the definition of LinkedList


//////////////////////// function prototypes /////////////////////////////////////

// You should not change the prototype of this function
void RecursiveReverse(ListNode **ptrHead);

void printList(LinkedList *ll);
void removeAllItems(LinkedList *ll);
ListNode * findNode(LinkedList *ll, int index);
int insertNode(LinkedList *ll, int index, int value);
int removeNode(LinkedList *ll, int index);


//////////////////////////// main() //////////////////////////////////////////////

int main()
{
	LinkedList ll;
	int c, i, j;
	c = 1;
	//Initialize the linked list 1 as an empty linked list
	ll.head = NULL;
	ll.size = 0;

	    // 정수 1, 2, 3, 4, 5를 저장할 노드들을 동적 할당하여 생성
		ListNode *node1 = (ListNode *)malloc(sizeof(ListNode));
		ListNode *node2 = (ListNode *)malloc(sizeof(ListNode));
		ListNode *node3 = (ListNode *)malloc(sizeof(ListNode));
		ListNode *node4 = (ListNode *)malloc(sizeof(ListNode));
		ListNode *node5 = (ListNode *)malloc(sizeof(ListNode));
	
		// 각 노드에 값 할당
		node1->item = 1;
		node2->item = 2;
		node3->item = 3;
		node4->item = 4;
		node5->item = 5;
	
		// 노드들을 연결하여 리스트 구성
		node1->next = node2;
		node2->next = node3;
		node3->next = node4;
		node4->next = node5;
		node5->next = NULL;
	
		// LinkedList의 헤드를 첫 번째 노드로 설정하고, 크기를 업데이트
		ll.head = node1;
		ll.size = 5;

	printf("1: Insert an integer to the linked list:\n");
	printf("2: Reversed the linked list:\n");
	printf("0: Quit:\n");

	while (c != 0)
	{
		printf("Please input your choice(1/2/0): ");
		scanf("%d", &c);

		switch (c)
		{
		case 1:
			printf("Input an integer that you want to add to the linked list: ");
			scanf("%d", &i);
			j = insertNode(&ll, ll.size, i);
			printf("The resulting linked list is: ");
			printList(&ll);
			break;
		case 2:
			RecursiveReverse(&(ll.head)); // You need to code this function
			printf("The resulting linked list after reversed the given linked list is: ");
			printList(&ll);
			removeAllItems(&ll);
			break;
		case 0:
			removeAllItems(&ll);
			break;
		default:
			printf("Choice unknown;\n");
			break;
		}
	}
	return 0;
}

////////////////////////////////////////////////////////////////////////

void RecursiveReverse(ListNode **ptrHead)
{
	// 1. 기저 조건: 리스트가 비어있거나 노드가 하나만 있으면 그대로 반환
	if (*ptrHead == NULL || (*ptrHead)->next == NULL)
	return;
	// 2. 첫 번째 노드를 first, 그 다음 노드부터의 리스트를 rest로 분리
	ListNode *first = *ptrHead;
	ListNode *rest = first->next;
	// 3. rest(나머지 리스트)에 대해 재귀 호출로 뒤집기
	RecursiveReverse(&rest);

	// 4. 재귀 호출 후, 'first' 노드를 뒤집힌 리스트의 가장 뒤쪽에 연결하기 위해서
	//    먼저, 현재 first의 바로 다음 노드(기존 first->next)의 next가 first를 가리키도록 함
	first->next->next = first;
	// 5. first의 next를 NULL로 설정하여 기존 연결을 끊음 (first가 새 리스트의 마지막 노드가 됨)
	first->next = NULL;
	// 6. 최종적으로, ptrHead가 새로운 리스트의 헤드(rest)를 가리키도록 업데이트
	*ptrHead = rest;
}

//////////////////////////////////////////////////////////////////////////////////

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
