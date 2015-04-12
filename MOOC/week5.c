#include <stdio.h>
#include <stdlib.h>


typedef struct Node * pNode;
typedef struct Node {
	int content;
	pNode next;
} Node;

pNode insert(pNode pHead, int value) {
	pNode pNewNode = (pNode)malloc(sizeof(struct Node));
	pNewNode->content = value;
	pNewNode->next = pHead;
	return pNewNode;
}

void print_list(pNode head) {
	pNode pointer = head;
	while(pointer != NULL){
		if (pointer->next != NULL) printf("%d ", pointer->content);
		else printf("%d", pointer->content);
		pointer = pointer->next;
	}

}

int main(int argc, char const *argv[])
{
	int _num;
	pNode pHead = NULL;
	while ((scanf("%d", &_num)) && _num != -1) {
		pHead = insert(pHead, _num);
		// printf("Fuck!\n");

	}

	print_list(pHead);
	



	return 0;
}