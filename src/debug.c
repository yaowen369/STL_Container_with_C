#include "debug.h"
#include "CTLStack.h"



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
            printf("result is normal\n");
            break;
        case CTL_OUT_OF_RANGE:
            printf("ctl is out of range!\n");
            break;
        case CTL_PTR_IS_NULL:
			printf("ctl ptr is null!\n");
			break;
		case CTL_NO_VALUE:
			printf("ctl no value\n");
			break;
		case CTL_TYPESIZE_NO_MATCH:
			printf("ctl typeSize no match!\n");
			break;
		case RECORD_PTR_IS_NULL:
			printf("record ptr is null\n");
			break;
		case MALLOC_FAIL:
			printf("malloc fail\n");
			break;
		case NUM_IS_WRONG:
			printf("num is wrong\n");
			break;
		case NUM_WRONG_BUT_DO_SOMETHING:
			printf("num wrong but do something\n");
			break;
		default:
			printf("debug.cpp文件中DealResult()函数出现未定义值！\n");
			break;
    }
}// end of "DealResult"



/**
D:\code\github_blog\STL_Container_with_C\src\ctl.h|14|warning: "NULL" redefined|
c:\mingw\lib\gcc\mingw32\6.3.0\include\stddef.h|406|note: this is the location of the previous definition|
D:\code\github_blog\STL_Container_with_C\src\debug.c|62|error: conflicting types for 'PrintStack'|
D:\code\github_blog\STL_Container_with_C\src\debug.h|12|note: previous declaration of 'PrintStack' was here|
D:\code\github_blog\STL_Container_with_C\src\debug.c||In function 'PrintStack':|
*/

// 输出stack中的数据等资料。
void PrintStack(struct CTLStack stack){

    void *ptr;

    char *str = "";
    switch(stack.typeSize){
        case TYPE_CHAR:
            str = 'Stack 的数据类型为 char 类型\n';
            break;
        case TYPE_INT:
            str = 'Stack 的数据类型为 int 类型\n';
            break;
        case TYPE_DOUBLE:
            str = 'Stack 的数据类型为 double 类型\n';
            break;
        default:
            str = "PrintStack 出现未定义的typeSize = " + stack.typeSize;

    }
    printf(str);
	printf("stack中typeSize=%d, \t top指针位置=%d, \t length=%d\n", stack.typeSize, stack.top, stack.length);

	printf("stack中的元素从底部到顶部依次是:\n");
	for (int i=0; i<stack.top; i++){
        if (i%10 == 0)
            printf("\n");
        ptr = stack.data;
        ptr = (char *)ptr + i*stack.typeSize;
        PrintValue(ptr, stack.typeSize);
	}
	putchar(10);
}




