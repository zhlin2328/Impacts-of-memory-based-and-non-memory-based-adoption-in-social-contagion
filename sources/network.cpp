/****************************************Copyright (c)*************************************************
**                      		Fujian Medical University
**                               http://www.fjmu.edu.cn/
**--------------File Info------------------------------------------------------------------------------
** File name:           network.cpp
** Created by:          linzhaohua
** Created date:        2018-4-28
** Version:             V1.0
** Descriptions:        network.cpp
********************************************************************************************************/
#include "../headers/config.h"

#ifdef ER_NETWORK
struct ERNetwork g_Net; //定义全局变量

#elif defined WS_NETWORK
struct WSNetwork g_Net;

#elif defined BA_NETWORK
struct BANetwork g_Net;

#elif defined COMPLETE_NETWORK
struct CmpltNetwork g_Net;

#elif defined UCM_NETWORK
struct UCMNetwork g_Net;

#elif defined REGULAR_RANDOM_NETWORK
struct RRNNetwork g_Net;

#elif defined REGULAR_NETWORK
struct REGNetwork g_Net;

#else
#error "no defined network"
#endif
LIST *g_netAdjList;

/********************************************************************************************************************************
** Function name:       fun_nktonn
** Descriptions:        generate nk to nn network,还没验证正确性
** input parameters:    None
** output parameters:   net_nn
** Returned value:      net_nn
********************************************************************************************************************************/
int **fun_nktonn(void)
{
	int **b;
	int temp;
	NODE *work;

	b = (int **)malloc(g_Net.N * sizeof(int *));
	for (int i = 0; i < g_Net.N; i++)
	{
		b[i] = (int *)malloc(g_Net.N * sizeof(int));
	}
	for (int i = 0; i < g_Net.N; i++)
	{
		for (int j = 0; j < g_Net.N; j++)
		{
			b[i][j] = 0;
		}
	}
	for (int i = 0; i < g_Net.N; i++)
	{
		work = g_netAdjList[i].p_head->next;
		while (NULL != work)
		{
			temp = work->data;
			b[i][temp] = 1;
		}
	}
	Free2D_NK(g_Net.N, g_netAdjList);
	return b;
}
/********************************************************************************************************************************
** Function name:       fun_nntonk
** Descriptions:        generate nn to nk network
** input parameters:    net_nn
** output parameters:   None
** Returned value:      None
********************************************************************************************************************************/
void fun_nntonk(int **net_nn)  //convert adjacant matrix to single linked list
{
	Init_NK();  
	for (int i = 0; i < g_Net.N; i++)
	{
		for (int j = i; j < g_Net.N; j++)
		{
			if (net_nn[i][j] == 1)
			{
				Push_Back_NK(j, i);
				Push_Back_NK(i, j);
			}
		}
	}
	for (int i = 0; i < g_Net.N; i++)
	{
		free(net_nn[i]);
	}
	free(net_nn);
}
/***********************************************End Of File*********************************************************************/

