/****************************************Copyright (c)*************************************************
**                      		Fujian Medical University
**                               http://www.fjmu.edu.cn/
**--------------File Info------------------------------------------------------------------------------
** File name:           cal_rho_abscissa_value3.cpp
** Created by:          linzhaohua
** Created date:        2024-4-20
** Version:             V1.0
** Descriptions:        SIS记忆阈值模型程序,这个是rho0画法的rhoParm,将rhoParm求平均，
						求易感性指标,以及由易感性判断得到的传播阈值，
********************************************************************************************************/
#include "../headers/config.h"

static void Cal_AveStRho_Of_Diff_Networks(void);
static void Cal_Final_AveSusMeas(vector<vector<double> >& aveStRho_Parm, vector<vector<double> >& aveSus_Meas);
static void Cal_AveStRho_Of_Diff_Diffusions(int flag, vector<vector<double>> &aveStRho_Parm, vector<vector<double>> &aveSus_Meas);
static void Cal_AveStRho_Parm_And_AveSusMeas(int flag, int num, vector<vector<double> >& rhoParm, vector<vector<double> >& susMeas, vector<vector<double> >& aveStRho_Parm, vector<vector<double> >& aveSus_Meas);
static void Cal_AveSteadyRho_Of_Diff_Parm_Values(vector<vector<double> >& rhoParm, vector<vector<double> >& susMeas);
static void Cal_StRho_And_Susceptibility(vector<vector<double> >& rhoT, double& stRho1, double& stRho2, double& stRho3,
 double& susceptibility1, double& susceptibility2, double& susceptibility3);
/********************************************************************************************************************************
** Function name:       Draw_Rho_Vs_AbscissaParm_Diagram3
** Descriptions:        Draw_Rho_Vs_AbscissaParm_Diagram3
** input parameters:    None
** output parameters:   None
** Returned value:      None
********************************************************************************************************************************/
void Draw_Rho_Vs_AbscissaParm_Diagram3(void)
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
	vector<vector<double> > aveStRho_Parm;
	vector<vector<double> > susMeas;
	vector<vector<double> > aveSus_Meas;
	char *name;

	name = (char *)malloc(NAME_SIZE * sizeof(char));
	for (int i = 0; i < TOTAL_NETWORK_NUM; i++)
	{
		clock_t tick, tock;																	//record time;
		tick = clock();

		sprintf(name, NETWORK_FILE, i, g_Net.SERIAL);										//read netwotk data  
		Read_Network_File(name);

		Cal_AveStRho_Of_Diff_Diffusions(i, rhoParm, susMeas);
		Cal_AveStRho_Parm_And_AveSusMeas(i, TOTAL_NETWORK_NUM, rhoParm, susMeas, aveStRho_Parm, aveSus_Meas);

		Free2D_NK(g_Net.N, g_netAdjList);
		tock = clock();																		//record time;
		cout << "One parameter simulation time was " << 1.0*(tock - tick) / CLOCKS_PER_SEC << endl;
	}
	Output_Parm_StRho_To_File(aveStRho_Parm);
	Output_Parm_StRhoSquare_To_File(aveSus_Meas);											//here aveSus_Meas's value is stRho^2, not yet susceptibility
	Cal_Final_AveSusMeas(aveStRho_Parm, aveSus_Meas);										//calculate value of susceptibility 
	free(name);

	Output_AveSteadyRho_Parm_To_File(aveStRho_Parm);
	Output_AveSusMeas_To_File(aveSus_Meas);

	Cal_And_Output_Propagation_Threshold_Value(aveSus_Meas);
	Cal_And_Output_Propagation_Threshold_Value_atype(aveSus_Meas);
	Cal_And_Output_Propagation_Threshold_Value_btype(aveSus_Meas);
}
/********************************************************************************************************************************
** Function name:       Cal_Final_AveSusMeas
** Descriptions:        Cal_Final_AveSusMeas
** input parameters:    aveStRho_Parm,aveSus_Meas
** output parameters:   None
** Returned value:      None
********************************************************************************************************************************/
void Cal_Final_AveSusMeas(vector<vector<double> >& aveStRho_Parm, vector<vector<double> >& aveSus_Meas)
{
    size_t length = aveSus_Meas[1].size();

    for (size_t index = 0; index < length; ++index)
    {
        if (aveStRho_Parm[1][index] == 0.0)
        {
            aveSus_Meas[1][index] = 0.0;
        }
        else
        {
            aveSus_Meas[1][index] = g_Net.N * (aveSus_Meas[1][index] - aveStRho_Parm[1][index] * aveStRho_Parm[1][index]) / aveStRho_Parm[1][index];
        }

        if (aveStRho_Parm[2][index] == 0.0)
        {
            aveSus_Meas[2][index] = 0.0;
        }
        else
        {
            aveSus_Meas[2][index] = g_Net.N * (aveSus_Meas[2][index] - aveStRho_Parm[2][index] * aveStRho_Parm[2][index]) / aveStRho_Parm[2][index];
        }

        if (aveStRho_Parm[3][index] == 0.0)
        {
            aveSus_Meas[3][index] = 0.0;
        }
        else
        {
            aveSus_Meas[3][index] = g_Net.N * (aveSus_Meas[3][index] - aveStRho_Parm[3][index] * aveStRho_Parm[3][index]) / aveStRho_Parm[3][index];
        }
    }
}



/********************************************************************************************************************************
** Function name:       Cal_AveStRho_Of_Diff_Diffusions
** Descriptions:        Cal_AveStRho_Of_Diff_Diffusions
** input parameters:    flag,aveStRho_Parm,aveSus_Meas
** output parameters:   None
** Returned value:      None
********************************************************************************************************************************/
void Cal_AveStRho_Of_Diff_Diffusions(int flag, vector<vector<double>> &aveStRho_Parm, vector<vector<double>> &aveSus_Meas)
{
    vector<vector<double>> rhoParm;
    vector<vector<double>> susMeas;

	char filename[50];  
	sprintf(filename, "task%d_notave_rhoParm_results.csv", g_taskNum);
	ofstream outFile(filename, flag == 0 ? ios::out | ios::trunc : ios::out | ios::app);  // "ios::trunc": Clear the file; "ios::app": Append content
    if (!outFile.is_open()) {
        cerr << "The file 'notave_rhoParm_results.csv' cannot be opened for writing." << endl;
        return;
    }
	if (flag == 0) {
    outFile << "x,y1,y2,y3,y4\n";  
	}	

    //Set the output format to ensure that the output precision is 6 digits after the decimal point
    outFile << fixed << setprecision(6);

    // Main loop: calculate rhoParm and susMeas and update aveStRho_Parm and aveSus_Meas
    for (int i = 0; i < TOTAL_DIFFUSION_NUM; i++)
    {
        // Calculate rhoParm and susMeas
        Cal_AveSteadyRho_Of_Diff_Parm_Values(rhoParm, susMeas);

        //Write rhoParm data to file
        for (int j = 0; j < int(rhoParm[0].size()); j++) { 
            for (int k = 0; k < 4; k++) { // 4 column
                outFile << rhoParm[k][j];
                if (k < 3) {
                    outFile << ","; //separate columns with commas
                }
            }
            outFile << "\n"; 
        }

        // Update aveStRho_Parm and aveSus_Meas
        Cal_AveStRho_Parm_And_AveSusMeas(i, TOTAL_DIFFUSION_NUM, rhoParm, susMeas, aveStRho_Parm, aveSus_Meas);
    }

    // Close file
    outFile.close();
}
/********************************************************************************************************************************
** Function name:       Cal_AveStRho_Parm_And_AveSusMeas
** Descriptions:        Cal_AveStRho_Parm_And_AveSusMeas
** input parameters:    flag,num,rhoParm,susMeas,aveStRho_Parm,aveSus_Meas
** output parameters:   None
** Returned value:      None
********************************************************************************************************************************/
void Cal_AveStRho_Parm_And_AveSusMeas(int flag, int num, vector<vector<double> >& rhoParm, vector<vector<double> >& susMeas, vector<vector<double> >& aveStRho_Parm, vector<vector<double> >& aveSus_Meas)
{
	int index = 0;

	if (flag == 0)
	{
		aveStRho_Parm.resize(4, vector<double>(rhoParm[0].size(), 0.0));
		aveSus_Meas.resize(4, vector<double>(susMeas[0].size(), 0.0));
	}
	for (auto it1 = rhoParm[1].begin(); it1 != rhoParm[1].end(); it1++)
	{
		aveStRho_Parm[0][index] += rhoParm[0][index] / num;
		aveStRho_Parm[1][index] += rhoParm[1][index] / num;
		aveStRho_Parm[2][index] += rhoParm[2][index] / num;
		aveStRho_Parm[3][index] += rhoParm[3][index] / num;

		aveSus_Meas[0][index] += susMeas[0][index] / num;
		aveSus_Meas[1][index] += susMeas[1][index] / num;
		aveSus_Meas[2][index] += susMeas[2][index] / num;
		aveSus_Meas[3][index] += susMeas[3][index] / num;
		index++;
	}
	Free_2DDouble_Vector(4, rhoParm);
	Free_2DDouble_Vector(4, susMeas);
}
/********************************************************************************************************************************
** Function name:       Cal_AveSteadyRho_Of_Diff_Parm_Values
** Descriptions:        Cal_AveSteadyRho_Of_Diff_Parm_Values
** input parameters:    rhoParm,susMeas
** output parameters:   None
** Returned value:      None
********************************************************************************************************************************/
void Cal_AveSteadyRho_Of_Diff_Parm_Values(vector<vector<double> >& rhoParm, vector<vector<double> >& susMeas)
{
	double stRho1;
	double stRho2;
	double stRho3;
	double susceptibility1;
	double susceptibility2;
	double susceptibility3;
	vector<vector<double> > rhoT;

	rhoParm.resize(4);
	susMeas.resize(4);
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

		printf("parm = %f\n", p);
		rhoT.resize(4, vector<double>(g_Spd.TOTAL_UPDATE_STEPS));					//resize space,要注意如果之前rhoT(2)的话，再用rhoT.resize(2, vector<double>(g_Spd.TOTAL_UPDATE_STEPS,1.5))并不会使rhoT每个元素维1.5，因为它检查了发现为size=2相同，所以就不会再resize了，所以一定要先完全释放空间！！
		Cal_Rho_Of_Memory_Model(rhoT);
		Cal_StRho_And_Susceptibility(rhoT, stRho1, stRho2, stRho3,
		 susceptibility1, susceptibility2, susceptibility3);

		rhoParm[0].push_back(p);													//output abscissa rate
		//rhoParm[0].push_back(p*g_Spd.UPDATE_STEP_LEN);							//output abscissa probability
		rhoParm[1].push_back(stRho1);
		rhoParm[2].push_back(stRho2);
		rhoParm[3].push_back(stRho3);

		susMeas[0].push_back(p);
		susMeas[1].push_back(susceptibility1);
		susMeas[2].push_back(susceptibility2);
		susMeas[3].push_back(susceptibility3);

		Free_2DDouble_Vector(4, rhoT);
	}
}
/********************************************************************************************************************************
** Function name:       Cal_StRho_And_Susceptibility
** Descriptions:        计算稳态rho值和易感性指标的值
** input parameters:    rhoT,stRho,susceptibility
** output parameters:   None
** Returned value:      None
********************************************************************************************************************************/
void Cal_StRho_And_Susceptibility(vector<vector<double> >& rhoT, double& stRho1, double& stRho2, double& stRho3,
 double& susceptibility1, double& susceptibility2, double& susceptibility3)
{
	double temp = (PCT_OF_STEP_BEGIN_OF_CAL_STEADY_RHO)*g_Spd.TOTAL_UPDATE_STEPS;
	int stepBegin_Of_Cal_Steady_Rho = Double_Into_Int(temp);

	stRho1 = 0.0;
	stRho2 = 0.0;
	stRho3 = 0.0;
	for (int i = stepBegin_Of_Cal_Steady_Rho; i < g_Spd.TOTAL_UPDATE_STEPS; i++)
	{
		stRho1 += rhoT[1][i];
		stRho2 += rhoT[2][i];
		stRho3 += rhoT[3][i];
	}
	stRho1 /= 1.0*(g_Spd.TOTAL_UPDATE_STEPS - stepBegin_Of_Cal_Steady_Rho);
	stRho2 /= 1.0*(g_Spd.TOTAL_UPDATE_STEPS - stepBegin_Of_Cal_Steady_Rho);
	stRho3 /= 1.0*(g_Spd.TOTAL_UPDATE_STEPS - stepBegin_Of_Cal_Steady_Rho);
	susceptibility1 = stRho1 * stRho1;
	susceptibility2 = stRho2 * stRho2;
	susceptibility3 = stRho3 * stRho3;
}
/*****************************************************End Of File***************************************/