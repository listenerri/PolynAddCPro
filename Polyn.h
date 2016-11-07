#include "StructDefine.h"

int InputData(int nOrder, PLNODE *sPolyn);
int GetInt(int *value);

PLinkList CreatePolyn(PLinkList sPolyn);
void ListInsert(PLinkList sPolyn, PLNODE sNewNode);
void PrintPoly(PLNODE sPTemp);
PLinkList ListSort(PLinkList sPolyn);
void PrintPolyn(PLinkList sPolyn);
PLinkList AddPolyn(PLinkList sPolyn1,PLinkList sPolyn2);
