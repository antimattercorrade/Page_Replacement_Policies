#include "definitions.h"

/*
	Function to generate CSV file storing the hit rates
*/
void generate_csv(struct workload* load, int cache_size)
{
	//Create file name for policy
	char work_type[50];
	if(load->type == LOCAL)
	{
		strcpy(work_type, "LOCAL.csv");
	}
	else if(load->type == LOOP)
	{
		strcpy(work_type, "LOOP.csv");
	}
	else if(load->type == RANDOM)
	{
		strcpy(work_type, "RAND.csv");
	}
	
	FILE* fw;

	for(int i = 0; i < 4; i++)
	{
		char path[2048];
		strcpy(path, "./CSV/");

		if(i == 0)
		{
			strcat(path,"FIFO_");
			strcat(path, work_type);
		}
		else if(i == 1)
		{
			strcat(path,"LRU_");
			strcat(path, work_type);
		}
		else if(i == 2)
		{
			strcat(path,"LRU_APPROX_");
			strcat(path, work_type);
		}
		else if(i == 3)
		{
			strcat(path,"RANDOM_");
			strcat(path, work_type);
		}

		//Open CSV file in write mode
		fw = fopen(path,"w");		    

		//Return if file cannot be opened
		if (fw == NULL)									
		{
			printf("Could not open file");
			return;									
		}

		//Initialize variables
		float rate;
		int size = 1;
		//Vary the cache size and calculate hit rates
		while(size <= cache_size)
		{
			if(i == 0)
			{
				rate = policy_FIFO(load, size);
			}
			else if(i == 1)
			{
				rate = policy_LRU(load, size);
			}
			else if(i == 2)
			{
				rate = policy_LRUapprox(load, size);
			}
			else if(i == 3)
			{
				rate = policy_RANDOM(load, size);
			}
			//Store the hit rates in respective file
			fprintf(fw,"%d,%f\n",size,100*rate);
			size++;
		}
		fclose(fw);	
	}
}