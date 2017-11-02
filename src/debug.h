/**
 *  1. 本文件中声明的函数用于对CTL进行测试输出，主要是将这些结构体输出，便于观察
 *  2. 我们进行测试时，默认只测试 char，int，double类型，所以 在进行输入输出时，直接根据 typeSize 来进行区分
 */


 #ifndef _CTL_DEBUG_H
 #define _CTL_DEBUG_H

 #include "CTLStack.h"
 #include "CTLQueue.h"
 #include "CTLList.h"
 #include "CTLVector.h"

 union ScanVal
{
	int i;
	char ch;
	double dou;
};

 extern void PrintStack(struct CTLStack stack);
 extern void DealResult(int result);
 extern void PrintQueue(struct CTLQueue queue, int typeSize);
 extern void PrintList(CTLList list);


 //函数功能：根据size大小不同，来区分输出时的是int ,double,或者char类型
extern void PrintType(void *record, int size);

//函数功能：根据size不同，来区分输入的是val的哪一个成员
extern void ScanType(union ScanVal *val, int size);

extern void PrintVector(struct CTLVector vector);


 #endif // _CTL_DEBUG_H
