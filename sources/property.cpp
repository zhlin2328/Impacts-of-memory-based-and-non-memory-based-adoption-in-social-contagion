/****************************************Copyright (c)*************************************************
**                      		Fujian Medical University
**                               http://www.fjmu.edu.cn/
**--------------File Info------------------------------------------------------------------------------
** File name:           property.cpp
** Created date:        2018-3-16
** Version:             V1.0
** Descriptions:        property.cpp
********************************************************************************************************/
#include "../headers/config.h"
/********************************************************************************************************************************
** Function name:       nkmax_nk
** Descriptions:        calculate nkmax_nk
** input parameters:    N,net_nk
** output parameters:   nkmax
** Returned value:      nkmax
********************************************************************************************************************************/
int nkmax_nk(const int N, vector< vector< int > > net_nk)   //caculate nkmax(degree maximum) for nk
{
	int nkmax = 0;
	for (int i = 0; i<N; i++)
	{
		nkmax = (nkmax>net_nk[i][0]) ? nkmax : net_nk[i][0];
	}
	return nkmax;
}
/********************************************************************************************************************************
** Function name:       avenk_nk
** Descriptions:        calculate avenk_nk
** input parameters:    N,net_nk
** output parameters:   avenk
** Returned value:      avenk
********************************************************************************************************************************/
double avenk_nk(const int N, vector< vector< int > > net_nk)
{
	double avenk = 0;
	for (int i = 0; i<N; i++)
	{
		avenk += net_nk[i][0];
	}
	avenk /= N;
	return avenk;

}
/********************************************************************************************************************************
** Function name:       cupk_nk
** Descriptions:        calculate cumulation pk(degree distribution)
** input parameters:    N,net_nk
** output parameters:   cupk(cumulation pk)
** Returned value:      cupk
********************************************************************************************************************************/
double *cupk_nk(const int N, vector< vector< int > > net_nk)
{
	int nkmax;
	double *cupk;


	nkmax = nkmax_nk(N, net_nk);
	cupk = (double *)malloc((nkmax + 1) * sizeof(double));
	for (int i = 0; i<nkmax + 1; i++)
	{
		cupk[i] = 0;
	}
	for (int i = 0; i<N; i++)
	{
		cupk[net_nk[i][0]]++;
	}
	cupk[nkmax] /= double(N);
	for (int i = nkmax - 1; i >= 0; i--)
	{
		cupk[i] = cupk[i] / double(N) + cupk[i + 1];
	}
	return cupk;
}
/********************************************************************************************************************************
** Function name:       pk_nk
** Descriptions:        calculate pk_nk(degree distribution)
** input parameters:    N,net_nk
** output parameters:   pk_nk
** Returned value:      pk
********************************************************************************************************************************/
double *pk_nk(const int N, vector< vector< int > > net_nk)  //caculate pk(degree distribution)
{
	int nkmax;
	double *pk;


	nkmax = nkmax_nk(N, net_nk);
	pk = (double *)malloc((nkmax + 1) * sizeof(double));
	for (int i = 0; i<nkmax + 1; i++)
	{
		pk[i] = 0;
	}
	for (int i = 0; i<N; i++)
	{
		pk[net_nk[i][0]]++;
	}
	for (int i = 0; i<nkmax + 1; i++)
	{
		pk[i] /= double(N);
	}
	return pk;
}
/********************************************************************************************************************************
** Function name:       s_avepath_nk
** Descriptions:        s_avepath_nk
** input parameters:    s,N,net_nk
** output parameters:   s_avepath
** Returned value:      s_avepath
********************************************************************************************************************************/
double s_avepath_nk(const int s, const int N, vector< vector< int > > net_nk)
{
	int *u_color;
	int *u_d;
	int *u_pai;
	int *q;  //queue
	double s_avepath = 0;
	int tail = 0;
	int head = 0;
	int V;

	u_color = (int *)malloc(N * sizeof(int));
	u_d = (int *)malloc(N * sizeof(int));
	u_pai = (int *)malloc(N * sizeof(int));
	q = (int *)malloc((N + 1) * sizeof(int));

	for (int i = 0; i<N; i++)  //initialization
	{
		u_color[i] = 0;  //white:0,gray:1,black:2
		u_d[i] = -9999;
		u_pai[i] = -9999;
		q[i] = -9999;
	}
	q[N] = -9999;

	u_color[s] = 1;  //gray
	u_d[s] = 0;
	u_pai[s] = -9999;

	q[head] = s;
	tail++;
	while (!(head == tail))
	{
		for (int i = 1; i <= net_nk[q[head]][0]; i++)
		{
			V = net_nk[q[head]][i];
			if (u_color[V] == 0)
			{
				u_color[V] = 1;
				u_d[V] = u_d[q[head]] + 1;
				u_pai[V] = q[head];
				q[tail++] = V;
			}
		}
		u_color[q[head++]] = 2;
	}
	for (int i = 0; i<N; i++)
	{
		s_avepath += double(u_d[i]);
	}
	s_avepath /= double(N - 1);

	free(u_color);
	free(u_d);
	free(u_pai);
	free(q);

	return s_avepath;
}
/********************************************************************************************************************************
** Function name:       s_hm_avepath_nk
** Descriptions:        harmonic mean
** input parameters:    s,N,net_nk
** output parameters:   s_avepath
** Returned value:      s_avepath
********************************************************************************************************************************/
double s_hm_avepath_nk(const int s, const int N, vector< vector< int > > net_nk) 
{
	int *u_color;
	int *u_d;
	int *u_pai;
	int *q;  //queue
	double s_avepath = 0;
	int tail = 0;
	int head = 0;
	int V;

	u_color = (int *)malloc(N * sizeof(int));
	u_d = (int *)malloc(N * sizeof(int));
	u_pai = (int *)malloc(N * sizeof(int));
	q = (int *)malloc((N + 1) * sizeof(int));

	for (int i = 0; i<N; i++)  //initialization
	{
		u_color[i] = 0;  //white:0,gray:1,black:2
		u_d[i] = -9999;
		u_pai[i] = -9999;
		q[i] = -9999;
	}
	q[N] = -9999;

	u_color[s] = 1;  //gray
	u_d[s] = 0;
	u_pai[s] = -9999;

	q[head] = s;
	tail++;
	while (!(head == tail))
	{
		for (int i = 1; i <= net_nk[q[head]][0]; i++)
		{
			V = net_nk[q[head]][i];
			if (u_color[V] == 0)
			{
				u_color[V] = 1;
				u_d[V] = u_d[q[head]] + 1;
				u_pai[V] = q[head];
				q[tail++] = V;
			}
		}
		u_color[q[head++]] = 2;
	}
	for (int i = 0; i<N; i++)
	{
		if ((i != s) && (u_d[i] != -9999))
		{
			s_avepath += 1.0 / double(u_d[i]);
		}

	}
	s_avepath /= double(N - 1);

	free(u_color);
	free(u_d);
	free(u_pai);
	free(q);

	return s_avepath;
}
/********************************************************************************************************************************
** Function name:       isconnected_nk
** Descriptions:        isconnected_nk
** input parameters:    N,net_nk
** output parameters:   connected: 1 or unconnected: 0
** Returned value:      1 or 0
********************************************************************************************************************************/
int isconnected_nk(const int N, vector< vector< int > > net_nk)
{
	int *u_color;
	int *q;  //queue
	int tail = 0;
	int head = 0;
	int V;

	u_color = (int *)malloc(N * sizeof(int));
	q = (int *)malloc((N + 1) * sizeof(int));

	for (int i = 0; i<N; i++)  //initialization
	{
		u_color[i] = 0;  //white:0,gray:1,black:2
		q[i] = -9999;
	}
	q[N] = -9999;
	u_color[0] = 1;  //gray,initial node=0

	q[head] = 0;
	tail++;
	while (!(head == tail))
	{
		for (int i = 1; i <= net_nk[q[head]][0]; i++)
		{
			V = net_nk[q[head]][i];
			if (u_color[V] == 0)
			{
				u_color[V] = 1;
				q[tail++] = V;
			}
		}
		u_color[q[head++]] = 2;
	}
	free(u_color);
	free(q);
	if (tail == N)
	{
		return 1;  //connected
	}
	else
	{
		return 0;  //unconnected
	}
}
/********************************************************************************************************************************
** Function name:       avepath_nk
** Descriptions:        avepath_nk
** input parameters:    N,net_nk
** output parameters:   avepath
** Returned value:      avepath
********************************************************************************************************************************/
double avepath_nk(const int N, vector< vector< int > > net_nk)  //need "fun_s_avepath_nk"
{
	double sum = 0;
	for (int i = 0; i<N; i++)
	{
		sum += s_avepath_nk(i, N, net_nk);
	}
	return sum / double(N);
}
double hm_avepath_nk(const int N, vector< vector< int > > net_nk)
{
	double sum = 0;
	for (int i = 0; i<N; i++)
	{
		sum += s_hm_avepath_nk(i, N, net_nk);
	}
	return sum / double(N);
}





/********************************************************************************************************************************
** Function name:       nkmax_nn
** Descriptions:        nkmax_nn
** input parameters:    N,*nk
** output parameters:   nkmax
** Returned value:      nkmax
********************************************************************************************************************************/
int nkmax_nn(const int N, int *nk)   //find nk max
{
	int nkmax = 0;
	for (int i = 0; i<N; i++)
	{
		nkmax = (nk[i]>nkmax) ? nk[i] : nkmax;
	}
	return nkmax;
}
/********************************************************************************************************************************
** Function name:       nk_nn
** Descriptions:        nk_nn
** input parameters:    N,net_nn
** output parameters:   nk
** Returned value:      nk
********************************************************************************************************************************/
int *nk_nn(const int N, int **net_nn)  //caculate node degree for nn
{
	int *nk;

	nk = (int *)malloc(N * sizeof(int));

	for (int i = 0; i<N; i++)
	{
		nk[i] = 0;
		for (int j = 0; j<N; j++)
		{
			nk[i] += net_nn[i][j];
		}
	}
	return nk;
}
/********************************************************************************************************************************
** Function name:       avenk_nn
** Descriptions:        avenk_nn
** input parameters:    N,nk_nn
** output parameters:   avenk
** Returned value:      avenk
********************************************************************************************************************************/
double avenk_nn(const int N, int *nk_nn)
{
	double avenk = 0;
	for (int i = 0; i<N; i++)
	{
		avenk += nk_nn[i];
	}
	avenk /= N;
	return avenk;

}
/********************************************************************************************************************************
** Function name:       pk_nn
** Descriptions:        pk_nn
** input parameters:    N,*nk
** output parameters:   pk
** Returned value:      pk
********************************************************************************************************************************/
double *pk_nn(const int N, int *nk)  //caculate pk(degree distribution)
{
	double *pk;
	int nkmax;

	nkmax = nkmax_nn(N, nk);
	pk = (double *)malloc((nkmax + 1) * sizeof(double));
	for (int i = 0; i<nkmax + 1; i++)
	{
		pk[i] = 0;
	}
	for (int i = 0; i<N; i++)
	{
		pk[nk[i]]++;
	}
	for (int i = 0; i<nkmax + 1; i++)
	{
		pk[i] /= double(N);
	}
	return pk;
}
/********************************************************************************************************************************
** Function name:       cc_nn
** Descriptions:        calculate cluster coefficient of net_nn
** input parameters:    N,net_nn
** output parameters:   avec
** Returned value:      avec
********************************************************************************************************************************/
double cc_nn(const int N, int **net)  
{
	int *nebor;
	double *c;
	int m;
	double avec = 0;

	nebor = (int *)malloc(N * sizeof(int));  //neighbor
	c = (double *)malloc(N * sizeof(double));

	for (int i = 0; i<N; i++)
	{
		for (int j = 0; j<N; j++)
		{
			nebor[j] = -9999;
		}
		int k = -1;
		for (int j = 0; j<N; j++)
		{
			if (net[i][j] == 1)
			{
				k++;
				nebor[k] = j;
			}
		}
		if ((k + 1) <= 1)
		{
			c[i] = 0;
		}
		else
		{
			m = 0;
			for (int I = 0; I<k; I++)
			{
				for (int II = I + 1; II <= k; II++)
				{
					if (net[nebor[I]][nebor[II]] == 1)
					{
						m++;
					}
				}
			}
			c[i] = (double)(2 * m) / (double)(k*(k + 1));
		}
		avec += c[i];
	}
	avec /= N;  

	free(nebor);
	free(c);
	return avec;
}
/********************************************************************************************************************************
** Function name:       cck_nn
** Descriptions:        calculate cluster coefficient of net_nn
** input parameters:    nkmax,N,*nk,*pk,net_nn
** output parameters:   cck
** Returned value:      cck
********************************************************************************************************************************/
double *cck_nn(const int nkmax, const int N, int *nk, double *pk, int **net)  //cluster coefficient
{
	int *nebor;
	double *c;
	double *cck;  //cc(k) distribution
	int m;

	nebor = (int *)malloc(N * sizeof(int));  //neighbor
	c = (double *)malloc(N * sizeof(double));
	cck = (double *)malloc((nkmax + 1) * sizeof(double));


	for (int i = 0; i<N; i++)
	{
		for (int j = 0; j<N; j++)
		{
			nebor[j] = -9999;
		}
		int k = -1;
		for (int j = 0; j<N; j++)
		{
			if (net[i][j] == 1)
			{
				k++;
				nebor[k] = j;
			}
		}
		if ((k + 1) <= 1)
		{
			c[i] = 0;
		}
		else
		{
			m = 0;
			for (int I = 0; I<k; I++)
			{
				for (int II = I + 1; II <= k; II++)
				{
					if (net[nebor[I]][nebor[II]] == 1)
					{
						m++;
					}
				}
			}
			c[i] = (double)(2 * m) / (double)(k*(k + 1));
		}
	}

	for (int i = 0; i<nkmax + 1; i++)  //initialization
	{
		cck[i] = 0;
	}
	for (int i = 0; i<N; i++)
	{
		cck[nk[i]] += c[i];

	}
	for (int i = 0; i<nkmax + 1; i++)
	{
		if (pk[i] != 0)
		{
			cck[i] /= (pk[i] * N);
		}
	}

	free(nebor);
	free(c);
	return cck;
}
/********************************************************************************************************************************
** Function name:       s_avepath_nn
** Descriptions:        s_avepath_nn
** input parameters:    s,N,net_nn
** output parameters:   s_avepath
** Returned value:      s_avepath
********************************************************************************************************************************/
double s_avepath_nn(const int s, const int N, int **net_nn)
{
	int *u_color;
	int *u_d;
	int *u_pai;
	int *q;  //queue
	double s_avepath = 0;
	int tail = 0;
	int head = 0;

	u_color = (int *)malloc(N * sizeof(int));
	u_d = (int *)malloc(N * sizeof(int));
	u_pai = (int *)malloc(N * sizeof(int));
	q = (int *)malloc((N + 1) * sizeof(int));

	for (int i = 0; i<N; i++)  //initialization
	{
		u_color[i] = 0;  //white:0,gray:1,black:2
		u_d[i] = -9999;
		u_pai[i] = -9999;
		q[i] = -9999;
	}
	q[N] = -9999;

	u_color[s] = 1;  //gray
	u_d[s] = 0;
	u_pai[s] = -9999;

	q[head] = s;
	tail++;
	while (!(head == tail))
	{
		for (int i = 0; i<N; i++)
		{
			if ((net_nn[q[head]][i] == 1) && (u_color[i] == 0))
			{
				u_color[i] = 1;
				u_d[i] = u_d[q[head]] + 1;
				u_pai[i] = q[head];
				q[tail++] = i;
			}
		}
		u_color[q[head++]] = 2;
	}
	for (int i = 0; i<N; i++)
	{
		s_avepath += double(u_d[i]);
	}
	s_avepath /= double(N - 1);

	free(u_color);
	free(u_d);
	free(u_pai);
	free(q);

	return s_avepath;
}
/********************************************************************************************************************************
** Function name:       isconnected_nn
** Descriptions:        isconnected_nn
** input parameters:    N,net_nn
** output parameters:   connected: 1 or unconnected: 0
** Returned value:      1 or 0
********************************************************************************************************************************/
int isconnected_nn(const int N, int **net_nn)
{
	int *u_color;
	int *q;  //queue
	int tail = 0;
	int head = 0;

	u_color = (int *)malloc(N * sizeof(int));
	q = (int *)malloc((N + 1) * sizeof(int));

	for (int i = 0; i<N; i++)  //initialization
	{
		u_color[i] = 0;  //white:0,gray:1,black:2
		q[i] = -9999;
	}
	q[N] = -9999;
	u_color[0] = 1;  //gray,initial node=0

	q[head] = 0;
	tail++;
	while (!(head == tail))
	{
		for (int i = 0; i<N; i++)
		{
			if ((net_nn[q[head]][i] == 1) && (u_color[i] == 0))
			{
				u_color[i] = 1;
				q[tail++] = i;
			}
		}
		u_color[q[head++]] = 2;
	}
	free(u_color);
	free(q);
	if (tail == N)
	{
		return 1;  //connected
	}
	else
	{
		return 0;  //unconnected
	}
}
/********************************************************************************************************************************
** Function name:       avepath_nn
** Descriptions:        avepath_nn
** input parameters:    N,net_nn
** output parameters:   avepath
** Returned value:      avepath
********************************************************************************************************************************/
double avepath_nn(const int N, int **net_nn)  //need "fun_s_avepath_nn"
{
	double sum = 0;
	for (int i = 0; i<N; i++)
	{
		sum += s_avepath_nn(i, N, net_nn);
	}
	return sum / double(N);
}
/***********************************************End Of File*********************************************************************/
