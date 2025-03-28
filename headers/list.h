#pragma once
/****************************************Copyright (c)*************************************************
**                      		Fujian Medical University
**                               http://www.fjmu.edu.cn/
**--------------File Info------------------------------------------------------------------------------
** File name:           list.h
** Created by:          linzhaohua
** Created date:        2018-4-12
** Version:             V1.0
** Descriptions:        list.h
********************************************************************************************************/
#ifndef __LIST_H
#define __LIST_H

typedef int DATATYPE;
typedef struct Node { //debug
	DATATYPE data;    //������
	struct Node *next;    //ָ����
}NODE;
typedef struct List  //��������
{
	NODE *p_head; //��ͷָ��
	NODE *p_tail; //��βָ��
} LIST;

void Init_NK(void);
void Pop_Back_NK(int rowIndex);
void Push_Back_NK(DATATYPE data, int rowIndex);
void Delete_Edge_NK(int edgeEnd, int edgeBegin);
int Is_In_List_NK(int desNode, int srcNode);
void Output_NK(int num, LIST *net);
void Free2D_NK(int num, LIST *net);
int Is_Head_Data_Equal_Length(int node);

#endif //__LIST_H
/*****************************************************End Of File***************************************/

