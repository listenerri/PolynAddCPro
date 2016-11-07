#include <stddef.h>
#include <stdlib.h>
#include <stdio.h>
#include "Polyn.h"

//创建空表
PLinkList CreatePolyn(PLinkList sPolyn) {
	//为头节点开辟空间
	sPolyn = (PLinkList)malloc(sizeof(PLNODE));
	//判断sPolyn是否为空，是就退出
	sPolyn->next = NULL;
	return sPolyn;
}

//将新节点插入链表尾部
void ListInsert(PLinkList sPolyn, PLNODE sNewNode) {
	//建立临时链表用于找到链表尾部
	PLinkList sTemp = sPolyn;
	//为新节点申请空间返回其指针
	PLinkList psNewNode = (PLinkList)malloc(sizeof(PLNODE));

	//判断psNewNode是否为空，是就退出
	
	//将指针将新节点存入空间
	*psNewNode = sNewNode;

	//找到链表尾部并指向新链表
	while(sTemp->next != NULL) {

		sTemp = sTemp->next;
	}

	//将新节点插入链表尾部
	sTemp->next = psNewNode;

	//将新节点的指针域置为空
	psNewNode->next = NULL;

}

//输出多项表达式的某一项
void PrintPoly(PLNODE sPTemp) {
	//当指数为0时，直接输出系数
	if(sPTemp.nExpn == 0) {
		printf("%.2f", sPTemp.dbCoef);
	}
	//当指数为1时
	else if(sPTemp.dbCoef == 1) {
		if(sPTemp.nExpn == 1) {
			printf("X");
		}
		else {
			printf("X^%d", sPTemp.nExpn);
		}
	}
	//当指数为-1时
	else if(sPTemp.dbCoef == -1) {
		if(sPTemp.nExpn == 1) {
			printf("-X");
		}
		else {
			printf("-X^%d", sPTemp.nExpn);
		}
	}
	else {
		if(sPTemp.nExpn == 1) {
			printf("%.2fX", sPTemp.dbCoef);
		}
		else {
			printf("%.2fX^%d", sPTemp.dbCoef, sPTemp.nExpn);
		}
	}
}

//输出多项表达式整体
void PrintPolyn(PLinkList sPolyn) {
	int nIndex = 0;
	//sPTemp指向第一个项数
	PLinkList sPTemp = sPolyn->next;
	while(sPTemp != NULL) {
		nIndex++;
		//直接输出第一项
		if(nIndex == 1) {
			PrintPoly(*sPTemp);
		}
		//如果系数大于0，先输出+号
		else if(sPTemp->dbCoef > 0) {
			printf("+");
			PrintPoly(*sPTemp);
		}
		else {
			PrintPoly(*sPTemp);
		}
		sPTemp = sPTemp->next;
	}
}

//多项式相加
PLinkList AddPolyn(PLinkList sPolyn1,PLinkList sPolyn2) {
	//创建和多项式空链表
	PLinkList sPolynAdd = NULL;
	sPolynAdd = CreatePolyn(sPolynAdd);
	//定义两个指针分别指向第一，二个多项式的第一项
	PLinkList sPolyn1Temp = sPolyn1->next;
	PLinkList sPolyn2Temp = sPolyn2->next;
	//要插入到和多项式的新节点
	PLNODE sNewNode;

	//遍历两个多项式,将其数据按规则放入新链表(一元多项式之和)
	while((sPolyn1Temp != NULL) && (sPolyn2Temp != NULL)) {
		//取A多项式一项的指数和B多项式一项的指数之差
		int nEx = sPolyn1Temp->nExpn - sPolyn2Temp->nExpn;
		//当指数之差小于0
		if(nEx < 0) {
			//将A多项式中较小的一项作为新节点的一项
			//B多项式中较大的一项暂不处理
			sNewNode.nExpn = sPolyn1Temp->nExpn;
			sNewNode.dbCoef = sPolyn1Temp->dbCoef;
			//将提取出来的新节点存入和链表中
			ListInsert(sPolynAdd,sNewNode);
			//让sPolyn1Temp指向下一个节点
			//准备读取A多项式的下一项
			sPolyn1Temp = sPolyn1Temp->next;
		}
		//当指数之差等于0
		else if(nEx == 0) {
			//取两项的系数之和
			double dbCo = sPolyn1Temp->dbCoef + sPolyn2Temp->dbCoef;
			//当前相同指数项的系数和不为零
			if(dbCo != 0.0) {
				sNewNode.nExpn = sPolyn1Temp->nExpn;
				sNewNode.dbCoef = dbCo;
				//将提取出来的项存入和链表中
				ListInsert(sPolynAdd,sNewNode);
			}
			//移动sPolyn1Temp的节点
			//准备读取A多项式的下一项
			sPolyn1Temp = sPolyn1Temp->next;
			//移动sPolyn2Temp的节点
			//准备读取B多项式的下一项
			sPolyn2Temp = sPolyn2Temp->next;
		}
		//当指数之差大于0
		else {
			sNewNode.nExpn = sPolyn2Temp->nExpn;
			sNewNode.dbCoef = sPolyn2Temp->dbCoef;
			//将提取出来的项存入和链表中
			ListInsert(sPolynAdd,sNewNode);
			//移动sPolyn2Temp的节点
			sPolyn2Temp = sPolyn2Temp->next;
		}
	}

	//当有一个链表遍历完时就停止循环，可能另一个链表还没遍历完
	//定义新链表，判断哪个没遍历完就赋值给新链表
	//并把新链表中剩余的节点放到和链表中
	PLinkList sPolynTemp = NULL; 
	if(sPolyn1Temp == NULL) {
	    sPolynTemp = sPolyn2Temp;
	}
	else if(sPolyn2Temp == NULL) {
	    sPolynTemp = sPolyn1Temp;
	}
	while(sPolynTemp != NULL) {
		sNewNode.nExpn = sPolynTemp->nExpn;
		sNewNode.dbCoef = sPolynTemp->dbCoef;
		//将提取出来的项存入和链表中
		ListInsert(sPolynAdd,sNewNode);
		//移动sPolyn2Temp的节点
		sPolynTemp = sPolynTemp->next;
	}

	return sPolynAdd;
}

//释放链表
void FreePolyn(PLinkList sPolyn) {
	PLinkList sTemp = sPolyn;
	while(sPolyn != NULL) {
		sPolyn = sPolyn->next;
		free(sTemp);
		sTemp = sPolyn;
	}
}

//按照各项系数由小到达的顺序将多项式排序
PLinkList ListSort(PLinkList sPolyn) {
	PLinkList sTemp1,sTemp2;
	int nTemp = 0;
	double dbTemp = 0.0;
	for(sTemp1 = sPolyn; sTemp1 != NULL; sTemp1 =sTemp1->next) {
		for(sTemp2 = sTemp1->next; sTemp2 != NULL; sTemp2 =sTemp2->next) {
			if(sTemp1->nExpn > sTemp2->nExpn) {
				//如果sTemp1节点的指数值大，就交换两个节点的指数
				nTemp = sTemp2->nExpn;
				sTemp2->nExpn = sTemp1->nExpn;
				sTemp1->nExpn = nTemp;
				//同时交换两个节点的系数
				dbTemp = sTemp2->dbCoef;
				sTemp2->dbCoef = sTemp1->dbCoef;
				sTemp1->dbCoef = dbTemp;
			}
		}
	}
	return sPolyn;
}
