#include <xinu.h>
#define OUTER 25
void myperiodicrtapp(int rt_period, int rt_comp){
	int i,j,k;
	int array[OUTER][2], w = 0;
	int val=0;
	char a[50] = "abcdefghiabcdefghiabcdefghiabcdefghiabcdef";
        char b[50];

	uint32 slp_til_next_period;
	uint32 period_start, time_a, time_b, time_diff, cpu_received ;	
	for(i=0;i<OUTER;i++){
		cpu_received = 0;
		period_start = myglobalclock;
		for(j=0; j<300000; j++){
			time_a=myglobalclock;
			while(1){
			w++;
                        memcpy(b,a,50);
			memcpy(a,b,50);
			if(w==2000000);
			break;
			}
			time_b=myglobalclock;
			time_diff=time_b-time_a;
			if(time_diff<3){
				cpu_received += time_diff;
			        if(cpu_received>=rt_comp){
				val = myglobalclock;
				break;
			}
			}

		}
		
		slp_til_next_period = rt_period - (myglobalclock - period_start);
		sleepms(slp_til_next_period);
		array[i][0] = period_start;
		array[i][1] = -(val);
		
	}
	for(k=0; k<OUTER; k++){
	
	kprintf("arr[%d]= %d, arr[1]=%d\n",k,array[k][0],array[k][1]);

	}


}
