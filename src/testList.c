#include "testList.h"


//将这个list进行清空操作之后的结果信息输出
static void PrintListClear(CTLList *list){
	int result;

	result = CTLListClear(list);
	if (result == NORMAL)
		printf("\t\t 这个队列清空操作结果正常!\n");
	else
	{
		printf("\t\t 这个队列清空操作结果异常，原因是：");
		DealResult(result);
	}
}


//将这个list是否为空的信息输出
static void PrintListEmpty(CTLList list){
	if (CTLListIsEmpty(list) == TRUE)
		printf("\t\t 这个队列是空的\n");
	else
		printf("\t\t 这个队列不是空的\n");
}


//这个list中元素个数输出
static void PrintListNum(CTLList list){
	printf("\t\t 这个队列中元素的个数为%d\n", CTLListGetNum(list));
}


//测试CTLListGetHead()函数，将第一个节点的数据输出
static void TestListGetHead(CTLList list){
	ListNode *head;

	printf("\t\t测试CTLListGetHead()函数\n");
	head = CTLListGetHead(list);
	if (head == NULL)
		printf("\t\t这个队列是空的,没有所谓第一个节点\n");
	else {
		printf("\t\t这个队列的第一个节点的数据是:");
		PrintType(head->data, list.typeSize);
		putchar(10);
	}
}

//测试CTLListGetTail()函数，将最后一个节点的数据输出
static void TestListGetTail(CTLList list){
	ListNode *tail;

	printf("\t\t测试CTLListGetTail()函数\n");
	tail = CTLListGetTail(list);
	if (tail == NULL)
		printf("\t\t\t这个队列是空的,没有所谓最后一个节点\n");
	else {
		printf("\t\t\t这个队列的最后一个节点的数据是:");
		PrintType(tail->data, list.typeSize);
		putchar(10);
	}
}

//测试CTLListPushFront()函数;
static void TestListPushFront(CTLList *list){
	int result;
	union ScanVal val;

	printf("\t\t现在是在测试CTLListPushFront()函数;\n");
	printf("\t\t\t之前的数据是:\n");
	PrintList(*list);
	printf("\t\t请输入你要插入的数据\n");
	ScanType(&val, list->typeSize);
	result = CTLListPushFront(list, (void *)(&val));
	if (result == NORMAL){
		printf("\t\t\t操作正常结束，输出链表\n");
		PrintList(*list);
	}
	else
		DealResult(result);
}

//测试CTLListPushTail()函数;
static void TestListPushTail(CTLList *list){
	int result;
	union ScanVal val;

	printf("\t\t现在是在测试CTLListPushTail()函数;\n");
	printf("\t\t\t之前的数据是:\n");
	PrintList(*list);
	printf("\t\t请输入你要插入的数据\n");
	ScanType(&val, list->typeSize);
	result = CTLListPushTail(list, (void *)(&val));
	if (result == NORMAL){
		printf("\t\t\t操作正常结束，输出链表\n");
		PrintList(*list);
	}
	else
		DealResult(result);
}

//测试CTLListPopFront()函数
static void TestListPopFront(CTLList *list){
	int result;
	union ScanVal record;

	printf("\t\t现在测试CTLListPopFront()函数\n"    \
		    "\t\t\t之前的链表是：\n");
	PrintList(*list);
	result = CTLListPopFront(list, (void *)(&record));
	if (result == NORMAL){
		printf("\t\t\t弹出操作正常，弹出的数据是");
		PrintType((void *)(&record), list->typeSize);
		putchar(10);
	}
	else
		DealResult(result);

	printf("\t\t弹出操作之后的链表是:\n");
	PrintList(*list);
}

//测试CTLListPopTail()函数
static void TestListPopTail(CTLList *list){
	int result;
	union ScanVal record;

	printf("\t\t现在测试CTLListPopTail()函数\n"    \
		    "\t\t\t之前的链表是：\n");
	PrintList(*list);
	result = CTLListPopTail(list, (void *)(&record));
	if (result == NORMAL){
		printf("\t\t弹出操作正常，弹出的数据是");
		PrintType((void *)(&record), list->typeSize);
		putchar(10);
	}
	else
		DealResult(result);

	printf("\t\t弹出操作之后的链表是:\n");
	PrintList(*list);
}

//测试CTLListInsert()函数
static void TestListInsert(CTLList *list){
	int insNum, result;
	union ScanVal insVal;

	printf("\t\t现在测试CTLListInsert()函数\n"       \
		   "\t\t\t原来的链表是：\n");
	PrintList(*list);
	printf("\t\t\t请输入你想插入的位置:");
	scanf("%d", &insNum);
	getchar();
	printf("\t\t请输入你想插入的数据\n");
	ScanType(&insVal, list->typeSize);

	result = CTLListInsert(list, (void *)(&insVal), insNum);
	DealResult(result);
	printf("\t\t\t操作后的链表是：\n");
	PrintList(*list);
}


//测试CTLListDelete()函数
static void TestListDelete(CTLList *list){
	int delNum, result;
	union ScanVal val;

	printf("\t\t现在测试的是CTLListDelete()函数\n"   \
		    "\t\t\t操作之前的链表是:\n");
	PrintList(*list);
	printf("\t\t请输入你想删除的位置:");
	scanf("%d", &delNum);
	getchar();
	result = CTLListDelete(list, (void *)(&val), delNum);
	if (result == NORMAL){
		printf("\t\t\t操作正常，删除的数据是：");
		PrintType((void *)(&val), list->typeSize);
		putchar(10);
		printf("\t\t\t操作后的链表是:\n");
		PrintList(*list);
	}
	else
		DealResult(result);
}

//测试CTLListRead()函数
static void TestListRead(CTLList *list){
	int readNum, result;
	union ScanVal val;

	printf("\t\t现在测试的是CTLListRead()函数\n");
	printf("\t\t\t请输入你想读取的位置:");
	scanf("%d", &readNum);
	getchar();
	result = CTLListRead(list, (void *)(&val), readNum);
	if (result == NORMAL){
		printf("\t\t\t读取操作正常，读取的数据是：");
		PrintType((void *)(&val), list->typeSize);
		putchar(10);
	}
	else
		DealResult(result);
}


//测试CTLListSet()函数
static void TestListSet(CTLList *list){
	int setNum, result;
	union ScanVal setVal;

	printf("\t\t现在测试CTLListSet()函数\n"       \
		   "\t\t\t原来的链表是：\n");
	PrintList(*list);
	printf("\t\t\t请输入你想设置的位置:");
	scanf("%d", &setNum);
	getchar();
	printf("\t\t\t请输入你想设置的数据\n");
	ScanType(&setVal, list->typeSize);

	result = CTLListSet(list, (void *)(&setVal), setNum);
	if (result == NORMAL)
	{
		printf("\t\t\t设置操作正常,设置后的链表为\n");
		PrintList(*list);
	}
	else
		DealResult(result);
}

//测试CTLListRemoveAll()函数
static void TestListRemoveAll(CTLList *list){
	int result;
	union ScanVal val;

	printf("\t\t现在测试的是CTLListRemoveAll()函数\n"   \
		    "\t\t\t操作之前的链表是:\n");
	PrintList(*list);
	printf("\t\t请输入你想删除的数据:\n");
	ScanType(&val, list->typeSize);
	result = CTLListRemoveAll(list, (void *)(&val));
	printf("\t\t\t操作正常, 共删除了%d个数据：\n", result);
	printf("\t\t\t操作后的链表是:\n");
	PrintList(*list);
}



//测试CTLListLocate()函数
static void TestListLocate(CTLList *list){
	int result;
	union ScanVal val;
	ListNode *pos, *ptr;

	printf("\t\t现在是在测试CTLListLocate()函数\n"   \
		   "\t\t这个链表的情况是:\n");
	PrintList(*list);
	printf("\t\t\t输入你想定位的数值:\n");
	ScanType(&val, list->typeSize);
	result = CTLListLocate(list, &pos, (void *)(&val));
	if (result != NORMAL)
		DealResult(result);
	else{
		if (pos == NULL)
			printf("\t\t\t链表中不存在包含这个值的结点\n");
		else {
			printf("\t\t\t这个结点的值是:");
			PrintType(pos->data, list->typeSize);
			putchar(10);

			ptr = pos->next;
			if(ptr != NULL){
				printf("\t\t\t这个结点的下一个结点的数据是:");
				PrintType(ptr->data, list->typeSize);
				putchar(10);
			}
			else
				printf("\t\t\t这个结点已经是最后一个结点了\n");
		}
	}
}


//函数功能：测试CTLListConnect()函数
static void TestListConnect(){
	int i, val, result;
	char ch;

	INIT_CTL_LIST(int ,listInt1);
	INIT_CTL_LIST(int, listInt2);
	INIT_CTL_LIST(char, listChar);

	printf("\t\t为了方便起见，每个list添加四个数据\n");
	for (i=0; i<4; i++){
		printf("\t输入listInt1的第%d个数据:", i+1);
		scanf("%d", &val);
		getchar();
		if (CTLListPushTail(&listInt1, (void *)(&val)) != NORMAL)
			printf("\t插入数据出现异常");
	}
	for (i=0; i<4; i++){
		printf("\t输入listInt2的第%d个数据:", i+1);
		scanf("%d", &val);
		getchar();
		if (CTLListPushTail(&listInt2, (void *)(&val)) != NORMAL)
			printf("\t插入数据出现异常");
	}
	for (i=0; i<4; i++){
		printf("\t输入listChar的第%d个数据:", i+1);
		scanf("%c", &ch);
		getchar();
		if (CTLListPushTail(&listChar, (void *)(&ch)) != NORMAL)
			printf("\t插入数据出现异常");
	}

	printf("\t\t\t listInt1的情况是：\n");
	PrintList(listInt1);
	printf("\t\t\t listInt2的情况是:\n");
	PrintList(listInt2);
	printf("\t\t\t listChar的情况是：\n");
	PrintList(listChar);

	printf("\t\tlistInt1做头，listInt2做尾连接起来\n");
	result = CTLListConnect(&listInt1, &listInt2);
	if (result != NORMAL)
		DealResult(result);
	printf("\t\t\t连接后的listInt1情况是：\n");
	PrintList(listInt1);

	printf("\t\t以listInt2为头，连接后的listInt1做尾，连接起来\n");
	result = CTLListConnect(&listInt2, &listInt1);
	if (result != NORMAL)
		DealResult(result);
	printf("\t\t\t连接后的listInt2情况是：\n");
	PrintList(listInt2);

	printf("\t\t\t以listInt1做头，listChar做尾，连接起来\n");
	result = CTLListConnect(&listInt1, &listChar);
	if (result != NORMAL)
		DealResult(result);

	FREE_CTL_LIST(listInt1);
	FREE_CTL_LIST(listInt2);
	FREE_CTL_LIST(listChar);
}



//进行list测试的总函数，与外部的接口函数
void TestList(){
	int flag, type, quit;
	char choice;
	CTLList *list;

	INIT_CTL_LIST(int, listInt);
	INIT_CTL_LIST(char, listChar);
	INIT_CTL_LIST(double, listDou);

	quit = 1;
	while (quit){
		printf("请输入你想测试的类型\n"   \
			   "1(int), 2(char), 3(double) :");
		scanf("%d", &type);
		getchar();
		flag = TRUE;
		switch (type){
			case 1:
				list = &listInt;
				break;
			case 2:
				list = &listChar;
				break;
			case 3:
				list = &listDou;
				break;
			default:
				flag = FALSE;
				break;
		} //switch (type) is over

		printf("操作序号是：\n"   \
			   "c(Clear), e(IsEmpty), n(GetNum), h(GetHead)\n"   \
			    "t(GetTail), a(PushFront), b(PushTail), \n"      \
				"x(PopFront), y(PopTail), i(Insert) \n"    \
				"d(Delete), r(Read), s(Set), z(Connect)\n"   \
				"m(RemoveAll), l(locate), p(PrintList), q(quit)\n");
		while (flag == TRUE){
			printf("\t\t请输入你选择的操作序号:");
			scanf("%c", &choice);
			getchar();

			switch (choice){
				case 'c':
					PrintListClear(list);
					break;
				case 'e':
					PrintListEmpty(*list);
					break;
				case 'n':
					PrintListNum(*list);
					break;
				case 'h':
					TestListGetHead(*list);
					break;
				case 't':
					TestListGetTail(*list);
					break;
				case 'a':
					TestListPushFront(list);
					break;
				case 'b':
					TestListPushTail(list);
					break;
				case 'x':
					TestListPopFront(list);
					break;
				case 'y':
					TestListPopTail(list);
					break;
				case 'i':
					TestListInsert(list);
					break;
				case 'd':
					TestListDelete(list);
					break;
				case 'r':
					TestListRead(list);
					break;
				case 's':
					TestListSet(list);
					break;
				case 'z':
					 TestListConnect();
					 break;
				case 'm':
					TestListRemoveAll(list);
					break;
				case 'l':
					TestListLocate(list);
					break;
				case 'p':
					PrintList(*list);
					break;
				case 'q':
					flag = FALSE;
					break;
				default:
					printf("你输入的值有误\n");
					break;
			} //switch (choice) is over
			printf("\n\n");
		}  //while (flg == TURE) is over

		printf("\t\t输入0结束测试，输入非零值代表继续测试:");
		scanf("%d", &quit);
		getchar();
	}//while (quit) is over

	FREE_CTL_LIST(listInt);
	FREE_CTL_LIST(listChar);
	FREE_CTL_LIST(listDou);

}





