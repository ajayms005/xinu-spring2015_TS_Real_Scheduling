#include<xinu.h>


int cycle_detect()
{
	int visited[NPROC+NSEM]= {0};
	int i,j,k,p,l;
	int cycle = 0;
	for(i=0;i<NPROC+NSEM;i++)
	{ 
		k = 0;
		cycle = 0;
		for(j=0;j<NSEM+NPROC;j++)
		{
			if(matrix[i][j]==1)
			{
				visited[k++] = j;
			}
		}
		int node;
		for(p=0;p<k;p++)
		{
			node = visited[p];
			for(l=0;l<NSEM+NPROC; l++)
			{
				if(matrix[node][l] == 1)
				{
					if(l==i)
					{
						cycle = 1;
						break;
					}else
					{
						visited[k++] = l;
					}
				}
			}
			if(cycle==1)
				break;
		}
		if(cycle==1)
			break;
	}
	return cycle;
}












