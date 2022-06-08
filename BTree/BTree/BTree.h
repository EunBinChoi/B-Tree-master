#pragma once
#include <stdio.h>
#include <stdlib.h>
#define SIZE 2 //키 개수
typedef struct bTNode{
	int r_key;		//오른쪽 키(큰 값)
	int l_key;		//왼쪽 키(작은 값)
	struct bTNode* p_left;	//왼쪽 자식의 주소(왼쪽 키값 보다 작은 값)
	struct bTNode* p_middle;	//중간 자식의 주소	(오른쪽 키값과 왼쪽 키값의 사이 값)
	struct bTNode* p_right;		//오른쪽 자식의 주소
	struct bTNode* p_parent;	//부모의 주소
	int cnt;		//키 개수 
}BTNode;

BTNode* root;	//루트의 주소
int isThreeNode(BTNode* n);	//해당 노드 n의 키가 2개 인지 검사하는 함수
int isLeafNode(BTNode* n);	//해당 노드 n이 리프 노드인지 판별하는 함수

//print
void print_tree(BTNode* r);		// 중위 순회 방식 출력 함수
void print_tree_level(BTNode* root, int level);	//레벨 형식 출력 함수


//삽입 관련 함수
BTNode* createNode(int n);	//n이라는 키값을 가지는 노드 생성 함수
int* sortData(int a, int b, int c);	//a,b,c 값을 정렬해서 배열의 주소를 반환해주는 함수
void input_Item(BTNode* n, int item);	//n 노드(2-node)에 item 값을 삽입하는 함수
void insertNode(int item);						//item값을 트리에 삽입해주는 함수
BTNode* splitNode(BTNode* n, BTNode* x, int pos);	//노드를 분할 하는 함수
int computePos(BTNode* parent, BTNode* n);		//n이 parent의 어느 위치의 자식인지 판별하는 함수
void insertRec(BTNode* n, int item);			//재귀적으로 item의 값을 삽입


//삭제 관련 함수
int removeNode(int item);		//key 값을 삭제 하는 함수
BTNode* FindNextLargest(int item, BTNode* n);	//
void fix(BTNode* node, BTNode* pChild);	//
int Redistribute(BTNode* node, int* situation);


//트리 전체 삭제
void destroy(BTNode* n);

void destroy(BTNode* n){
	//NULL인 경우 함수 종료
	if (n == NULL){
		return;
	}
	if (isThreeNode(n)){		//3노드인 경우
		//3개의 자식을 모두 재귀호출
		destroy(n->p_left);
		destroy(n->p_middle);
		destroy(n->p_right);

		//3개의 자식을 모두 호출 한 뒤 n 메모리 해제
		free(n);
	}
	else{  //2노드 인 경우
		//2개의 자식을 모두 호출
		destroy(n->p_left);
		destroy(n->p_right);
		//호출 후 메모리 해제
		free(n);
	}
}


//값이 다 찼는지 검사
int isThreeNode(BTNode* n) {
	if (n->cnt >= SIZE)
		return 1;
	else
		return 0;
}
//마지막 노드인지 검사
int  isLeafNode(BTNode* n) {
	//아무것도 저장한게 없으면 리프 노드 
	if (n->p_left == NULL && n->p_right == NULL && n->p_middle == NULL) return 1;
	else return 0;
}

//트리를 레벨 형식으로 출력 
void print_tree_level(BTNode* n, int level)
{
	int j;
	
	if (n != NULL)
	{
		//왼쪽 자식 호출하고(레벨 1 증가)
		print_tree_level(n->p_left, level + 1);
		
		//레벨 만큼 가로에 | 출력
		for (j = 0; j < level; j++)
			printf("|  ");

		//왼쪽 키 출력
		printf("+[%2d]\n", n->l_key);
		
		//가운데 자식 호출하고(레벨 1 증가)
		print_tree_level(n->p_middle, level + 1);

		//레벨 만큼 가로에 | 출력
		for (j = 0; j < level; j++)
			printf("|  ");

		//오른쪽 키가 비어 있으면, 공백 출력
		if (n->r_key == -1)
			printf("+[  ]\n");
		else //비어 있지 않은 경우는 오른쪽 키 출력
			printf("+[%2d]\n", n->r_key);
		
		//오른쪽 자식 호출
		print_tree_level(n->p_right, level + 1);
	}
}
//중위 순외방식으로 출력하는 함수
void print_tree(BTNode* r)
{
	if (r != NULL)
	{
		if (isThreeNode(r)){	//3 node 인 경우
			//왼쪽 자식 호출 -> 값 출력 -> 중간 자식 호출 -> 값 출력 -> 오른쪽 자식 호출
			print_tree(r->p_left);
			printf("(%d, %d, %d)\n", r->cnt, r->l_key, r->r_key);
			print_tree(r->p_middle);
			if (r->p_middle)
				printf("(%d, %d, %d)\n", r->cnt, r->l_key, r->r_key);
			print_tree(r->p_right);
		}
		else{ //2 node
			//왼쪽 자식 호출 -> 값 출력 -> 오른쪽 자식 호출
			print_tree(r->p_left);
			printf("(%d, %d)\n", r->cnt, r->l_key);
			print_tree(r->p_right);
		}

	}
}

BTNode* search(BTNode* n, int item){
	//해당 item을 가지는 key 값을 탐색함
	if (n->l_key == item){
		return n;
	}
	else if (n->cnt == 2 && n->r_key == item){
		return n;
	}
	else if (isLeafNode(n)){
		return NULL;
	}
	
	if (n->cnt == 1) { //2-node
		if (item < n->l_key) search(n->p_left, item);		//탐색 하려는 값이 왼쪽 보다 작으면 왼쪽 서브 트리 방문
		else search(n->p_right, item);						//탐색 하려는 값이 왼쪽 키값 보다 크면 오른쪽 서브 트리 방문
	}
	else { //3-node
		if (item < n->l_key) search(n->p_left, item);		//탐색 하려는 값이 왼쪽 키값 보다 작으면 왼쪽 서브트리 방문
		else if (item > n->r_key) search(n->p_right, item); //탐색 하려는 값이 오른쪽 키값 보다 크면 왼쪽 서브트리 방문
		else search(n->p_middle, item);						//두 값 사이에 있으면, 가운데 서브트리 방문
	}
}

//왼쪽 키값이 n 인 노드 생성
BTNode* createNode(int n)
{
	BTNode* tmp;

	//동적 할당으로 노드 생성
	tmp = (BTNode*)malloc(sizeof(BTNode));
	tmp->cnt = 1;			//키값은 한개
	tmp->p_parent = NULL;	//부모는 아직 없고
	tmp->r_key = -1;		//오른쪽 키값도 없고
	tmp->l_key = n;			//왼쪽 키값은 n
	tmp->p_left = NULL;		// 자식 모두 없는 상태
	tmp->p_middle = NULL;
	tmp->p_right = NULL;
	return tmp;			//만든 노드 주소 반환
}
//가운데 값 찾으려고..
int* sortData(int a, int b, int c) {
	//a : 이전 l value
	//b : 이전 r value
	//c : 새로운 값,
	//동적 배열을 생성해서, 3개의 값을 차례로 정렬한 값을 저장
	int* arr = (int *)malloc(sizeof(int) * 3);
	if (c < a) {
		arr[0] = c;
		arr[1] = a;
		arr[2] = b;
	}
	else if (c > b) {
		arr[0] = a;
		arr[1] = b;
		arr[2] = c;
	}
	else {
		arr[0] = a;
		arr[1] = c;
		arr[2] = b;
	}
	return arr; //주소 반환
}
void input_Item(BTNode* n, int item) {
	if (n->l_key > item) {	//넣으려고 하는 아이템이 왼쪽 키보다 작으면,
		n->r_key = n->l_key;	//오른쪽 키에 기존 왼쪽 키를 넣고
		n->l_key = item;		//왼쪽 키는 새로운 키값을 넣음
	}
	else   //그렇지 않는 경우 넣으려는 값은 그냥 오른쪽에 넣으면 됨
	{
		n->r_key = item;
	}
	//키 개수는 이제 두 개
	n->cnt = 2;
}
BTNode* FindNextLargest(int item, BTNode* n){
	BTNode* next = 0;
	
	//item을 대체할 유망한 자식을 찾기 위한 과정
	//해당 키값을 기준으로 왼쪽 서브트리를 최대값, 혹은 오른쪽 서브트리의 최소값이 유망한 자식이 됨
	//현재 코드에서는 오른쪽 서브트리의 최소값을 찾는 방법을 사용함
	//n이 3노드 이면서, 왼쪽 값이 item인 경우 
	//item의 오른쪽 서브 트리는 middle이 되기 때문에 next는 middle 부터 시작함.
	if (isThreeNode(n) && n->l_key == item){
		next = n->p_middle;
	}
	else{
		//2노드의 경우 오른쪽 서브트리로 시작함.
		next = n->p_right;
	}

	//시작 서브트리부터 왼쪽으로 leaf 까지 내려가면, 해당 leaf에 최소값이 있음.
	while (!isLeafNode(next)){
		next = next->p_left;
	}
	//최소 값이 있는  leaf 의 주소를 반환함.
	return next;
}
int removeNode(int item){
	BTNode* n = search(root, item);	//삭제 하려는 아이템이 있는 노드를 찾고 주소를 n에 저장
	BTNode* leafNode ;		//임시 저장소
	int tmp = 0;
	if (n == NULL) return 0;	//찾으려는 값이 없으면 0을 반환

	if (!isLeafNode(n)){	//삭제하려는 값이 있는 노드가 리프노드가 아니면
		// 유망한 자식을 찾음 (왼쪽 서브트리의 제일 큰 값, 또는 오른쪽 서브트리의 제일 작은 값이 유망한 자식이 됨)
		leafNode = FindNextLargest(item, n);

		//유망한 자식과 키값을 교환함
		if (n->l_key == item){
			tmp = n->l_key;
			n->l_key = leafNode->l_key;
			leafNode->l_key = tmp;
		}
		else{
			tmp = n->r_key;
			n->r_key = leafNode->l_key;
			leafNode->l_key = tmp;
		}
	}
	else{
		//리프 노드인 경우 leaf를  n으로 설정함
		leafNode = n;
	}

	if (isThreeNode(leafNode)){	//리프노드가 3노드인경우
		if (item == leafNode->l_key){		//삭제하려는 값이 왼쪽에 있으면,
			leafNode->l_key = leafNode->r_key;	//오른쪽 값을 왼쪽으로 옮겨 주고
		}
		leafNode->r_key = -1;	//오른쪽 값을 비우고
		leafNode->cnt= 1;		//이제 해당 리프 노드는 2노드가 됨
	}
	else{
		fix(leafNode,0);	//리프노드가 2노드 인경우 키값이 하나 밖에 없기 때문에, 트리를 고치는 과정이 필요함
		
	}
	return 1;
}
void ReassignChildren(BTNode* node, BTNode* pChildOfNode, int situation)
{
	//부모노드를  parent에 저장함
	BTNode* parent = node->p_parent;

	switch (situation) {

	case 1:
		//case 1 부모가 3 노드이고, 삭제된 노드가 왼쪽에 있고, 가운데 형제가 3노드 일때,
		/*  
		(20,      40)    (a)    (30,     40)     (b)   (30,     40)
		/      |     \     =>   /     |    \     =>    /     |    \
	   ( )   (30,35)   50      20    35     50        20    35    50
		|     /  | \   /\      |    / | \   /\        /\    / \   /\
		C   29 32  37 60 70    C  29 32 37 45 70     C 29 32  37 45 70 */
		//삭제된 노드의 왼쪽 자식을 pChildOfNode로 연결하고 부모 설정  
		node->p_left = pChildOfNode;
		if (node->p_left != NULL) node->p_left->p_parent = node;

		//삭제된 노드 오른쪽 자식에 재분배된 가운데 형제의 왼쪽자식을 데려옴 
		node->p_right = parent->p_middle->p_left;
		if (node->p_right != NULL) node->p_right->p_parent = node;

		//재분배된 가운데 노드의 왼쪽 자식을 삭제된 왼쪽 형제로 보냈기 때문에,
		//재분배된 가운데 노드의 가운데 자식을 왼쪽 자식으로 옮겨줌
		parent->p_middle->p_left = parent->p_middle->p_middle;
		if (parent->p_middle->p_left != NULL) parent->p_middle->p_left->p_parent = parent->p_middle;
		parent->p_middle->p_middle = NULL;
		break;
	case 2: //case 2 부모가 3 노드이고, 삭제된 노드가 왼쪽에 있고, 오른쪽 형제가 3노드 일때,

		/*      (10,         20)     Redist.   (15,   30)		            (15,   30)
		         /      |     \       =>     /     |    \      Reassign    /    |     \ 
		       ( )     15    (30,40)        10    20     40        =>      10   20     40 
		        |      / \    / | \          |    / \   / | \    Children / \   / \   / \ 
		        5    12  17  25 35 70        5   12 17 25 35 70          5  12 17 25 35 70
				  */ 
		//삭제된 노드의 왼쪽 자식을 pChildOfNode로 연결하고 부모 설정         											      
		node->p_left = pChildOfNode;
		if (node->p_left != NULL) node->p_left->p_parent = node;

		//삭제된 노드 오른쪽 자식에 가운데 형제의 왼쪽자식을 데려옴 
		node->p_right = parent->p_middle->p_left;
		if (node->p_right != NULL) node->p_right->p_parent = node;

		//가운데 형제의 왼쪽 자식을 가운데 형제의 오른쪽 자식을 대체하고,
		parent->p_middle->p_left = parent->p_middle->p_right;

		//가운데 형제의 오른쪽 자식을 오른쪽 형제의 왼쪽 자식을 대체한다.
		parent->p_middle->p_right = parent->p_right->p_left;
		if (parent->p_middle->p_right != NULL) parent->p_middle->p_right->p_parent = parent->p_middle;

		//오른쪽 형제의 왼쪽 자식은 오른쪽 자식의 가운데 자식을 체한다.
		parent->p_right->p_left = parent->p_right->p_middle;
		parent->p_right->p_middle = NULL;
		break;

	case 3: //case 3 부모가 3 노드이고, 삭제된 노드가 가운데에 있고, 왼쪽 형제가 3노드 일때,


		/*																 	
		    (10,  20)          Redist. 	    (8,  20)          Reassign   	    (8,  20)          
		   /     |   \             =>  	   /     |   \          Children 	   /     |   \        
		(6,8)   ( )  (30, 40)          	  6     (10)  (30, 40)      =>   	  6     (10)  (30, 40)
		/ | \    |    /  |  \          	/ | \    |    /  |  \            	/  \    / \   /  |  \ 
		1 7 9    c   25 35  70         1  7 9    c   25 35  70			   1   7   9   c  25 35  70		
		*/
		//삭제된 노드의 오른쪽 자식을 pChildOfNode로 연결하고 부모 설정    
		node->p_right = pChildOfNode;
		if (node->p_right != NULL)node->p_right->p_parent = node;

		//삭제된 노드의 왼쪽 자식을 왼쪽 형제의 오른쪽 자식을 데려옴
		node->p_left = parent->p_left->p_right;
		if (node->p_left != NULL) node->p_left->p_parent = node;
		
		//왼쪽 형제노드의 오른쪽 자식은 중간 자식으로 바꿔줌
		parent->p_left->p_right = parent->p_left->p_middle;
		parent->p_left->p_middle = NULL;
		break;

	case 4: //case 4 부모가 3노드이고, 삭제된 노드가 가운데에 있고, 오른쪽 형제가 3노드 일때,
		/*    
		      (10,  20)          Redist.    (10,  30)       Reassign      (10,     30)
		     /    |    \         =>          /    |    \     Children      /      |   \
		(5,8)    ( )  (30, 40)           (5,8)    20    40      =>       (5,8)   20    40
		/  | \    |   /   |  \          /  | \    |    / | \             / | \    /\    / \
		1   7  9  17  25  35  70       1   7  9  17  25 35  70        1  7  9 17 25 35  70 */
		//삭제된 노드의 왼쪽 자식을 pChildOfNode로 연결하고 부모 설정
		node->p_left = pChildOfNode;
		if (node->p_left != NULL)node->p_left->p_parent = node;

		//삭제된 노드의 오른쪽 자식을 오른쪽 형제의 왼쪽 자식을 데려옴
		node->p_right = parent->p_right->p_left;
		if (node->p_right != NULL) node->p_right->p_parent = node;

		//오른쪽 형제의 왼쪽 자식은 오른쪽 형제의 중간 자식을 업데이트 함
		parent->p_right->p_left = parent->p_right->p_middle;
		parent->p_right->p_middle = NULL;
		break;

	case 5:
		//case 5 부모가 3노드이고, 삭제된 노드가 오른쪽에 있고, 가운데 형제가 3노드 일때,
		/*
		  (10,       25)              (10,      19)    Reassign      (10,       19)
		  /       |     \       =>    /      |      \   Children     /      |       \
		 5    (15, 19)   ( )         5       15      25    =>       5       15       25
		/ \    /  |  \    |         / \     / | \     |            / \     /  \     /  \
	   1   7  12 17  22  60        1   7  12  17 22  60           1   7  12   17  22   60   */
		//삭제된 노드의 오른쪽 자식을 pChildOfNode로 연결하고 부모 설정    
		node->p_right = pChildOfNode;
		if (node->p_right != NULL) node->p_right->p_parent = node;

		//삭제된 노드의 왼쪽 자식은 가운데 형제의 오른쪽 자식으로 설정
		node->p_left = parent->p_middle->p_right;
		if (node->p_left != NULL) node->p_left->p_parent = node;

		//가운데 형제의 오른쪽 자식은 가운데 자식으로 대체
		parent->p_middle->p_right = parent->p_middle->p_middle;
		parent->p_middle->p_middle = NULL;

	case 6:
		//case 6 부모가 3노드이고, 삭제된 노드가 오른쪽에 있고, 왼쪽 형제가 3노드 일때,
		/* 
		     (20,       40)               (18,   30)           (18,    30)
		    /       |     \    Redist   /     |   \   Shift   /     |    \
		(10, 18)   30     ( )   =>   10     20    40   =>   10     20     40
		/  | \    /  \    /    (a)   / | \   / \   /   (b)  /  \   / \    / \
		5  12  19 25  32  55        5 12 19 25 32 55       5   12 19 25  32 55
		*/
		node->p_right = (node->p_left = pChildOfNode) ? node->p_left : node->p_right;
		if (pChildOfNode != NULL) pChildOfNode->p_parent = node;

		//삭제된 노드의 왼쪽 자식은 가운데 형제의 오른쪽 자식으로 대체
		node->p_left = parent->p_middle->p_right;
		if (node->p_left != NULL) node->p_left->p_parent = node;

		//가운데 형제의 오른쪽 자식은 왼쪽 자식을 대체
		parent->p_middle->p_right = parent->p_middle->p_left;
		//왼쪽은 왼쪽의 왼쪽 형제의 오른쪽 자식으로 대체
		parent->p_middle->p_left = parent->p_left->p_right;
		parent->p_middle->p_left->p_parent = parent->p_middle;
		//왼쪽 형제의 오른쪽 자식은 가운데 자식으로 대체
		parent->p_left->p_right = parent->p_left->p_middle;

		break;

	case 7: //case 7 부모가 2노드이고, 삭제된 노드가 왼쪽에 있고, 오른쪽 형제가 3노드 일때,
		/*
		     20                            30                    30
	      	/  \         Redistribute     /  \      Reassign    /   \
		( )   (30, 40)     =>           20    40     =>       20     40
		 |    /  |  \                   |    / | \           / \    / \
	     5  25  35  50                  5  25  35  50       5  25 35  50 */

		//삭제된 노드의 왼쪽 자식을 pChildOfNode로 연결하고 부모 설정  
		node->p_left = pChildOfNode;
		if (pChildOfNode != NULL) pChildOfNode->p_parent = node;

		//오른쪽 자식은 오른쪽 형제의 왼쪽 자식으로 대체
		node->p_right = parent->p_right->p_left;
		if (node->p_right != NULL) node->p_right->p_parent = node;

		//오른쪽 형제의 왼쪽 자식은 가운데 자식으로 대체
		parent->p_right->p_left = parent->p_right->p_middle;
		parent->p_right->p_middle = NULL;
		break;


	case 8: /* //case 8 부모가 2노드이고, 삭제된 노드가 오른쪽에 있고, 왼쪽 형제가 3노드 일때,
			     50        After              40                        40
		     	/   \      Redistribute      /   \      Reassign       /  \
			(30, 40) ( )     =>           30     50       =>         30   50
			/  |  \   |                   / | \    |    Children     / \   / \
		   25  35 45  60                 25 35 45  60               25 35 45 60   */
		//삭제된 노드의 오른쪽 자식을 pChildOfNode로 연결하고 부모 설정    
		node->p_right = pChildOfNode;
		if (pChildOfNode != NULL) pChildOfNode->p_parent = node;

		//삭제된 노드의 왼쪽 자식은 왼쪽 형제의 오른쪽 자식으로 대체
		node->p_left = parent->p_left->p_right;
		if (node->p_left != NULL)node->p_left->p_parent = node;

		//왼쪽 형제의 오른쪽 자식은 왼쪽 자식의 가운데로 대체
		parent->p_left->p_right = parent->p_left->p_middle;
		parent->p_right->p_middle = NULL;
		break;
	}
}
int Redistribute(BTNode* node, int* situation){
	int bRc = 1;
	BTNode *parent = node->p_parent;

	if (isThreeNode(parent)) {		//부모가 3노드인 경우
		if (node == parent->p_left) { //왼쪽에 삭제 노드가 있으면
			if (isThreeNode(parent->p_middle)) { 
				//case 1 부모가 3 노드이고, 삭제된 노드가 왼쪽에 있고, 가운데 형제가 3노드 일때,
				/*
				(20,      40)           (30,     40)
				/      |     \    =>    /     |    \
			   ( )  (30,35)  50        20    35     50
				|    /  | \    /\       |    / | \   /\
				C   29 32  37 60 70     C  29 32 37 45 70
				*/

				
				//삭제노드의 왼쪽 값에 부모노드의 왼쪽 값을 넣고
				node->l_key = parent->l_key;
				node->cnt = 1;

				//부모 노드의 왼쪽에 가운데 노드의 왼쪽 값을 넣고
				parent->l_key = parent->p_middle->l_key;
				//가운데 노드의 왼쪽 값에 오른쪽 값을 넣음
				parent->p_middle->l_key = parent->p_middle->r_key;

				//가운데 노드 크기 1 감소
				parent->p_middle->r_key = -1;
				parent->p_middle->cnt=1;

				*situation = 1;

			}
			else if (isThreeNode(parent->p_right)) {	//case 2 부모가 3 노드이고, 삭제된 노드가 왼쪽에 있고, 오른쪽 형제가 3노드 일때,
				/*
				(10,   20)                 (15,   30)
				/    |    \          =>    /    |    \
		     ( )    15    (30, 40)        10    20     40 */

				//삭제 노드의 왼쪽 값에 부모의 왼쪽 값을 넣고
				node->l_key = parent->l_key;
				node->cnt = 1;

				//부모의 왼쪽 값에 가운데 자식의 왼쪽 값을 넣고
				parent->l_key = parent->p_middle->l_key;

				//가운데 자식의 왼쪽 값에 부모의 오른쪽 값을 넣고
				parent->p_middle->l_key = parent->r_key;

				//부모의 오른쪽 값에 오른쪽 자식의 왼쪽 값을 넣고
				parent->r_key = parent->p_right->l_key;

				//부모의 오른쪽 자식의 왼쪽 값에 오른쪽 자식의 오른쪽 값을 넣는다.
				parent->p_right->l_key = parent->p_right->r_key;

				//오른쪽 자식은 이제 2노드
				parent->p_right->r_key = -1;
				parent->p_right->cnt = 1;
				*situation = 2;

			}
			else {
				//부모는 3노드지만 형제들이 다 2노드 인 경우
				bRc = 0;
			}

		}
		else if (node == parent->p_middle) { //가운데에 삭제 된 노드가 있는 경우
			//case 3 부모가 3 노드이고, 삭제된 노드가 가운데에 있고, 왼쪽 형제가 3노드 일때,
			if (isThreeNode(parent->p_left)) {
				//왼쪽에 3노드가 있는 경우
				/*
				(10, 20)                   (5, 20)
				/    |  \             =>   /   |  \
			 (1, 5) ( ) (30, 40)          1    10  (30, 40) */

				//삭제된 노드의 왼쪽 값을 부모의 왼쪽 값으로 설정하고
				node->l_key = parent->l_key;
				node->cnt = 1;
				//부모의 왼쪽 값을 왼쪽 자식의 오른쪽 값으로 설정한다.
				parent->l_key = parent->p_left->r_key;

				//이제 왼쪽 자식은 2노드
				parent->p_left->r_key = -1;
				parent->p_left->cnt = 1;

				*situation = 3;

			}
			//case 4 부모가 3노드이고, 삭제된 노드가 가운데에 있고, 오른쪽 형제가 3노드 일때,
			else if (isThreeNode(parent->p_right)) {
				/*
				(10,    20)                 (10,  30)
				/    |    \           =>    /    |   \
				1   ( )  (30, 40)         1    20   40
				*/
				//삭제된 노드의 왼쪽 값을 부모의 오른쪽 값으로 설정하고,
				node->l_key = parent->r_key;
				node->cnt = 1;
				//부모의 오른쪽 값을 오른쪽 자식 노드의 왼쪽 값으로 설정하고,
				parent->r_key = parent->p_right->l_key;
				//오른쪽 자식의 오른쪽 키를 왼쪽으로 옮기고
				parent->p_right->l_key = parent->p_right->r_key;

				//이제 오른쪽 키는 2노드
				parent->p_right->r_key = -1;
				parent->p_right->cnt = 1;

				*situation = 4;
			}
			else {
				bRc = 0;
			}

		}
		else  { //오른쪽에 삭제 노드가 있으면
			if (isThreeNode(parent->p_middle)) {
				//case 5 부모가 3노드이고, 삭제된 노드가 오른쪽에 있고, 가운데 형제가 3노드 일때,
				/*
				(10,          25)              (10,       19)
				/       |       \       =>    /      |       \
				5    (15, 19)   ( )         5       15       25
			   / \    /  |  \    /          / \     / | \     /
		      1   7  12 17  22  60         1   7  12  17 18  60       */
				//삭제 노드의 왼쪽 키를 부모의 오른쪽 키로 저장하고,
				node->l_key = parent->r_key;
				node->cnt = 1;

				//부모의 오른쪽 키는 가운데 자식의 오른쪽 키로 설정하고,
				parent->r_key = parent->p_middle->r_key;
			
				//가운데 자식은 이제 2노드
				parent->p_middle->r_key = -1; 
				parent->p_middle->cnt = 1;

				*situation = 5;

			}
			else if (isThreeNode(parent->p_left)) {
				//case 6 부모가 3노드이고, 삭제된 노드가 오른쪽에 있고, 왼쪽 형제가 3노드 일때,
			/*  
				(20,         40)               (18,   30)
				/        |     \      =>     /     |   \
			(10, 18)     30     ( )         10     20    40
			/  |   \    /  \    /          / | \   / \   /
			5  12  19  25  32  55         5  7 19 25 32 55      */

				//삭제된 노드의 왼쪽 키값은 부모의 오른쪽 값으로 되고,
				node->l_key = parent->r_key;
				node->cnt = 1;
			
				//부모의 오른쪽 키값은 가운데 자식의 왼쪽 키값으로 되고,
				parent->r_key = parent->p_middle->l_key;
				//가운데 자식의 왼쪽 키값은 부모의 왼쪽 키값이 되고,
				parent->p_middle->l_key = parent->l_key;
				//부모의 왼쪽 키값은 왼쪽 자식의 오른쪽 값이 되고,
				parent->l_key = parent->p_left->r_key;

				//왼쪽 자식은 이제 2노드
				parent->p_left->r_key = -1;
				parent->p_left->cnt = 1;
				*situation = 6;

			}
			else {	//형제에 3노드가 없는 경우
				bRc = 0;
			}
		}

	}
	else { // 부모가 2노드인 경우
		if (parent->p_left == node) {	//왼쪽에 삭제하려는 값이 있는 경우
			if (isThreeNode(parent->p_right)) {
				//case 7 부모가 2노드이고, 삭제된 노드가 왼쪽에 있고, 오른쪽 형제가 3노드 일때,
				/* 
				  ( 30 )                (40 )
			      /     \         =>     /   \
				( )     (40,50)        30    50
				/        /              /     /
				5       35             5    35       */
				//삭제 된 노드의 왼쪽 키를 부모의 왼쪽 키로 설정 해주고,
				node->l_key = parent->l_key;
				node->cnt = 1;

				//부모의 왼쪽 키는 오른쪽 자식의 왼쪽 키로 설정해주고,
				parent->l_key = parent->p_right->l_key;
				//오른쪽 자식의 왼쪽 키를 오른쪽 키로 바꿔줌
				parent->p_right->l_key = parent->p_right->r_key; 
			
				//오른쪽 자식은 이제 2노드
				parent->p_right->r_key = -1;
				parent->p_right->cnt = 1;
				*situation = 7;

			}
			else {
				//자식이 모두 2노드 인 경우
				bRc = 0;
			}

		}
		else {  //오른쪽에 삭제하려는 값이 있는 경우
			if (isThreeNode(parent->p_left)) {
				//case 8 부모가 2노드이고, 삭제된 노드가 오른쪽에 있고, 왼쪽 형제가 3노드 일때,
				/*
				       ( 30 )                (20 )
				      /     \         =>     /   \
				(10,20)     (  )            10    30
				/           /               /     /
				5          35              5      35       */
				//삭제된 노드의 왼쪽 키를 부모의 왼쪽 키로 설정하고,
				node->l_key = parent->l_key;
				node->cnt = 1;
				//부모의 왼쪽 키는 왼쪽 자식의 오른쪽 키로 설정하고
				parent->l_key = parent->p_left->r_key;

				//왼쪽 자식은 이제 2노드
				parent->p_left->r_key = -1;
				parent->p_left->cnt = 1;
				*situation = 8;

			}
			else {	//자식이 모두 2노드 인 경우
				bRc = 0;
			}
		}
	}
	return bRc;
}
void fix(BTNode* node, BTNode* pChild){
	BTNode* parent;				//부모의 주소
	BTNode* pSibling;		//합병할 대상 자식
	BTNode* middleChild;	//리프노드가 아닌 경우에 자식들의 위치를 재조정하기 위해,
	int situation;				//케이스 저장
	int parentIsEmpty = 0;		//부모가 삭제되 었는지 저장
	int left_right = 0; // 0 : left, 1: right
	//고치려는 노드가 루트인경우
	if (node == root){
		free(root);	//루트를 메모리 해제하고
		root = pChild;	//자식을 루트로 바꿈
		if (pChild!=NULL) pChild->p_parent = NULL;
	}
	else{ 
		parent = node->p_parent;	//부모를 저장함
		if (Redistribute(node, &situation)){	//재분배(형제 노드 중 3노드가 있는경우) 과정실행 
			if (!isLeafNode(node)) {		//노드가 leaf가 아닌 경우
				ReassignChildren(node, pChild, situation);	//자식을 재배정해야 함
			}
		}
		else{ //모든 형제 노드가 2노드 인경우 재분배를 할 수 없음 따라서, 합병 과정을 수행해야함
			if (isThreeNode(parent)){	//부모가 3 노드 인경우 
				if (parent->p_right == node){	//삭제 하려는 노드가 부모의 오른쪽 자식이면,
					/*
					  18 삭제 시,				  
						(9,        15)          	   9      
						/    |      \      =>   	/     \              
					   7    c:12     17             7    (c:12,15)       
					*/
					
					pSibling = parent->p_middle;		// 가운데 있는 형제에게 합병
					pSibling->r_key = parent->r_key;	//형제의 오른쪽 키에 부모의 오른쪽 키를 넣고, 
					

					middleChild = pSibling->p_right;	//기존에 가운데 자식이 오른쪽 자식을 가지고 있었으면 가운데로 옮겨줌 

					parent->p_right = pSibling;			//가운데 형제를 부모의 오른쪽 자식으로 옮겨 주고
					parent->p_middle = NULL;			//부모의 가운데 자식은 NULL로 설정

					left_right = 1;						//삭제는 오른쪽에서 수행됨
				}
				else if (parent->p_middle == node) {
					//삭제 하려는 노드가 부모의 가운데 자식이면
					/*
					 5 삭제 시,
					(4,7)             4
					/ | \      =>    / \
				   1  5  8          1  (7,8)
					*/
					//오른쪽 자식으로 합병함
					pSibling = parent->p_right;

					//오른쪽 자식의 오른쪽 값에 기존 왼쪽 값을 넣고
					// 왼쪽 값에는 부모의 오른쪽 값을 승계받음
					pSibling->r_key = pSibling->l_key;
					pSibling->l_key = parent->r_key;

					//리프노드가 아닌 경우만 의미가 있음.
					middleChild = pSibling->p_left;	//오른쪽 자식이 왼쪽 자식을 가지고 있었으면, 가운데로 옮겨줌

					//가운데 자식은 null로 설정
					parent->p_middle = NULL;
					
					left_right = 0;

				}
				else { 
					//삭제 하려는 노드가 부모의 왼쪽 자식이면
					/*
					1 삭제 시,
					 (4,7)              7
					 / | \      =>    /   \
					1  5  8         (4,5)  8
					*/
					//가운데 자식으로 병합함.
					pSibling = parent->p_middle;

					//가운데 자식의 오른쪽 키를 왼쪽 키로 옮기고, 왼쪽 키에 부모의 왼쪽키를 넣음
					pSibling->r_key = pSibling->l_key;
					pSibling->l_key = parent->l_key;
					//부모의 왼쪽 키에 부모의 오른쪽 키를 넣고,
					parent->l_key = parent->r_key;

					//가운데 자식의 왼쪽 자식이 가운데 자식으로 바뀜 
					middleChild = pSibling->p_left;

					//부모의 왼쪽 자식을 가운데 자식으로 변경하고,
					parent->p_left = pSibling;
					//가운데 자식은 null로 설정
					parent->p_middle = NULL;

					
					left_right = 0;
				}
				//부모는 이제 2노드가 됨
				parent->r_key = -1;
				parent->cnt = 1;
				
			}
			else { //부모와 자식이 모두 2노드 인 경우
				//부모의 오른쪽 자식 노드가 삭제하려는 노드면
				if (parent->p_right == node) {
					/*
					  5삭제 
						4               (  )
					   / \     =>      /   \
					  1   5        (1,4)    ( )
					*/
					//왼쪽 자식으로 병합함
					pSibling = parent->p_left;
					//왼쪽 자식의 오른쪽 키에 부모의 왼쪽 키 삽입
					pSibling->r_key = parent->l_key;

					//왼쪽 자식의 오른쪽 자식이 가운데로 바뀜(중간 노드의 경우)
					middleChild = pSibling->p_right;
				
					left_right = 1;

				}
				else {
					/*
					1삭제           
					  4              (  )
					 / \     =>	   /    \
					1   5		 ( )    (4,5)
					*/ 
					//오른쪽 자식으로 병합함
					pSibling = parent->p_right;
					//오른쪽 자식의 오른쪽 값에 기존 왼쪽 값을 넣고
					pSibling->r_key = pSibling->l_key;
					//왼쪽 값은 부모의 왼쪽 값으로 넣음
					pSibling->l_key = parent->l_key;
					//오른쪽 자식의 왼쪽 자식이 가운데로 바뀜(중간 노드의 경우)
					middleChild = pSibling->p_left;
					
					left_right = 0;
				}
				//부모가 공백이 됨.
				parentIsEmpty = 1;
			}			
			//합병된 자식은 이제 3노드가 됨
			pSibling->cnt = 2;

			//노드가 리프가 아니었을 경우
			if (!isLeafNode(node)) {
				/*
				19 삭제 시,
			    	(9,        15)          	(9,        15)      	
				    /     |      \      =>       /    |         \      pChild : (17,18)	
				    7    12    18               7      12       (  )         
				   / \   / \     / \		   / \   / \        / 		
				  1  8  10 13   17  19		  1  8  10 13   (17,18)   	   

						      (9,        15)      	
						      /    |         \      
				  =>        7      12       (  )         
						   / \    / \       / 		
						  1  8   10 13   (17,18)   	

						     9         	
						  /     \             
				  =>      7     (12,15) 
					     / \    /  |   \   
					    1  8   10 13  (17,18)

				*/
				pSibling->p_middle = middleChild;	//새로 병합된 노드의 가운데 자식을 업데이트 해주고,

				//가운데 자식의 부모를 다시 병합된 노드로 저장해준다.
				if (middleChild != NULL)middleChild->p_parent = pSibling;
				// pChild를 방향에 맞게, 오른쪽이나 왼쪽에 붙여준다.
				if (left_right == 0){
					pSibling->p_left = pChild;
					if (pChild != NULL) pChild->p_parent = pSibling;
				}
				else{
					pSibling->p_right = pChild;
					if (pChild != NULL) pChild->p_parent = pSibling;
				}
			}

			//삭제한  노드 메모리 해제
			free(node);

			if (parentIsEmpty) {	//부모가 삭제 되 었으면,	
				fix(parent, pSibling);	//부모노드와, 합병된 노드의 주소를 기준으로 트리를 고치는 함수를 재실행
			}		
		}
	}
}

void insertNode(int item) {
	if (root == NULL) {	//트리가 비어있는 경우.
		root = createNode(item);	//노드를 생성하고, 생성한 노드가 root  노드가 됨
	}
	else if (isLeafNode(root)) {	//루트 노드가 리프 노드인 경우
		if (root->cnt == 1) {	//값이 아직 하나만 있는 경우
			input_Item(root, item);	//아이템을 삽입함
		}
		else {	//2개가 다 찬 경우 노드를 분할함(level 1 증가)
			root = splitNode(root, createNode(item), 0);
		}
	}
	else {	//그 외의 모든 경우는 재귀적으로 노드의 말단 까지 이동함.
		insertRec(root, item);
	}

}
//노드를 분할하는 함수
BTNode* splitNode(BTNode* n, BTNode* x, int pos) {

	//세개의 값을 정렬 (가운데 값 찾기)
	int* arr = sortData(n->l_key, n->r_key, x->l_key);
	
	BTNode* p = createNode(arr[1]);//가운데 값이 새로운 부모
	BTNode* l = createNode(arr[0]);//작은 값은 왼쪽 자식
	BTNode* r = createNode(arr[2]);//큰 값은 오른쪽 자식
	
	BTNode* nodeCache[4];	

	free(arr);	//배열은 메모리 해제

	p->p_left = l;	//새로운 부모에 왼쪽 자식을 연결
	p->p_right = r;	//새로운 부모에 오른쪽 자식을 연결

	l->p_parent = p;	//왼쪽 자식에게 부모의 주소를 알려줌
	r->p_parent = p;	//오른쪽 자식에게 부모의 주소를 알려줌

	if (pos == 0) {   //왼쪽
		/*
		//2가 삽입 하려고 했던 상태
			 (n: 4, 7)
		      /  |  \
 		  (1,3)  5   8					(p : 4)
										/	  \			 
			(x:2)					   2       7
			/   \                     / \     / \
		   1     3                   1   3    5  8
		*/

		nodeCache[0] = x->p_left;
		nodeCache[1] = x->p_right;
		nodeCache[2] = n->p_middle;
		nodeCache[3] = n->p_right;
	}
	else if (pos == 2) {	//오른쪽
		/*
		 //10삽입
			 (n: 4, 7)
		      /  |  \
 		     3   5   (8,9)				(p : 7)
										/	  \			 
			(x:9)					   4       9
			/   \                     / \     / \
		   8     10                  3   5    8  10
		*/

		nodeCache[0] = n->p_left;
		nodeCache[1] = n->p_middle;
		nodeCache[2] = x->p_left;
		nodeCache[3] = x->p_right;
	}
	else {				//가운데
		/*
		//7삽입
		     (n: 4, 10)
		     /    |    \
		    3   (5,6)   12				(p : 6)
			                             /	  \
		 (x:6)					        4       10
		 /   \                         / \     / \
		5    7                        3   5    7  12
		*/
		nodeCache[0] = n->p_left;
		nodeCache[1] = x->p_left;
		nodeCache[2] = x->p_right;
		nodeCache[3] = n->p_right;
	}
	//기존에 자식들이 있었으면,
	if (nodeCache[0] != NULL) {

		//새롭게 만든 노드에 연결해줌
		l->p_left = nodeCache[0];
		l->p_right = nodeCache[1];
		nodeCache[0]->p_parent = nodeCache[1]->p_parent = l;
		r->p_left = nodeCache[2];
		r->p_right = nodeCache[3];
		nodeCache[2]->p_parent = nodeCache[3]->p_parent = r;
	}
	return p;
}
//n이 parent의 어느 위치의 자식인지 판별하는 함수
int computePos(BTNode* parent, BTNode* n) {
	if (parent->p_left == n) return 0;    //왼쪽 자식이면 0반환
	else if (parent->p_middle == n) return 1; //가운데 자식이면 1 반환
	else return 2;  //오른쪽 자식이면 2반환
}
void insertRec(BTNode* n, int item) {
	int pos;
	BTNode* np;
	BTNode* p;
	if (n != NULL &&isLeafNode(n)) {		//leaf 노드인경우
		if (n->cnt == 1) {	//칸이 비어 있으면 그 노드에 키 삽입
			input_Item(n, item);
		}
		else {	//leaf 가 가득 차있는 경우
			//leaf 가 가득차 있는 경우 분할 해야되는데, 먼저 위치부터 찾고
			pos = computePos(n->p_parent, n);
			//분할 작업 하고, 새로 분할한 노드를 np에 저장
			np = splitNode(n, createNode(item), pos);
			while (n->p_parent != root) {	//루트까지 반복
				p = n->p_parent;	
				if (p->cnt == 1) {//부모가 아직 여유공간이 있는 경우에는
					
					input_Item(p, np->l_key);	//부모에 새로만든 노드인 np의 키값을 넣고
					pos = computePos(p, n);	//위치를 찾아서,
					if (pos == 0) {	//n이 왼쪽에 있었으면,
						//새로 만든 np 노드의 왼쪽, 오른쪽 자식을 p의 왼쪽 중간 자식에 연결

						/*
						3삽입
						 (p: 4  )              (np: 2)            (2,4)
						 /       \       +     /     \    =>     / | \
					  (1,2)       5           1       3         1  3  5
						*/
						p->p_left = np->p_left;	
						p->p_middle = np->p_right;
					}
					else if (pos == 2) {	//오른쪽 인경우 중간, 오른쪽에  자식 연결
						/*
						5삽입
						  (p: 3  )              (np: 5)           (3,5)
						 /       \        +     /     \    =>     / | \
						 1     (n  : 4,7)      4       7         1  4  7
						*/

						p->p_middle = np->p_left;
						p->p_right = np->p_right;
					}
					//np의 왼쪽과 오른쪽 자식들이 비어 있지 않은 경우에는 부모로 연결해줌
					if (np->p_left != NULL){
						np->p_left->p_parent = p;
					}
					if (np->p_right != NULL){
						np->p_right->p_parent = p;
					}
					free(np);	//np 메모리 해제
					break;  //삽입 완료
				}
				else {    //부모에서 공간이 없으면,
					pos = computePos(p, n);   //n의 위치를 파악하고,
					n = n->p_parent;  //n을 부모로 바꾸고
					np = splitNode(n, np, pos);   //분할 함
				}
			}

			if (n->p_parent == root) { //돌다가 부모가 루트면,
				pos = computePos(n->p_parent, n);   //위치를 찾고
				p = n->p_parent;
				if (p->cnt == 1) {   //루트가 공간이 있으면
					input_Item(n->p_parent, np->l_key);	//집어 넣고
					if (pos == 0) {		//자식( n)이 왼쪽에 있으면

						/*
						3삽입
						(p: 4  )              (np: 2)            (2,4)
						/       \       +     /     \    =>     / | \
						(1,2)    5           1       3         1  3  5
						*/
						p->p_left = np->p_left;
						p->p_middle = np->p_right;
					}
					else if (pos == 2) {   //자식이 오른쪽에 있으면
						/*
						5삽입
						(p: 3  )              (np: 5)           (3,5)
						/       \        +     /     \    =>     / | \
						1     (n  : 4,7)      4       7         1  4  7
						*/
						p->p_middle = np->p_left;
						p->p_right = np->p_right;
					}
					//부모 연결
					if (np->p_left != NULL){
						np->p_left->p_parent = p;
					}
					if (np->p_right != NULL){
						np->p_right->p_parent = p;
					}
					free(np); 
				}
				else {    //부모에 공간이 없으면,
					pos = computePos(n->p_parent, n);
					n = n->p_parent;	
					root = splitNode(n, np, pos);    //루트가 분할 되면서 레벨 1 증가
				}
			}
		}
	}
	else {
		if (n->cnt == 1) { //2-노드 인경우
			if (item < n->l_key) insertRec(n->p_left, item);		//삽입 하려는 값이 왼쪽 보다 작으면 왼쪽 서브 트리 방문
			else insertRec(n->p_right, item);						//삽입 하려는 값이 왼쪽 키값 보다 크면 오른쪽 서브 트리 방문
		}
		else { //3-노드 인경우
			if (item < n->l_key) insertRec(n->p_left, item);		//삽입 하려는 값이 왼쪽 키값 보다 작으면 왼쪽 서브트리 방문
			else if (item > n->r_key) insertRec(n->p_right, item);  //삽입 하려는 값이 오른쪽 키값 보다 크면 왼쪽 서브트리 방문
			else insertRec(n->p_middle, item);						//두 값 사이에 있으면, 가운데 서브트리 방문
		}
	}
}