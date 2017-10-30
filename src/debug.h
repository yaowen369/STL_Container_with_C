/**
 *  1. 本文件中声明的函数用于对CTL进行测试输出，主要是将这些结构体输出，便于观察
 *  2. 我们进行测试时，默认只测试 char，int，double类型，所以 在进行输出时，直接根据 typeSize 来进行区分
 *  2. 测试stack和queue时，都是将int，double，char类型用不同的函数进行区分，
 *     从list开始，有些地方在测试int，double，char类型都是用typeSize大小来调整PrintType()和ScaleType函数进行区分
 */


 #ifndef _CTL_DEBUG_H
 #define _CTL_DEBUG_H

 #include "CTLStack.h"
 #include "CTLQueue.h"

 extern void PrintStack(struct CTLStack stack);
 extern void DealResult(int result);
 extern void PrintQueue(struct CTLQueue queue, int typeSize);



 #endif // _CTL_DEBUG_H
