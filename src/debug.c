#include "debug.h"




//根据 typeSize 的长度，输出值，
// 这是 其他输出方法的辅助方法.
void PrintValue(void *ptr, int typeSize){
    switch (typeSize){
         case TYPE_CHAR:
            printf("%c  ", *((char *)ptr));
            break;
        case TYPE_INT:
              printf("%d  ", *((int *)ptr));
            break;
        case TYPE_DOUBLE:
            printf("%f  ", *((double *)ptr));
            break;
        default:
            printf("printValue() -> 出现未知的值。 typeSize=" + typeSize);

    }
}

// 像console输出result，便于观察
void DealResult(int result){
    switch(result){
        case NORMAL:
            printf("\t \t \t result is normal\n");
            break;
        case CTL_OUT_OF_RANGE:
            printf("\t \t \t ctl is out of range!\n");
            break;
        case CTL_PTR_IS_NULL:
			printf("\t \t \t ctl ptr is null!\n");
			break;
		case CTL_NO_VALUE:
			printf("\t \t \t ctl no value\n");
			break;
		case CTL_TYPESIZE_NO_MATCH:
			printf("\t \t \t ctl typeSize no match!\n");
			break;
		case RECORD_PTR_IS_NULL:
			printf("\t \t \t record ptr is null\n");
			break;
		case MALLOC_FAIL:
			printf("\t \t \t malloc fail\n");
			break;
		case NUM_IS_WRONG:
			printf("\t \t \t num is wrong\n");
			break;
		case NUM_WRONG_BUT_DO_SOMETHING:
			printf("\t \t \t num wrong but do something\n");
			break;
		default:
			printf("\t \t \t debug.cpp文件中DealResult()函数出现未定义值！\n");
			break;
    }
}// end of "DealResult"


// -------------   queue测试代码 start  ---------------------//


// 输出stack中的数据等资料。
void PrintStack(struct CTLStack stack){

    void *ptr;

    char *str = "";
    switch(stack.typeSize){
        case TYPE_CHAR:
            str = "Stack 的数据类型为 char 类型\n";
            break;
        case TYPE_INT:
            str = "Stack 的数据类型为 int 类型\n";
            break;
        case TYPE_DOUBLE:
            str = "Stack 的数据类型为 double 类型\n";
            break;
        default:
            str = "PrintStack 出现未定义的typeSize = " + stack.typeSize;

    }
    printf(str);
	printf("stack中typeSize=%d, \t top指针位置=%d, \t length=%d\n", stack.typeSize, stack.top, stack.length);

	printf("stack中的元素从底部到顶部依次是:\n");
	for (int i=0; i<=stack.top; i++){
        if (i%10 == 0)
            printf("\n");
        ptr = stack.data;
        ptr = (char *)ptr + i*stack.typeSize;
        PrintValue(ptr, stack.typeSize);
	}
	putchar(10);
}

// 依次输出queue中的数据，无数据的位置输出*号代替(因为我们把 length长度的内容都输出)
void PrintQueue(struct CTLQueue queue, int typeSize){
	int i;
	//double *pVar;
	void *pVoid;

	printf("这个queue的信息如下:\n");
    char *str = "";
    switch(queue.typeSize){
        case TYPE_CHAR:
            str = "\t\tQueue 的数据类型为 char 类型\n";
            break;
        case TYPE_INT:
            str = "\t\tQueue 的数据类型为 int 类型\n";
            break;
        case TYPE_DOUBLE:
            str = "\t\tQueue 的数据类型为 double 类型\n";
            break;
        default:
            str = "\t\tPrintQueue 出现未定义的typeSize = " + queue.typeSize;

    }
    printf(str);

    printf("\t\ttypeSize=%d, front=%d, rear=%d, length=%d\n", queue.typeSize, queue.front, queue.rear, queue.length-1);
	printf("\t\t这个queue中共有%d个元素,他们依次是：\n", CTLQueueGetNum(queue));


	for (i=0; i<queue.length-1; i++){
        if (i%10 == 0)
            printf("\n");

        if ((i<queue.front) || (i>=queue.rear))
            printf("*  ");
        else{
            pVoid = queue.data;
            pVoid = (char *)pVoid + i * queue.typeSize;
            PrintValue(pVoid, typeSize);
        }
    }
    printf("\n");
}//end of "PrintQueue(..."

// -------------   List 测试代码 start  ---------------------//


//依次输出list中的数据以及其他资料（假设其数据类型为int类型）
static void PrintListInt(CTLList list){
	int i;
	int *pInt;
	ListNode *ptr = list.root;

	printf("\t 这个list中元素类型所占字节数是%d, 其元素个数为%d\n", list.typeSize, list.num);
	printf("\t 这些数据都是int类型，他们依次是：");
	for (i=0; i<list.num; i++){
		if (i%10 == 0)
			printf("\n");

		pInt = (int *)(ptr->data);
		printf("%d  ", *pInt);
		ptr = ptr->next;
	}
	putchar(10);
}

//依次输出list中的数据以及其他资料（假设其数据类型为double类型）
static void PrintListDouble(CTLList list) {
	int i;
	double *pDou;
	ListNode *ptr = list.root;

	printf("\t 这个list中元素类型所占字节数是%d, 其元素个数为%d\n", list.typeSize, list.num);
	printf("\t 这些数据都是double类型，他们依次是：");
	for (i=0; i<list.num; i++){
		if (i%10 == 0)
			printf("\n");

		pDou = (double *)(ptr->data);
		printf("%f  ", *pDou);
		ptr = ptr->next;
	}
	putchar(10);
}

//依次输出list中的数据以及其他资料（假设其数据类型为char类型）
static void PrintListChar(CTLList list){
	int i;
	char *pChar;
	ListNode *ptr = list.root;

	printf("\t 这个list中元素类型所占字节数是%d, 其元素个数为%d\n", list.typeSize, list.num);
	printf("\t 这些数据都是char类型，他们依次是：");
	for (i=0; i<list.num; i++){
		if (i%10 == 0)
			printf("\n");

		pChar = (char *)(ptr->data);
		printf("%c  ", *pChar);
		ptr = ptr->next;
	}
	putchar(10);
}

//依次输出list中数据以及相关资料，（根据typeSize大小来自动区分类型）
void PrintList(CTLList list){
	switch (list.typeSize){
		case 1:
			PrintListChar(list);
			break;
		case 4:
			PrintListInt(list);
			break;
		case 8:
			PrintListDouble(list);
			break;
		default:
			printf("debug,cpp中PrintList()函数typeSize出现未定义值\n");
			break;
	}
}



//根据size大小不同，来区分输出时的是int ,double,或者char类型
void PrintType(void *record, int size){
	assert(record);

	switch(size){
		case 1:
			printf("%c", *((char *)record));
			break;
		case 4:
			printf("%d", *((int *)record));
			break;
		case 8:
			printf("%f", *((double *)record));
			break;
		default:
			printf("debug.cpp文件中PrintListType()形参size出现未定义值\n");
			break;
	}
}


//根据size不同，来区分输入的是val的哪一个成员
void ScanType(union ScanVal *val, int size){
	switch(size){
		case 1:
			printf("请输入char类型数据.");
			scanf("%c", &val->ch);
			getchar();
			break;
		case 4:
			printf("请输入int类型数据.");
			scanf("%d", &val->i);
			getchar();
			break;
		case 8:
			printf("请输入double类型数据.");
			scanf("%lf", &val->dou);
			getchar();
			break;
		default:
			printf("debug.cpp文件中ScanfType()形参size出现未定义值\n");
			break;
	}
}


//依次输出vrector的相关资料，以及各个数据(其数据类型为int)
static void PrintVectorInt(CTLVector vector){
	int i, *pInt;
	void *ptr;

	printf("\t vector的相关资料是:\n"       \
		   "\t typeSize=%d, length=%d, quan=%d\n", vector.typeSize, vector.length, vector.quan);
	printf("vector的数据依次是:");
	for (i=0; i<vector.quan; i++){
		if (i%10 == 0)
			putchar(10);
		ptr = vector.data;
		ptr = (char *)ptr + i*vector.typeSize;
		pInt = (int *)ptr;
		printf("%d  ", *pInt);

	}
	printf("\n");
}

//依次输出vrector的相关资料，以及各个数据(其数据类型为double)
static void PrintVectorDouble(CTLVector vector){
	int i;
	double *pDou;
	void *ptr;

	printf("\t vector的相关资料是:\n"       \
		   "\t typeSize=%d, length=%d, quan=%d\n", vector.typeSize, vector.length, vector.quan);
	printf("vector的数据依次是:");
	for (i=0; i<vector.quan; i++){
		if (i%10 == 0)
			putchar(10);
		ptr = vector.data;
		ptr = (char *)ptr + i*vector.typeSize;
		pDou = (double *)ptr;
		printf("%f  ", *pDou);

	}
	printf("\n");
}

//依次输出vrector的相关资料，以及各个数据(其数据类型为char)
static void PrintVectorChar(CTLVector vector){
	int i;
	char *pChar;
	void *ptr;

	printf("\t vector的相关资料是:\n"       \
		   "\t typeSize=%d, length=%d, quan=%d\n", vector.typeSize, vector.length, vector.quan);
	printf("vector的数据依次是:");
	for (i=0; i<vector.quan; i++){
		if (i%10 == 0)
			putchar(10);
		ptr = vector.data;
		ptr = (char *)ptr + i*vector.typeSize;
		pChar = (char *)ptr;
		printf("%c  ", *pChar);

	}
	printf("\n");
}

//函数功能：1、依次输出vrector的相关资料，以及各个数据(根据typeSize大小，自动选择类型)
void PrintVector(struct CTLVector vector){
	switch (vector.typeSize){
		case 1:
			PrintVectorChar(vector);
			break;
		case 4:
			PrintVectorInt(vector);
			break;
		case 8:
			PrintVectorDouble(vector);
			break;
		default:
			printf("debug.cpp文件中PrintVector()函数typeSize出现未定义值\n");
			break;
	}
}



