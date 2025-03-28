/****************************************Copyright (c)*************************************************
**                      		Fujian Medical University
**                               http://www.fjmu.edu.cn/
**--------------File Info------------------------------------------------------------------------------
** File name:           cal_rho_abscissa_value1.cpp
** Created by:          linzhaohua
** Created date:        2024-4-20
** Version:             V1.0
** Descriptions:        SIS记忆阈值模型程序,这个是rho0画法的rhoParm,将rhoParm求平均
********************************************************************************************************/
#include "../headers/config.h"

static void Cal_AveStRho_Of_Diff_Networks(void);
static void Cal_AveStRho_Of_Diff_Diffusions(int netCnt, vector<vector<double> >& aveStRho_Parm);
static void Cal_AveSteadyRho_Of_Diff_Parm_Values(vector<vector<double> >& rhoParm);
/********************************************************************************************************************************
** Function name:       Draw_Rho_Vs_AbscissaParm_Diagram1
** Descriptions:        Draw_Rho_Vs_AbscissaParm_Diagram1
** input parameters:    None
** output parameters:   None
** Returned value:      None
********************************************************************************************************************************/
void Draw_Rho_Vs_AbscissaParm_Diagram1(void)
{
	Set_Network_Parm();
	Set_Spd_Parm();
	Set_Rd_Parm();
	Allocate_Types_Of_Nodes();		//here we allocate nodes' types
	Cal_AveStRho_Of_Diff_Networks();
}
/********************************************************************************************************************************
** Function name:       Cal_AveStRho_Of_Diff_Networks
** Descriptions:        Cal_AveStRho_Of_Diff_Networks
** input parameters:    None
** output parameters:   None
** Returned value:      None
********************************************************************************************************************************/
void Cal_AveStRho_Of_Diff_Networks(void)
{
	vector<vector<double> > rhoParm;
	vector<vector<double> > aveStRho_Parm(4);
	int index;
	char *name;
	//char name[NAME_SIZE];

	name = (char *)malloc(NAME_SIZE * sizeof(char));
	for (int i = 0; i < TOTAL_NETWORK_NUM; i++)
	{
		clock_t tick, tock;																	//record time;
		tick = clock();

		sprintf(name, NETWORK_FILE, i, g_Net.SERIAL);										//read netwotk data  
		Read_Network_File(name);

		Cal_AveStRho_Of_Diff_Diffusions(i, rhoParm);
		if (i == 0)
		{
			aveStRho_Parm[0].resize(rhoParm[0].size());
			aveStRho_Parm[1].resize(rhoParm[1].size());
			aveStRho_Parm[2].resize(rhoParm[2].size());
			aveStRho_Parm[3].resize(rhoParm[3].size());
		}
		index = 0;
		for (vector< double >::iterator it1 = rhoParm[1].begin(); it1 != rhoParm[1].end(); it1++)
		{
			aveStRho_Parm[0][index] += rhoParm[0][index] / TOTAL_NETWORK_NUM;
			aveStRho_Parm[1][index] += rhoParm[1][index] / TOTAL_NETWORK_NUM;
			aveStRho_Parm[2][index] += rhoParm[2][index] / TOTAL_NETWORK_NUM;
			aveStRho_Parm[3][index] += rhoParm[3][index] / TOTAL_NETWORK_NUM;
			index++;
		}
		Free_2DDouble_Vector(4, rhoParm);
		Free2D_NK(g_Net.N, g_netAdjList);

		tock = clock();																	//record time;
		cout << "One parameter simulation time was " << 1.0*(tock - tick) / CLOCKS_PER_SEC << endl;
	}
	free(name);
	Output_AveSteadyRho_Parm_To_File(aveStRho_Parm);
}
/********************************************************************************************************************************
** Function name:       Cal_AveStRho_Of_Diff_Diffusions
** Descriptions:        Cal_AveStRho_Of_Diff_Diffusions
** input parameters:    aveStRho_Parm
** output parameters:   None
** Returned value:      None
********************************************************************************************************************************/
void Cal_AveStRho_Of_Diff_Diffusions(int netCnt, vector<vector<double> >& aveStRho_Parm)
{
	vector<vector<double> > rhoParm;
	int index;

	for (int i = 0; i < TOTAL_DIFFUSION_NUM; i++)
	{
		Cal_AveSteadyRho_Of_Diff_Parm_Values(rhoParm);
		if (i == 0)
		{
			aveStRho_Parm.resize(4);
			aveStRho_Parm[0].resize(rhoParm[0].size());
			aveStRho_Parm[1].resize(rhoParm[1].size());
			aveStRho_Parm[2].resize(rhoParm[2].size());
			aveStRho_Parm[3].resize(rhoParm[3].size());
		}
		index = 0;
		for (vector< double >::iterator it1 = rhoParm[1].begin(); it1 != rhoParm[1].end(); it1++)
		{
			aveStRho_Parm[0][index] += rhoParm[0][index] / TOTAL_DIFFUSION_NUM;
			aveStRho_Parm[1][index] += rhoParm[1][index] / TOTAL_DIFFUSION_NUM;
			aveStRho_Parm[2][index] += rhoParm[2][index] / TOTAL_DIFFUSION_NUM;
			aveStRho_Parm[3][index] += rhoParm[3][index] / TOTAL_DIFFUSION_NUM;
			index++;
		}
		Output_NotAve_StRho_Parm_To_File(netCnt, i, rhoParm);
		Free_2DDouble_Vector(4, rhoParm);
	}
}
/********************************************************************************************************************************
** Function name:       Cal_AveSteadyRho_Of_Diff_Parm_Values
** Descriptions:        Cal_AveSteadyRho_Of_Diff_Parm_Values
** input parameters:    rhoParm
** output parameters:   None
** Returned value:      None
********************************************************************************************************************************/
void Cal_AveSteadyRho_Of_Diff_Parm_Values(vector<vector<double> >& rhoParm)
{
	vector<vector<double> > rhoT;
	double stRho;
	double stRhoA;
	double stRhoB;
	double temp = (PCT_OF_STEP_BEGIN_OF_CAL_STEADY_RHO)*g_Spd.TOTAL_UPDATE_STEPS;
	int stepBegin_Of_Cal_Steady_Rho = Double_Into_Int(temp);							

	rhoParm.resize(4);
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
		rhoT.resize(4);  //resize space
		for (int j = 0; j < 4; j++)
		{
			rhoT[j].resize(g_Spd.TOTAL_UPDATE_STEPS);
		}
		Cal_Rho_Of_Memory_Model(rhoT);
		for (int i = stepBegin_Of_Cal_Steady_Rho; i < g_Spd.TOTAL_UPDATE_STEPS; i++)
		{
			stRho += rhoT[1][i];
			stRhoA += rhoT[2][i];
			stRhoB += rhoT[3][i];
		}
		stRho /= 1.0*(g_Spd.TOTAL_UPDATE_STEPS - stepBegin_Of_Cal_Steady_Rho);
		stRhoA /= 1.0*(g_Spd.TOTAL_UPDATE_STEPS - stepBegin_Of_Cal_Steady_Rho);
		stRhoB /= 1.0*(g_Spd.TOTAL_UPDATE_STEPS - stepBegin_Of_Cal_Steady_Rho);
		rhoParm[0].push_back(p);													//output abscissa rate
		//rhoParm[0].push_back(p*g_Spd.UPDATE_STEP_LEN);							//output abscissa probability
		rhoParm[1].push_back(stRho);
		rhoParm[2].push_back(stRhoA);
		rhoParm[3].push_back(stRhoB);

		Free_2DDouble_Vector(4, rhoT);
	}
}
/*****************************************************End Of File***************************************/
