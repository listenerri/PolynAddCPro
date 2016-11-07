typedef struct PLNODE{
	//系数域
	double dbCoef;
	//指数域
	int nExpn;
	//指针域，指向下一个节点
	struct PLNODE * next;
}PLNODE, *PLinkList;
