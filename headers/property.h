/****************************************Copyright (c)*************************************************
**                      		Fujian Medical University
**                               http://www.fjmu.edu.cn/
**--------------File Info------------------------------------------------------------------------------
** File name:           property.h
** Created by:          linzhaohua
** Created date:        2018-3-16
** Version:             V1.0
** Descriptions:        property.h
********************************************************************************************************/
#ifndef __PROPERTY_H
#define __PROPERTY_H
int nkmax_nk(const int N, vector< vector< int > > net_nk);
double avenk_nk(const int N, vector< vector< int > > net_nk);
double *cupk_nk(const int N, vector< vector< int > > net_nk);  //caculate cumulation pk(degree distribution) 
double *pk_nk(const int N, vector< vector< int > > net_nk);
double s_avepath_nk(const int s, const int N, vector< vector< int > > net_nk);
double s_hm_avepath_nk(const int s, const int N, vector< vector< int > > net_nk); //harmonic mean  //not been checked
int isconnected_nk(const int N, vector< vector< int > > net_nk);
double avepath_nk(const int N, vector< vector< int > > net_nk);
double hm_avepath_nk(const int N, vector< vector< int > > net_nk);   //not checked

int nkmax_nn(const int N, int *nk);
int *nk_nn(const int N, int **net_nn);
double avenk_nn(const int N, int *nk_nn);
double *pk_nn(const int N, int *nk);
double cc_nn(const int N, int **net);  //is N or N-1?
double *cck_nn(const int nkmax, const int N, int *nk, double *pk, int **net);  //cc distribution
double s_avepath_nn(const int s, const int N, int **net_nn);
int isconnected_nn(const int N, int **net_nn);
double avepath_nn(const int N, int **net_nn);

#endif //__PROPERTY_H
/*****************************************************End Of File***************************************/