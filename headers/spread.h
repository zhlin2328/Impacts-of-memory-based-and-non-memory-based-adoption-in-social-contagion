/****************************************Copyright (c)*************************************************
**                      		Fujian Medical University
**                               http://www.fjmu.edu.cn/
**--------------File Info------------------------------------------------------------------------------
** File name:           spread.h
** Created by:          linzhaohua
** Created date:        2019-3-18
** Version:             V1.0
** Descriptions:        spread.h
********************************************************************************************************/
#ifndef __SPREAD_H
#define __SPREAD_H

typedef struct
{
	double INFECT_PROB;
	double RECOVER_PROB;
	int MEMORY_SPACE;							//calculate need how many space 
	int usedMemory_Space;						//infect_new_size
	int rhoACnt;
	int rhoBCnt;
	int rhoCnt;
	vector<int> state;
	vector<int> thCnt;							//cnt_of_satisfing_threshold_condition. th: threshold
	deque<deque<int> > thIn_NodeMemory;			//store each node's num of satisfing_threshold_condition,memory length is memory
	vector<int> neighborI_Num;
	vector<int> neighborI_Num_Old;
}DIFFUSION;

void Cal_Rho_Of_Memory_Model(vector<vector<double> >& rhoT);

#endif //__SPREAD_H
/*****************************************************End Of File***************************************/