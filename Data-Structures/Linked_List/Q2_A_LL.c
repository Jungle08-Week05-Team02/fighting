//////////////////////////////////////////////////////////////////////////////////

/* CE1007/CZ1007 Data Structures
Lab Test: Section A - Linked List Questions
Purpose: Implementing the required functions for Question 2 */

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
void alternateMergeLinkedList(LinkedList *ll1, LinkedList *ll2);

void printList(LinkedList *ll);
void removeAllItems(LinkedList *ll);
ListNode *findNode(LinkedList *ll, int index);
int insertNode(LinkedList *ll, int index, int value);
int removeNode(LinkedList *ll, int index);


//////////////////////////// main() //////////////////////////////////////////////

int main()
{
	LinkedList ll1, ll2;
	int c, i, j;
	c = 1;
	//Initialize the linked list 1 as an empty linked list
	ll1.head = NULL;
	ll1.size = 0;

	//Initialize the linked list 2 as an empty linked list
	ll2.head = NULL;
	ll2.size = 0;

	printf("1: Insert an integer to the linked list 1:\n");
	printf("2: Insert an integer to the linked list 2:\n");
	printf("3: Create the alternate merged linked list:\n");
	printf("0: Quit:\n");

	while (c != 0)
	{
		printf("Please input your choice(1/2/3/0): ");
		scanf("%d", &c);

		switch (c)
		{
		case 1:
			printf("Input an integer that you want to add to the linked list 1: ");
			scanf("%d", &i);
			j = insertNode(&ll1, ll1.size, i);
			printf("Linked list 1: ");
			printList(&ll1);
			break;
		case 2:
			printf("Input an integer that you want to add to the linked list 2: ");
			scanf("%d", &i);
			j = insertNode(&ll2, ll2.size, i);
			printf("Linked list 2: ");
			printList(&ll2);
			break;
		case 3:
		    printf("The resulting linked lists after merging the given linked list are:\n");
			alternateMergeLinkedList(&ll1, &ll2); // You need to code this function
			printf("The resulting linked list 1: ");
			printList(&ll1);
			printf("The resulting linked list 2: ");
			printList(&ll2);
			removeAllItems(&ll1);
			removeAllItems(&ll2);
			break;
		case 0:
			removeAllItems(&ll1);
			removeAllItems(&ll2);
			break;
		default:
			printf("Choice unknown;\n");
			break;
		}
	}
	return 0;
}

//////////////////////////////////////////////////////////////////////////////////

void alternateMergeLinkedList(LinkedList *ll1, LinkedList *ll2)
{
    /* add your code here */
	// 두 개의 연결 리스트 ll1, ll2가 주어졌을 때,
	// ll2의 노드를 ll1의 노드 사이사이에 하나씩 끼워 넣는다.
	// ll2의 노드는 순서를 유지해야 하며, ll1의 기존 순서도 유지되어야 한다.
	// ll2가 ll1보다 길면 남은 노드들은 ll2에 그대로 남는다.
	// ll1이 더 길거나 같다면 ll2는 비워진다.

    if (ll1 == NULL || ll2 == NULL) return; // "함수를 그냥 종료한다" - 함수 리턴값이 void일 땐 return;만 써서 조용히 빠져나오는 게 흔한 패턴

    ListNode *cur1 = ll1->head;
    ListNode *cur2 = ll2->head;
    int index = 1;  // 첫 삽입 위치는 ll1의 두 번째 자리

    // 병합: ll1 노드 사이에 ll2 노드를 하나씩 끼워 넣기
    while (cur1 != NULL && cur2 != NULL)
    {
        insertNode(ll1, index, cur2->item);
        cur2 = cur2->next;
        cur1 = cur1->next->next;  // 새로 삽입된 노드 다음 다음으로 이동
        index += 2;               // 다음 삽입 위치는 두 칸 뒤
    }

    // ll2에서 삽입한 만큼 앞에서 제거
    while (ll2->head != cur2)
    {
        removeNode(ll2, 0);
    }
	
	// 새로운 연결리스트를 만들고 거기에 병합했다가 ll1을 그걸로 바꾸고, index를 관리해서 ll2를 삭제하는 식으로 했는데 별로 안좋은 방법이라 바꿈

}

// void alternateMergeLinkedList(LinkedList *ll1, LinkedList *ll2)
// {
//     /* add your code here */
//     // 1. temp를 선언하고 ll2의 head의 next를 가리킴
//     // 2. ll2의 head의 next가 ll1의 head의 next를 가리킴
//     // 3. ll1의 head의 next가 ll2의 head를 가리킴
//     // 4. ll2의 head가 temp를 가리킴.
//     /* add your code here */
//     // 두 리스트 중 하나라도 비어있으면 종료
//     if (ll1 == NULL || ll2 == NULL || ll1->head == NULL || ll2->head == NULL) {
//         return;
//     }
//     // 현재 위치를 추적하는 포인터
//     ListNode *curr1 = ll1->head;
//     // ll2가 비거나 ll1의 마지막에 도달할 때까지 반복
//     while (curr1 != NULL && ll2->head != NULL) {
//         // 1. temp를 선언하고 ll2의 head의 next를 가리킴
//         ListNode *temp = ll2->head->next;
//         // 2. ll2의 head의 next가 ll1의 head의 next를 가리킴
//         ll2->head->next = curr1->next;
//         // 3. ll1의 head의 next가 ll2의 head를 가리킴
//         curr1->next = ll2->head;
//         // 4. ll2의 head가 temp를 가리킴
//         ll2->head = temp;
//         // curr1을 방금 삽입한 노드로 이동
//         curr1 = curr1->next->next;
//     }
// }

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
