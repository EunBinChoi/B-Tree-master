#pragma once
#include <stdio.h>
#include <stdlib.h>
#define SIZE 2 //Ű ����
typedef struct bTNode{
	int r_key;		//������ Ű(ū ��)
	int l_key;		//���� Ű(���� ��)
	struct bTNode* p_left;	//���� �ڽ��� �ּ�(���� Ű�� ���� ���� ��)
	struct bTNode* p_middle;	//�߰� �ڽ��� �ּ�	(������ Ű���� ���� Ű���� ���� ��)
	struct bTNode* p_right;		//������ �ڽ��� �ּ�
	struct bTNode* p_parent;	//�θ��� �ּ�
	int cnt;		//Ű ���� 
}BTNode;

BTNode* root;	//��Ʈ�� �ּ�
int isThreeNode(BTNode* n);	//�ش� ��� n�� Ű�� 2�� ���� �˻��ϴ� �Լ�
int isLeafNode(BTNode* n);	//�ش� ��� n�� ���� ������� �Ǻ��ϴ� �Լ�

//print
void print_tree(BTNode* r);		// ���� ��ȸ ��� ��� �Լ�
void print_tree_level(BTNode* root, int level);	//���� ���� ��� �Լ�


//���� ���� �Լ�
BTNode* createNode(int n);	//n�̶�� Ű���� ������ ��� ���� �Լ�
int* sortData(int a, int b, int c);	//a,b,c ���� �����ؼ� �迭�� �ּҸ� ��ȯ���ִ� �Լ�
void input_Item(BTNode* n, int item);	//n ���(2-node)�� item ���� �����ϴ� �Լ�
void insertNode(int item);						//item���� Ʈ���� �������ִ� �Լ�
BTNode* splitNode(BTNode* n, BTNode* x, int pos);	//��带 ���� �ϴ� �Լ�
int computePos(BTNode* parent, BTNode* n);		//n�� parent�� ��� ��ġ�� �ڽ����� �Ǻ��ϴ� �Լ�
void insertRec(BTNode* n, int item);			//��������� item�� ���� ����


//���� ���� �Լ�
int removeNode(int item);		//key ���� ���� �ϴ� �Լ�
BTNode* FindNextLargest(int item, BTNode* n);	//
void fix(BTNode* node, BTNode* pChild);	//
int Redistribute(BTNode* node, int* situation);


//Ʈ�� ��ü ����
void destroy(BTNode* n);

void destroy(BTNode* n){
	//NULL�� ��� �Լ� ����
	if (n == NULL){
		return;
	}
	if (isThreeNode(n)){		//3����� ���
		//3���� �ڽ��� ��� ���ȣ��
		destroy(n->p_left);
		destroy(n->p_middle);
		destroy(n->p_right);

		//3���� �ڽ��� ��� ȣ�� �� �� n �޸� ����
		free(n);
	}
	else{  //2��� �� ���
		//2���� �ڽ��� ��� ȣ��
		destroy(n->p_left);
		destroy(n->p_right);
		//ȣ�� �� �޸� ����
		free(n);
	}
}


//���� �� á���� �˻�
int isThreeNode(BTNode* n) {
	if (n->cnt >= SIZE)
		return 1;
	else
		return 0;
}
//������ ������� �˻�
int  isLeafNode(BTNode* n) {
	//�ƹ��͵� �����Ѱ� ������ ���� ��� 
	if (n->p_left == NULL && n->p_right == NULL && n->p_middle == NULL) return 1;
	else return 0;
}

//Ʈ���� ���� �������� ��� 
void print_tree_level(BTNode* n, int level)
{
	int j;
	
	if (n != NULL)
	{
		//���� �ڽ� ȣ���ϰ�(���� 1 ����)
		print_tree_level(n->p_left, level + 1);
		
		//���� ��ŭ ���ο� | ���
		for (j = 0; j < level; j++)
			printf("|  ");

		//���� Ű ���
		printf("+[%2d]\n", n->l_key);
		
		//��� �ڽ� ȣ���ϰ�(���� 1 ����)
		print_tree_level(n->p_middle, level + 1);

		//���� ��ŭ ���ο� | ���
		for (j = 0; j < level; j++)
			printf("|  ");

		//������ Ű�� ��� ������, ���� ���
		if (n->r_key == -1)
			printf("+[  ]\n");
		else //��� ���� ���� ���� ������ Ű ���
			printf("+[%2d]\n", n->r_key);
		
		//������ �ڽ� ȣ��
		print_tree_level(n->p_right, level + 1);
	}
}
//���� ���ܹ������ ����ϴ� �Լ�
void print_tree(BTNode* r)
{
	if (r != NULL)
	{
		if (isThreeNode(r)){	//3 node �� ���
			//���� �ڽ� ȣ�� -> �� ��� -> �߰� �ڽ� ȣ�� -> �� ��� -> ������ �ڽ� ȣ��
			print_tree(r->p_left);
			printf("(%d, %d, %d)\n", r->cnt, r->l_key, r->r_key);
			print_tree(r->p_middle);
			if (r->p_middle)
				printf("(%d, %d, %d)\n", r->cnt, r->l_key, r->r_key);
			print_tree(r->p_right);
		}
		else{ //2 node
			//���� �ڽ� ȣ�� -> �� ��� -> ������ �ڽ� ȣ��
			print_tree(r->p_left);
			printf("(%d, %d)\n", r->cnt, r->l_key);
			print_tree(r->p_right);
		}

	}
}

BTNode* search(BTNode* n, int item){
	//�ش� item�� ������ key ���� Ž����
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
		if (item < n->l_key) search(n->p_left, item);		//Ž�� �Ϸ��� ���� ���� ���� ������ ���� ���� Ʈ�� �湮
		else search(n->p_right, item);						//Ž�� �Ϸ��� ���� ���� Ű�� ���� ũ�� ������ ���� Ʈ�� �湮
	}
	else { //3-node
		if (item < n->l_key) search(n->p_left, item);		//Ž�� �Ϸ��� ���� ���� Ű�� ���� ������ ���� ����Ʈ�� �湮
		else if (item > n->r_key) search(n->p_right, item); //Ž�� �Ϸ��� ���� ������ Ű�� ���� ũ�� ���� ����Ʈ�� �湮
		else search(n->p_middle, item);						//�� �� ���̿� ������, ��� ����Ʈ�� �湮
	}
}

//���� Ű���� n �� ��� ����
BTNode* createNode(int n)
{
	BTNode* tmp;

	//���� �Ҵ����� ��� ����
	tmp = (BTNode*)malloc(sizeof(BTNode));
	tmp->cnt = 1;			//Ű���� �Ѱ�
	tmp->p_parent = NULL;	//�θ�� ���� ����
	tmp->r_key = -1;		//������ Ű���� ����
	tmp->l_key = n;			//���� Ű���� n
	tmp->p_left = NULL;		// �ڽ� ��� ���� ����
	tmp->p_middle = NULL;
	tmp->p_right = NULL;
	return tmp;			//���� ��� �ּ� ��ȯ
}
//��� �� ã������..
int* sortData(int a, int b, int c) {
	//a : ���� l value
	//b : ���� r value
	//c : ���ο� ��,
	//���� �迭�� �����ؼ�, 3���� ���� ���ʷ� ������ ���� ����
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
	return arr; //�ּ� ��ȯ
}
void input_Item(BTNode* n, int item) {
	if (n->l_key > item) {	//�������� �ϴ� �������� ���� Ű���� ������,
		n->r_key = n->l_key;	//������ Ű�� ���� ���� Ű�� �ְ�
		n->l_key = item;		//���� Ű�� ���ο� Ű���� ����
	}
	else   //�׷��� �ʴ� ��� �������� ���� �׳� �����ʿ� ������ ��
	{
		n->r_key = item;
	}
	//Ű ������ ���� �� ��
	n->cnt = 2;
}
BTNode* FindNextLargest(int item, BTNode* n){
	BTNode* next = 0;
	
	//item�� ��ü�� ������ �ڽ��� ã�� ���� ����
	//�ش� Ű���� �������� ���� ����Ʈ���� �ִ밪, Ȥ�� ������ ����Ʈ���� �ּҰ��� ������ �ڽ��� ��
	//���� �ڵ忡���� ������ ����Ʈ���� �ּҰ��� ã�� ����� �����
	//n�� 3��� �̸鼭, ���� ���� item�� ��� 
	//item�� ������ ���� Ʈ���� middle�� �Ǳ� ������ next�� middle ���� ������.
	if (isThreeNode(n) && n->l_key == item){
		next = n->p_middle;
	}
	else{
		//2����� ��� ������ ����Ʈ���� ������.
		next = n->p_right;
	}

	//���� ����Ʈ������ �������� leaf ���� ��������, �ش� leaf�� �ּҰ��� ����.
	while (!isLeafNode(next)){
		next = next->p_left;
	}
	//�ּ� ���� �ִ�  leaf �� �ּҸ� ��ȯ��.
	return next;
}
int removeNode(int item){
	BTNode* n = search(root, item);	//���� �Ϸ��� �������� �ִ� ��带 ã�� �ּҸ� n�� ����
	BTNode* leafNode ;		//�ӽ� �����
	int tmp = 0;
	if (n == NULL) return 0;	//ã������ ���� ������ 0�� ��ȯ

	if (!isLeafNode(n)){	//�����Ϸ��� ���� �ִ� ��尡 ������尡 �ƴϸ�
		// ������ �ڽ��� ã�� (���� ����Ʈ���� ���� ū ��, �Ǵ� ������ ����Ʈ���� ���� ���� ���� ������ �ڽ��� ��)
		leafNode = FindNextLargest(item, n);

		//������ �ڽİ� Ű���� ��ȯ��
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
		//���� ����� ��� leaf��  n���� ������
		leafNode = n;
	}

	if (isThreeNode(leafNode)){	//������尡 3����ΰ��
		if (item == leafNode->l_key){		//�����Ϸ��� ���� ���ʿ� ������,
			leafNode->l_key = leafNode->r_key;	//������ ���� �������� �Ű� �ְ�
		}
		leafNode->r_key = -1;	//������ ���� ����
		leafNode->cnt= 1;		//���� �ش� ���� ���� 2��尡 ��
	}
	else{
		fix(leafNode,0);	//������尡 2��� �ΰ�� Ű���� �ϳ� �ۿ� ���� ������, Ʈ���� ��ġ�� ������ �ʿ���
		
	}
	return 1;
}
void ReassignChildren(BTNode* node, BTNode* pChildOfNode, int situation)
{
	//�θ��带  parent�� ������
	BTNode* parent = node->p_parent;

	switch (situation) {

	case 1:
		//case 1 �θ� 3 ����̰�, ������ ��尡 ���ʿ� �ְ�, ��� ������ 3��� �϶�,
		/*  
		(20,      40)    (a)    (30,     40)     (b)   (30,     40)
		/      |     \     =>   /     |    \     =>    /     |    \
	   ( )   (30,35)   50      20    35     50        20    35    50
		|     /  | \   /\      |    / | \   /\        /\    / \   /\
		C   29 32  37 60 70    C  29 32 37 45 70     C 29 32  37 45 70 */
		//������ ����� ���� �ڽ��� pChildOfNode�� �����ϰ� �θ� ����  
		node->p_left = pChildOfNode;
		if (node->p_left != NULL) node->p_left->p_parent = node;

		//������ ��� ������ �ڽĿ� ��й�� ��� ������ �����ڽ��� ������ 
		node->p_right = parent->p_middle->p_left;
		if (node->p_right != NULL) node->p_right->p_parent = node;

		//��й�� ��� ����� ���� �ڽ��� ������ ���� ������ ���±� ������,
		//��й�� ��� ����� ��� �ڽ��� ���� �ڽ����� �Ű���
		parent->p_middle->p_left = parent->p_middle->p_middle;
		if (parent->p_middle->p_left != NULL) parent->p_middle->p_left->p_parent = parent->p_middle;
		parent->p_middle->p_middle = NULL;
		break;
	case 2: //case 2 �θ� 3 ����̰�, ������ ��尡 ���ʿ� �ְ�, ������ ������ 3��� �϶�,

		/*      (10,         20)     Redist.   (15,   30)		            (15,   30)
		         /      |     \       =>     /     |    \      Reassign    /    |     \ 
		       ( )     15    (30,40)        10    20     40        =>      10   20     40 
		        |      / \    / | \          |    / \   / | \    Children / \   / \   / \ 
		        5    12  17  25 35 70        5   12 17 25 35 70          5  12 17 25 35 70
				  */ 
		//������ ����� ���� �ڽ��� pChildOfNode�� �����ϰ� �θ� ����         											      
		node->p_left = pChildOfNode;
		if (node->p_left != NULL) node->p_left->p_parent = node;

		//������ ��� ������ �ڽĿ� ��� ������ �����ڽ��� ������ 
		node->p_right = parent->p_middle->p_left;
		if (node->p_right != NULL) node->p_right->p_parent = node;

		//��� ������ ���� �ڽ��� ��� ������ ������ �ڽ��� ��ü�ϰ�,
		parent->p_middle->p_left = parent->p_middle->p_right;

		//��� ������ ������ �ڽ��� ������ ������ ���� �ڽ��� ��ü�Ѵ�.
		parent->p_middle->p_right = parent->p_right->p_left;
		if (parent->p_middle->p_right != NULL) parent->p_middle->p_right->p_parent = parent->p_middle;

		//������ ������ ���� �ڽ��� ������ �ڽ��� ��� �ڽ��� ü�Ѵ�.
		parent->p_right->p_left = parent->p_right->p_middle;
		parent->p_right->p_middle = NULL;
		break;

	case 3: //case 3 �θ� 3 ����̰�, ������ ��尡 ����� �ְ�, ���� ������ 3��� �϶�,


		/*																 	
		    (10,  20)          Redist. 	    (8,  20)          Reassign   	    (8,  20)          
		   /     |   \             =>  	   /     |   \          Children 	   /     |   \        
		(6,8)   ( )  (30, 40)          	  6     (10)  (30, 40)      =>   	  6     (10)  (30, 40)
		/ | \    |    /  |  \          	/ | \    |    /  |  \            	/  \    / \   /  |  \ 
		1 7 9    c   25 35  70         1  7 9    c   25 35  70			   1   7   9   c  25 35  70		
		*/
		//������ ����� ������ �ڽ��� pChildOfNode�� �����ϰ� �θ� ����    
		node->p_right = pChildOfNode;
		if (node->p_right != NULL)node->p_right->p_parent = node;

		//������ ����� ���� �ڽ��� ���� ������ ������ �ڽ��� ������
		node->p_left = parent->p_left->p_right;
		if (node->p_left != NULL) node->p_left->p_parent = node;
		
		//���� ��������� ������ �ڽ��� �߰� �ڽ����� �ٲ���
		parent->p_left->p_right = parent->p_left->p_middle;
		parent->p_left->p_middle = NULL;
		break;

	case 4: //case 4 �θ� 3����̰�, ������ ��尡 ����� �ְ�, ������ ������ 3��� �϶�,
		/*    
		      (10,  20)          Redist.    (10,  30)       Reassign      (10,     30)
		     /    |    \         =>          /    |    \     Children      /      |   \
		(5,8)    ( )  (30, 40)           (5,8)    20    40      =>       (5,8)   20    40
		/  | \    |   /   |  \          /  | \    |    / | \             / | \    /\    / \
		1   7  9  17  25  35  70       1   7  9  17  25 35  70        1  7  9 17 25 35  70 */
		//������ ����� ���� �ڽ��� pChildOfNode�� �����ϰ� �θ� ����
		node->p_left = pChildOfNode;
		if (node->p_left != NULL)node->p_left->p_parent = node;

		//������ ����� ������ �ڽ��� ������ ������ ���� �ڽ��� ������
		node->p_right = parent->p_right->p_left;
		if (node->p_right != NULL) node->p_right->p_parent = node;

		//������ ������ ���� �ڽ��� ������ ������ �߰� �ڽ��� ������Ʈ ��
		parent->p_right->p_left = parent->p_right->p_middle;
		parent->p_right->p_middle = NULL;
		break;

	case 5:
		//case 5 �θ� 3����̰�, ������ ��尡 �����ʿ� �ְ�, ��� ������ 3��� �϶�,
		/*
		  (10,       25)              (10,      19)    Reassign      (10,       19)
		  /       |     \       =>    /      |      \   Children     /      |       \
		 5    (15, 19)   ( )         5       15      25    =>       5       15       25
		/ \    /  |  \    |         / \     / | \     |            / \     /  \     /  \
	   1   7  12 17  22  60        1   7  12  17 22  60           1   7  12   17  22   60   */
		//������ ����� ������ �ڽ��� pChildOfNode�� �����ϰ� �θ� ����    
		node->p_right = pChildOfNode;
		if (node->p_right != NULL) node->p_right->p_parent = node;

		//������ ����� ���� �ڽ��� ��� ������ ������ �ڽ����� ����
		node->p_left = parent->p_middle->p_right;
		if (node->p_left != NULL) node->p_left->p_parent = node;

		//��� ������ ������ �ڽ��� ��� �ڽ����� ��ü
		parent->p_middle->p_right = parent->p_middle->p_middle;
		parent->p_middle->p_middle = NULL;

	case 6:
		//case 6 �θ� 3����̰�, ������ ��尡 �����ʿ� �ְ�, ���� ������ 3��� �϶�,
		/* 
		     (20,       40)               (18,   30)           (18,    30)
		    /       |     \    Redist   /     |   \   Shift   /     |    \
		(10, 18)   30     ( )   =>   10     20    40   =>   10     20     40
		/  | \    /  \    /    (a)   / | \   / \   /   (b)  /  \   / \    / \
		5  12  19 25  32  55        5 12 19 25 32 55       5   12 19 25  32 55
		*/
		node->p_right = (node->p_left = pChildOfNode) ? node->p_left : node->p_right;
		if (pChildOfNode != NULL) pChildOfNode->p_parent = node;

		//������ ����� ���� �ڽ��� ��� ������ ������ �ڽ����� ��ü
		node->p_left = parent->p_middle->p_right;
		if (node->p_left != NULL) node->p_left->p_parent = node;

		//��� ������ ������ �ڽ��� ���� �ڽ��� ��ü
		parent->p_middle->p_right = parent->p_middle->p_left;
		//������ ������ ���� ������ ������ �ڽ����� ��ü
		parent->p_middle->p_left = parent->p_left->p_right;
		parent->p_middle->p_left->p_parent = parent->p_middle;
		//���� ������ ������ �ڽ��� ��� �ڽ����� ��ü
		parent->p_left->p_right = parent->p_left->p_middle;

		break;

	case 7: //case 7 �θ� 2����̰�, ������ ��尡 ���ʿ� �ְ�, ������ ������ 3��� �϶�,
		/*
		     20                            30                    30
	      	/  \         Redistribute     /  \      Reassign    /   \
		( )   (30, 40)     =>           20    40     =>       20     40
		 |    /  |  \                   |    / | \           / \    / \
	     5  25  35  50                  5  25  35  50       5  25 35  50 */

		//������ ����� ���� �ڽ��� pChildOfNode�� �����ϰ� �θ� ����  
		node->p_left = pChildOfNode;
		if (pChildOfNode != NULL) pChildOfNode->p_parent = node;

		//������ �ڽ��� ������ ������ ���� �ڽ����� ��ü
		node->p_right = parent->p_right->p_left;
		if (node->p_right != NULL) node->p_right->p_parent = node;

		//������ ������ ���� �ڽ��� ��� �ڽ����� ��ü
		parent->p_right->p_left = parent->p_right->p_middle;
		parent->p_right->p_middle = NULL;
		break;


	case 8: /* //case 8 �θ� 2����̰�, ������ ��尡 �����ʿ� �ְ�, ���� ������ 3��� �϶�,
			     50        After              40                        40
		     	/   \      Redistribute      /   \      Reassign       /  \
			(30, 40) ( )     =>           30     50       =>         30   50
			/  |  \   |                   / | \    |    Children     / \   / \
		   25  35 45  60                 25 35 45  60               25 35 45 60   */
		//������ ����� ������ �ڽ��� pChildOfNode�� �����ϰ� �θ� ����    
		node->p_right = pChildOfNode;
		if (pChildOfNode != NULL) pChildOfNode->p_parent = node;

		//������ ����� ���� �ڽ��� ���� ������ ������ �ڽ����� ��ü
		node->p_left = parent->p_left->p_right;
		if (node->p_left != NULL)node->p_left->p_parent = node;

		//���� ������ ������ �ڽ��� ���� �ڽ��� ����� ��ü
		parent->p_left->p_right = parent->p_left->p_middle;
		parent->p_right->p_middle = NULL;
		break;
	}
}
int Redistribute(BTNode* node, int* situation){
	int bRc = 1;
	BTNode *parent = node->p_parent;

	if (isThreeNode(parent)) {		//�θ� 3����� ���
		if (node == parent->p_left) { //���ʿ� ���� ��尡 ������
			if (isThreeNode(parent->p_middle)) { 
				//case 1 �θ� 3 ����̰�, ������ ��尡 ���ʿ� �ְ�, ��� ������ 3��� �϶�,
				/*
				(20,      40)           (30,     40)
				/      |     \    =>    /     |    \
			   ( )  (30,35)  50        20    35     50
				|    /  | \    /\       |    / | \   /\
				C   29 32  37 60 70     C  29 32 37 45 70
				*/

				
				//��������� ���� ���� �θ����� ���� ���� �ְ�
				node->l_key = parent->l_key;
				node->cnt = 1;

				//�θ� ����� ���ʿ� ��� ����� ���� ���� �ְ�
				parent->l_key = parent->p_middle->l_key;
				//��� ����� ���� ���� ������ ���� ����
				parent->p_middle->l_key = parent->p_middle->r_key;

				//��� ��� ũ�� 1 ����
				parent->p_middle->r_key = -1;
				parent->p_middle->cnt=1;

				*situation = 1;

			}
			else if (isThreeNode(parent->p_right)) {	//case 2 �θ� 3 ����̰�, ������ ��尡 ���ʿ� �ְ�, ������ ������ 3��� �϶�,
				/*
				(10,   20)                 (15,   30)
				/    |    \          =>    /    |    \
		     ( )    15    (30, 40)        10    20     40 */

				//���� ����� ���� ���� �θ��� ���� ���� �ְ�
				node->l_key = parent->l_key;
				node->cnt = 1;

				//�θ��� ���� ���� ��� �ڽ��� ���� ���� �ְ�
				parent->l_key = parent->p_middle->l_key;

				//��� �ڽ��� ���� ���� �θ��� ������ ���� �ְ�
				parent->p_middle->l_key = parent->r_key;

				//�θ��� ������ ���� ������ �ڽ��� ���� ���� �ְ�
				parent->r_key = parent->p_right->l_key;

				//�θ��� ������ �ڽ��� ���� ���� ������ �ڽ��� ������ ���� �ִ´�.
				parent->p_right->l_key = parent->p_right->r_key;

				//������ �ڽ��� ���� 2���
				parent->p_right->r_key = -1;
				parent->p_right->cnt = 1;
				*situation = 2;

			}
			else {
				//�θ�� 3������� �������� �� 2��� �� ���
				bRc = 0;
			}

		}
		else if (node == parent->p_middle) { //����� ���� �� ��尡 �ִ� ���
			//case 3 �θ� 3 ����̰�, ������ ��尡 ����� �ְ�, ���� ������ 3��� �϶�,
			if (isThreeNode(parent->p_left)) {
				//���ʿ� 3��尡 �ִ� ���
				/*
				(10, 20)                   (5, 20)
				/    |  \             =>   /   |  \
			 (1, 5) ( ) (30, 40)          1    10  (30, 40) */

				//������ ����� ���� ���� �θ��� ���� ������ �����ϰ�
				node->l_key = parent->l_key;
				node->cnt = 1;
				//�θ��� ���� ���� ���� �ڽ��� ������ ������ �����Ѵ�.
				parent->l_key = parent->p_left->r_key;

				//���� ���� �ڽ��� 2���
				parent->p_left->r_key = -1;
				parent->p_left->cnt = 1;

				*situation = 3;

			}
			//case 4 �θ� 3����̰�, ������ ��尡 ����� �ְ�, ������ ������ 3��� �϶�,
			else if (isThreeNode(parent->p_right)) {
				/*
				(10,    20)                 (10,  30)
				/    |    \           =>    /    |   \
				1   ( )  (30, 40)         1    20   40
				*/
				//������ ����� ���� ���� �θ��� ������ ������ �����ϰ�,
				node->l_key = parent->r_key;
				node->cnt = 1;
				//�θ��� ������ ���� ������ �ڽ� ����� ���� ������ �����ϰ�,
				parent->r_key = parent->p_right->l_key;
				//������ �ڽ��� ������ Ű�� �������� �ű��
				parent->p_right->l_key = parent->p_right->r_key;

				//���� ������ Ű�� 2���
				parent->p_right->r_key = -1;
				parent->p_right->cnt = 1;

				*situation = 4;
			}
			else {
				bRc = 0;
			}

		}
		else  { //�����ʿ� ���� ��尡 ������
			if (isThreeNode(parent->p_middle)) {
				//case 5 �θ� 3����̰�, ������ ��尡 �����ʿ� �ְ�, ��� ������ 3��� �϶�,
				/*
				(10,          25)              (10,       19)
				/       |       \       =>    /      |       \
				5    (15, 19)   ( )         5       15       25
			   / \    /  |  \    /          / \     / | \     /
		      1   7  12 17  22  60         1   7  12  17 18  60       */
				//���� ����� ���� Ű�� �θ��� ������ Ű�� �����ϰ�,
				node->l_key = parent->r_key;
				node->cnt = 1;

				//�θ��� ������ Ű�� ��� �ڽ��� ������ Ű�� �����ϰ�,
				parent->r_key = parent->p_middle->r_key;
			
				//��� �ڽ��� ���� 2���
				parent->p_middle->r_key = -1; 
				parent->p_middle->cnt = 1;

				*situation = 5;

			}
			else if (isThreeNode(parent->p_left)) {
				//case 6 �θ� 3����̰�, ������ ��尡 �����ʿ� �ְ�, ���� ������ 3��� �϶�,
			/*  
				(20,         40)               (18,   30)
				/        |     \      =>     /     |   \
			(10, 18)     30     ( )         10     20    40
			/  |   \    /  \    /          / | \   / \   /
			5  12  19  25  32  55         5  7 19 25 32 55      */

				//������ ����� ���� Ű���� �θ��� ������ ������ �ǰ�,
				node->l_key = parent->r_key;
				node->cnt = 1;
			
				//�θ��� ������ Ű���� ��� �ڽ��� ���� Ű������ �ǰ�,
				parent->r_key = parent->p_middle->l_key;
				//��� �ڽ��� ���� Ű���� �θ��� ���� Ű���� �ǰ�,
				parent->p_middle->l_key = parent->l_key;
				//�θ��� ���� Ű���� ���� �ڽ��� ������ ���� �ǰ�,
				parent->l_key = parent->p_left->r_key;

				//���� �ڽ��� ���� 2���
				parent->p_left->r_key = -1;
				parent->p_left->cnt = 1;
				*situation = 6;

			}
			else {	//������ 3��尡 ���� ���
				bRc = 0;
			}
		}

	}
	else { // �θ� 2����� ���
		if (parent->p_left == node) {	//���ʿ� �����Ϸ��� ���� �ִ� ���
			if (isThreeNode(parent->p_right)) {
				//case 7 �θ� 2����̰�, ������ ��尡 ���ʿ� �ְ�, ������ ������ 3��� �϶�,
				/* 
				  ( 30 )                (40 )
			      /     \         =>     /   \
				( )     (40,50)        30    50
				/        /              /     /
				5       35             5    35       */
				//���� �� ����� ���� Ű�� �θ��� ���� Ű�� ���� ���ְ�,
				node->l_key = parent->l_key;
				node->cnt = 1;

				//�θ��� ���� Ű�� ������ �ڽ��� ���� Ű�� �������ְ�,
				parent->l_key = parent->p_right->l_key;
				//������ �ڽ��� ���� Ű�� ������ Ű�� �ٲ���
				parent->p_right->l_key = parent->p_right->r_key; 
			
				//������ �ڽ��� ���� 2���
				parent->p_right->r_key = -1;
				parent->p_right->cnt = 1;
				*situation = 7;

			}
			else {
				//�ڽ��� ��� 2��� �� ���
				bRc = 0;
			}

		}
		else {  //�����ʿ� �����Ϸ��� ���� �ִ� ���
			if (isThreeNode(parent->p_left)) {
				//case 8 �θ� 2����̰�, ������ ��尡 �����ʿ� �ְ�, ���� ������ 3��� �϶�,
				/*
				       ( 30 )                (20 )
				      /     \         =>     /   \
				(10,20)     (  )            10    30
				/           /               /     /
				5          35              5      35       */
				//������ ����� ���� Ű�� �θ��� ���� Ű�� �����ϰ�,
				node->l_key = parent->l_key;
				node->cnt = 1;
				//�θ��� ���� Ű�� ���� �ڽ��� ������ Ű�� �����ϰ�
				parent->l_key = parent->p_left->r_key;

				//���� �ڽ��� ���� 2���
				parent->p_left->r_key = -1;
				parent->p_left->cnt = 1;
				*situation = 8;

			}
			else {	//�ڽ��� ��� 2��� �� ���
				bRc = 0;
			}
		}
	}
	return bRc;
}
void fix(BTNode* node, BTNode* pChild){
	BTNode* parent;				//�θ��� �ּ�
	BTNode* pSibling;		//�պ��� ��� �ڽ�
	BTNode* middleChild;	//������尡 �ƴ� ��쿡 �ڽĵ��� ��ġ�� �������ϱ� ����,
	int situation;				//���̽� ����
	int parentIsEmpty = 0;		//�θ� ������ ������ ����
	int left_right = 0; // 0 : left, 1: right
	//��ġ���� ��尡 ��Ʈ�ΰ��
	if (node == root){
		free(root);	//��Ʈ�� �޸� �����ϰ�
		root = pChild;	//�ڽ��� ��Ʈ�� �ٲ�
		if (pChild!=NULL) pChild->p_parent = NULL;
	}
	else{ 
		parent = node->p_parent;	//�θ� ������
		if (Redistribute(node, &situation)){	//��й�(���� ��� �� 3��尡 �ִ°��) �������� 
			if (!isLeafNode(node)) {		//��尡 leaf�� �ƴ� ���
				ReassignChildren(node, pChild, situation);	//�ڽ��� ������ؾ� ��
			}
		}
		else{ //��� ���� ��尡 2��� �ΰ�� ��й踦 �� �� ���� ����, �պ� ������ �����ؾ���
			if (isThreeNode(parent)){	//�θ� 3 ��� �ΰ�� 
				if (parent->p_right == node){	//���� �Ϸ��� ��尡 �θ��� ������ �ڽ��̸�,
					/*
					  18 ���� ��,				  
						(9,        15)          	   9      
						/    |      \      =>   	/     \              
					   7    c:12     17             7    (c:12,15)       
					*/
					
					pSibling = parent->p_middle;		// ��� �ִ� �������� �պ�
					pSibling->r_key = parent->r_key;	//������ ������ Ű�� �θ��� ������ Ű�� �ְ�, 
					

					middleChild = pSibling->p_right;	//������ ��� �ڽ��� ������ �ڽ��� ������ �־����� ����� �Ű��� 

					parent->p_right = pSibling;			//��� ������ �θ��� ������ �ڽ����� �Ű� �ְ�
					parent->p_middle = NULL;			//�θ��� ��� �ڽ��� NULL�� ����

					left_right = 1;						//������ �����ʿ��� �����
				}
				else if (parent->p_middle == node) {
					//���� �Ϸ��� ��尡 �θ��� ��� �ڽ��̸�
					/*
					 5 ���� ��,
					(4,7)             4
					/ | \      =>    / \
				   1  5  8          1  (7,8)
					*/
					//������ �ڽ����� �պ���
					pSibling = parent->p_right;

					//������ �ڽ��� ������ ���� ���� ���� ���� �ְ�
					// ���� ������ �θ��� ������ ���� �°����
					pSibling->r_key = pSibling->l_key;
					pSibling->l_key = parent->r_key;

					//������尡 �ƴ� ��츸 �ǹ̰� ����.
					middleChild = pSibling->p_left;	//������ �ڽ��� ���� �ڽ��� ������ �־�����, ����� �Ű���

					//��� �ڽ��� null�� ����
					parent->p_middle = NULL;
					
					left_right = 0;

				}
				else { 
					//���� �Ϸ��� ��尡 �θ��� ���� �ڽ��̸�
					/*
					1 ���� ��,
					 (4,7)              7
					 / | \      =>    /   \
					1  5  8         (4,5)  8
					*/
					//��� �ڽ����� ������.
					pSibling = parent->p_middle;

					//��� �ڽ��� ������ Ű�� ���� Ű�� �ű��, ���� Ű�� �θ��� ����Ű�� ����
					pSibling->r_key = pSibling->l_key;
					pSibling->l_key = parent->l_key;
					//�θ��� ���� Ű�� �θ��� ������ Ű�� �ְ�,
					parent->l_key = parent->r_key;

					//��� �ڽ��� ���� �ڽ��� ��� �ڽ����� �ٲ� 
					middleChild = pSibling->p_left;

					//�θ��� ���� �ڽ��� ��� �ڽ����� �����ϰ�,
					parent->p_left = pSibling;
					//��� �ڽ��� null�� ����
					parent->p_middle = NULL;

					
					left_right = 0;
				}
				//�θ�� ���� 2��尡 ��
				parent->r_key = -1;
				parent->cnt = 1;
				
			}
			else { //�θ�� �ڽ��� ��� 2��� �� ���
				//�θ��� ������ �ڽ� ��尡 �����Ϸ��� ����
				if (parent->p_right == node) {
					/*
					  5���� 
						4               (  )
					   / \     =>      /   \
					  1   5        (1,4)    ( )
					*/
					//���� �ڽ����� ������
					pSibling = parent->p_left;
					//���� �ڽ��� ������ Ű�� �θ��� ���� Ű ����
					pSibling->r_key = parent->l_key;

					//���� �ڽ��� ������ �ڽ��� ����� �ٲ�(�߰� ����� ���)
					middleChild = pSibling->p_right;
				
					left_right = 1;

				}
				else {
					/*
					1����           
					  4              (  )
					 / \     =>	   /    \
					1   5		 ( )    (4,5)
					*/ 
					//������ �ڽ����� ������
					pSibling = parent->p_right;
					//������ �ڽ��� ������ ���� ���� ���� ���� �ְ�
					pSibling->r_key = pSibling->l_key;
					//���� ���� �θ��� ���� ������ ����
					pSibling->l_key = parent->l_key;
					//������ �ڽ��� ���� �ڽ��� ����� �ٲ�(�߰� ����� ���)
					middleChild = pSibling->p_left;
					
					left_right = 0;
				}
				//�θ� ������ ��.
				parentIsEmpty = 1;
			}			
			//�պ��� �ڽ��� ���� 3��尡 ��
			pSibling->cnt = 2;

			//��尡 ������ �ƴϾ��� ���
			if (!isLeafNode(node)) {
				/*
				19 ���� ��,
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
				pSibling->p_middle = middleChild;	//���� ���յ� ����� ��� �ڽ��� ������Ʈ ���ְ�,

				//��� �ڽ��� �θ� �ٽ� ���յ� ���� �������ش�.
				if (middleChild != NULL)middleChild->p_parent = pSibling;
				// pChild�� ���⿡ �°�, �������̳� ���ʿ� �ٿ��ش�.
				if (left_right == 0){
					pSibling->p_left = pChild;
					if (pChild != NULL) pChild->p_parent = pSibling;
				}
				else{
					pSibling->p_right = pChild;
					if (pChild != NULL) pChild->p_parent = pSibling;
				}
			}

			//������  ��� �޸� ����
			free(node);

			if (parentIsEmpty) {	//�θ� ���� �� ������,	
				fix(parent, pSibling);	//�θ����, �պ��� ����� �ּҸ� �������� Ʈ���� ��ġ�� �Լ��� �����
			}		
		}
	}
}

void insertNode(int item) {
	if (root == NULL) {	//Ʈ���� ����ִ� ���.
		root = createNode(item);	//��带 �����ϰ�, ������ ��尡 root  ��尡 ��
	}
	else if (isLeafNode(root)) {	//��Ʈ ��尡 ���� ����� ���
		if (root->cnt == 1) {	//���� ���� �ϳ��� �ִ� ���
			input_Item(root, item);	//�������� ������
		}
		else {	//2���� �� �� ��� ��带 ������(level 1 ����)
			root = splitNode(root, createNode(item), 0);
		}
	}
	else {	//�� ���� ��� ���� ��������� ����� ���� ���� �̵���.
		insertRec(root, item);
	}

}
//��带 �����ϴ� �Լ�
BTNode* splitNode(BTNode* n, BTNode* x, int pos) {

	//������ ���� ���� (��� �� ã��)
	int* arr = sortData(n->l_key, n->r_key, x->l_key);
	
	BTNode* p = createNode(arr[1]);//��� ���� ���ο� �θ�
	BTNode* l = createNode(arr[0]);//���� ���� ���� �ڽ�
	BTNode* r = createNode(arr[2]);//ū ���� ������ �ڽ�
	
	BTNode* nodeCache[4];	

	free(arr);	//�迭�� �޸� ����

	p->p_left = l;	//���ο� �θ� ���� �ڽ��� ����
	p->p_right = r;	//���ο� �θ� ������ �ڽ��� ����

	l->p_parent = p;	//���� �ڽĿ��� �θ��� �ּҸ� �˷���
	r->p_parent = p;	//������ �ڽĿ��� �θ��� �ּҸ� �˷���

	if (pos == 0) {   //����
		/*
		//2�� ���� �Ϸ��� �ߴ� ����
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
	else if (pos == 2) {	//������
		/*
		 //10����
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
	else {				//���
		/*
		//7����
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
	//������ �ڽĵ��� �־�����,
	if (nodeCache[0] != NULL) {

		//���Ӱ� ���� ��忡 ��������
		l->p_left = nodeCache[0];
		l->p_right = nodeCache[1];
		nodeCache[0]->p_parent = nodeCache[1]->p_parent = l;
		r->p_left = nodeCache[2];
		r->p_right = nodeCache[3];
		nodeCache[2]->p_parent = nodeCache[3]->p_parent = r;
	}
	return p;
}
//n�� parent�� ��� ��ġ�� �ڽ����� �Ǻ��ϴ� �Լ�
int computePos(BTNode* parent, BTNode* n) {
	if (parent->p_left == n) return 0;    //���� �ڽ��̸� 0��ȯ
	else if (parent->p_middle == n) return 1; //��� �ڽ��̸� 1 ��ȯ
	else return 2;  //������ �ڽ��̸� 2��ȯ
}
void insertRec(BTNode* n, int item) {
	int pos;
	BTNode* np;
	BTNode* p;
	if (n != NULL &&isLeafNode(n)) {		//leaf ����ΰ��
		if (n->cnt == 1) {	//ĭ�� ��� ������ �� ��忡 Ű ����
			input_Item(n, item);
		}
		else {	//leaf �� ���� ���ִ� ���
			//leaf �� ������ �ִ� ��� ���� �ؾߵǴµ�, ���� ��ġ���� ã��
			pos = computePos(n->p_parent, n);
			//���� �۾� �ϰ�, ���� ������ ��带 np�� ����
			np = splitNode(n, createNode(item), pos);
			while (n->p_parent != root) {	//��Ʈ���� �ݺ�
				p = n->p_parent;	
				if (p->cnt == 1) {//�θ� ���� ���������� �ִ� ��쿡��
					
					input_Item(p, np->l_key);	//�θ� ���θ��� ����� np�� Ű���� �ְ�
					pos = computePos(p, n);	//��ġ�� ã�Ƽ�,
					if (pos == 0) {	//n�� ���ʿ� �־�����,
						//���� ���� np ����� ����, ������ �ڽ��� p�� ���� �߰� �ڽĿ� ����

						/*
						3����
						 (p: 4  )              (np: 2)            (2,4)
						 /       \       +     /     \    =>     / | \
					  (1,2)       5           1       3         1  3  5
						*/
						p->p_left = np->p_left;	
						p->p_middle = np->p_right;
					}
					else if (pos == 2) {	//������ �ΰ�� �߰�, �����ʿ�  �ڽ� ����
						/*
						5����
						  (p: 3  )              (np: 5)           (3,5)
						 /       \        +     /     \    =>     / | \
						 1     (n  : 4,7)      4       7         1  4  7
						*/

						p->p_middle = np->p_left;
						p->p_right = np->p_right;
					}
					//np�� ���ʰ� ������ �ڽĵ��� ��� ���� ���� ��쿡�� �θ�� ��������
					if (np->p_left != NULL){
						np->p_left->p_parent = p;
					}
					if (np->p_right != NULL){
						np->p_right->p_parent = p;
					}
					free(np);	//np �޸� ����
					break;  //���� �Ϸ�
				}
				else {    //�θ𿡼� ������ ������,
					pos = computePos(p, n);   //n�� ��ġ�� �ľ��ϰ�,
					n = n->p_parent;  //n�� �θ�� �ٲٰ�
					np = splitNode(n, np, pos);   //���� ��
				}
			}

			if (n->p_parent == root) { //���ٰ� �θ� ��Ʈ��,
				pos = computePos(n->p_parent, n);   //��ġ�� ã��
				p = n->p_parent;
				if (p->cnt == 1) {   //��Ʈ�� ������ ������
					input_Item(n->p_parent, np->l_key);	//���� �ְ�
					if (pos == 0) {		//�ڽ�( n)�� ���ʿ� ������

						/*
						3����
						(p: 4  )              (np: 2)            (2,4)
						/       \       +     /     \    =>     / | \
						(1,2)    5           1       3         1  3  5
						*/
						p->p_left = np->p_left;
						p->p_middle = np->p_right;
					}
					else if (pos == 2) {   //�ڽ��� �����ʿ� ������
						/*
						5����
						(p: 3  )              (np: 5)           (3,5)
						/       \        +     /     \    =>     / | \
						1     (n  : 4,7)      4       7         1  4  7
						*/
						p->p_middle = np->p_left;
						p->p_right = np->p_right;
					}
					//�θ� ����
					if (np->p_left != NULL){
						np->p_left->p_parent = p;
					}
					if (np->p_right != NULL){
						np->p_right->p_parent = p;
					}
					free(np); 
				}
				else {    //�θ� ������ ������,
					pos = computePos(n->p_parent, n);
					n = n->p_parent;	
					root = splitNode(n, np, pos);    //��Ʈ�� ���� �Ǹ鼭 ���� 1 ����
				}
			}
		}
	}
	else {
		if (n->cnt == 1) { //2-��� �ΰ��
			if (item < n->l_key) insertRec(n->p_left, item);		//���� �Ϸ��� ���� ���� ���� ������ ���� ���� Ʈ�� �湮
			else insertRec(n->p_right, item);						//���� �Ϸ��� ���� ���� Ű�� ���� ũ�� ������ ���� Ʈ�� �湮
		}
		else { //3-��� �ΰ��
			if (item < n->l_key) insertRec(n->p_left, item);		//���� �Ϸ��� ���� ���� Ű�� ���� ������ ���� ����Ʈ�� �湮
			else if (item > n->r_key) insertRec(n->p_right, item);  //���� �Ϸ��� ���� ������ Ű�� ���� ũ�� ���� ����Ʈ�� �湮
			else insertRec(n->p_middle, item);						//�� �� ���̿� ������, ��� ����Ʈ�� �湮
		}
	}
}