/****************************************Copyright (c)*************************************************
**                      		Fujian Medical University
**                               http://www.fjmu.edu.cn/
**--------------File Info--------------------------------------------------------------------------------------------------------
** File name:           set_parms.cpp
** Created by:          linzhaohua
** Created date:        2024-4-20
** Version:             V1.0
** Descriptions:        set_parms.cpp
********************************************************************************************************************************/
#include "../headers/config.h"

SPD g_Spd;
int g_taskNum;
/********************************************************************************************************************************
** Function name:       Double_Into_Int
** Descriptions:        Double_Into_Int
** input parameters:    oldValue
** output parameters:   newValue
** Returned value:      newValue
********************************************************************************************************************************/
int Double_Into_Int(const double oldValue)
{
	int newValue = int(oldValue);
	if (newValue - oldValue > 0.99)  
	{
		newValue--;
	}
	else if (oldValue - newValue > 0.99)
	{
		newValue++;
	}
	return newValue;
}
/********************************************************************************************************************************
** Function name:       Set_Spd_Parm
** Descriptions:        Set_Spd_Parm
** input parameters:    None
** output parameters:   None
** Returned value:      None
********************************************************************************************************************************/
void Set_Spd_Parm(void)
{
	double temp;

#ifdef PARM_INFECT_RATE
	g_Spd.RECOVER_RATE = 0.5;
#elif defined PARM_RECOVER_RATE
	g_Spd.INFECT_RATE = 0.5;
#endif
	g_Spd.UPDATE_STEP_LEN = 1.0;
	g_Spd.REAL_TIME_LEN = 1000;
	temp = g_Spd.REAL_TIME_LEN / g_Spd.UPDATE_STEP_LEN;
	g_Spd.TOTAL_UPDATE_STEPS = Double_Into_Int(temp);
	g_Spd.INTIAL_RHO_NUM = 500;
	g_Spd.INFECT_THRESHOLD_A = 3.0 + double(g_taskNum)*1.0;
	g_Spd.INFECT_THRESHOLD_B = 6.0;
	g_Spd.MEMORY_LEN = 3.0;
	g_Spd.ALPHA_FACTOR = 0.5;

	Output_Spd_Parm();
}
/********************************************************************************************************************************
** Function name:       Allocate_Types_Of_Nodes
** Descriptions:        Allocate_Types_Of_Nodes
** input parameters:    None
** output parameters:   None
** Returned value:      None
********************************************************************************************************************************/
void Allocate_Types_Of_Nodes(void)
{
	int aType_Num = Double_Into_Int(g_Spd.ALPHA_FACTOR * double(g_Net.N));
	int node;

	g_Spd.nodeType.resize(g_Net.N, 1);
	for (int i = 0; i < aType_Num; i++)
	{
		do
		{
			node = g_Rd.distD(g_Rd.mt);
		} while (g_Spd.nodeType[node] == 0);
		g_Spd.nodeType[node] = 0;		//0: type A; 1: type B
	}
}
/********************************************************************************************************************************
** Function name:       Set_Network_Parm
** Descriptions:        Set_Network_Parm
** input parameters:    None
** output parameters:   None
** Returned value:      None
********************************************************************************************************************************/
void Set_Network_Parm(void)
{
#ifdef ER_NETWORK
	g_Net.SERIAL = 1;
	g_Net.N = 1000;
	g_Net.P = 0.006;

#elif defined WS_NETWORK
	g_Net.SERIAL = 2;
	g_Net.N = 1000;
	g_Net.HALF_DEGREE = 6;
	g_Net.P = 1;

#elif defined BA_NETWORK
	g_Net.SERIAL = 3;
	g_Net.N = 100;
	g_Net.M0 = 4;
	g_Net.M = 3;

#elif defined COMPLETE_NETWORK
	g_Net.SERIAL = 4;
	g_Net.N = 100;

#elif defined UCM_NETWORK
	g_Net.SERIAL = 5;
	g_Net.N = 5000;
	g_Net.KMIN = 12;
	g_Net.KMAX = 71;
	g_Net.GAMMA = 3.0;  //range limit: gamma > 0

#elif defined REGULAR_RANDOM_NETWORK
	g_Net.SERIAL = 6;
	g_Net.N = 5000;
	g_Net.DEGREE = 20;

#elif defined REGULAR_NETWORK
	g_Net.SERIAL = 7;
	g_Net.N = 100;
	g_Net.DEGREE = 10;
#endif
	Output_Network_Parm();
}
/********************************************************************************************************************************
** Function name:       Set_Rd_Parm
** Descriptions:        设置随机数发生器所依赖的是哪个种子,以及均匀int分布和均匀real分布的分布范围参数
** input parameters:    None
** output parameters:   None
** Returned value:      None
********************************************************************************************************************************/
void Set_Rd_Parm(void)
{
	g_Rd.mt.seed(g_Rd.rd());
	g_Rd.distF.param(std::uniform_real_distribution<double>::param_type(0, 1));
	g_Rd.distD.param(std::uniform_int_distribution<int>::param_type(0, g_Net.N - 1));
	Output_Rd_Parm();
}
/***********************************************End Of File*********************************************************************/