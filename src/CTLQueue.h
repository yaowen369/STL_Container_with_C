#ifndef _CTL_QUEUE_H
#define _CTL_QUEUE_H

#include "ctl.h"

struct CTLQueue{
    void *data;       //指向数据区域
    size_t typeSize;  //queue中存放元素类型所占的字节数
    int front;        //队头位置
    int rear;         //队尾位置
    int length;       //queue中所能容纳的元素的最大个数
};

#define INIT_CTL_QUEUE(type, name, len)  \
        type ctl_queue_array_##name[sizeof(type)*(len+1)] = {0};  \
        struct CTLQueue name = {   \
        ctl_queue_array_##name, sizeof(type), 0, 0, len+1}



// 判断队列是否为空
// @return 如果queue为空，则返回TURE；否则返回FALSE
extern int CTLQueueIsEmpty(struct CTLQueue queue);

// 判断队列是否为满
// @return 如果queue为满，则返回TURE；否则返回FALSE
extern int CTLQueueIsFull(struct CTLQueue queue);

// 进队操作，在队列queue的队尾加入元素record
// @return 如果进队成功，则返回NORMAL，否则返回相应的错误标号
extern int CTLQueueEnter(struct CTLQueue *queue, void *record);

// 取队头元素操作，将队列queue的队头元素用record带出，但不删除
// @return 出队成功，返回NORMAL，否则返回相应的错误标号
extern int CTLQueueGetHead(struct CTLQueue *queue, void *record);

// 出队操作，将队列queue的队头元素删除，并用record带出
// @return 出队成功，返回NORMAL，否则返回相应的错误标号
extern int CTLQueueDelete(struct CTLQueue *queue, void *record);

// 将队列queue置为空队列
// @return 如果正常，则返回NORMAL，否则返回相应错误标号
extern int CTLQueueClear(struct CTLQueue *queue);

//返回队列中元素的个数
extern int CTLQueueGetNum(struct CTLQueue queue);

//将队列src复制给队列dst
// 备注：仅仅根据情况，对结构体中的data区域进行复制，其他如front之类未动.
//   Todo 未来有空，把这个函数的功能设计的更仔细，更详细
//@return 如果操作正常，则返回NORMAL，否则返回相应错误标号
extern int CTLQueueCopy(struct CTLQueue *dst, struct CTLQueue *src);


#endif // _CTL_QUEUE_H
