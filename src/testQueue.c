#include "testQueue.h"

//将queue是否为空队列的状态输出
static void PrintQueueEmpty(struct CTLQueue queue){
	if (CTLQueueIsEmpty(queue) == TRUE)
		printf("\t 这个队列是空的\n");
	else
		printf("\t 这个队列是非空的\n");
}

//将这个队列是否为满的状态输出
static void PrintQueueFull(struct CTLQueue queue){
	if (CTLQueueIsFull(queue) == TRUE)
		printf("\t 这个队列是满的\n");
	else
		printf("\t 这个队列不是满的\n");
}


//将这个函数中元素的数量输出
static void PrintQueueQuan(struct CTLQueue queue){
	printf("\t 这个队列中元素的数量是 %d.\n", CTLQueueGetNum(queue));
}

//测试CTLQueueClear（）函数，并将处理状态输出
static void PrintQueueClear(struct CTLQueue *queue){
	int result = CTLQueueClear(queue);

	if (result == NORMAL)
		printf("\t 这个队列已经被清空了\n");
	else
	{
		printf("\t 这个队列清空失败，原因是");
		DealResult(result);
	}
}

//测试CTLQueueEnter()函数，在queue队尾加入一个int型数据
static void TestEnterInt(struct CTLQueue *queue){
	int var, result;

	printf("请输入你想插入的int型数据:");
	scanf("%d", &var);
	getchar();

	result = CTLQueueEnter(queue, &var);
	if (result == NORMAL)
		printf("\t 进队成功\n");
	else
	{
		printf("\t 进队失败,原因是:");
		DealResult(result);
	}
}



//测试CTLQueueEnter()函数，在queue队尾加入一个double型数据
static void TestEnterDouble(struct CTLQueue *queue){
	double var;
	int result;

	printf("请输入你想插入的double型数据:");
	scanf("%lf", &var);
	getchar();

	result = CTLQueueEnter(queue, &var);
	if (result == NORMAL)
		printf("\t 进队成功\n");
	else
	{
		printf("\t 进队失败,原因是:");
		DealResult(result);
	}
}


//测试CTLQueueEnter()函数，在queue队尾加入一个char型数据
static void TestEnterChar(struct CTLQueue *queue){
	char var;
	int result;

	printf("请输入你想插入的char型数据:");
	scanf("%c", &var);
	getchar();

	result = CTLQueueEnter(queue, &var);
	if (result == NORMAL)
		printf("\t 进队成功\n");
	else
	{
		printf("\t 进队失败,原因是:");
		DealResult(result);
	}
}


//测试CTLQueueDelete()函数，将queue的队头的元素删除(元素类型为int)
static void TestDeleteInt(struct CTLQueue *queue)
{
	int var, result;

	result = CTLQueueDelete(queue, &var);
	if (result == NORMAL){
		printf("\t 出队操作成功，队头元素是%d\n", var);
	} else {
		printf("\t 出队操作失败，原因是");
		DealResult(result);
	}
}

//测试CTLQueueDelete()函数，将queue的队头的元素删除(元素类型为double)
static void TestDeleteDouble(struct CTLQueue *queue){
	double var;
	int result;

	result = CTLQueueDelete(queue, &var);
	if (result == NORMAL)
		printf("\t 出队操作成功，队头元素是%f\n", var);
	else
	{
		printf("\t 出队操作失败，原因是");
		DealResult(result);
	}
}

//测试CTLQueueDelete()函数，将queue的队头的元素删除(元素类型为char)
static void TestDeleteChar(struct CTLQueue *queue){
	char var;
	int result;

	result = CTLQueueDelete(queue, &var);
	if (result == NORMAL)
		printf("\t 出队操作成功，队头元素是%c\n", var);
	else
	{
		printf("\t 出队操作失败，原因是");
		DealResult(result);
	}
}


//测试CTLQueueGetHead()函数，取队头元素（元素类型为int）
static void TestGetHeadInt(struct CTLQueue *queue){
	int var, result;

	result = CTLQueueGetHead(queue, &var);
	if (result == NORMAL)
		printf("\t 取队头操作成功，队头元素是%d\n", var);
	else
	{
		printf("\t 取队头操作失败，原因是");
		DealResult(result);
	}
}

//函数功能：测试CTLQueueGetHead()函数，取队头元素（元素类型为double）
static void TestGetHeadDouble(struct CTLQueue *queue){
	double var;
	int result;

	result = CTLQueueGetHead(queue, &var);
	if (result == NORMAL)
		printf("\t 取队头操作成功，队头元素是%f\n", var);
	else
	{
		printf("\t 取队头操作失败，原因是");
		DealResult(result);
	}
}

//测试CTLQueueGetHead()函数，取队头元素（元素类型为char）
static void TestGetHeadChar(struct CTLQueue *queue){
	char var;
	int result;

	result = CTLQueueGetHead(queue, &var);
	if (result == NORMAL)
		printf("\t 取队头操作成功，队头元素是%c\n", var);
	else
	{
		printf("\t 取队头操作失败，原因是");
		DealResult(result);
	}
}


//进行queue各个函数的测试（数据类型为int类型）
static void TestQueueInt(){
	char choice;
	int flg = TRUE;

	INIT_CTL_QUEUE(int, queue, 7);

	printf("操作序号依次是\n"
		"e(CTLQueueIsEmpty), f(CTLQueueIsFull), t(CTLQueueEnter)\n"
		"g(CTLQueueGetHead), d(CTLQueueDelete), c(CTLQueueClear)\n"
		"a(CTLQueueGetNum), p(PrintQueue), q(退出这次测试)\n");

	while (flg == TRUE){
		printf("请输入你选择的操作序号:");
		scanf("%c", &choice);
		getchar();

		switch (choice){
			case 'e':
				PrintQueueEmpty(queue);
				break;
			case 'f':
				PrintQueueFull(queue);
				break;
			case 't':
				TestEnterInt(&queue);
				break;
			case 'g':
				TestGetHeadInt(&queue);
				break;
			case 'd':
				TestDeleteInt(&queue);
				break;
			case 'c':
				PrintQueueClear(&queue);
				break;
			case 'a':
				PrintQueueQuan(queue);
				break;
			case 'p':
				PrintQueue(queue, queue.typeSize);
				break;
			case 'q':
				flg = FALSE;
				break;
			default:
				printf("你输入的操作选择是错误的\n");
				break;
		}//end of "switch"
	}  //end of "while (flg == TRUE){"
}//end of "static void TestQueueInt()"




//进行queue各个函数的测试（数据类型为double类型）
static void TestQueueDouble(){
	char choice;
	int flg = TRUE;

	INIT_CTL_QUEUE(double, queue, 6);

	printf("操作序号依次是\n"
		"e(CTLQueueIsEmpty), f(CTLQueueIsFull), t(CTLQueueEnter)\n"
		"g(CTLQueueGetHead), d(CTLQueueDelete), c(CTLQueueClear)\n"
		"a(CTLQueueGetQuan), p(PrintQueue), q(退出这次测试)\n");

	while (flg == TRUE){
		printf("请输入你选择的操作序号:");
		scanf("%c", &choice);
		getchar();

		switch (choice){
			case 'e':
				PrintQueueEmpty(queue);
				break;
			case 'f':
				PrintQueueFull(queue);
				break;
			case 't':
				TestEnterDouble(&queue);
				break;
			case 'g':
				TestGetHeadDouble(&queue);
				break;
			case 'd':
				TestDeleteDouble(&queue);
				break;
			case 'c':
				PrintQueueClear(&queue);
				break;
			case 'a':
				PrintQueueQuan(queue);
				break;
			case 'p':
				PrintQueue(queue, queue.typeSize);
				break;
			case 'q':
				flg = FALSE;
				break;
			default:
				printf("你输入的操作选择是错误的\n");
				break;
		}
	}//end of "while (flg == TRUE)"
}



//进行queue各个函数的测试（数据类型为char类型）
static void TestQueueChar(){
	char choice;
	int flg = TRUE;

	//INIT_CTL_QUEUE(char ,queue, 5);

	INIT_CTL_QUEUE(char, queue, 5);

	printf("操作序号依次是\n"
		"e(CTLQueueIsEmpty), f(CTLQueueIsFull), t(CTLQueueEnter)\n"
		"g(CTLQueueGetHead), d(CTLQueueDelete), c(CTLQueueClear)\n"
		"a(CTLQueueGetNum), p(PrintQueue), q(退出这次测试)\n");

	while (flg == TRUE){
		printf("请输入你选择的操作序号:");
		scanf("%c", &choice);
		getchar();

		switch (choice){
			case 'e':
				PrintQueueEmpty(queue);
				break;
			case 'f':
				PrintQueueFull(queue);
				break;
			case 't':
				TestEnterChar(&queue);
				break;
			case 'g':
				TestGetHeadChar(&queue);
				break;
			case 'd':
				TestDeleteChar(&queue);
				break;
			case 'c':
				PrintQueueClear(&queue);
				break;
			case 'a':
				PrintQueueQuan(queue);
				break;
			case 'p':
				PrintQueue(queue, queue.typeSize);
				break;
			case 'q':
				flg = FALSE;
				break;
			default:
				printf("你输入的操作选择是错误的\n");
				break;
		}
	}//end of "while (flg == TRUE)"
}


//函数功能：专门进行CTLQueueCopy()测试的函数，以int型为例
static void TestQueueCopy(){
	char choice;
	int flg = TRUE;

	INIT_CTL_QUEUE(int, queInt1, 5);
	INIT_CTL_QUEUE(int, queInt2, 6);
	INIT_CTL_QUEUE(int, queInt3, 7);
	INIT_CTL_QUEUE(double, queDouble, 6);

	printf("测试queue的复制，先初始化一个栈");

	printf("操作序号依次是\n"
		"t(CTLQueueEnter), d(CTLQueueDelete)\n"
		"p(PrintQueue), q(退出这次测试)\n");

	while (flg == TRUE){
		printf("请输入你选择的操作序号:");
		scanf("%c", &choice);
		getchar();

		switch (choice){
			case 't':
				TestEnterInt(&queInt2);
				break;
			case 'd':
				TestDeleteInt(&queInt2);
				break;
			case 'p':
				PrintQueue(queInt2, queInt2.typeSize);
				break;
			case 'q':
				flg = FALSE;
				break;
			default:
				printf("\t 你输入的操作选择是错误的\n");
				break;
		}
	}

	printf("  现在由queInt2向queInt1复制\n");
	DealResult( CTLQueueCopy(&queInt1, &queInt2) );
	printf("\t queInt1的信息是：\n");
	PrintQueue(queInt1, queInt1.typeSize);
	printf("\t queInt2的信息是：\n");
	PrintQueue(queInt2, queInt2.typeSize);

	printf("\n\n");
	printf("  现在由queInt2向queInt3复制\n");
	DealResult( CTLQueueCopy(&queInt3, &queInt2) );
	printf("\t queInt3的信息是：\n");
	PrintQueue(queInt3, queInt3.typeSize);
	printf("\t queInt2的信息是：\n");
	PrintQueue(queInt2, queInt2.typeSize);

	printf("\n\n");
	printf("  现在由queInt2向queDouble复制\n");
	DealResult( CTLQueueCopy(&queDouble, &queInt2) );
	printf("\t queDouble的信息是：\n");
	PrintQueue(queDouble, queDouble.typeSize);
	printf("\t queInt2的信息是：\n");
	PrintQueue(queInt2, queInt2.typeSize);
}


//进行queue测试的与外部的接口函数
void TestQueue()
{
	int var = 1;

	printf("请输入你要测试的类型， 1:queue的int类型， 2:double类型，  "
        "3:char类型,  4:测试queue的复制,  0:退出测试\n");

    scanf("%d", &var);
    getchar();

    while (var != 0){
        switch (var){
            case 1:
                TestQueueInt();
                break;
            case 2:
                TestQueueDouble();
                break;
            case 3:
                TestQueueChar();
                break;
            case 4:
                TestQueueCopy();
                break;
            case 0:
                var = 0;
                break;
            default:
                printf("你输入了未定义的值 %d\n", var);
        }

        printf("请输入你要测试的类型， 1:queue的int类型， 2:double类型，  "
        "3:char类型,  4:测试queue的复制,  0:退出测试:\n");

        scanf("%d", &var);
        getchar();
    }


}






