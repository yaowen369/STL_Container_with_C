#include "CTLStack.h"

/**
 * 将stack所指向的栈清空
 * @return 正常返回 NORMAL, 异常返回相应的错误标识
 */
int CTLStackClear(struct CTLStack *stack) {
    if (stack == NULL)
        return CTL_PTR_IS_NULL;

    memset(stack->data, 0, stack->length * stack->typeSize);
    stack->top= -1;
    return NORMAL;
}

/**
 * 如果栈为空，则返回 TRUE;否则返回 FALSE
 */
int CTLStackIsEmpty(struct CTLStack stack){
    if (stack.top == -1){
        return TRUE;
    }else {
        return FALSE;
    }
}

/**
 * 如果栈满，则返回 TRUE, 否则返回 FALSE
 */
int CTLStackIsFull(struct CTLStack stack){
    if (stack.top == stack.length - 1){
        return TRUE;
    }else {
        return FALSE;
    }
}


/**
 * 在stack的栈顶压入一个record 所指向的数据
 * @return 正常返回NORMAL, 否则返回相应错误标号
 */
int CTLStackPush(struct CTLStack *stack, void *record){

    if ((stack == NULL) || (record==NULL)){
        return CTL_PTR_IS_NULL;
    }

    if (stack->top == stack->length-1){
        return CTL_OUT_OF_RANGE;
    }

    void *ptr;

    stack->top++;
    ptr = (char *)(stack->data) + stack->top*stack->typeSize;
    memcpy(ptr, record, stack->typeSize);
    return NORMAL;
}

/**
 * 弹出栈顶值，通过record指针带出结果
 * @return 正常返回NORMAL, 异常返回错误标号
 */
int CTLStackPop(struct CTLStack *stack, void *record){

    //在peek函数写在后面的情况下，会报错吗？
    int resultVar = CTLStackPeek(stack, record);
    if (resultVar == NORMAL){
        stack->top--;
    }
    return resultVar;
}


/**
 * 读取栈顶的值，并通过record指针带出结果
 * @return 正常返回NORMAL, 异常返回错误标号
 */
int CTLStackPeek(struct CTLStack *stack, void *record){
     if ((stack == NULL) || (record==NULL)){
        return CTL_PTR_IS_NULL;
    }
    if (stack->top == -1){
        return CTL_NO_VALUE;
    }

    void *ptr;
    ptr = (char *)(stack->data) + stack->top*stack->typeSize;
    memcpy(record, ptr, stack->typeSize);
    return NORMAL;
}

/**
 * 复制一个栈， (将sour栈复制到 dest栈)
 * @return 正常返回NORMAL, 异常返回错误标号
 */
int CTLStackCopy(struct CTLStack *dest, struct CTLStack *sour){
    if ((dest==NULL) || (sour==NULL)){
        return CTL_PTR_IS_NULL;
    }
    if (dest->typeSize != sour->typeSize){
        return CTL_TYPESIZE_NO_MATCH;
    }

    int len, result = NORMAL;

    memset(dest->data, 0, dest->length*dest->typeSize);

    if (dest->length < sour->length){
        len = dest->length;
        result = CTL_OUT_OF_RANGE;
    }else{
        len = sour->length;
    }

    memcpy(dest->data, sour->data, len*dest->typeSize);
    if (sour->top > len-1){
        dest->top = len-1;
    }else{
        dest->top = sour->top;
    }

    return result;
}

