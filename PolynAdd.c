#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <ctype.h>
#include "Polyn.h"

/*
 * 核心思想：
 * 将每一个多项式抽象成一个链表
 * 多项式的每一项都抽象成链表中的一个节点
 * 
 * 共涉及到三个链表：
 * 1.加数链表
 * 2.被加数链表
 * 3.和链表
 */

int main() {
	//输出界面
	printf("\n/* 注意: 系数为浮点类型, 指数为整数(可为负)类型 */\n");
	printf("/* 注意: 本程序计算结果精度为2, 请按指数从小到大的顺序输入多项式 */\n\n");

	//创建第一个多项式的头节点
	PLinkList sPolyn1 = NULL;
	sPolyn1 = CreatePolyn(sPolyn1);
	if(sPolyn1 == NULL) {
	    printf("%s\n", "第一个多项式头节点为空!!!");
	}
	int inputResult1 = InputData(1, sPolyn1);
	if (inputResult1 != 0) {
	    printf("%s\n", "输入有误, 正在退出程序..");
	    return -1;
	}

	//创建第二个多项式的头节点
	PLinkList sPolyn2 = NULL;
	sPolyn2 = CreatePolyn(sPolyn2);
	if(sPolyn2 == NULL) {
	    printf("%s\n", "第二个多项式头节点为空!!!");
	}
	int inputResult2 = InputData(2, sPolyn2);
	if (inputResult2 != 0) {
	    printf("%s\n", "输入有误, 正在退出程序..");
	    return -1;
	}


	//打印输出一元多项式
	printf("\n############输入结束############\n\n");
	printf("%s\n", "第一个多项式为:");
	PrintPolyn(sPolyn1);
	printf("\n");
	printf("%s\n", "第二个多项式为:");
	PrintPolyn(sPolyn2);
	printf("\n\n");

	//将两个一元多项式相加
	printf("%s\n", "正在将两个多项式相加...");
	printf("%s\n", "结果为:");
	PLinkList resultPolyn = AddPolyn(ListSort(sPolyn1), ListSort(sPolyn2));

	//打印输出一元多项式之和
	PrintPolyn(resultPolyn);
	printf("\n\n");

	return 0;
}

//将数据放入链表并打印
int InputData(int nOrder, PLNODE *sPolyn) {
	//使用GetInt()函数输入项数并检查是否为整数且大于0
	if (nOrder == 1) {
	    printf("%s\n", "请输入第一个多项式的项数:");
	}
	else if (nOrder == 2) {
	    printf("%s\n", "请输入第二个多项式的项数:");
	}
	int numXiang = 0;
	int flagXiang = GetInt(&numXiang);
	while ( flagXiang != 0 || numXiang == 0 ) {
	    printf("%s\n", "项数必须为非零正整数!请重新输入:");
	    flagXiang = GetInt(&numXiang);
	}

	//定义新节点
	PLNODE sNewNode;
	//定义两个记录已输入过的指数的数组以及已使用的下标
	int nExpnTemp1[100], nExpnTemp2[100];
	int nExpnNum1=1, nExpnNum2=1;
	//根据项数循环
	for(int i = 0; i < numXiang; i++) {
		//输入系数，且系数不能为0
		if (nOrder == 1) {
		    printf("请输入第一个多项式第%d项的系数:\n", i+1);
		}
		else if (nOrder == 2) {
		    printf("请输入第二个多项式第%d项的系数:\n", i+1);
		}
		int dbCoef = 0;
		int flagXi = GetInt(&dbCoef);
		while ( flagXi != 0 || dbCoef == 0 ) {
		    printf("%s\n", "系数必须为非零实数!请重新输入:");
		    flagXi = GetInt(&dbCoef);
		}

		//输入指数并检测是否为实数
		if (nOrder == 1) {
		    printf("请输入第一个多项式第%d项的指数:\n", i+1);
		}
		else if (nOrder == 2) {
		    printf("请输入第二个多项式第%d项的指数:\n", i+1);
		}
		int nExpn = 0;
		int flagZhi = GetInt(&nExpn);
		while ( flagZhi != 0 ) {
		    printf("%s\n", "指数必须为实数!请重新输入:");
		    flagZhi = GetInt(&nExpn);
		}

		//将当前指数与数组中的指数比较，如果发现之前输入过就报错
		if (nOrder == 1) {
		    for (int j = 0; j < nExpnNum1; j++) {
		        if (nExpn == nExpnTemp1[i]) {
		            printf("%s\n", "你输入了重复的系数!");
		        }
		    }
		}
		else if (nOrder == 2) {
		    for (int k = 0; k < nExpnNum2; k++) {
		        if (nExpn == nExpnTemp2[k]) {
		            printf("%s\n", "你输入了重复的系数!");
			    return -1;
		        }
		    }
		}

		//使用数组记录之前输入的指数
		if (nOrder == 1) {
		    nExpnTemp1[nExpnNum1-1] = nExpn;
		    nExpnNum1++;
		}
		else if (nOrder == 2) {
		    nExpnTemp2[nExpnNum2-1] = nExpn;
		    nExpnNum2++;
		}

		//存入数据
		sNewNode.dbCoef = dbCoef;
		sNewNode.nExpn = nExpn;

		//将新节点插入多项式链表尾部
		ListInsert(sPolyn,sNewNode);
	}
    return 0;
}

//接受一个指针参数,用于存放最终的数据
//让用户输入数据,判断是否是数字,并转换为整型
//本方法只完成上述功能,具体数据用于何种目的,
//由调用本方法的地方决定
int GetInt(int *value) {
	char str[256] = {0};
	//清空缓存区
	fflush(stdin);
	//等待输入数据，并将数据存到str中
	scanf("%s", str);
	unsigned int index = 1;
	int nTemp = 0;
	//判断输入的是否为负数
	if(str[0] == '-') {
		nTemp = 1;
	}
	for(index = nTemp; index < strlen(str); index++) {
		//判断str中每个字符是否为0-9，是就循环，不是就返回false
		if(isdigit(str[index]) == 0)
		    return 1;
	}
	//如果输入的字符串为纯数字就转化为整型
	*value = atoi(str);
	return 0;
}
