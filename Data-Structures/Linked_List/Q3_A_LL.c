//////////////////////////////////////////////////////////////////////////////////

/* CE1007/CZ1007 Data Structures
Lab Test: Section A - Linked List Questions
Purpose: Implementing the required functions for Question 3 */

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
void moveOddItemsToBack(LinkedList *ll);

void printList(LinkedList *ll);
void removeAllItems(LinkedList *ll);
ListNode * findNode(LinkedList *ll, int index);
int insertNode(LinkedList *ll, int index, int value);
int removeNode(LinkedList *ll, int index);

void createHardCodedList(LinkedList *ll) {
    // 2, 3, 4, 7, 15, 18 값을 가진 노드를 순차적으로 연결
    ListNode *node1 = (ListNode *)malloc(sizeof(ListNode));
    node1->item = 1;
    node1->next = NULL;

    ListNode *node2 = (ListNode *)malloc(sizeof(ListNode));
    node2->item = 3;
    node2->next = NULL;

    ListNode *node3 = (ListNode *)malloc(sizeof(ListNode));
    node3->item = 5;
    node3->next = NULL;

    // ListNode *node4 = (ListNode *)malloc(sizeof(ListNode));
    // node4->item = 7;
    // node4->next = NULL;

    // ListNode *node5 = (ListNode *)malloc(sizeof(ListNode));
    // node5->item = 15;
    // node5->next = NULL;

    // ListNode *node6 = (ListNode *)malloc(sizeof(ListNode));
    // node6->item = 18;
    // node6->next = NULL;

    // 연결 리스트 구성
    ll->head = node1;
    node1->next = node2;
    node2->next = node3;
    // node3->next = node4;
    // node4->next = node5;
    // node5->next = node6;
    ll->size = 6;
}

//////////////////////////// main() //////////////////////////////////////////////

int main()
{
	LinkedList ll;
	int c, i, j;
	c = 1;
	//Initialize the linked list 1 as an empty linked list
	ll.head = NULL;
	ll.size = 0;

	createHardCodedList(&ll);

	printf("1: Insert an integer to the linked list:\n");
	printf("2: Move all odd integers to the back of the linked list:\n");
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
			moveOddItemsToBack(&ll); // You need to code this function
			printf("The resulting linked list after moving odd integers to the back of the linked list is: ");
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

//////////////////////////////////////////////////////////////////////////////////

void moveOddItemsToBack(LinkedList *ll)
{
	/* add your code here */

	// 1. cur 포인터 선언, 헤드를 가리킴
	// 2. tail 포인터 선언, 테일 노드를 가리킴 (tail->next null이면 stop)
	// 3. cur이 가리키는 노드의 item이 짝수이면, cur에 cur->next 할당, 홀수이면 end노드가 cur이 가리키는 노드를 가리키도록 설정
	// 4. end->next = cur
	// 5. cur -> next = cur->next->next
	// 6. cur = cur-> next
	// 7. end= end->next
	// 8. end->next = null


		if (ll == NULL || ll->head == NULL || ll->head->next == NULL) 
			return;  // 리스트가 비어 있거나 노드가 하나뿐이면 처리 불필요
		
		ListNode *cur = ll->head;
		ListNode *prev = NULL;
		ListNode *tail = ll->head;
		
		
		while (tail->next != NULL) {
			tail = tail->next;
		}
		
		
		
		// 리스트를 한 번만 순회하면서 홀수 노드를 뒤로 이동
		int count = 0;  // 처리한 노드 수를 카운트
		int totalNodes = ll->size;  // 리스트의 총 노드 수
		
		while (cur != NULL && count < totalNodes) {
			count++;
			
			if (cur->item % 2 != 0) {  // 홀수인 경우
				
				// 홀수 노드가 헤드인 경우
				if (prev == NULL) {
					ll->head = cur->next;  // 헤드 업데이트
					
					// 현재 노드를 마지막으로 이동
					tail->next = cur;
					cur->next = NULL;
					tail = cur;
					
					// 현재 포인터 업데이트
					cur = ll->head;
				} else {
					// 현재 노드가 헤드가 아닌 경우
					ListNode *temp = cur->next;  // 다음 노드 저장
					
					// 현재 노드를 리스트에서 제거
					prev->next = temp;
					
					// 현재 노드를 마지막으로 이동
					tail->next = cur;
					cur->next = NULL;
					tail = cur;
					
					// 현재 포인터 업데이트
					cur = temp;
				}
			} else {  // 짝수인 경우
				prev = cur;
				cur = cur->next;
			}
		}
	
}

///////////////////////////////////////////////////////////////////////////////////

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


ListNode *findNode(LinkedList *ll, int index){

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
