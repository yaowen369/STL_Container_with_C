#include "CTLList.h"

//将list清空，释放各个节点的空间
// @return 正常返回NORMAL；否则返回相应的错误标号
int CTLListClear(CTLList *list){
	ListNode *prevP, *nextP;

	if (list == NULL)
		return CTL_PTR_IS_NULL;

	for (prevP=list->root; prevP!=NULL; prevP=nextP){
		nextP = prevP->next;
		free(prevP->data);
		free(prevP);
	}
	list->root = NULL;
	list->num = 0;
	return NORMAL;
}


//list为空，则返回TURE；否则返回FALSE
int CTLListIsEmpty(CTLList list){
	if (list.num == 0)
		return TRUE;
	else
		return FALSE;
}


//返回List中数据元素的个数
int CTLListGetNum(CTLList list){
	return list.num;
}

//返回指向链表中第一个节点的指针；若第一个节点为空，则返回NULL
ListNode *CTLListGetHead(CTLList list){
	return list.root;
}


//返回指向链表中尾节点的指针；若链表为空，则返回NULL
ListNode *CTLListGetTail(CTLList list){
	ListNode *prevP, *nextP;

	for (nextP=prevP=list.root; nextP!=NULL; ){
		prevP = nextP;
		nextP = prevP->next;
	}

	return prevP;
}


//向list头部添加数据record
//@return  正常，返回NORMAL；否则返回相应的错误标号
int CTLListPushFront(CTLList *list, void *record){
	ListNode *node;

	if (list == NULL)
		return CTL_PTR_IS_NULL;

	node = (ListNode *)malloc(NODE_SIZE);
	node->data = (void *)malloc(list->typeSize);
	if ((node==NULL) || (node->data==NULL))
		return MALLOC_FAIL;

	memcpy(node->data, record, list->typeSize);
	node->next  = list->root;
	list->root = node;
	list->num++;
	return NORMAL;
}


//向list尾部添加数据record
//@return 正常则返回NORMAL；否则返回相应的错误标号
int CTLListPushTail(CTLList *list, void *record){
	ListNode *node, *ptr;

	if (list == NULL)
		return CTL_PTR_IS_NULL;

	node = (ListNode *)malloc(NODE_SIZE);
	node->data = (void *)malloc(list->typeSize);
	if ((node==NULL) || (node->data==NULL))
		return MALLOC_FAIL;

	memcpy(node->data, record, list->typeSize);
	node->next = NULL;
	ptr = CTLListGetTail(*list);
	if (ptr != NULL)
		ptr->next = node;
	else
		list->root = node;

	list->num++;
	return NORMAL;
}



//弹出头部数据。将list头部的数据由record带出，然后删除这个节点
//@return 删除正常则返回NORMAL；否则返回相应的错误标号
int CTLListPopFront(CTLList *list, void *record){
	ListNode *ptr;

	if (list == NULL)
		return CTL_PTR_IS_NULL;
	if (list->root == NULL)
		return CTL_NO_VALUE;

	ptr = list->root;
	memcpy(record, ptr->data, list->typeSize);
	list->root = ptr->next;
	list->num--;
	free(ptr->data);
	free(ptr);
	return NORMAL;
}


//弹出尾部数据。将list尾部的数据由record带出，然后删除这个节点
//@return 删除正常则返回NORMAL；否则返回相应的错误标号
int CTLListPopTail(CTLList *list, void *record){
	ListNode *prevP, *nextP;

	if (list == NULL)
		return CTL_PTR_IS_NULL;
	if (list->root == NULL)
		return CTL_NO_VALUE;

	if (list->root ->next == NULL){   //链表只有一个节点
		prevP = list->root;
		list->root = NULL;
		memcpy(record, prevP->data, list->typeSize);
		free(prevP->data);
		free(prevP);
	} else {
		for (prevP=nextP=list->root; nextP->next!=NULL; ){
			prevP = nextP;
			nextP = prevP->next;
		}

		prevP->next = NULL;
		memcpy(record, nextP->data, list->typeSize);
		free(nextP->data);
		free(nextP);
	}

	list->num--;
	return NORMAL;
}


//1、在链表list的第num位置处插入数据record
//2、如果位置num(最小值为1)大于链表的元素数量，则将数据插入到队尾
//@return 一切正常则返回NORMAL，否则返回相应错误标号
int CTLListInsert(CTLList *list, void *record, int num){
	int i;
	ListNode *prevP, *node;

	if (list == NULL)
		return CTL_PTR_IS_NULL;
	if (num <= 0)
		return NUM_IS_WRONG;
	if (num > list->num+1) {       //将record插入到尾部
		CTLListPushTail(list, record);
		return NUM_WRONG_BUT_DO_SOMETHING;
	}

	node = (ListNode *)malloc(NODE_SIZE);
	node->data = (void *)malloc(list->typeSize);
	if ((node==NULL) || (node->data==NULL))
		return MALLOC_FAIL;
	memcpy(node->data, record, list->typeSize);
	if (num == 1){
		node->next = list->root;
		list->root = node;
	} else {
		num--;
		prevP = list->root;
		for (i=num; i>1; i--)
			prevP=prevP->next;

		node->next = prevP->next;
		prevP->next = node;
	}

	list->num++;
	return NORMAL;
}

//删除链表list的第num(最小值为1)位置处的节点，并将该节点处的data值用record带出
//@return 如果删除正常，则返回NORMAL；否则返回相应的错误标号
int CTLListDelete(CTLList *list, void *record, int num){
	int i;
	ListNode *prevP, *nextP;

	if (list == NULL)
		return CTL_PTR_IS_NULL;
	if (record == NULL)
		return RECORD_PTR_IS_NULL;
	if ((num<=0) || (num>list->num))
		return NUM_IS_WRONG;

	nextP = list->root;
	if (num == 1){
		list->root = nextP->next;
	} else {
		num--;
		for (i=num; i>0; i--)
		{
			prevP = nextP;
			nextP = prevP->next;
		}
		prevP->next = nextP->next;
	}

	memcpy(record, nextP->data, list->typeSize);
	free(nextP->data);
	free(nextP);
	list->num--;
	return NORMAL;
}


//读取链表list的第num(最小值为1)位置处的节点的数据值（不删除），将其用record带出
//@return  如果读取正常，则返回NORMAL；否则返回相应的错误标号
int CTLListRead(CTLList *list, void *record, int num){
	int i;
	ListNode *prevP, *nextP;

	if (list == NULL)
		return CTL_PTR_IS_NULL;
	if (record == NULL)
		return RECORD_PTR_IS_NULL;
	if ((num<=0) || (num>list->num))
		return NUM_IS_WRONG;

	nextP = list->root;
	num--;
	for (i=num; i>0; i--){
		prevP = nextP;
		nextP = prevP->next;
	}
	memcpy(record, nextP->data, list->typeSize);
	return NORMAL;
}


//将链表list的第num(最小值为1)位置处的节点的data值更改为*record值
//@return 如果更改正常，则返回NORMAL；否则返回相应的错误标号
int CTLListSet(CTLList *list, void *record, int num){
	int i;
	ListNode *prevP, *nextP;

	if (list == NULL)
		return CTL_PTR_IS_NULL;
	if (record == NULL)
		return RECORD_PTR_IS_NULL;
	if ((num<=0) || (num>list->num))
		return NUM_IS_WRONG;

	nextP = list->root;
	num--;
	for (i=num; i>0; i--){
		prevP = nextP;
		nextP = prevP->next;
	}
	memcpy(nextP->data, record, list->typeSize);
	return NORMAL;
}

//将tail所指向的链表连接到front所指向链表的尾部；结果是延长 front的链表
//@return  连接正常则返回NORMAL；否则返回相应错误标号
int CTLListConnect(CTLList *front, CTLList *tail){
	ListNode *frontTail;

	if (front->typeSize != tail->typeSize)
		return CTL_TYPESIZE_NO_MATCH;
	if ((front==NULL) || (tail==NULL))
		return CTL_PTR_IS_NULL;

	frontTail = CTLListGetTail(*front);
	if (frontTail == NULL)
		front->root = tail->root;
	else
		frontTail->next = tail->root;

	front->num = front->num + tail->num;
	return NORMAL;
}



//将list中data等于record的所有节点都删除
//@return  正常情况下返回删除的节点的个数；异常情况下返回相应的错误标号
int CTLListRemoveAll(CTLList *list, const void *record){
	int result = list->num;
	ListNode *pM, *pN, *temp;

	if (list == NULL)
		return CTL_PTR_IS_NULL;
	if (record == NULL)
		return RECORD_PTR_IS_NULL;

	pN = list->root;
	while (pN != NULL){
		if (memcmp(pN->data, record, list->typeSize) == 0){
			if (pN == list->root)
				list->root = pN->next;
			else
				pM->next = pN->next;

			temp = pN->next;
			free(pN->data);
			free(pN);
			list->num--;
			pN = temp;
			continue;
		}
		pM = pN;
		pN = pN->next;
	}

	result -= list->num;
	return result;
}

//1、如果list中存在数据元素record，则将ptr指针指向这个节点。
//2、若这样的节点有多个，则ptr指向的是第一个。
//3、如果不存在这样的节点，则将ptr指向NULL
//@return 如果存在错误，则返回相应的错误标号；否则返回NORMAL
int CTLListLocate(CTLList *list, ListNode **ptr, void *record){
	ListNode *p;

	if (list == NULL)
		return CTL_PTR_IS_NULL;
	if (record == NULL)
		return RECORD_PTR_IS_NULL;

	*ptr = NULL;
	p = list->root;
	while (p != NULL){
		if (memcmp(p->data, record, list->typeSize) == 0)
		{
			*ptr = p;
			break;
		}
		p = p->next;
	}

	return NORMAL;
}


