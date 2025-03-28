/****************************************Copyright (c)*************************************************
**                      		Fujian Medical University
**                               http://www.fjmu.edu.cn/
**--------------File Info------------------------------------------------------------------------------
** File name:           spread.cpp
** Created by:          linzhaohua
** Created date:        2024-4-20
** Version:             V1.0
** Descriptions:        spread.cpp
********************************************************************************************************/
#include "../headers/config.h"

static void Cal_ThIn_NodeMemory(DIFFUSION *p_Dif);
static void Set_Diffusion_Parm(DIFFUSION *p_Dif);
static void Init_Diffusion_Env(DIFFUSION *p_Dif, vector<vector<double> >& rhoT);
static void Calculate_Total_ThCnt_Of_Nodes(DIFFUSION *p_Dif);
static void Start_One_Step_Diffusion(DIFFUSION *p_Dif);
static void Fail(DIFFUSION *p_Dif, int node);
static void Recover(DIFFUSION *p_Dif, int node);
static void Inc_NeiborI_Num(DIFFUSION *p_Dif, int srcNode);
static void Dec_NeiborI_Num(DIFFUSION *p_Dif, int srcNode);
/********************************************************************************************************************************
** Function name:       Cal_Rho_Of_Memory_Model
** Descriptions:        Cal_Rho_Of_Memory_Model
** input parameters:    rhoT
** output parameters:   None
** Returned value:      None
********************************************************************************************************************************/
void Cal_Rho_Of_Memory_Model(vector<vector<double> >& rhoT)
{
	DIFFUSION Dif;

	//Allocate_Types_Of_Nodes();
	Set_Diffusion_Parm(&Dif);
	Init_Diffusion_Env(&Dif, rhoT);
	//Output_OtherPara_To_File(Dif, 0);
	for (int i = 1; i < g_Spd.TOTAL_UPDATE_STEPS; i++)
	{
		Cal_ThIn_NodeMemory(&Dif);
		Calculate_Total_ThCnt_Of_Nodes(&Dif);
		Start_One_Step_Diffusion(&Dif);
		//Output_OtherPara_To_File(Dif, i);

		rhoT[0][i] = rhoT[0][i - 1] + g_Spd.UPDATE_STEP_LEN;
		rhoT[1][i] = (1.0 * Dif.rhoCnt) / g_Net.N;
		rhoT[2][i] = (1.0 * Dif.rhoACnt) / g_Net.N;
		rhoT[3][i] = (1.0 * Dif.rhoBCnt) / g_Net.N;
	}
	//vector<int>().swap(g_Spd.nodeType);
}
void Cal_ThIn_NodeMemory(DIFFUSION *p_Dif)
{
	for (int i = 0; i < g_Net.N; i++)
	{
		if (g_Spd.nodeType[i] == 1)			//is type B
		{
			p_Dif->usedMemory_Space = p_Dif->thIn_NodeMemory[i].size();  //计算已使用的memory空间
			if (p_Dif->usedMemory_Space >= p_Dif->MEMORY_SPACE)
			{
				p_Dif->thIn_NodeMemory[i].pop_front();
			}

			if (p_Dif->neighborI_Num[i] >= g_Spd.INFECT_THRESHOLD_B)
			{
				p_Dif->thIn_NodeMemory[i].push_back(1);
			}
			else
			{
				p_Dif->thIn_NodeMemory[i].push_back(0);
			}
		}
	}
}
/********************************************************************************************************************************
** Function name:       Set_Diffusion_Parm
** Descriptions:        Set_Diffusion_Parm
** input parameters:    p_Dif
** output parameters:   None
** Returned value:      None
********************************************************************************************************************************/
void Set_Diffusion_Parm(DIFFUSION *p_Dif)
{
	int temp = Double_Into_Int(1.0 / g_Spd.UPDATE_STEP_LEN);
	double temp2;

	p_Dif->INFECT_PROB = g_Spd.INFECT_RATE * g_Spd.UPDATE_STEP_LEN;
	p_Dif->RECOVER_PROB = g_Spd.RECOVER_RATE * g_Spd.UPDATE_STEP_LEN;

	temp2 = g_Spd.MEMORY_LEN * double(temp);
	p_Dif->MEMORY_SPACE = Double_Into_Int(temp2);					

	p_Dif->usedMemory_Space = 0;
	p_Dif->thIn_NodeMemory.resize(g_Net.N);
	for (int i = 0; i < g_Net.N; i++)								//S state: 0;I state: 1
	{
		p_Dif->state.push_back(0);
		p_Dif->thCnt.push_back(0);
	}
	p_Dif->neighborI_Num.resize(g_Net.N, 0);
	p_Dif->neighborI_Num_Old.resize(g_Net.N, 0);
	Output_Diffusion_Parm(p_Dif);
}
/********************************************************************************************************************************
** Function name:       Init_Diffusion_Env
** Descriptions:        Init_Diffusion_Env
** input parameters:    p_Dif,rhoT
** output parameters:   None
** Returned value:      None
********************************************************************************************************************************/
void Init_Diffusion_Env(DIFFUSION *p_Dif, vector<vector<double> >& rhoT)
{
	int node;

	p_Dif->rhoCnt = 0;
	p_Dif->rhoACnt = 0;
	p_Dif->rhoBCnt = 0;
	for (int i = 0; i < g_Spd.INTIAL_RHO_NUM; i++)					//nodes for i states at first
	{
		do
		{
			node = g_Rd.distD(g_Rd.mt);
		} while (p_Dif->state[node] == 1);

		if (g_Spd.nodeType[node] == 0)
		{
			p_Dif->rhoACnt++;
		}
		else if (g_Spd.nodeType[node] == 1)
		{
			p_Dif->rhoBCnt++;
		}
		Fail(p_Dif, node);
	}
	rhoT[0][0] = 0.0;
	rhoT[1][0] = double(p_Dif->rhoCnt) / g_Net.N;
	rhoT[2][0] = double(p_Dif->rhoACnt) / g_Net.N;
	rhoT[3][0] = double(p_Dif->rhoBCnt) / g_Net.N;
}
/********************************************************************************************************************************
** Function name:       Calculate_Total_ThCnt_Of_Nodes
** Descriptions:        Calculate_Total_ThCnt_Of_Nodes
** input parameters:    p_Dif
** output parameters:   None
** Returned value:      None
********************************************************************************************************************************/
void Calculate_Total_ThCnt_Of_Nodes(DIFFUSION *p_Dif)
{
	vector< int >::iterator it1 = p_Dif->thCnt.begin();
	for (int i = 0; i < g_Net.N; i++)
	{
		if (g_Spd.nodeType[i] == 1)					//is type B
		{
			*it1 = 0;
			for (deque< int >::iterator it2 = p_Dif->thIn_NodeMemory[i].begin(); it2 != p_Dif->thIn_NodeMemory[i].end(); it2++)
			{
				*it1 += *it2;
			}
		}
		it1++;
	}
}
/********************************************************************************************************************************
** Function name:       Start_One_Step_Diffusion
** Descriptions:        Start_One_Step_Diffusion
** input parameters:    p_Dif
** output parameters:   None
** Returned value:      None
********************************************************************************************************************************/
void Start_One_Step_Diffusion(DIFFUSION *p_Dif)
{
	double temp;

	p_Dif->neighborI_Num_Old = p_Dif->neighborI_Num;
	for (int i = 0; i < g_Net.N; i++)
	{
		if (g_Spd.nodeType[i] == 0)					//is type A
		{
			if (p_Dif->state[i] == 0)
			{
				if ((p_Dif->neighborI_Num_Old[i] >= g_Spd.INFECT_THRESHOLD_A) && g_Rd.distF(g_Rd.mt) < p_Dif->INFECT_PROB)
				{
					p_Dif->rhoACnt++;
					Fail(p_Dif, i);
				}
			}
			else if (p_Dif->state[i] == 1)
			{
				if (g_Rd.distF(g_Rd.mt) < p_Dif->RECOVER_PROB)
				{
					p_Dif->rhoACnt--;
					Recover(p_Dif, i);
				}
			}
		}
		else if (g_Spd.nodeType[i] == 1)			//is type B
		{
			if (p_Dif->state[i] == 0)
			{
				if ((p_Dif->thCnt[i] == p_Dif->MEMORY_SPACE) && g_Rd.distF(g_Rd.mt) < p_Dif->INFECT_PROB)
				{
					p_Dif->rhoBCnt++;
					Fail(p_Dif, i);
				}
			}
			else if (p_Dif->state[i] == 1)
			{
				if (g_Rd.distF(g_Rd.mt) < p_Dif->RECOVER_PROB)
				{
					p_Dif->rhoBCnt--;
					Recover(p_Dif, i);
				}
			}
		}
	}
}
/********************************************************************************************************************************
** Function name:       Fail
** Descriptions:        Fail
** input parameters:    p_Dif,node
** output parameters:   None
** Returned value:      None
********************************************************************************************************************************/
void Fail(DIFFUSION *p_Dif, int node)
{
	p_Dif->state[node] = 1;
	p_Dif->rhoCnt++;
	Inc_NeiborI_Num(p_Dif, node);
}
/********************************************************************************************************************************
** Function name:       Recover
** Descriptions:        Recover
** input parameters:    p_Dif,node
** output parameters:   None
** Returned value:      None
********************************************************************************************************************************/
void Recover(DIFFUSION *p_Dif, int node)
{
	p_Dif->state[node] = 0;
	p_Dif->rhoCnt--;
	Dec_NeiborI_Num(p_Dif, node);
}
/********************************************************************************************************************************
** Function name:       Inc_NeiborI_Num
** Descriptions:        将srcNode节点的邻居节点的neighborI_Num加1
** input parameters:    p_Dif,srcNode
** output parameters:   None
** Returned value:      None
********************************************************************************************************************************/
void Inc_NeiborI_Num(DIFFUSION *p_Dif, int srcNode)
{
	NODE *work;
	int desNode;

	work = g_netAdjList[srcNode].p_head->next;
	while (NULL != work)
	{
		desNode = work->data;
		p_Dif->neighborI_Num[desNode]++;

		work = work->next;
	}
}
/********************************************************************************************************************************
** Function name:       Dec_NeiborI_Num
** Descriptions:        将srcNode节点的邻居节点的neighborI_Num减1
** input parameters:    p_Dif,srcNode
** output parameters:   None
** Returned value:      None
********************************************************************************************************************************/
void Dec_NeiborI_Num(DIFFUSION *p_Dif, int srcNode)
{
	NODE *work;
	int desNode;

	work = g_netAdjList[srcNode].p_head->next;
	while (NULL != work)
	{
		desNode = work->data;
		p_Dif->neighborI_Num[desNode]--;

		work = work->next;
	}
}
/*****************************************************End Of File***************************************/
