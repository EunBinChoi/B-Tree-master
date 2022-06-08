#include <stdio.h>
#include <conio.h>
#include "BTree.h"

//메뉴 출력 함수
void printMenu() {
	
	printf("\n------------------------------ B Tree 구현 ------------------------------\n\n");
	printf("---메뉴---\n");
	printf(" 0. 종료\n");
	printf(" 1. 삽입\n");
	printf(" 2. 삭제\n");
	printf(" 3. 출력\n");
	printf(" 4. 레벨 출력\n");
	printf("----------\n");
	printf(" >> ");
}

int main(void)
{
	int menu = 0;	//메뉴의 번호를 저장할 변수
	int input = 0;	//키값을 저장할 변수
	while (1) {		
		fflush(stdin);	//입력 버퍼 초기화
		printMenu();	//메뉴 출력 함수 실행
		scanf("%d", &menu);	//사용자로 부터 메뉴 번호 입력 받음
		switch (menu) {	//입력된 메뉴에 따라,
		case 0:			// 종료
			destroy(root);	//종료전 모든 노드 삭제
			return 1;
		case 1:			// 삽입
			printf(" Insert key >> ");
			scanf("%d", &input);	//삽입할 키를 입력 받음
			//중복 키 검사
			if (root == NULL || search(root, input) == NULL)
			{
				insertNode(input);		//삽입 함수 실행
				printf(" >> 키를 삽입했습니다.\n");
			}
			else{
				printf(" >> 이미 키가 있습니다.\n");
			}
			break;
		case 2:			// 삭제
			printf(" Remove key >> ");
			scanf("%d", &input);	//삭제할 키값을 입력 받음
			if (removeNode(input)){	//정상적으로 삭제가 되었으면,
				printf(" >> 삭제가 완료 되었습니다.\n");
			}
			else{
				printf(" >> 키가 없습니다.\n");
			}
			break;
		case 3:			// 출력
			print_tree(root);	
			break;
		case 4:			// 레벨 출력
			print_tree_level(root, 0);

			break;
		}
		printf("\n Press enter any key!!");
		getch();
		system("cls");
	}

	return 0;
}