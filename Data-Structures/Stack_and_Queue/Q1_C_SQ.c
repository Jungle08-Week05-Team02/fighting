//////////////////////////////////////////////////////////////////////////////////

/* CE1007/CZ1007 Data Structures
Lab Test: Section C - Stack and Queue Questions
Purpose: Implementing the required functions for Question 1 */

//////////////////////////////////////////////////////////////////////////////////

#include <stdio.h>
#include <stdlib.h>

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


typedef struct _queue
{
	LinkedList ll;
} Queue;  // You should not change the definition of Queue

///////////////////////// function prototypes ////////////////////////////////////

// You should not change the prototypes of these functions
void createQueueFromLinkedList(LinkedList *ll, Queue *q);
void removeOddValues(Queue *q);

void enqueue(Queue *q, int item);
int dequeue(Queue *q);
int isEmptyQueue(Queue *q);
void removeAllItemsFromQueue(Queue *q);

void printList(LinkedList *ll);
ListNode * findNode(LinkedList *ll, int index);
int insertNode(LinkedList *ll, int index, int value);
int removeNode(LinkedList *ll, int index);
void removeAllItems(LinkedList *ll);

//////////////////////////// main() //////////////////////////////////////////////

int main()
{
	int c, i;
	LinkedList ll;
	Queue q;

	//Queue q;는 내부에 LinkedList 하나를 멤버로 가지는 구조체이고, 그 LinkedList는 다시 head와 size를 멤버로 가지는 구조체다.
	
	// q ───────────────┐
    //              ▼
    //     +------------------+
    //     | LinkedList ll    |   ← 구조체 변수 q 안에 포함됨
    //     |  ┌────────────┐  |
    //     |  │ int size   │  |
    //     |  │ ListNode*  │──┼──▶ [노드들 시작 주소]  ← 이게 head
    //     +------------------+
	
	// q	Queue 구조체 (로컬 변수)
	// q.ll	LinkedList 구조체
	// q.ll.head	첫 번째 노드를 가리키는 포인터
	// q.ll.size	큐에 들어있는 노드의 개수

	// enqueue(&q, 10);           // LinkedList에 10 삽입
	// printList(&(q.ll));        // 연결 리스트 출력
	// q.ll.head->item == 10;     // 첫 번째 노드 값 접근

	c = 1;

	// Initialize the linked list as an empty linked list
	ll.head = NULL;
	ll.size = 0;

	// Initialize the Queue as an empty queue
	q.ll.head = NULL;
	q.ll.size = 0;


	printf("1: Insert an integer into the linked list:\n");
	printf("2: Create the queue from the linked list:\n");
	printf("3: Remove odd numbers from the queue:\n");
	printf("0: Quit:\n");


	while (c != 0)
	{
		printf("Please input your choice(1/2/3/0): ");
		scanf("%d", &c);

		switch (c)
		{
		case 1:
			printf("Input an integer that you want to insert into the List: ");
			scanf("%d", &i);
			insertNode(&ll, ll.size, i);
			printf("The resulting linked list is: ");
			printList(&ll);
			break;
		case 2:
			createQueueFromLinkedList(&ll, &q); // You need to code this function
			printf("The resulting queue is: ");
			printList(&(q.ll));
			break;
		case 3:
			removeOddValues(&q); // You need to code this function
			printf("The resulting queue after removing odd integers is: ");
			printList(&(q.ll));
			removeAllItemsFromQueue(&q);
			removeAllItems(&ll);
			break;
		case 0:
			removeAllItemsFromQueue(&q);
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

void createQueueFromLinkedList(LinkedList *ll, Queue *q)
{
	/* add your code here */
	// 연결 리스트의 모든 값을 순서대로 큐에 삽입한다.
	// 큐가 비어있지 않으면 먼저 비운 뒤 삽입을 진행한다.
	// 연결 리스트의 첫 번째 노드부터 차례로 enqueue한다.

	if (ll == NULL || ll->head == NULL) return;
	if (!isEmptyQueue(q)) // 큐가 비어있지 않으면(0) 실행(not 연산 -> 1)
	{
		removeAllItemsFromQueue(q);
	}
	ListNode *cur = ll->head;
	while (cur != NULL)
	{
		enqueue(q, cur->item);
		cur = cur -> next;
	}

}

void removeOddValues(Queue *q)
{
	/* add your code here */
	// 큐에 있는 홀수 값 노드들을 모두 제거한다.
	// 첫 노드부터 끝까지 한 번 순회하면서 조건을 만족하면 삭제하고 연결을 재구성한다.
	// 노드 제거 시에는 next를 먼저 저장하고, 삭제 후 cur을 진행한다.
	
	// . 연산자 : 구조체 변수에 직접 접근할 때 사용
	// -> 연산자 : 구조체 포인터가 가리키는 구조체의 멤버에 접근할 때 사용

	// q.ll.head	Queue q;에서 내부 head 접근
	// q->ll.head	Queue *q;일 때 내부 head 접근
	// (*q).ll.head	Queue *q;의 일반적인 접근 방식

	// if(q->ll == NULL || q->ll->head == NULL) return; // q->ll은 LinkedList 구조체 자체이므로 포인터처럼 비교 불가
    if (q == NULL || q->ll.head == NULL) return;
    ListNode *cur = q->ll.head;
    ListNode *prev = NULL;
    
    while (cur != NULL)
    {
        ListNode *next = cur->next;  // 다음 노드를 미리 저장
        if (cur->item % 2 == 1)  // 홀수면 삭제
        {
            if (prev == NULL) // 첫 번째 노드가 홀수일 경우
            {
                q->ll.head = next;
                free(cur);
            }
            else // 중간 이후 홀수 노드 삭제
            {
                prev->next = next;
                free(cur);
            }
            q->ll.size--;  // 삭제했으므로 사이즈 감소
        }
        else
        {
            prev = cur; // 홀수가 아니면 prev만 전진
        }
        cur = next;  // 다음 노드로 진행
    }
}

// removeNode 함수 사용 버전
// void removeOddValues(Queue *q)
// {
//     if (q == NULL || q->ll.head == NULL) return;
//     int i = 0;
//     int size = q->ll.size;

//     while (i < size)
//     {
//         ListNode *node = findNode(&(q->ll), i);
//         if (node->item % 2 == 1)  // 홀수면 삭제
//         {
//             removeNode(&(q->ll), i);
//             size--;  // 삭제하면 전체 사이즈도 줄고 인덱스는 그대로 (다음 노드가 당겨지니까)
//         }
//         else
//         {
//             i++;  // 삭제 안했으면 다음 인덱스로 이동
//         }
//     }
// }


//////////////////////////////////////////////////////////////////////////////////

void enqueue(Queue *q, int item) {
	insertNode(&(q->ll), q->ll.size, item); // insertNode(LinkedList *ll, int index, int value)
}

int dequeue(Queue *q) {
	int item;

	if (!isEmptyQueue(q)) { //  큐가 비어있지 않으면(0) 실행(not 연산 -> 1)
		item = ((q->ll).head)->item;
		removeNode(&(q->ll), 0);
		return item;
	}
	return -1;
}

int isEmptyQueue(Queue *q) {
	if ((q->ll).size == 0)
		return 1;
	return 0;
}

void removeAllItemsFromQueue(Queue *q)
{
	int count, i;
	if (q == NULL)
		return;
	count = q->ll.size;

	for (i = 0; i < count; i++)
		dequeue(q);
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
