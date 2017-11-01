#ifndef _CTL_LIST_H
#define _CTL_LIST_H


/**
 * 因为在List当中，我们使用malloc来请求内存空间，所以需要特别注意避免内存泄漏
 */


#include "ctl.h"

typedef struct LIST_NODE {
    void *data;      //指向该节点的数据区域
    struct LIST_NODE *next;   //指向下一个节点
}ListNode;

typedef struct CTL_LIST{
    ListNode *root;    //指向该链表的头指针
    size_t typeSize;  //链表中该类型元素所占的字节数
    int num;          // 元素的个数
}CTLList;


#define NODE_SIZE  sizeof(ListNode)

//初始化list
#define INIT_CTL_LIST(type, name) \
		CTLList name = {NULL, sizeof(type), 0}

//结束list，释放其所用空间
#define FREE_CTL_LIST(name)  CTLListClear(&name)



//将list清空，释放各个节点的空间
// @return 正常返回NORMAL；否则返回相应的错误标号
extern int CTLListClear(CTLList *list);

//list为空，则返回TURE；否则返回FALSE
extern int CTLListIsEmpty(CTLList list);

//返回List中数据元素的个数
extern int CTLListGetNum(CTLList list);

//返回指向链表中第一个节点的指针；若第一个节点为空，则返回NULL
extern ListNode *CTLListGetHead(CTLList list);


//返回指向链表中尾节点的指针；若链表为空，则返回NULL
extern ListNode *CTLListGetTail(CTLList list);

//向list头部添加数据record
//@return  正常，返回NORMAL；否则返回相应的错误标号
extern int CTLListPushFront(CTLList *list, void *record);

//向list尾部添加数据record
//@return 正常则返回NORMAL；否则返回相应的错误标号
extern int CTLListPushTail(CTLList *list, void *record);

//弹出头部数据。将list头部的数据由record带出，然后删除这个节点
//@return 删除正常则返回NORMAL；否则返回相应的错误标号
extern int CTLListPopFront(CTLList *list, void *record);

//弹出尾部数据。将list尾部的数据由record带出，然后删除这个节点
//@return 删除正常则返回NORMAL；否则返回相应的错误标号
extern int CTLListPopTail(CTLList *list, void *record);


//1、在链表list的第num位置处插入数据record
//2、如果位置num(最小值为1)大于链表的元素数量，则将数据插入到队尾
//@return 一切正常则返回NORMAL，否则返回相应错误标号
extern int CTLListInsert(CTLList *list, void *record, int num);


//删除链表list的第num(最小值为1)位置处的节点，并将该节点处的data值用record带出
//@return 如果删除正常，则返回NORMAL；否则返回相应的错误标号
extern int CTLListDelete(CTLList *list, void *record, int num);

//读取链表list的第num(最小值为1)位置处的节点的数据值（不删除），将其用record带出
//@return  如果读取正常，则返回NORMAL；否则返回相应的错误标号
extern int CTLListRead(CTLList *list, void *record, int num);


//将链表list的第num(最小值为1)位置处的节点的data值更改为*record值
//@return 如果更改正常，则返回NORMAL；否则返回相应的错误标号
extern int CTLListSet(CTLList *list, void *record, int num);

//将tail所指向的链表连接到front所指向链表的尾部；结果是延长 front的链表
//@return  连接正常则返回NORMAL；否则返回相应错误标号
extern int CTLListConnect(CTLList *front, CTLList *tail);



//将list中data等于record的所有节点都删除
//@return  正常情况下返回删除的节点的个数；异常情况下返回相应的错误标号
extern int CTLListRemoveAll(CTLList *list, const void *record);


//1、如果list中存在数据元素record，则将ptr指针指向这个节点。
//2、若这样的节点有多个，则ptr指向的是第一个。
//3、如果不存在这样的节点，则将ptr指向NULL
//@return 如果存在错误，则返回相应的错误标号；否则返回NORMAL
extern int CTLListLocate(CTLList *list, ListNode **ptr, void *record);

#endif // _CTL_LIST_H
