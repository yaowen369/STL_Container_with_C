#include "CTLStack.h"
#include "testStack.h"
#include "debug.h"


static void PrintStackClear(struct CTLStack *stack)
{
	printf("\t 将CTLStackClear()函数返回结果输出!\n");
	DealResult( CTLStackClear(stack) );
}

static void PrintStackEmpty(struct CTLStack stack)
{
	if (CTLStackIsEmpty(stack) == TRUE)
		printf("\t \t这个栈是空的！\n");
	else
		printf("\t \t这个栈不是空的！\n");
}

static void PrintStackFull(struct CTLStack stack)
{
	if (CTLStackIsFull(stack) == TRUE)
		printf("\t \t这个栈是满的!\n");
	else
		printf("\t \t这个栈不是满的!\n");
}


static void TestStackInt(){
    int result, num, flag = TRUE;
    char var;

    INIT_CTL_STACK(int, stackInt1, 8);

    printf("操作序号依次为:\n"
            "c(CTLStackClear),  e(CTLStackIsEmpty),\n"
			"f(CTLStackIsFull), h(CTLStackPush),p(CTLStackPop),\n"
			"g( CTLStackPeek), o(PrintStack), q(quit)\n");

    while (flag == TRUE){
        printf("请输入操作序号:");
        scanf("%c", &var);
        getchar();   //接收回车
        switch (var){
            case 'c':
                PrintStackClear(&stackInt1);
                break;
            case 'e':
                PrintStackEmpty(stackInt1);
                break;
            case 'f':
                PrintStackFull(stackInt1);
                break;
            case 'h':
                printf("请输入你想入栈的值:");
                scanf("%d", &num);
                getchar();
                result = CTLStackPush(&stackInt1, (void *)(&num));
                DealResult(result);
                break;
            case 'p':
                result  = CTLStackPop(&stackInt1, (void *)(&num));
                if (result == NORMAL){
                    printf("\t \t出栈的值是 %d.\n", num);
                }else{
                    DealResult(result);
                }
                break;
            case 'g':
                result = CTLStackPeek( &stackInt1, (void *)(&num));
				if (result == NORMAL)
					printf("\t \t栈顶的值是%d.\n", num);
				else
					DealResult(result);
				break;
            case 'o':
                PrintStack(stackInt1);
                break;
            case 'q':
                flag = FALSE;
                break;
            default:
                printf("\t \t你输入的值 %c 异常，请继续输入\n", var);
        }//end of "switch..."
    }//end of " while (flag == TRUE)"
}//end of "TestStackInt"


static void TestStackChar(){
    int result, flag = TRUE;
    char operatorVar;
    char var;

    INIT_CTL_STACK(char, stackChar1, 8);

    printf("操作序号依次为:\n"
            "c(CTLStackClear),  e(CTLStackIsEmpty),\n"
			"f(CTLStackIsFull), h(CTLStackPush),p(CTLStackPop),\n"
			"g( CTLStackPeek), o(PrintStack), q(quit)\n");

    while (flag == TRUE){
        printf("请输入操作序号:");
        scanf("%c", &operatorVar);
        getchar();   //接收回车
        switch (operatorVar){
            case 'c':
                PrintStackClear(&stackChar1);
                break;
            case 'e':
                PrintStackEmpty(stackChar1);
                break;
            case 'f':
                PrintStackFull(stackChar1);
                break;
            case 'h':
                printf("请输入你想入栈的值:");
                scanf("%c", &var);
                getchar();
                result = CTLStackPush(&stackChar1, (void *)(&var));
                DealResult(result);
                break;
            case 'p':
                result  = CTLStackPop(&stackChar1, (void *)(&var));
                if (result == NORMAL){
                    printf("\t \t出栈的值是 %c.\n", var);
                }else{
                    DealResult(result);
                }
                break;
            case 'g':
                result = CTLStackPeek( &stackChar1, (void *)(&var));
				if (result == NORMAL)
					printf("\t \t栈顶的值是%c.\n", var);
				else
					DealResult(result);
				break;
            case 'o':
                PrintStack(stackChar1);
                break;
            case 'q':
                flag = FALSE;
                break;
            default:
                printf("\t \t你输入的值 %c 异常，请继续输入\n", operatorVar);
        }//end of "switch..."
    }//end of " while (flag == TRUE)"
}// end of "TestStackChar()"

static  void TestStackDouble(){
    int result, flag = TRUE;
    char operatorVar;
    double var;

    INIT_CTL_STACK(double, stackDouble1, 8);

    printf("操作序号依次为:\n"
            "c(CTLStackClear),  e(CTLStackIsEmpty),\n"
			"f(CTLStackIsFull), h(CTLStackPush),p(CTLStackPop),\n"
			"g( CTLStackPeek), o(PrintStack), q(quit)\n");

    while (flag == TRUE){
        printf("请输入操作序号:");
        scanf("%c", &operatorVar);
        getchar();   //接收回车
        switch (operatorVar){
            case 'c':
                PrintStackClear(&stackDouble1);
                break;
            case 'e':
                PrintStackEmpty(stackDouble1);
                break;
            case 'f':
                PrintStackFull(stackDouble1);
                break;
            case 'h':
                printf("请输入你想入栈的值:");
                scanf("%lf", &var);
                getchar();
                result = CTLStackPush(&stackDouble1, (void *)(&var));
                DealResult(result);
                break;
            case 'p':
                result  = CTLStackPop(&stackDouble1, (void *)(&var));
                if (result == NORMAL){
                    printf("\t \t出栈的值是 %f.\n", var);
                }else{
                    DealResult(result);
                }
                break;
            case 'g':
                result = CTLStackPeek( &stackDouble1, (void *)(&var));
				if (result == NORMAL)
					printf("\t \t栈顶的值是%f.\n", var);
				else
					DealResult(result);
				break;
            case 'o':
                PrintStack(stackDouble1);
                break;
            case 'q':
                flag = FALSE;
                break;
            default:
                printf("\t \t你输入的值 %c 异常，请继续输入\n", operatorVar);
        }//end of "switch..."
    }//end of " while (flag == TRUE)"
}// end of "TestStackDouble()"



//进行CTLStackCopy（）函数的测试
static void TestCTLStackCopy()
{
	int result1, result2;
	int i, num, pushInt;

	INIT_CTL_STACK(int, stackInt1, 7);
	INIT_CTL_STACK(int, stackInt2, 9);
	INIT_CTL_STACK(int, stackInt3, 11);

	INIT_CTL_STACK(char, stackChar1, 6);
	while (1)
	{
		CTLStackClear(&stackInt2);

		printf("请输入你要给stackInt2压栈压入值的个数(最多9个):");
		scanf("%d", &num);
		getchar();
		for (i=0; i<num; i++)
		{
			printf("请输入你要压入的第%d个值：", i+1);
			scanf("%d", &pushInt);
			getchar();
			CTLStackPush(&stackInt2, (void *)(&pushInt));
		}
		PrintStack(stackInt2);

		printf("以下是stackInt1的情况\n");
		result1 = CTLStackCopy(&stackInt1, &stackInt2);
		DealResult(result1);
		PrintStack(stackInt1);

		printf("以下是stackInt3的情况\n");
		result2 = CTLStackCopy(&stackInt3, &stackInt2);
		DealResult(result2);
		PrintStack(stackInt3);

		printf("测试类型不兼容语句\n");
		result1 = CTLStackCopy(&stackChar1, &stackInt2);
		DealResult(result1);
	}
}

void TestCTLStack(){
    printf("进行CTLStack的测试！\n");

    printf("请输入你要测试的类型，int，char，double类型, 或者输入copy进行拷贝的测试\n");
    char testType[11];
    char *typePtr;

    typePtr = fgets(testType, 10, stdin);

    if (testType[strlen(typePtr) - 1] == '\n'){
        testType[strlen(typePtr) - 1] = '\0';
    }

    if (strcmp(typePtr, "int") == 0){
        TestStackInt();
    }else if (strcmp(typePtr, "char") == 0){
        TestStackChar();
    }else  if (strcmp(typePtr, "double") == 0){
        TestStackDouble();
    }else if (strcmp(typePtr, "copy") == 0){
        TestCTLStackCopy();
    }else {
        printf("你输入的值有误, %s\n", typePtr);
    }

    printf("测试结束!!!!");
}
