//#pragma warning(disable:4996)
/****************************************Copyright (c)*************************************************
**                      		Fujian Medical University
**                               http://www.fjmu.edu.cn/
**--------------File Info------------------------------------------------------------------------------
** File name:           list.cpp
** Created by:          linzhaohua
** Created date:        2018-4-12
** Version:             V1.0
** Descriptions:        list.cpp
********************************************************************************************************/
#include "../headers/config.h"
/********************************************************************************************************************************
** Function name:       Init_NK
** Descriptions:        Init_NK
** input parameters:    None
** output parameters:   None
** Returned value:      None
********************************************************************************************************************************/
void Init_NK(void)
{
	g_netAdjList = (LIST *)malloc(g_Net.N * sizeof(LIST));
	for (int i = 0; i < g_Net.N; i++)
	{
		NODE *p_node = (NODE *)malloc(sizeof(NODE));

		g_netAdjList[i].p_head = p_node;
		g_netAdjList[i].p_head->data = 0;  //head->data用来存网络节点的度，也就是这一行链表的长度,->next用来存首个节点,tail的地址为最后一个节点
		g_netAdjList[i].p_head->next = NULL;
		g_netAdjList[i].p_tail = g_netAdjList[i].p_head;
	}
}
/********************************************************************************************************************************
** Function name:       Pop_Back_NK
** Descriptions:        Pop_Back_NK
** input parameters:    rowIndex
** output parameters:   None
** Returned value:      None
********************************************************************************************************************************/
void Pop_Back_NK(int rowIndex)
{

	NODE *work = g_netAdjList[rowIndex].p_head->next;
	NODE *temp = g_netAdjList[rowIndex].p_head;

	if (NULL == work)
	{
		printf("Pop_Back: no node in this list\n");
		exit(-1); 
	}
	while (NULL != work->next)
	{
		temp = work;
		work = work->next;
	}
	temp->next = NULL;
	g_netAdjList[rowIndex].p_tail = temp;
	free(work);
	work = NULL;
	g_netAdjList[rowIndex].p_head->data -= 1;
}
/********************************************************************************************************************************
** Function name:       Push_Back_NK
** Descriptions:        Push_Back_NK
** input parameters:    data,rowIndex
** output parameters:   None
** Returned value:      None
********************************************************************************************************************************/
void Push_Back_NK(DATATYPE data, int rowIndex)
{
	NODE *p_node = (NODE *)malloc(sizeof(NODE));

	p_node->data = data;
	p_node->next = NULL;
	g_netAdjList[rowIndex].p_tail->next = p_node;
	g_netAdjList[rowIndex].p_tail = p_node;

	g_netAdjList[rowIndex].p_head->data += 1;
}
/********************************************************************************************************************************
** Function name:       Delete_Edge_NK
** Descriptions:        delete edgeEnd in the list of edgeBegin
** input parameters:    edgeEnd,edgeBegin
** output parameters:   None
** Returned value:      None
********************************************************************************************************************************/
void Delete_Edge_NK(int edgeEnd, int edgeBegin)
{
	NODE *preNode = g_netAdjList[edgeBegin].p_head;
	NODE *curNode = g_netAdjList[edgeBegin].p_head->next;

	while (NULL != curNode)
	{
		if (curNode->data == edgeEnd)
		{
			if (NULL == curNode->next)
			{
				g_netAdjList[edgeBegin].p_tail = preNode;
			}
			preNode->next = curNode->next;
			free(curNode);		//指针被释放后不会等于NULL，除非释放后又令其等于NULL
			g_netAdjList[edgeBegin].p_head->data -= 1;
			break;
		}
		else
		{
			preNode = curNode;
			curNode = curNode->next;
		}
	}
	if (NULL == curNode)
	{
		printf("Delete_Edge: no edges in this list or not found\n");
		exit(-1);
	}
}
/********************************************************************************************************************************
** Function name:       Is_In_List_NK
** Descriptions:        判断desNode是否在srcNode的链表里（yes：return 1，no：return 0）
** input parameters:    desNode,srcNode
** output parameters:   判断值,return 1 if it is in the list, else return 0
** Returned value:      1,0
********************************************************************************************************************************/
int Is_In_List_NK(int desNode, int srcNode)
{
	NODE *work;

	work = g_netAdjList[srcNode].p_head->next;
	while (NULL != work)
	{
		if (work->data == desNode)
		{
			return 1;
			break;
		}
		work = work->next;
	}
	return 0;
}
/********************************************************************************************************************************
** Function name:       Output_NK
** Descriptions:        Output_NK
** input parameters:    num,net
** output parameters:   None
** Returned value:      None
********************************************************************************************************************************/
void Output_NK(int num, LIST *net)
{
	FILE *fp;
	NODE *work;

	fp = fopen("net_nk.csv", "w");
	/*if (NULL == net->p_head)
	{
		printf("net is NULL\n");
		exit(-1);
	}*/
	//cout << endl;
	for (int i = 0; i < num; i++)
	{
		work = net[i].p_head;
		//cout << work->data << " ";
		fprintf(fp, "%d,", work->data);

		while (NULL != work->next)
		{
			work = work->next;
			//cout << work->data << " ";
			fprintf(fp, "%d,", work->data);
		}
		//cout << endl;
		fprintf(fp, "\n");
	}
	fclose(fp);
}
/********************************************************************************************************************************
** Function name:       Free2D_NK
** Descriptions:        Free2D_NK
** input parameters:    num,net
** output parameters:   None
** Returned value:      None
********************************************************************************************************************************/
void Free2D_NK(int num, LIST *net)
{
	NODE *curNode;

	for (int i = 0; i < num; i++)
	{
		NODE *nextNode = net[i].p_head->next;
		while (NULL != nextNode)
		{
			curNode = nextNode;
			nextNode = nextNode->next;
			free(curNode);
		}
		free(net[i].p_head);
	}
	free(net);
	//net->p_head = NULL;
}
/********************************************************************************************************************************
** Function name:       Is_Head_Data_Equal_Length
** Descriptions:        判断节点node的head->data是否计算正确
** input parameters:    node
** output parameters:   yes：return 1，no：return 0
** Returned value:      1,0
********************************************************************************************************************************/
int Is_Head_Data_Equal_Length(int node)
{
	int cnt = 0;
	NODE *work = g_netAdjList[node].p_head->next;
	int headData = g_netAdjList[node].p_head->data;

	while (NULL != work)
	{
		cnt++;
		work = work->next;
	}
	if (cnt == headData)
	{
		return 1;
	}

	return 0;
}
/*****************************************************End Of File***************************************/
