#pragma once
/****************************************Copyright (c)*************************************************
**                      		Fujian Medical University
**                               http://www.fjmu.edu.cn/
**--------------File Info--------------------------------------------------------------------------------------------------------
** File name:           set_parms.h
** Created by:          linzhaohua
** Created date:        2019-5-13
** Version:             V1.0
** Descriptions:        set_parms.h
********************************************************************************************************************************/
#ifndef __SET_PARMS_H
#define __SET_PARMS_H

#define NAME_SIZE							300
#define EPSILON								0.00001

#define PCT_OF_STEP_BEGIN_OF_CAL_STEADY_RHO 0.9		//t1  //PCT:percentage
#define NETWORK_FILE						"/home/zhlin/documents/runnning_codes/network/RRN_Network_N5000_degree20/No%d_NetSerial%d_nk.csv"
#define TOTAL_DIFFUSION_NUM					10		//times
#define TOTAL_NETWORK_NUM					5		//TIMES

#define PARM_INFECT_RATE
//#define PARM_RECOVER_RATE

#define PARM_UP
//#define PARM_DOWN

#define PARM_VALUE_FROM						0.0
#define PARM_VALUE_TO						1.0
#define PARM_VALUE_DELTA					0.03

typedef struct Spread
{

	double INFECT_RATE;			//beta
	double RECOVER_RATE;		//mu
	double UPDATE_STEP_LEN;		//deltaT
	double REAL_TIME_LEN;		//time_end
	double ALPHA_FACTOR;		//proportion alpha is type A nodes, 1-alpha is type B nodes.  //0: type A; 1: type B
	int TOTAL_UPDATE_STEPS;		//T
	int INTIAL_RHO_NUM;
	double INFECT_THRESHOLD_A;
	double INFECT_THRESHOLD_B;
	double MEMORY_LEN;

	vector<int> nodeType;
}SPD;
extern SPD g_Spd;
extern int g_taskNum;

void Set_Network_Parm(void);
void Set_Spd_Parm(void);
void Allocate_Types_Of_Nodes(void);
void Set_Rd_Parm(void);
int Double_Into_Int(const double old_value);

#endif //__SET_PARMS_H
/***********************************************End Of File*********************************************************************/