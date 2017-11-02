#ifndef _CTL_VECTOR_H
#define _CTL_VECTOR_H

#include "ctl.h"

 struct CTLVector
{
	void *data;         //数据区域
	size_t typeSize;    //该类型元素所占内存数
	int length;         //数据区域的长度
	int quan;           //元素的数量
};

 typedef struct CTLVector CTLVector;


  //初始化vector
#define INIT_CTL_VECTOR(type, name, len)  \
		void *ctl_vector_##name = (void *)malloc(sizeof(type)*len);      \
		CTLVector name = {ctl_vector_##name, sizeof(type), len, 0}

//结束vector，释放其所占空间
#define FREE_CTL_VECTOR(name)   CTLVectorClear(&name)


//返回指向vector的第一个元素的指针,无数据则返回NULL
extern void *CTLVectorBegin(CTLVector vector);


//返回指向vector的最后一个元素的指针， 无数据则返回NULL
extern void *CTLVectorEnd(CTLVector vector);

//如果vector为空，则返回TRUE；否则返回FALSE
extern int CTLVectorEmpty(CTLVector vector);


//返回vector中当前元素的个数
extern int CTLVectorSize(CTLVector vector);


//将vector中第num(由1开始计数)个元素值由*record带出
//@return  正常返回NORMAL；否则返回相应的错误标号
extern int CTLVectorGetAt(const CTLVector *vector, void *record, int num);


//将vector的第num（由1开始计数）个元素的值更改为*record
//@return 如果正常，则返回NORMAL；否则返回相应的错误标号
extern int CTLVectorSetAt(const CTLVector *vector, const void *record, int num);

//1、在vector的第num个位置处插入数据*record
// 2、num从1开始计数，如果num大于vector长度，则将其插入到vector最后一个元素的后面
//@return 正常则返回NORMAL；否则返回相应的错误标号
extern int CTLVectorInsert(CTLVector *vector, const void *record, int num);


//将vector的长度设置为len，之前的数据保存（如果长度变小，则可能保存一部分）
//@return 正常返回NORMAL；异常情况下返回相应标号
extern int CTLVectorSetSize(CTLVector *vector, int len);


//将src的数据复制到dst。
//@return 正常返回NORMAL；异常返回相应标号
extern int CTLVectorCopy(CTLVector *dst, const CTLVector *src);


//将vector的num(由1开始)位置处的数据清零，而不做其他变化
//@return 正常情况下，返回NORMAL；异常情况下返回相应标号
extern int CTLVectorErase(const CTLVector *vector, int num);


//将vector的num(由1开始)位置处的数据删除，之后的数据往前移
//@return 正常情况下，返回NORMAL；异常情况下返回相应标号
extern int CTLVectorDelete(CTLVector *vector, int num);


//清空所有元素，释放空间
extern void CTLVectorClear(CTLVector *vector);

#endif // _CTL_VECTOR_H
