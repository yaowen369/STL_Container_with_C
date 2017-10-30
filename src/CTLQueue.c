#include "CTLQueue.h"



//判断队列是否为空
//@return TRUE or FLASE
int CTLQueueIsEmpty(struct CTLQueue queue){
	if (queue.front == queue.rear)
		return TRUE;
	else
		return FALSE;
}

//判断队列是否为满
//@return TRUE or FLASE
int CTLQueueIsFull(struct CTLQueue queue){
	if ((queue.rear+1)%queue.length == queue.front)
		return TRUE;
	else
		return FALSE;
}



//入操作，在队列queue的队尾加入元素record
//@return  如果进队成功，则返回NORMAL，否则返回相应的错误标号
int CTLQueueEnter(struct CTLQueue *queue, void *record){
	void *ptr;

	if (queue == NULL)
		return CTL_PTR_IS_NULL;
	if ((queue->rear!=0) && (queue->rear+1)%queue->length == queue->front)
		return CTL_OUT_OF_RANGE;
	if (record == NULL)
		return RECORD_PTR_IS_NULL;

	ptr = queue->data;
	ptr = (char *)ptr + queue->rear * queue->typeSize;
	memcpy(ptr, record, queue->typeSize);
	queue->rear = (queue->rear+1) % queue->length;
	return NORMAL;
}


//取队头元素，将队列queue的队头元素用record带出，但不删除
//@return  出队成功，返回NORMAL，否则返回相应的错误标号
int CTLQueueGetHead(struct CTLQueue *queue, void *record){
	void *ptr;

	if (queue == NULL)
		return CTL_PTR_IS_NULL;
	if (queue->rear == queue->front)
		return CTL_NO_VALUE;
	if (record == NULL)
		return RECORD_PTR_IS_NULL;

	ptr = queue->data;
	ptr = (char *)ptr + queue->front * queue->typeSize;
	memcpy(record, ptr, queue->typeSize);
	return NORMAL;
}


//出队操作，将队列queue的队头元素删除，并用record带出
//@return  出队成功，返回NORMAL，否则返回相应的错误标号
int CTLQueueDelete(struct CTLQueue *queue, void *record){
	int result;

	result = CTLQueueGetHead(queue, record);
	//if (result == NORMAL)
		//queue->front = (queue->front+1) % queue->length;

    if (result == NORMAL){
        memcpy(queue->data,
                (char *)(queue->data + queue->typeSize),
                 ((queue->rear-1)*queue->typeSize));
        queue->rear--;
    }

	return result;
}


//将队列queue置为空队列
//@return 如果正常，则返回NORMAL，否则返回相应错误标号
int CTLQueueClear(struct CTLQueue *queue){
	if (queue == NULL)
		return CTL_PTR_IS_NULL;

	memset(queue->data, NULL, queue->length * queue->typeSize);
	queue->front = queue->rear = 0;
	return NORMAL;
}

//返回队列中元素的个数
int CTLQueueGetNum(struct CTLQueue queue){
	int result;

	if (queue.rear >= queue.front)
		result = queue.rear - queue.front;
	else
		result = queue.rear + queue.length - queue.front;

	return result;
}


//将队列src复制给队列dst
// 备注：仅仅根据情况，对结构体中的data区域进行复制，其他如front之类未动.
//   Todo 未来有空，把这个函数的功能设计的更仔细，更详细
//@return 如果操作正常，则返回NORMAL，否则返回相应错误标号
int CTLQueueCopy(struct CTLQueue *dst, struct CTLQueue *src){
	int len, result;

	if (dst->typeSize != src->typeSize)
		return CTL_TYPESIZE_NO_MATCH;

	memset(dst->data, NULL, dst->length * dst->typeSize);

	if (dst->length == src->length)
	{
		len = dst->length;
		result = NORMAL;
	} else {
		if (dst->length > src->length)
			len = src->length;
		else
			len = dst->length;

		result = CTL_OUT_OF_RANGE;
	}

	memcpy(dst, src, len*src->typeSize);

	return result;
}



