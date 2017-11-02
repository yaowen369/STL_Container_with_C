#include "CTLVector.h"
#include "debug.h"

/**
 * Vector是动态数组，但是在我们的代码中，将其固定长度了。
 * 不过也可以通过 CTLVectorSetSize() 函数 动态扩容。
 * 但是能自动扩容那是最好的。
 * 未来有时间了再修改吧。
 */


//返回指向vector的第一个元素的指针,无数据则返回NULL
void *CTLVectorBegin(CTLVector vector){
	if (vector.quan != 0)
		return vector.data;
	else
		return NULL;
}


//返回指向vector的最后一个元素的指针， 无数据则返回NULL
void *CTLVectorEnd(CTLVector vector){
	void *ptr;

	if (vector.quan == 0)
		return NULL;
	else {
		ptr = vector.data;
		ptr = (char *)ptr + vector.typeSize*(vector.quan-1);
		return ptr;
	}
}


//如果vector为空，则返回TRUE；否则返回FALSE
int CTLVectorEmpty(CTLVector vector){
	if (vector.quan == 0)
		return TRUE;
	else
		return FALSE;
}

//返回vector中当前元素的个数
int CTLVectorSize(CTLVector vector){
	return vector.quan;
}


//将vector中第num(由1开始计数)个元素值由*record带出
//@return  正常返回NORMAL；否则返回相应的错误标号
int CTLVectorGetAt(const CTLVector *vector, void *record, int num){
	void *ptr;

	if (vector == NULL)
		return CTL_PTR_IS_NULL;
	if (num<=0 || num>vector->quan)
		return NUM_IS_WRONG;

	ptr = vector->data;
	ptr = (char *)ptr + vector->typeSize*(num-1);
	memcpy(record, ptr, vector->typeSize);
	return NORMAL;
}


//将vector的第num（由1开始计数）个元素的值更改为*record
//@return 如果正常，则返回NORMAL；否则返回相应的错误标号
int CTLVectorSetAt(const CTLVector *vector, const void *record, int num){
	void *ptr;

	if (vector == NULL)
		return CTL_PTR_IS_NULL;
	if (record == NULL)
		return RECORD_PTR_IS_NULL;
	if (num<=0 || num>vector->quan)
		return NUM_IS_WRONG;

	ptr = vector->data;
	ptr = (char *)ptr + vector->typeSize*(num-1);
	memcpy(ptr, record, vector->typeSize);
	return NORMAL;
}


//1、在vector的第num个位置处插入数据*record
// 2、num从1开始计数，如果num大于vector长度，则将其插入到vector最后一个元素的后面
//@return 正常则返回NORMAL；否则返回相应的错误标号
int CTLVectorInsert(CTLVector *vector, const void *record, int num){
	union ScanVal val;
	void *tmp = (void *)(&val);
	int i, result = NORMAL;

	if (vector == NULL)
		return CTL_PTR_IS_NULL;
	if (record == NULL)
		return RECORD_PTR_IS_NULL;
	if (num <= 0)
		return NUM_IS_WRONG;
	if (num > vector->quan+1){
		num = vector->quan + 1;
		result = NUM_WRONG_BUT_DO_SOMETHING;
	}
	if (num > vector->length)
		return CTL_OUT_OF_RANGE;

	vector->quan++;
	for (i=vector->quan; i>num; i--){
		CTLVectorGetAt(vector, tmp, i-1);
		CTLVectorSetAt(vector, tmp, i);
	}
	CTLVectorSetAt(vector, record, num);
	return result;
}

//将vector的长度设置为len，之前的数据保存（如果长度变小，则可能保存一部分）
//@return 正常返回NORMAL；异常情况下返回相应标号
int CTLVectorSetSize(CTLVector *vector, int len){
	void *ptr;
	int tmp;

	if (vector == NULL)
		return CTL_PTR_IS_NULL;
	if (len <= 0)
		return NUM_IS_WRONG;

	ptr = (void *)malloc(vector->typeSize * len);
	tmp = (len>vector->quan) ? vector->quan : len;
	memcpy(ptr, vector->data, tmp*vector->typeSize);
	free(vector->data);
	vector->data = ptr;
	vector->length = len;
	vector->quan = tmp;
	return NORMAL;
}


//将src的数据复制到dst。
//@return 正常返回NORMAL；异常返回相应标号
int CTLVectorCopy(CTLVector *dst, const CTLVector *src){
	int size;

	if (dst->typeSize != src->typeSize)
		return CTL_TYPESIZE_NO_MATCH;

	memset(dst->data, NULL, dst->length*dst->typeSize);
	if (dst->length > src->quan)
		size = src->quan;
	else
		size = dst->length;
	memcpy(dst->data, src->data, dst->typeSize*size);
	dst->quan = size;
	return NORMAL;
}

//将vector的num(由1开始)位置处的数据清零，而不做其他变化
//@return 正常返回NORMAL；异常情况下返回相应标号
int CTLVectorErase(const CTLVector *vector, int num){
	void *ptr;

	if (num<=0 || num>vector->quan)
		return NUM_IS_WRONG;

	ptr = vector->data;
	ptr = (char *)ptr + vector->typeSize*(num-1);
	memset(ptr, 0, vector->typeSize);
	return NORMAL;
}


//将vector的num(由1开始)位置处的数据删除，之后的数据往前移
//@return 正常情况下，返回NORMAL；异常情况下返回相应标号
int CTLVectorDelete(CTLVector *vector, int num){
	int i;
	union ScanVal val;
	void *record = (void *)(&val);

	if (num<=0 || num>vector->quan)
		return NUM_IS_WRONG;

	for (i=num; i<vector->quan+1; i++){
		CTLVectorGetAt(vector, record, i+1);
		CTLVectorSetAt(vector, record, i);
	}
	vector->quan--;
	return NORMAL;
}


//清空所有元素，释放空间
void CTLVectorClear(CTLVector *vector){
	free(vector->data);
	vector->quan = 0;
	vector->data = NULL;
}




