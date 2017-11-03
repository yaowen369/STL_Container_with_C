[TOC]

## 项目背景
  在C++中，`STL container`可以提高我们的开发效率，在java中也有类似的相关容器类。因为c++/java作为OOP语言，有泛型(模板),也存在继承关系，有`Object`,所以我们写一个容器，可以装入各种类型(也包括存在编译期的安全检查，不过java的泛型存在擦除现象)。但是在C语言中，比如我写一个`Stack`，如果定义`push(int var)`,那么就没办法弹入`double`等其他类型。甚至C语言也不存在重载的概念，那么我们怎么解决这个问题呢？
  
  其实答案很简单，C语言存在指针，可以直接进行内存操作。**所以在C语言的容器实现代码中，我们在填入数据时，完全不必关心什么类型，只需要直接分配内存进行操作就行了。记录相关内存区域的的top位置,起始位置，以及插入元素类型的字节大小等，取出时进行强制类型转换就好了。**(它自然也不会存在编译期的安全检查，但是C语言因为可以直接进行内存操作，所以本身就比java危险的多)。
  
## 项目简介
  因为是利用C语言来实现C+++ STL中container的功能，所以我们直接将该项目简称为**CTL**。
  由于c语言自身的特点，其功能会受到一定限制。目前实现了**stack**,**queue**,**list**,**vector**四种基本数据结构(容器)，每种容器都实现了相关的API函数。
  
## 使用说明
在使用容器之前，用`INIT_CTL_***`( 例如`INIT_CTL_QUEUE(type, name, len)` )建立容器对应的变量，并完成内存空间分配，之后就可以使用相关API函数进行操作了。相关API函数对变量输入，输出的参数类型都为指针，而操作位置，长度，相关错误码等类型为int。对于动态申请内存建立的容器(list和vector)，操作结束后必须调用`FREE_CTL_LIST`和`FREE_CTL_VECTOR`释放储存空间，避免内存泄漏。

> 具体使用方法可参考相关的测试文件（例如`testList.cpp`等文件，每种容器都实现了对应的测试文件，并测试通过了，每个API函数都添加了注释进行说明。

## 包含文件说明
   本项目只包含`stack`、`queue`、`list`、`vector`四种容器。它们的API函数的定义声明文件和测试文件，结构都是相似的。
   
 **以`list`为例进行说明。**
> + `CTLlist.h`: 主要包含相关结构体定义，宏定义，以及API函数声明。
> + `CTLList.cpp`: 主要包含相关API函数实现。
> + `testList.h`:  包含一个测试`List`的外部接口函数的声明。
> + `testList.cpp`: 包含进行测试的各个私有函数与总的入口函数。
> 以上类似结构的文件，都是独立的，均只与该种容器有关。

**下面的几个文件，则与各个容器都有关，主要是一些供测试输出的函数等。**
> + `ctl.h`:  CTL项目的公共头文件，包含一般宏定义，错误类型的标号宏定义。
> + `debug.cpp`:  本文件中的函数用于对CTL进行测试输出，主要是进行这些容器的输出,便于观察。
> + `debug.h`:   包含那些测试输出函数的声明。
> + `main.cpp`:  包含main（）函数，调用各个容器测试的主测试函数.


## 调用库函数说明
除了调用`printf()`,`scanf()`,`getchar()`,`putchar()`等库函数之外，因为是内存操作，所以还调用了`malloc()`,`free()`,`memcpy()`,`memcmp()`,`memset()`函数。

## 测试文件说明

在`testVector`等测试文件中，写一个主测试函数，内部有一个循环，在console根据手动输入内容选择不同的操作来调用各个测试函数，进行相关API操作，通过输入输出来进行观察测试。

各个测试文件结构都是类似的。在测试文件中，为了简便起见，只使用了int、char、double三种数据类型。

## API函数&测试方法示例

每种容器都实现了对应的操作方法。
*比如 `List`中相关内容如下：*

```c
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

```


*而`List`的测试方法示例如下：*

```c
//进行list测试的总函数，与外部的接口函数
void TestList(){
	int flag, type, quit;
	char choice;
	CTLList *list;

	INIT_CTL_LIST(int, listInt);
	INIT_CTL_LIST(char, listChar);
	INIT_CTL_LIST(double, listDou);

	quit = 1;
	while (quit){
		printf("请输入你想测试的类型\n"   \
			   "1(int), 2(char), 3(double) :");
		scanf("%d", &type);
		getchar();
		flag = TRUE;
		switch (type){
			case 1:
				list = &listInt;
				break;
			case 2:
				list = &listChar;
				break;
			case 3:
				list = &listDou;
				break;
			default:
				flag = FALSE;
				break;
		} //switch (type) is over

		printf("操作序号是：\n"   \
			   "c(Clear), e(IsEmpty), n(GetNum), h(GetHead)\n"   \
			    "t(GetTail), a(PushFront), b(PushTail), \n"      \
				"x(PopFront), y(PopTail), i(Insert) \n"    \
				"d(Delete), r(Read), s(Set), z(Connect)\n"   \
				"m(RemoveAll), l(locate), p(PrintList), q(quit)\n");
		while (flag == TRUE){
			printf("\t\t请输入你选择的操作序号:");
			scanf("%c", &choice);
			getchar();

			switch (choice){
				case 'c':
					PrintListClear(list);
					break;
				case 'e':
					PrintListEmpty(*list);
					break;
				case 'n':
					PrintListNum(*list);
					break;
				case 'h':
					TestListGetHead(*list);
					break;
				case 't':
					TestListGetTail(*list);
					break;
				case 'a':
					TestListPushFront(list);
					break;
				case 'b':
					TestListPushTail(list);
					break;
				case 'x':
					TestListPopFront(list);
					break;
				case 'y':
					TestListPopTail(list);
					break;
				case 'i':
					TestListInsert(list);
					break;
				case 'd':
					TestListDelete(list);
					break;
				case 'r':
					TestListRead(list);
					break;
				case 's':
					TestListSet(list);
					break;
				case 'z':
					 TestListConnect();
					 break;
				case 'm':
					TestListRemoveAll(list);
					break;
				case 'l':
					TestListLocate(list);
					break;
				case 'p':
					PrintList(*list);
					break;
				case 'q':
					flag = FALSE;
					break;
				default:
					printf("你输入的值有误\n");
					break;
			} //switch (choice) is over
			printf("\n\n");
		}  //while (flg == TURE) is over

		printf("\t\t输入0结束测试，输入非零值代表继续测试:");
		scanf("%d", &quit);
		getchar();
	}//while (quit) is over

	FREE_CTL_LIST(listInt);
	FREE_CTL_LIST(listChar);
	FREE_CTL_LIST(listDou);

}

//测试CTLListPushFront()函数;
static void TestListPushFront(CTLList *list){
	int result;
	union ScanVal val;

	printf("\t\t现在是在测试CTLListPushFront()函数;\n");
	printf("\t\t\t之前的数据是:\n");
	PrintList(*list);
	printf("\t\t请输入你要插入的数据\n");
	ScanType(&val, list->typeSize);
	result = CTLListPushFront(list, (void *)(&val));
	if (result == NORMAL){
		printf("\t\t\t操作正常结束，输出链表\n");
		PrintList(*list);
	} else {
		DealResult(result);
	}
}

```


## 后记&TODO
  坦白说，这个项目更像是一个练习的demo。因为设计的还不够严谨，类似`map`等容器也没有实现，因为时间关系，很多API函数与测试函数也并没有精心的设计。比如`Stack`我们利用数组来实现，这样就限制了长度，如果能用`malloc`来实现内存的动态增加减少才更有价值。在测试case中，也没有测试 `struct`,`union`等类型。这段太忙了，未来有空了再来看这个项目，争取将该项目设计的更加健壮合理，具有实际使用价值。也争取实现`map`等更多的容器类型。

