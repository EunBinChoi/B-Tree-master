#include <stdio.h>
#include <conio.h>
#include "BTree.h"

//�޴� ��� �Լ�
void printMenu() {
	
	printf("\n------------------------------ B Tree ���� ------------------------------\n\n");
	printf("---�޴�---\n");
	printf(" 0. ����\n");
	printf(" 1. ����\n");
	printf(" 2. ����\n");
	printf(" 3. ���\n");
	printf(" 4. ���� ���\n");
	printf("----------\n");
	printf(" >> ");
}

int main(void)
{
	int menu = 0;	//�޴��� ��ȣ�� ������ ����
	int input = 0;	//Ű���� ������ ����
	while (1) {		
		fflush(stdin);	//�Է� ���� �ʱ�ȭ
		printMenu();	//�޴� ��� �Լ� ����
		scanf("%d", &menu);	//����ڷ� ���� �޴� ��ȣ �Է� ����
		switch (menu) {	//�Էµ� �޴��� ����,
		case 0:			// ����
			destroy(root);	//������ ��� ��� ����
			return 1;
		case 1:			// ����
			printf(" Insert key >> ");
			scanf("%d", &input);	//������ Ű�� �Է� ����
			//�ߺ� Ű �˻�
			if (root == NULL || search(root, input) == NULL)
			{
				insertNode(input);		//���� �Լ� ����
				printf(" >> Ű�� �����߽��ϴ�.\n");
			}
			else{
				printf(" >> �̹� Ű�� �ֽ��ϴ�.\n");
			}
			break;
		case 2:			// ����
			printf(" Remove key >> ");
			scanf("%d", &input);	//������ Ű���� �Է� ����
			if (removeNode(input)){	//���������� ������ �Ǿ�����,
				printf(" >> ������ �Ϸ� �Ǿ����ϴ�.\n");
			}
			else{
				printf(" >> Ű�� �����ϴ�.\n");
			}
			break;
		case 3:			// ���
			print_tree(root);	
			break;
		case 4:			// ���� ���
			print_tree_level(root, 0);

			break;
		}
		printf("\n Press enter any key!!");
		getch();
		system("cls");
	}

	return 0;
}