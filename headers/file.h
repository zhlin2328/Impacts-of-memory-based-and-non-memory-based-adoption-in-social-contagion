/****************************************Copyright (c)*************************************************
**                      		Fujian Medical University
**                               http://www.fjmu.edu.cn/
**--------------File Info------------------------------------------------------------------------------
** File name:           file.h
** Created by:          linzhaohua
** Created date:        2018-3-16
** Version:             V1.0
** Descriptions:        file.h
********************************************************************************************************/
//#pragma warning(disable:4996)
#ifndef __FILE_H
#define __FILE_H

void Output_Network_Parm(void);
void Output_Spd_Parm(void);
void Output_Rd_Parm(void);
void Output_Diffusion_Parm(DIFFUSION *p_Dif);
void Output_Network_Parm_Into_File(void);
void Output_Spd_Parm_Into_File(void);
void Output_AveSteadyRho_Parm_To_File(vector<vector<double> >& aveStRho_Parm);
void Output_AveSusMeas_To_File(vector<vector<double> >& aveSus_Meas);
void Output_NotAveStRho_Parm_To_File(vector<vector<double> >& notAveStRho_Parm);
void Output_NotAve_StRho_Parm_To_File(int netCnt, int flag, vector<vector<double> >& rhoParm);
void Output_Parm_StRho_To_File(vector<vector<double> >& aveStRho_Parm);
void Output_Parm_StRhoSquare_To_File(vector<vector<double> >& aveSus_Meas);
void Cal_And_Output_Propagation_Threshold_Value(vector<vector<double> >& aveSus_Meas);
void Cal_And_Output_Propagation_Threshold_Value_atype(vector<vector<double> >& aveSus_Meas);
void Cal_And_Output_Propagation_Threshold_Value_btype(vector<vector<double> >& aveSus_Meas);
void Output_aveRho_t_To_File(vector<vector<double> >& aveRho_t);
void Read_Network_File(char *file_name);
void Output_StepNet_NK(int num, LIST *net, int step);
void Output_OtherPara_To_File(DIFFUSION& Dif, int step);



#endif //__FILE_H
/*****************************************************End Of File***************************************/
