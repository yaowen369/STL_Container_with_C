#include "testVector.h"


static void TestVectorBegin(CTLVector vector){
	void *ptr = CTLVectorBegin(vector);

	if (ptr == NULL)
		printf("\t\t\t这个vector为空，没有所谓第一个元素.\n");
	else{
		printf("\t\t\t这个Vector的第一个元素是:");
		PrintType(ptr, vector.typeSize);
		putchar(10);
	}
}


static void TestVectorEnd(CTLVector vector){
	void *ptr = CTLVectorEnd(vector);

	if (ptr == NULL)
		printf("\t\t\t这个vector为空，没有所谓最后一个元素.\n");
	else{
		printf("\t\t\t这个Vector的最后一个元素是:");
		PrintType(ptr, vector.typeSize);
		putchar(10);
	}
}

static void TestVectorEmpty(CTLVector vector){
	if (CTLVectorEmpty(vector) == TRUE)
		printf("\t\t\t这个vector为空。\n");
	else
		printf("\t\t\t这个vector不是空的.\n");
}


static void TestVectorSize(CTLVector vector){
	printf("\t\t\t这个vector的元素个数是%d\n", CTLVectorSize(vector));
}


static void TestVectoGetAt(CTLVector *vector){
	int num, result;
	union ScanVal val;
	void *record = (void *)(&val);

	printf("\t请输入你想得到数据的位置:");
	scanf("%d", &num);
	getchar();
	result = CTLVectorGetAt(vector, record, num);
	if (result == NORMAL){
		printf("\t\tvector中%d处数据是：", num);
		if (record == NULL)   //遇到了Erase位置
			printf("*");
		else
			PrintType(record, vector->typeSize);
		printf("\n");
	}
	else
		DealResult(result);
}

static void TestVectorSetAt(CTLVector *vector){
	int num, result;
	void *record;
	union ScanVal val;

	printf("\t设置之前的vector数据是:\n");
	PrintVector(*vector);
	printf("\t请输入你想设置数据的位置:");
	scanf("%d", &num);
	getchar();
	printf("\t请输入你需要设置的数据.\n");
	ScanType(&val, vector->typeSize);
	record = (void *)(&val);

	result = CTLVectorSetAt(vector, record, num);
	if (result == NORMAL){
		printf("\t\tvector中%d处数据是：", num);
		if (record == NULL)   //遇到了Erase位置
			printf("*");
		else
			PrintType(record, vector->typeSize);
		printf("\n");
	}
	else
		DealResult(result);
	printf("\t\t设置之后的vector的数据是:\n");
	PrintVector(*vector);
}



static void TestVectorInsert(CTLVector *vector){
	int num, result;
	union ScanVal val;

	printf("\t插入之前的vector数据是:\n");
	PrintVector(*vector);
	printf("\t请输入你想插入数据的位置:");
	scanf("%d", &num);
	getchar();
	printf("\t请输入你要插入的数据.\n");
	ScanType(&val, vector->typeSize);

	result = CTLVectorInsert(vector, (void *)(&val), num);
	DealResult(result);
	printf("\t\t插入之后的vector的数据是:\n");
	PrintVector(*vector);
}

static void TestVectorSetSize(CTLVector *vector){
	int len;

	printf("\t设置长度之前的vector是:\n");
	PrintVector(*vector);
	printf("\t请输入你想设置的新长度:");
	scanf("%d", &len);
	getchar();
	DealResult(CTLVectorSetSize(vector, len));
	printf("\t设置长度之后的vector是:\n");
	PrintVector(*vector);
}


static void TestVectorErase(CTLVector *vector){
	int pos;

	printf("\t\t擦除操作之前的vector是：\n");
	PrintVector(*vector);
	printf("\t\t请输入你想擦除的位置：");
	scanf("%d", &pos);
	getchar();
	DealResult(CTLVectorErase(vector, pos));
	printf("\t\t擦除操作之后的vector是：\n");
	PrintVector(*vector);
}

static void TestVectorDelete(CTLVector *vector){
	int pos;

	printf("\t\t删除操作之前的vector是：\n");
	PrintVector(*vector);
	printf("\t\t请输入你想删除的位置：");
	scanf("%d", &pos);
	getchar();
	DealResult(CTLVectorDelete(vector, pos));
	printf("\t\t删除操作之后的vector是：\n");
	PrintVector(*vector);
}

static void TestVectorClear(CTLVector *vector){
	printf("\t\t清除操作之前的vector是：\n");
	PrintVector(*vector);
	CTLVectorClear(vector);
	printf("\t\t清除操作之后的vector是：\n");
	PrintVector(*vector);
}

static void TestVectorCopy(){
	int i, result, var;

	INIT_CTL_VECTOR(int, vecInt1, 3);
	INIT_CTL_VECTOR(int, vecInt2, 5);
	INIT_CTL_VECTOR(int, vecInt3, 7);
	INIT_CTL_VECTOR(char, vecChar, 5);

	printf("\t现在测试CTLVectorCopy()函数\n");
	for (i=0; i<vecInt2.length-1; i++){
		printf("\t\t请输入插入vecInt2的第%d个数据:", i+1);
		scanf("%d", &var);
		getchar();
		result = CTLVectorInsert(&vecInt2, (void *)(&var), i+1);
		if (result != NORMAL)
			printf("\t\t插入vecInt2数据过程中出现异常\n");
	}

	printf("\t\t\tvecInt2的资料是:\n");
	PrintVector(vecInt2);

	printf("以vecInt2为src，以vecInt1为dst进行Copy操作.\n");
	result = CTLVectorCopy(&vecInt1, &vecInt2);
	DealResult(result);
	printf("\t\t复制后的vecInt1的资料是:\n");
	PrintVector(vecInt1);

	printf("\t以vecInt2为src，以vecInt3为dst进行Copy操作.\n");
	result = CTLVectorCopy(&vecInt3, &vecInt2);
	DealResult(result);
	printf("\t复制后的vecInt3的资料是:\n");
	PrintVector(vecInt3);

	printf("\t以vecInt2为src，以vecChar为dst进行Copy操作.\n");
	result = CTLVectorCopy(&vecChar, &vecInt2);
	DealResult(result);
	printf("\t复制后的vecChar的资料是:\n");
	PrintVector(vecChar);

	FREE_CTL_VECTOR(vecInt1);
	FREE_CTL_VECTOR(vecInt2);
	FREE_CTL_VECTOR(vecInt3);
	FREE_CTL_VECTOR(vecChar);
}


void TestVector(){
	int type, flg, quit;
	char choice;
	CTLVector *vec;

	INIT_CTL_VECTOR(int, vecInt, 8);
	INIT_CTL_VECTOR(char, vecChar, 8);
	INIT_CTL_VECTOR(double, vecDou, 8);

	quit = 1;
	while (quit){
		printf("\t\t1(int), 2(char), 3(double),请输入你要测试的类型;");
		scanf("%d", &type);
		getchar();
		switch (type){
			case 1:
				vec = &vecInt;
				break;
			case 2:
				vec = &vecChar;
				break;
			case 3:
				vec = &vecDou;
				break;
			default:
				printf("你输入了错误的值,\n");
				break;
		}  //switch (type) is over

		printf("操作序号为：\n"   \
			    "b(begin), n(end), e(empty), l(size)\n"  \
				 "g(GetAt), s(SetAt), i(insert), a(SetSize)\n"   \
				 "r(Erase), d(Delete), c(Clear), \n"    \
				 "p(Print), y(Copy), q(quit)\n");
		flg = TRUE;
		while (flg == TRUE){
			printf("\t请输入你选择的操作序号:");
			scanf("%c", &choice);
			getchar();

			switch (choice){
				case 'b':
					TestVectorBegin(*vec);
					break;
				case 'n':
					TestVectorEnd(*vec);
					break;
				case 'e':
					TestVectorEmpty(*vec);
					break;
				case 'l':
					TestVectorSize(*vec);
					break;
				case 'g':
					TestVectoGetAt(vec);
					break;
				case 's':
					TestVectorSetAt(vec);
					break;
				case 'i':
					TestVectorInsert(vec);
					break;
				case 'a':
					TestVectorSetSize(vec);

					break;
				case 'r':
					TestVectorErase(vec);
					break;
				case 'd':
					TestVectorDelete(vec);
					break;
				case 'c':
					TestVectorClear(vec);
					break;
				case 'p':
					PrintVector(*vec);
					break;
				case 'y':
					TestVectorCopy();
					break;
				case 'q':
					flg = FALSE;
					break;
				default:
					printf("你输入的操作序号不对\n");
					break;
			}  //switch (choice) is over

			printf("\n\n");
		}  //while (flg == TURE) is over

		printf("\t输入0结束测试，输入非零值代表继续测试:");
		scanf("%d", &quit);
		getchar();
	}  //while (quit) is over

	FREE_CTL_VECTOR(vecInt);
	FREE_CTL_VECTOR(vecChar);
	FREE_CTL_VECTOR(vecDou);
}

