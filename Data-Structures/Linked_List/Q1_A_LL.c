//////////////////////////////////////////////////////////////////////////////////

/* CE1007/CZ1007 Data Structures
Lab Test: Section A - Linked List Questions
Purpose: Implementing the required functions for Question 1 */

//////////////////////////////////////////////////////////////////////////////////

#include <stdio.h>
#include <stdlib.h>

//////////////////////////////////////////////////////////////////////////////////

// 노드 정의. 정수형 데이터(item)와 다음 노드의 주소(listNode*)를 저장하는 포인터(next)
typedef struct _listnode{
	int item;
	struct _listnode *next;
} ListNode;			// You should not change the definition of ListNode

// 연결 리스트 전체를 대표하는 구조체. 리스트 사이즈(size)와 가장 첫번째 노드를 가리키는 포인터(head)
typedef struct _linkedlist{
	int size;
	ListNode *head;
} LinkedList;			// You should not change the definition of LinkedList


///////////////////////// function prototypes ////////////////////////////////////

// 함수 원형 선언
//You should not change the prototype of this function
int insertSortedLL(LinkedList *ll, int item);

void printList(LinkedList *ll);
void removeAllItems(LinkedList *ll);
ListNode *findNode(LinkedList *ll, int index);
int insertNode(LinkedList *ll, int index, int value);
int removeNode(LinkedList *ll, int index);


//////////////////////////// main() //////////////////////////////////////////////

int main()
{
	// 새 연결리스트 ll 선언하고 초기화
	LinkedList ll;
	int c, i, j;
	c = 1;

	//Initialize the linked list 1 as an empty linked list
	ll.head = NULL;
	ll.size = 0;

	printf("1: Insert an integer to the sorted linked list:\n");
	printf("2: Print the index of the most recent input value:\n");
	printf("3: Print sorted linked list:\n");
	printf("0: Quit:");

	// 사용자 입력에 따라 반복 동작하는 메뉴 기반 인터페이스
	while (c != 0)
	{
		printf("\nPlease input your choice(1/2/3/0): ");
		scanf("%d", &c);

		switch (c)
		{
		case 1: // 숫자 하나를 리스트에 삽입
			printf("Input an integer that you want to add to the linked list: ");
			scanf("%d", &i);
			j = insertSortedLL(&ll, i);
			printf("The resulting linked list is: ");
			printList(&ll);
			break;
		case 2: // 가장 최근에 삽입한 값의 인덱스를 출력
			printf("The value %d was added at index %d\n", i, j);
			break;
		case 3: // 전체 리스트 출력, 메모리 정리 (free를 이용함)
			printf("The resulting sorted linked list is: ");
			printList(&ll);
			removeAllItems(&ll);
			break;
		case 0: // 종료 및 메모리 해제
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

int insertSortedLL(LinkedList *ll, int item)
{
	/* add your code here */
	// 여기서는 insertNode함수를 썼지만, 사실 그러면 한번 더 순회하면서 넣을 곳을 찾게 되서 최적화를 위해서는 다른 방법 쓰는 게 좋다 
	// 입력받은 정수 item을 오름차순 정렬 상태를 유지하면서 연결 리스트에 삽입한다.
	// 이미 리스트에 존재하는 값이라면 삽입하지 않고 -1을 반환한다.
	// 삽입에 성공했다면 해당 값이 삽입된 index를 반환한다.

	if (ll == NULL) return -1;

	// 리스트가 비었거나, 가장 앞에 넣어야 하는 경우
	if (ll->head == NULL) {
		insertNode(ll, 0, item);
		return 0;
	}
	if (item == ll->head->item) return -1;
	if (item < ll->head->item) {
		insertNode(ll, 0, item);
		return 0;
	}

	// 	구조체 포인터 ll이 가리키는 곳의 head 멤버(연결 리스트의 첫 번째 노드 주소)를 cur에 저장
	ListNode *cur = ll->head;
	int index = 0;

	// 아직 리스트 끝이 아니고 다음 노드의 값이 삽입하려는 값보다 작다면 계속 앞으로 진행
	// cur은 처음에 ll->head로부터 첫 번째 노드의 주소를 복사해서 저장한다
	// 이후 while문에서 cur->next를 기준으로 판단한다 → 즉, "현재 노드가 가리키는 다음 노드"의 값을 보고 비교한다
	// 만약 그 다음 노드의 값이 item보다 작으면, cur을 한 칸 앞으로 진행한다 (cur = cur->next) / 삽입할 위치 바로 앞까지 cur를 이동
	while (cur->next != NULL && cur->next->item < item){
		cur = cur -> next;
		index++;
	}

	// 마지막 노드와 그 다음 노드에서 중복 확인
	if (cur->item == item || (cur->next && cur->next->item == item)) return -1;

	insertNode(ll, index+1, item);
	return index+1;
}

///////////////////////////////////////////////////////////////////////////////////

void printList(LinkedList *ll){

	// 이 함수는 연결 리스트 전체 구조체의 주소를 받아, 그 안에 있는 첫 번째 노드 주소(head)를 꺼내 cur이라는 포인터에 저장
	// cur은 리스트를 탐색할 때 사용할 포인터이며, 만약 리스트 자체가 NULL이라면 (즉, 아예 존재하지 않는다면) 함수를 종료하고 아무것도 하지 않음
	
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

	// 만약 비어있거나 음수 인덱스거나 현재 리스트의 크기보다 큰 인덱스면 존재하지 않음
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

	// 빈 리스트이거나 맨 앞에 삽입할 때
	// If empty list or inserting first node, need to update head pointer
	if (ll->head == NULL || index == 0){
		cur = ll->head;
		ll->head = malloc(sizeof(ListNode));
		ll->head->item = value;
		ll->head->next = cur;
		ll->size++;
		return 0;
	}

	// 중간이나 끝에 삽입할 때
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

	// 리스트가 없거나, 삭제할 인덱스가 잘못된 경우
	// Highest index we can remove is size-1
	if (ll == NULL || index < 0 || index >= ll->size)
		return -1;

	// 첫 노드 삭제 : head 자체를 제거하고, 다음 노드를 새 head로 만듦
	// If removing first node, need to update head pointer
	if (index == 0){
		cur = ll->head->next;
		free(ll->head);
		ll->head = cur;
		ll->size--;

		return 0;
	}
	// 중간/끝 노드 삭제 : 지우려는 노드의 앞 노드를 찾아서, 그 노드의 next를 건너뛰도록 연결해줌
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
