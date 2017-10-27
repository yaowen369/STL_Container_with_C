/**
 * 1.本文件包含CTLStack的结构体，创建CTLStack的宏定义，进行操作的各个函数的声明
 * 2.本项目中所使用的stack结构为最简单的使用固定长度数组表示的顺序栈
 */


#ifndef _CTL_STACK_H
#define _CTL_STACK_H

 #include "ctl.h"

 struct CTLStack{
    void *data;        //指向数据区
    size_t typeSize;   //栈中的元素类型所占的字节数
    int top;           //栈顶指针的位置
    size_t  length;    //栈中所能容纳的(该类型)元素的最大的个数
 };


 /**
  * @params type: 欲放入栈中的元素的类型
  * @params name: 栈的名字(就是变量的名字)
  * @params len:  栈中所能容纳的元素的最大个数
  */
 #define INIT_CTL_STACK(type, name, len) \
    type ctl_stack_array_##name[len*sizeof(type)] = {0};  \
    struct CTLStack name = {ctl_stack_array_##name, sizeof(type), -1, len}

 #include "ctl.h"

 extern int CTLStackClear(struct CTLStack *stack);
 extern int CTLStackIsEmpty(struct CTLStack stack);
 extern int CTLStackIsFull(struct CTLStack stack);
 extern int CTLStackPush(struct CTLStack *stack, void *record);
 extern int CTLStackPop(struct CTLStack *stack, void *record);
 extern int CTLStackPeek(struct CTLStack *stack, void *record);
 extern int CTLStackCopy(struct CTLStack *dest, struct CTLStack *sour);

#endif // _CTL_STACK_H




