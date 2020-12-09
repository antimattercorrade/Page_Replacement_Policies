/* INSTRUCTIONS:

This file will contain all functions related with various policies.
Each policy must return the hit rate

*/

#include "definitions.h"

/*
	Function to implement FIFO policy
*/
float policy_FIFO(struct workload * w, int cache_size)
{
	/*
		Initialize variables
	*/
	float hit_rate = 0;
	int cache[cache_size];
	memset(cache, -1, cache_size*sizeof(cache[0]));
	int flag, hits = 0, faults = 0, pos = 0;

	/*
		Iterate for workload size
	*/
	for(int i = 0; i < w->size; i++)
	{
		flag = 0;
		/*
			If the current page is present in cache,
			increase hit count.
		*/
		for(int j = 0; j < cache_size; j++)
		{
			if(cache[j] == w->work[i])
			{
				flag = 1;
				hits++;
				break;
			}
		}
		/*
			If the current page is not present in cache,
			replace the oldest entry.
			Increase miss count.
		*/
		if(flag == 0)
		{
			if(pos == cache_size)
			{
				pos = 0;
			}
			cache[pos] = w->work[i];
			faults++;
			pos++;
		}
	}
	//Calculate hit rate
	hit_rate = ((float)hits)/((float)w->size);
	 
	return hit_rate;
}

/*
	Function to implement LRU policy
*/
float policy_LRU(struct workload * w, int cache_size)
{
	//Initialize variables
	float hit_rate = 0;
	int cache[cache_size], time[cache_size];
	memset(cache, -1, cache_size*sizeof(cache[0]));
	memset(time, 0, cache_size*sizeof(time[0]));
	int flag_hit, flag_miss, hits = 0, faults = 0, pos, count = 0;

	/*
		Iterate for workload size
	*/
	for(int i = 0; i < w->size; i++)
	{
		flag_hit = 0;
		flag_miss = 0;
		/*
			If the current page is present in cache,
			increase hit count.
			Update last accessed time for the page.
		*/
		for(int j = 0; j < cache_size; j++)
		{
			if(cache[j] == w->work[i])
			{
				flag_hit = 1;
				flag_miss = 1;
				count++;
				time[j] = count;
				hits++;
				break;
			}
		}
		/*
			If the cache is not full, insert the current
			page and increase miss count.
			Update the last accessed time for the page.
		*/
		if(flag_hit == 0)
		{
			for(int j = 0; j < cache_size; j++)
			{
				if(cache[j] == -1)
				{
					count++;
					faults++;
					cache[j] = w->work[i];
					time[j] = count;
					flag_miss = 1;
					break;
				}
			}
		}
		/*
			If the cache is full, replace the least recently
			used entry and increase miss count.
			Update the last accessed time for the page.
		*/
		if(flag_miss == 0)
		{
			int min = time[0], temp = 0;
			for(int k = 0; k < cache_size; k++)
			{
				if(time[k] < min)
				{
					min = time[k];
					temp = k;
				}
			}
			pos = temp;
			count++;
			faults++;
			cache[pos] = w->work[i];
			time[pos] = count;
		}
	}
	//Calculate hit rate
	hit_rate = ((float)hits)/((float)w->size);

	return hit_rate;
}

/*
	Function to implement LRU Approx policy
*/
float policy_LRUapprox(struct workload * w, int cache_size)
{
	//Initialize variables
	float hit_rate = 0;
	int cache[cache_size], bit_ref[cache_size];
	memset(cache, -1, cache_size*sizeof(cache[0]));
	memset(bit_ref, 0, cache_size*sizeof(bit_ref[0]));
	int flag, hits = 0, faults = 0, pos = 0, ins = 0;

	/*
		Iterate for workload size
	*/
	for(int i = 0; i < w->size; i++)
	{
		flag = 0;
		/*
			If the current page is present in cache,
			increase hit count.
			Update the bit reference for the page.
		*/
		for(int j = 0; j < cache_size; j++)
		{
			if(cache[j] == w->work[i])
			{
				flag = 1;
				bit_ref[j] = 1;
				hits++;
				break;
			}
		}
		/*
			If the current page is not present in the cache,
			iterate in bit_ref array.
			Set bit references to 0 if they are 1 and replace
			the first entry with bit 0.
			Start the next iteration from next position.
		*/
		if(flag == 0)
		{
			int steps = 0;
			while(steps < cache_size)
			{
				if(pos == cache_size)
				{
					pos = 0;
				}
				if(bit_ref[pos] == 1)
				{
					bit_ref[pos] = 0;
				}
				else if(bit_ref[pos] == 0)
				{
					cache[pos] = w->work[i];
					pos++;
					break;
				}
				pos++;
				steps++;
			}
		}
	}
	//Calculate hit rate
	hit_rate = ((float)hits)/((float)w->size);

	return hit_rate;
}

/*
	Function to implement Random policy
*/
float policy_RANDOM(struct workload * w, int cache_size)
{
	//Initialize variables
	float hit_rate = 0;
	int cache[cache_size];
	memset(cache, -1, cache_size*sizeof(cache[0]));
	int flag, hits = 0, faults = 0;

	/*
		Iterate for workload size
	*/
	for(int i = 0; i < w->size; i++)
	{
		flag = 0;
		/*
			If the current page is present in cache,
			increase hit count.
			Update the bit reference for the page.
		*/
		for(int j = 0; j < cache_size; j++)
		{
			if(cache[j] == w->work[i])
			{
				flag = 1;
				hits++;
				break;
			}
		}
		/*
			If the current page is not present in the cache,
			replace a random entry in cache.
		*/
		if(flag == 0)
		{
			cache[rand()%cache_size] = w->work[i];
			faults++;
		}
	}
	//Calculate hit rate
	hit_rate = ((float)hits)/((float)w->size);

	return hit_rate;
}
