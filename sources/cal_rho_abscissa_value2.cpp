/****************************************Copyright (c)*************************************************
**                      		Fujian Medical University
**                               http://www.fjmu.edu.cn/
**--------------File Info------------------------------------------------------------------------------
** File name:           cal_rho_abscissa_value2.cpp
** Created by:          linzhaohua
** Created date:        2024-4-20
** Version:             V1.0
** Descriptions:        SIS记忆阈值模型程序，这个是rho0画法的rhoParm，将avrRhoT求平均，再得出rhoParm
********************************************************************************************************/
#include "../headers/config.h"

static void Cal_AveSteadyRho_Of_Diff_Parm_Values(void);
static vector<vector<double> > Cal_AveRho_Of_Diff_Networks(void);
static vector<vector<double> > Cal_AveRho_Of_Diff_Diffusions(void);
/********************************************************************************************************************************
** Function name:       Draw_Rho_Vs_AbscissaParm_Diagram2
** Descriptions:        Draw_Rho_Vs_AbscissaParm_Diagram2
** input parameters:    None
** output parameters:   None
** Returned value:      None
********************************************************************************************************************************/
void Draw_Rho_Vs_AbscissaParm_Diagram2(void)
{
	Set_Network_Parm();
	Set_Spd_Parm();
	Set_Rd_Parm();
	Allocate_Types_Of_Nodes();		//here we allocate nodes' types
	Cal_AveSteadyRho_Of_Diff_Parm_Values();
}
/********************************************************************************************************************************
** Function name:       Cal_AveSteadyRho_Of_Diff_Parm_Values
** Descriptions:        Cal_AveSteadyRho_Of_Diff_Parm_Values
** input parameters:    None
** output parameters:   None
** Returned value:      None
********************************************************************************************************************************/
void Cal_AveSteadyRho_Of_Diff_Parm_Values(void)
{
	vector<vector<double> > aveStRho_Parm(4);
	double stRho;
	double stRhoA;
	double stRhoB;
	double temp = (PCT_OF_STEP_BEGIN_OF_CAL_STEADY_RHO)*g_Spd.TOTAL_UPDATE_STEPS;
	int stepBegin_Of_Cal_Steady_Rho = Double_Into_Int(temp);							//可以这样写变量吗,因为太长了？？

	clock_t tick, tock;																	//record time;
	tick = clock();
#ifdef PARM_UP
	for (double p = PARM_VALUE_FROM; p <= (PARM_VALUE_TO + EPSILON); p += PARM_VALUE_DELTA)
#elif defined PARM_DOWN
	for (double p = PARM_VALUE_FROM; p >= (PARM_VALUE_TO - EPSILON); p -= PARM_VALUE_DELTA)
#else
#error "no defined PARM_UP or PARM_DOWN"
#endif // defined
	{
#ifdef PARM_INFECT_RATE
		printf("beta = %f\n", p);
		g_Spd.INFECT_RATE = p;
#elif defined PARM_RECOVER_RATE
		g_Spd.RECOVER_RATE = p;
#endif // defined

		stRho = 0.0;
		stRhoA = 0.0;
		stRhoB = 0.0;
		printf("parm = %f\n", p);
		vector<vector<double> > aveRho_T = Cal_AveRho_Of_Diff_Networks();
		for (int i = stepBegin_Of_Cal_Steady_Rho; i < g_Spd.TOTAL_UPDATE_STEPS; i++)
		{
			stRho += aveRho_T[1][i];
			stRhoA += aveRho_T[2][i];
			stRhoB += aveRho_T[3][i];
		}
		stRho /= 1.0*(g_Spd.TOTAL_UPDATE_STEPS - stepBegin_Of_Cal_Steady_Rho);
		stRhoA /= 1.0*(g_Spd.TOTAL_UPDATE_STEPS - stepBegin_Of_Cal_Steady_Rho);
		stRhoB /= 1.0*(g_Spd.TOTAL_UPDATE_STEPS - stepBegin_Of_Cal_Steady_Rho);
		aveStRho_Parm[0].push_back(p);													//output abscissa rate
		//aveStRho_Parm[0].push_back(p*g_Spd.UPDATE_STEP_LEN);							//output abscissa probability
		aveStRho_Parm[1].push_back(stRho);
		aveStRho_Parm[2].push_back(stRhoA);
		aveStRho_Parm[3].push_back(stRhoB);

		Free_2DDouble_Vector(4, aveRho_T);

		tock = clock();																	//record time;
		cout << "One parameter simulation time was " << 1.0*(tock - tick) / CLOCKS_PER_SEC << endl;
	}
	Output_AveSteadyRho_Parm_To_File(aveStRho_Parm);
	Free_2DDouble_Vector(4, aveStRho_Parm);
}
/********************************************************************************************************************************
** Function name:       Cal_AveRho_Of_Diff_Networks
** Descriptions:        Cal_AveRho_Of_Diff_Networks
** input parameters:    None
** output parameters:   aveRho_t
** Returned value:      aveRho_t
********************************************************************************************************************************/
vector<vector<double> > Cal_AveRho_Of_Diff_Networks(void)
{
	vector<vector<double> > aveRho_T(4, vector<double>(g_Spd.TOTAL_UPDATE_STEPS));
	char *name;
	//char name[NAME_SIZE];

	name = (char *)malloc(NAME_SIZE * sizeof(char));
	for (int i = 0; i < TOTAL_NETWORK_NUM; i++)
	{
		sprintf(name, NETWORK_FILE, i, g_Net.SERIAL);  //read netwotk data  
		Read_Network_File(name);  

		vector<vector<double> > rhoT = Cal_AveRho_Of_Diff_Diffusions();
		for (int j = 0; j < g_Spd.TOTAL_UPDATE_STEPS; j++)
		{
			aveRho_T[0][j] += rhoT[0][j];
			aveRho_T[1][j] += rhoT[1][j];
			aveRho_T[2][j] += rhoT[2][j];
			aveRho_T[3][j] += rhoT[3][j];
		}
		Free_2DDouble_Vector(4, rhoT);
		Free2D_NK(g_Net.N, g_netAdjList);
	}
	for (int i = 0; i < g_Spd.TOTAL_UPDATE_STEPS; i++)
	{
		aveRho_T[0][i] /= TOTAL_NETWORK_NUM;
		aveRho_T[1][i] /= TOTAL_NETWORK_NUM;
		aveRho_T[2][i] /= TOTAL_NETWORK_NUM;
		aveRho_T[3][i] /= TOTAL_NETWORK_NUM;
	}

	free(name);

	Output_aveRho_t_To_File(aveRho_T);
	return aveRho_T;
}
/********************************************************************************************************************************
** Function name:       Cal_AveRho_Of_Diff_Diffusions
** Descriptions:        Cal_AveRho_Of_Diff_Diffusions
** input parameters:    None
** output parameters:   aveRho_t
** Returned value:      aveRho_t
********************************************************************************************************************************/
vector<vector<double> > Cal_AveRho_Of_Diff_Diffusions(void)
{
	vector<vector<double> > rhoT;
	vector<vector<double> > aveRho_T(4, vector<double>(g_Spd.TOTAL_UPDATE_STEPS));

	for (int i = 0; i < TOTAL_DIFFUSION_NUM; i++)  //into cycle
	{
		rhoT.resize(4);  //resize space
		for (int j = 0; j < 4; j++)
		{
			rhoT[j].resize(g_Spd.TOTAL_UPDATE_STEPS);
		}

		Cal_Rho_Of_Memory_Model(rhoT);
		for (int j = 0; j < g_Spd.TOTAL_UPDATE_STEPS; j++)
		{
			aveRho_T[0][j] += rhoT[0][j];
			aveRho_T[1][j] += rhoT[1][j];
			aveRho_T[2][j] += rhoT[2][j];
			aveRho_T[3][j] += rhoT[3][j];
		}
		Free_2DDouble_Vector(4, rhoT);
	}
	for (int i = 0; i < g_Spd.TOTAL_UPDATE_STEPS; i++)
	{
		aveRho_T[0][i] /= TOTAL_DIFFUSION_NUM;
		aveRho_T[1][i] /= TOTAL_DIFFUSION_NUM;
		aveRho_T[2][i] /= TOTAL_DIFFUSION_NUM;
		aveRho_T[3][i] /= TOTAL_DIFFUSION_NUM;
	}
	return aveRho_T;
}
/*****************************************************End Of File***************************************/
