/**
 * 本文件作为CTL项目的公共头文件，包含 一般情况宏定义，错误类型标号的宏定义
 */

#ifndef _CTL_STANDARD_H
#define _CTL_STANDARD_H


 #include <string.h>
 #include <stdio.h>
 #include <stdlib.h>
 #include <assert.h>

 #define NULL 0
 #define FALSE 0
 #define TRUE 1
 #define NORMAL 2

 #define TYPE_CHAR      1
 #define TYPE_INT       4
 #define TYPE_DOUBLE    8

 //错误标识
 #define CTL_OUT_OF_RANGE           1000     //超出了默认的cTL长度范围
 #define CTL_PTR_IS_NULL            1001     //作为形参的指向ctl的指针是空的
 #define CTL_NO_VALUE               1002     //CTL长度为0,或者 没有要求的值
 #define CTL_TYPESIZE_NO_MATCH      1003     //进行copy过程中，两者的元素类型字节数不匹配


 #define RECORD_PTR_IS_NULL         1004     //作为形参的指向record的指针为空

 #define MALLOC_FAIL                1005     //使用malloc函数分配内存失败，分配得到是空地址
 #define NUM_IS_WRONG               1006     //插入删除等位置信息是错误的
 #define NUM_WRONG_BUT_DO_SOMETHING 1007     //插入删除等位置信息是错误的，但是做了相应的处理

 //Todo 这里没有添加屏蔽警告的语句

#endif // _CTL_STANDARD_H

