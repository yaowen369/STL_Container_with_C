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
    //Todo
}

static  void TestStackDouble(){

}


void TestCTLStack(){
    printf("进行CTLStack的测试！\n");
    printf("现在进行的是 int 类型的 测试");
    TestStackInt();
    printf("测试结束!!!!");
}
