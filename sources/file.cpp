/****************************************Copyright (c)*************************************************
**                      		Fujian Medical University
**                               http://www.fjmu.edu.cn/
**--------------File Info------------------------------------------------------------------------------
** File name:           file.cpp
** Created by:          linzhaohua
** Created date:        2024-4-20
** Version:             V1.0
** Descriptions:        file.cpp
********************************************************************************************************/
#include "../headers/config.h"

#define NETWORK_INPUT_FILE_INFO_LEN			300
/********************************************************************************************************************************
** Function name:       Output_Network_Parm
** Descriptions:        Output_Network_Parm
** input parameters:    None
** output parameters:   None
** Returned value:      None
********************************************************************************************************************************/
void Output_Network_Parm(void)
{
    cout << "Network Parameter Information: " << endl;
#ifdef ER_NETWORK
    cout << "ER_NETWORK" << endl;
	cout << "g_Net.SERIAL: " << g_Net.SERIAL << endl;
	cout << "g_Net.N: " << g_Net.N << endl;
	cout << "g_Net.P: " << g_Net.P << endl;

#elif defined WS_NETWORK
    cout << "WS_NETWORK" << endl;
    cout << "g_Net.SERIAL: " << g_Net.SERIAL << endl;
    cout << "g_Net.N: " << g_Net.N  << endl;
    cout << "g_Net.HALF_DEGREE: " << g_Net.HALF_DEGREE << endl;
    cout << "g_Net.P: " << g_Net.P << endl;

#elif defined BA_NETWORK
    cout << "BA_NETWORK" << endl;
    cout << "g_Net.SERIAL: " << g_Net.SERIAL << endl;
    cout << "g_Net.N: " << g_Net.N << endl;
    cout << "g_Net.M0: " << g_Net.M0 << endl;
    cout << "g_Net.M: " << g_Net.M << endl;

#elif defined COMPLETE_NETWORK
    cout << "COMPLETE_NETWORK" << endl;
    cout << "g_Net.SERIAL: " << g_Net.SERIAL << endl;
    cout << "g_Net.N: " << g_Net.N << endl;

#elif defined UCM_NETWORK
    cout << "UCM_NETWORK" << endl;
    cout << "g_Net.SERIAL: " << g_Net.SERIAL << endl;
    cout << "g_Net.N: " << g_Net.N << endl;
    cout << "g_Net.KMIN: " << g_Net.KMIN << endl;
    cout << "g_Net.KMAX: " << g_Net.KMAX << endl;
    cout << "g_Net.GAMMA: " << g_Net.GAMMA << endl;

#elif defined REGULAR_RANDOM_NETWORK
    cout << "REGULAR_RANDOM_NETWORK" << endl;
    cout << "g_Net.SERIAL: " << g_Net.SERIAL << endl;
    cout << "g_Net.N: " << g_Net.N << endl;
    cout << "g_Net.DEGREE: " << g_Net.DEGREE << endl;

#elif defined REGULAR_NETWORK
    cout << "REGULAR_NETWORK" << endl;
    cout << "g_Net.SERIAL: " << g_Net.SERIAL << endl;
    cout << "g_Net.N: " << g_Net.N << endl;
    cout << "g_Net.DEGREE: " << g_Net.DEGREE << endl;
#endif
    cout << endl;
	//Output_Network_Parm_Into_File();
}
/********************************************************************************************************************************
** Function name:       Output_Spd_Parm
** Descriptions:        Output_Spd_Parm
** input parameters:    None
** output parameters:   None
** Returned value:      None
********************************************************************************************************************************/
void Output_Spd_Parm(void)
{
    cout << "Spread Parmeter Information: " << endl;
#ifdef PARM_INFECT_RATE
	cout << "g_Spd.RECOVER_RATE: " << g_Spd.RECOVER_RATE << endl;
#elif defined PARM_RECOVER_RATE
	cout << "g_Spd.INFECT_RATE: " << g_Spd.INFECT_RATE << endl;
#endif
    cout << "g_Spd.UPDATE_STEP_LEN: " << g_Spd.UPDATE_STEP_LEN << endl;
    cout << "g_Spd.REAL_TIME_LEN: " << g_Spd.REAL_TIME_LEN << endl;
    cout << "g_Spd.TOTAL_UPDATE_STEPS: " << g_Spd.TOTAL_UPDATE_STEPS << endl;
    cout << "g_Spd.INTIAL_RHO_NUM: " << g_Spd.INTIAL_RHO_NUM << endl;
    cout << "g_Spd.INFECT_THRESHOLD_A: " << g_Spd.INFECT_THRESHOLD_A << endl;
    cout << "g_Spd.INFECT_THRESHOLD_B: " << g_Spd.INFECT_THRESHOLD_B << endl;
    cout << "g_Spd.MEMORY_LEN: " << g_Spd.MEMORY_LEN << endl;
	cout << "g_Spd.ALPHA_FACTOR: " << g_Spd.ALPHA_FACTOR << endl;
    cout << endl;
	//Output_Spd_Parm_Into_File();
}
/********************************************************************************************************************************
** Function name:       Output_Rd_Parm
** Descriptions:        输出均匀随机数分布的范围参数
** input parameters:    None
** output parameters:   None
** Returned value:      None
********************************************************************************************************************************/
void Output_Rd_Parm(void)
{
	cout << "g_Rd.distF.min = " << g_Rd.distF.min() << endl;
	cout << "g_Rd.distF.max = " << g_Rd.distF.max() << endl;
	cout << "g_Rd.distD.min = " << g_Rd.distD.min() << endl;
	cout << "g_Rd.distD.max = " << g_Rd.distD.max() << endl;
}
/********************************************************************************************************************************
** Function name:       Output_Diffusion_Parm
** Descriptions:        输出传播过程的各个感染、恢复概率
** input parameters:    None
** output parameters:   None
** Returned value:      None
********************************************************************************************************************************/
void Output_Diffusion_Parm(DIFFUSION *p_Dif)
{
	cout << "Output_Diffusion_Parm: " << endl;
	cout << "p_Dif->INFECT_PROB = " << p_Dif->INFECT_PROB << endl;
	cout << "p_Dif->RECOVER_PROB = " << p_Dif->RECOVER_PROB << endl;
}
/********************************************************************************************************************************
** Function name:       Output_Network_Parm_Into_File
** Descriptions:        Output_Network_Parm_Into_File
** input parameters:    None
** output parameters:   None
** Returned value:      None
********************************************************************************************************************************/
void Output_Network_Parm_Into_File(void)
{
	FILE *fp;
	//char name[NAME_SIZE];
	char *name;

	name = (char *)malloc(NAME_SIZE * sizeof(char));
	sprintf(name, "task%d_Network_Parm.json", g_taskNum);  
	fp = fopen(name, "w");
	fprintf(fp, "{\n");
#ifdef ER_NETWORK
	fprintf(fp, "\t\"ER_NETWORK\": ,\n");
	fprintf(fp, "\t\"g_Net.SERIAL\": %d,\n", g_Net.SERIAL);
	fprintf(fp, "\t\"g_Net.N\": %d,\n", g_Net.N);
	fprintf(fp, "\t\"g_Net.P\": %f\n", g_Net.P);
#elif defined WS_NETWORK
	fprintf(fp, "\t\"WS_NETWORK\": ,\n");
	fprintf(fp, "\t\"g_Net.SERIAL\": %d,\n", g_Net.SERIAL);
	fprintf(fp, "\t\"g_Net.N\": %d,\n", g_Net.N);
	fprintf(fp, "\t\"g_Net.HALF_DEGREE\": %d,\n", g_Net.HALF_DEGREE);
	fprintf(fp, "\t\"g_Net.P\": %f\n", g_Net.P);
#elif defined BA_NETWORK
	fprintf(fp, "\t\"BA_NETWORK\": ,\n");
	fprintf(fp, "\t\"g_Net.SERIAL\": %d,\n", g_Net.SERIAL);
	fprintf(fp, "\t\"g_Net.N\": %d,\n", g_Net.N);
	fprintf(fp, "\t\"g_Net.M0\": %d\n", g_Net.M0);
	fprintf(fp, "\t\"g_Net.M\": %d\n", g_Net.M);
#elif defined COMPLETE_NETWORK
	fprintf(fp, "\t\"COMPLETE_NETWORK\": ,\n");
	fprintf(fp, "\t\"g_Net.SERIAL\": %d,\n", g_Net.SERIAL);
	fprintf(fp, "\t\"g_Net.N\": %d,\n", g_Net.N);
#elif defined UCM_NETWORK
	fprintf(fp, "\t\"UCM_NETWORK\": ,\n");
	fprintf(fp, "\t\"g_Net.SERIAL\": %d,\n", g_Net.SERIAL);
	fprintf(fp, "\t\"g_Net.N\": %d,\n", g_Net.N);
	fprintf(fp, "\t\"g_Net.KMIN\": %d\n", g_Net.KMIN);
	fprintf(fp, "\t\"g_Net.KMAX\": %d\n", g_Net.KMAX);
	fprintf(fp, "\t\"g_Net.GAMMA\": %f\n", g_Net.GAMMA);
#elif defined REGULAR_RANDOM_NETWORK
	fprintf(fp, "\t\"REGULAR_RANDOM_NETWORK\": ,\n");
	fprintf(fp, "\t\"g_Net.SERIAL\": %d,\n", g_Net.SERIAL);
	fprintf(fp, "\t\"g_Net.N\": %d,\n", g_Net.N);
	fprintf(fp, "\t\"g_Net.DEGREE\": %d\n", g_Net.DEGREE);
#elif defined REGULAR_NETWORK
	fprintf(fp, "\t\"REGULAR_NETWORK\": ,\n");
	fprintf(fp, "\t\"g_Net.SERIAL\": %d,\n", g_Net.SERIAL);
	fprintf(fp, "\t\"g_Net.N\": %d,\n", g_Net.N);
	fprintf(fp, "\t\"g_Net.DEGREE\": %d\n", g_Net.DEGREE);
#endif
	fprintf(fp, "}");
	fclose(fp);
	free(name);
}
/********************************************************************************************************************************
** Function name:       Output_Spd_Parm_Into_File
** Descriptions:        Output_Spd_Parm_Into_File
** input parameters:    None
** output parameters:   None
** Returned value:      None
********************************************************************************************************************************/
void Output_Spd_Parm_Into_File(void)
{
	FILE *fp;
	//char name[NAME_SIZE];
	char *name;

	name = (char *)malloc(NAME_SIZE * sizeof(char));
	sprintf(name, "task%d_Spd_Parm.json", g_taskNum); 
	fp = fopen(name, "w");
	fprintf(fp, "{\n");

#ifdef PARM_INFECT_RATE
	fprintf(fp, "\t\"g_Spd.RECOVER_RATE\": %f,\n", g_Spd.RECOVER_RATE);
#elif defined PARM_RECOVER_RATE
	fprintf(fp, "\t\"g_Spd.INFECT_RATE\": %f,\n", g_Spd.INFECT_RATE);
#endif
	fprintf(fp, "\t\"g_Spd.UPDATE_STEP_LEN\": %f,\n", g_Spd.UPDATE_STEP_LEN);
	fprintf(fp, "\t\"g_Spd.REAL_TIME_LEN\": %f,\n", g_Spd.REAL_TIME_LEN);
	fprintf(fp, "\t\"g_Spd.TOTAL_UPDATE_STEPS\": %d,\n", g_Spd.TOTAL_UPDATE_STEPS);
	fprintf(fp, "\t\"g_Spd.INTIAL_RHO_NUM\": %d,\n", g_Spd.INTIAL_RHO_NUM);
	fprintf(fp, "\t\"g_Spd.INFECT_THRESHOLD_A\": %f,\n", g_Spd.INFECT_THRESHOLD_A);
	fprintf(fp, "\t\"g_Spd.INFECT_THRESHOLD_B\": %f,\n", g_Spd.INFECT_THRESHOLD_B);
	fprintf(fp, "\t\"g_Spd.MEMORY_LEN\": %f,\n", g_Spd.MEMORY_LEN);
	fprintf(fp, "\t\"g_Spd.ALPHA_FACTOR\": %f\n", g_Spd.ALPHA_FACTOR);

	fprintf(fp, "}");
	fclose(fp);
	free(name);
}
/********************************************************************************************************************************
** Function name:       Output_AveSteadyRho_Parm_To_File
** Descriptions:        Output_AveSteadyRho_Parm_To_File
** input parameters:    aveStRho_Parm
** output parameters:   None
** Returned value:      None
********************************************************************************************************************************/
void Output_AveSteadyRho_Parm_To_File(vector<vector<double> >& aveStRho_Parm)
{
	FILE *fp;
	int index = 0;
	//char name[NAME_SIZE];
	char *name;

	name = (char *)malloc(NAME_SIZE * sizeof(char));
	sprintf(name, "task%d_AveSteadyRho_Parm.csv", g_taskNum); 
	fp = fopen(name, "w");
	fprintf(fp, "x,y1,y2,y3,y4\n");
	for (vector<double>::iterator it = aveStRho_Parm[1].begin(); it != aveStRho_Parm[1].end(); it++)
	{
		fprintf(fp, "%f,%f,%f,%f\n", aveStRho_Parm[0][index], *it, aveStRho_Parm[2][index], aveStRho_Parm[3][index]);
		index++;
	}
	fclose(fp);
	free(name);
}
/********************************************************************************************************************************
** Function name:       Output_AveSusMeas_To_File
** Descriptions:        Output_AveSusMeas_To_File
** input parameters:    aveSus_Meas
** output parameters:   None
** Returned value:      None
********************************************************************************************************************************/
void Output_AveSusMeas_To_File(vector<vector<double> >& aveSus_Meas)
{
	FILE *fp;
	int index = 0;
	//char name[NAME_SIZE];
	char *name;

	name = (char *)malloc(NAME_SIZE * sizeof(char));
	sprintf(name, "task%d_AveSusMeas_Parm.csv", g_taskNum);
	fp = fopen(name, "w");
	fprintf(fp, "x,y1,y2,y3,y4\n");
	for (vector<double>::iterator it = aveSus_Meas[1].begin(); it != aveSus_Meas[1].end(); it++)
	{
		fprintf(fp, "%f,%f,%f,%f\n", aveSus_Meas[0][index], *it, aveSus_Meas[2][index], aveSus_Meas[3][index]);
		index++;
	}
	fclose(fp);
	free(name);
}
/********************************************************************************************************************************
** Function name:       Output_NotAve_StRho_Parm_To_File
** Descriptions:        Output_NotAve_StRho_Parm_To_File
** input parameters:    netCnt,flag,rhoParm
** output parameters:   None
** Returned value:      None
********************************************************************************************************************************/
void Output_NotAve_StRho_Parm_To_File(int netCnt, int flag, vector<vector<double> >& rhoParm)
{
	FILE *fp;
	int index = 0;
	//char name[NAME_SIZE];
	char *name;

	name = (char *)malloc(NAME_SIZE * sizeof(char));
	sprintf(name, "task%d_NotAveStRho_Parm.csv", g_taskNum);
	if (netCnt == 0 && flag == 0)           //clear file content
	{
		fp = fopen(name, "w+");
		fprintf(fp, "x,y1,y2,y3,y4\n");
	}
	else
	{
		fp = fopen(name, "a+");
	}
	for (auto it = rhoParm[1].begin(); it != rhoParm[1].end(); it++)
	{
		fprintf(fp, "%f,%f,%f,%f\n", rhoParm[0][index], *it, rhoParm[2][index], rhoParm[3][index]);
		index++;
	}
	fclose(fp);
	free(name);
}
/********************************************************************************************************************************
** Function name:       Output_Parm_StRho_To_File
** Descriptions:        Output_Parm_StRho_To_File
** input parameters:    aveStRho_Parm
** output parameters:   None
** Returned value:      None
********************************************************************************************************************************/
void Output_Parm_StRho_To_File(vector<vector<double> >& aveStRho_Parm)
{
	FILE *fp;
	int index = 0;
	//char name[NAME_SIZE];
	char *name;

	name = (char *)malloc(NAME_SIZE * sizeof(char));
	sprintf(name, "task%d_Parm_StRho.csv", g_taskNum);
	fp = fopen(name, "w");
	fprintf(fp, "x,y1,y2,y3,y4\n");
	for (vector<double>::iterator it = aveStRho_Parm[1].begin(); it != aveStRho_Parm[1].end(); it++)
	{
		fprintf(fp, "%f,%f,%f,%f\n", aveStRho_Parm[0][index], aveStRho_Parm[1][index], aveStRho_Parm[2][index], aveStRho_Parm[3][index]);
		index++;
	}
	fclose(fp);
	free(name);
}
/********************************************************************************************************************************
** Function name:       Output_Parm_StRhoSquare_To_File
** Descriptions:        Output_Parm_StRhoSquare_To_File
** input parameters:    aveSus_Meas
** output parameters:   None
** Returned value:      None
********************************************************************************************************************************/
void Output_Parm_StRhoSquare_To_File(vector<vector<double> >& aveSus_Meas)
{
	FILE *fp;
	int index = 0;
	//char name[NAME_SIZE];
	char *name;

	name = (char *)malloc(NAME_SIZE * sizeof(char));
	sprintf(name, "task%d_Parm_StRhoSquare.csv", g_taskNum);
	fp = fopen(name, "w");
	fprintf(fp, "x,y1,y2,y3,y4\n");
	for (vector<double>::iterator it = aveSus_Meas[1].begin(); it != aveSus_Meas[1].end(); it++)
	{
		fprintf(fp, "%f,%f,%f,%f\n", aveSus_Meas[0][index], aveSus_Meas[1][index], aveSus_Meas[2][index], aveSus_Meas[3][index]);
		index++;
	}
	fclose(fp);
	free(name);
}
/********************************************************************************************************************************
** Function name:       Cal_And_Output_Propagation_Threshold_Value
** Descriptions:        Cal_And_Output_Propagation_Threshold_Value
** input parameters:    aveSus_Meas
** output parameters:   None
** Returned value:      None
********************************************************************************************************************************/
void Cal_And_Output_Propagation_Threshold_Value(vector<vector<double> >& aveSus_Meas)
{
	FILE *fp;
	char *name;
	auto itMax = std::max_element(aveSus_Meas[1].begin(), aveSus_Meas[1].end());
	int index;

	index = std::distance(aveSus_Meas[1].begin(), itMax);

	name = (char *)malloc(NAME_SIZE * sizeof(char));
	sprintf(name, "task%d_PropThreshold_vs_NetSize.csv", g_taskNum);
	fp = fopen(name, "w");
	fprintf(fp, "x,y1,y2\n");
	fprintf(fp, "%d,%f\n", g_Net.N, aveSus_Meas[0][index]);
	fclose(fp);
	free(name);

	sprintf(name, "task%d_PropThreshold_vs_gamma.csv", g_taskNum);
	fp = fopen(name, "w");
	fprintf(fp, "x,y1,y2\n");
	fprintf(fp, "%f,%f\n", g_Spd.ALPHA_FACTOR, aveSus_Meas[0][index]);
	fclose(fp);
	free(name);
}
/********************************************************************************************************************************
** Function name:       Cal_And_Output_Propagation_Threshold_Value_atype
** Descriptions:        Cal_And_Output_Propagation_Threshold_Value_atype
** input parameters:    aveSus_Meas
** output parameters:   None
** Returned value:      None
********************************************************************************************************************************/
void Cal_And_Output_Propagation_Threshold_Value_atype(vector<vector<double> >& aveSus_Meas)
{
	FILE *fp;
	char *name;
	auto itMax = std::max_element(aveSus_Meas[2].begin(), aveSus_Meas[2].end()); //aveSus_Meas[2]: atype
	int index;

	index = std::distance(aveSus_Meas[2].begin(), itMax);	//aveSus_Meas[2]: atype

	name = (char *)malloc(NAME_SIZE * sizeof(char));
	sprintf(name, "task%d_PropThreshold_vs_NetSize_atype.csv", g_taskNum);
	fp = fopen(name, "w");
	fprintf(fp, "x,y1,y2\n");
	fprintf(fp, "%d,%f\n", g_Net.N, aveSus_Meas[0][index]);
	fclose(fp);
	free(name);

	sprintf(name, "task%d_PropThreshold_vs_gamma_atype.csv", g_taskNum);
	fp = fopen(name, "w");
	fprintf(fp, "x,y1,y2\n");
	fprintf(fp, "%f,%f\n", g_Spd.ALPHA_FACTOR, aveSus_Meas[0][index]);
	fclose(fp);
	free(name);
}
/********************************************************************************************************************************
** Function name:       Cal_And_Output_Propagation_Threshold_Value_btype
** Descriptions:        Cal_And_Output_Propagation_Threshold_Value_btype
** input parameters:    aveSus_Meas
** output parameters:   None
** Returned value:      None
********************************************************************************************************************************/
void Cal_And_Output_Propagation_Threshold_Value_btype(vector<vector<double> >& aveSus_Meas)
{
	FILE *fp;
	char *name;
	auto itMax = std::max_element(aveSus_Meas[3].begin(), aveSus_Meas[3].end()); //aveSus_Meas[3]: btype
	int index;

	index = std::distance(aveSus_Meas[3].begin(), itMax);	//aveSus_Meas[3]: btype

	name = (char *)malloc(NAME_SIZE * sizeof(char));
	sprintf(name, "task%d_PropThreshold_vs_NetSize_btype.csv", g_taskNum);
	fp = fopen(name, "w");
	fprintf(fp, "x,y1,y2\n");
	fprintf(fp, "%d,%f\n", g_Net.N, aveSus_Meas[0][index]);
	fclose(fp);
	free(name);

	sprintf(name, "task%d_PropThreshold_vs_gamma_btype.csv", g_taskNum);
	fp = fopen(name, "w");
	fprintf(fp, "x,y1,y2\n");
	fprintf(fp, "%f,%f\n", g_Spd.ALPHA_FACTOR, aveSus_Meas[0][index]);
	fclose(fp);
	free(name);
}
/********************************************************************************************************************************
** Function name:       Output_aveRho_t_To_File
** Descriptions:        Output_aveRho_t_To_File
** input parameters:    aveRho_t
** output parameters:   None
** Returned value:      None
********************************************************************************************************************************/
void Output_aveRho_t_To_File(vector<vector<double> >& aveRho_t)
{
	FILE *fp;
	//char name[NAME_SIZE];
	char *name;

	name = (char *)malloc(NAME_SIZE * sizeof(char));
#ifdef PARM_INFECT_RATE
	sprintf(name, "task%d_aveRho_t_parm=%0.5f.csv", g_taskNum, g_Spd.INFECT_RATE);
#elif defined PARM_RECOVER_RATE
	sprintf(name, "task%d_aveRho_t_parm=%0.5f.csv", g_taskNum, g_Spd.RECOVER_RATE);
#endif // defined
	fp = fopen(name, "w");
	fprintf(fp, "x,y1,y2,y3,y4\n");
	for (int i = 0; i < g_Spd.TOTAL_UPDATE_STEPS; i++)
	{
	    //printf("%f,%f\n", aveRho_t[0][i], aveRho_t[1][i]);  //debug
		fprintf(fp, "%f,%f,%f,%f\n", aveRho_t[0][i], aveRho_t[1][i], aveRho_t[2][i], aveRho_t[3][i]);
	}
	fclose(fp);
	free(name);
}
/********************************************************************************************************************************
** Function name:       Read_Network_File
** Descriptions:        Read_Network_File
** input parameters:    file_name
** output parameters:   None
** Returned value:      None
********************************************************************************************************************************/
void Read_Network_File(char *file_name)
{
	int temp;
	int degree;
	char words[NETWORK_INPUT_FILE_INFO_LEN];
	FILE *fp;

	Init_NK();
	fp = fopen(file_name, "r");
	fgets(words, NETWORK_INPUT_FILE_INFO_LEN, fp);			//read network information
	printf("Network Input File Information: %s\n", words);
	for (int i = 0; i < g_Net.N; i++)						//read node_edge
	{
		fscanf(fp, "%d,", &temp);
		degree = temp;
		for (int j = 1; j <= degree; j++)
		{
			fscanf(fp, "%d,", &temp);
			Push_Back_NK(temp, i);
		}
		//fscanf(fp,"\n");									//have or not have is ok
	}
	fclose(fp);

	//Output_NK(g_Net.N, g_netAdjList);
}


/********************************************************************************************************************************
** Function name:       Output_StepNet_NK
** Descriptions:        Output_StepNet_NK
** input parameters:    num,net,step,name
** output parameters:   None
** Returned value:      None
********************************************************************************************************************************/
void Output_StepNet_NK(int num, LIST *net, int step)	//for debug
{
	FILE *fp;
	char *name;
	NODE *work;

	name = (char *)malloc(NAME_SIZE * sizeof(char));
	sprintf(name, "task%d_net_step=%d.csv", g_taskNum, step);
	fp = fopen(name, "w");
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
** Function name:       Output_OtherPara_To_File
** Descriptions:        Output_OtherPara_To_File
** input parameters:    Dif,step
** output parameters:   None
** Returned value:      None
********************************************************************************************************************************/
void Output_OtherPara_To_File(DIFFUSION& Dif, int step)				//for debug
{
	FILE *fp;
	char *name;

	name = (char *)malloc(NAME_SIZE * sizeof(char));

	sprintf(name, "task%d_%d_rhoCnt.csv", g_taskNum, step);
	fp = fopen(name, "w");
	fprintf(fp, "%f\n", double(Dif.rhoCnt)/double(g_Net.N));
	fclose(fp);

	sprintf(name, "task%d_%d_state.csv", g_taskNum, step);
	fp = fopen(name, "w");
	for (int i = 0; i < g_Net.N; i++)
	{
		fprintf(fp, "%d\n", Dif.state[i]);
	}
	fclose(fp);

	sprintf(name, "task%d_%d_newICnt.csv", g_taskNum, step);
	fp = fopen(name, "w");
	for (int i = 0; i < g_Net.N; i++)
	{
		fprintf(fp, "%d\n", Dif.thCnt[i]);
	}
	fclose(fp);

	sprintf(name, "task%d_%d_newINum_In_NodeMemory.csv", g_taskNum, step);
	fp = fopen(name, "w");
	for (int i = 0; i < g_Net.N; i++)
	{
		for (auto it = Dif.thIn_NodeMemory[i].begin(); it != Dif.thIn_NodeMemory[i].end(); it++)
		{
			fprintf(fp, "%d,", *it);
		}
		fprintf(fp, "\n");
	}
	fclose(fp);

	sprintf(name, "task%d_%d_neighborI_Num.csv", g_taskNum, step);
	fp = fopen(name, "w");
	for (int i = 0; i < g_Net.N; i++)
	{
		fprintf(fp, "%d\n", Dif.neighborI_Num[i]);
	}
	fclose(fp);

	sprintf(name, "task%d_%d_neighborI_Num_Old.csv", g_taskNum, step);
	fp = fopen(name, "w");
	for (int i = 0; i < g_Net.N; i++)
	{
		fprintf(fp, "%d\n", Dif.neighborI_Num_Old[i]);
	}
	fclose(fp);

	free(name);
}
/*****************************************************End Of File***************************************/
