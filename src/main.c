#include <stdio.h>
#include <stdlib.h>
#include "testStack.h"
#include "testQueue.h"
#include "testList.h"


int main(){
    //TestCTLStack();
    	int var;

	printf("1(CTLStack), 2(CTLQueue), 3(CTLList), 4(CTLVecotr)\n"    \
		   "请输入1、2、3、4来选择你要测试的数据结构:");
	scanf("%d", &var);

	switch (var){
		case 1:
			TestCTLStack();
			break;
		case 2:
			TestQueue();
			break;
		case 3:
			TestList();
			break;
		case 4:
			//TestVector();
			break;
		default:
			printf("你输入的值有误\n");
			break;
	}


    system("pause");
    return 0;
}
