/*
INSTRUCTIONS:
This file must include only the main function
The main function should print out the various cases
and finally print out tables showing the performance
of various policies with the different workloads.
Vary the cache size.

You may include a function or 2 to ease the printing of tables.

*/


/*
	Include Headers
*/

#include "definitions.h"

/*
	Main Function
*/

int main()
{
	// Initialize Variables
	struct workload* load;
	int pages, size, cache_size;
	float fifo_rate, lru_rate, lru_approx_rate, random_rate;
	WorkloadsT type;

	//Input Unique number of pages, workload size and cache size
	printf("Enter number of pages:");
	scanf("%d", &pages);

	printf("\nEnter size of workload:");
	scanf("%d", &size);

	printf("\nEnter cache size:");
	scanf("%d", &cache_size);

	//Randomize seed to rand to generate random workloads
	srand(time(NULL));

	//Local Workload
	type = LOCAL;

	//Generate workload of the type specified
	load = generate_workload(type, pages, size);

	//Generate CSV files and store hit rates of all policies for varying cache sizes
	generate_csv(load, cache_size);
	
	//Get hit rates of all policies for the specified cache size
	fifo_rate = policy_FIFO(load, cache_size);
	lru_rate = policy_LRU(load, cache_size);
	lru_approx_rate = policy_LRUapprox(load, cache_size);
	random_rate = policy_RANDOM(load, cache_size);

	//Print hit rates to standard output
	printf(GREEN "------------------LOCAL Workload---------------------\n" RESET);
	printf("FIFO Hit Rate: %f\n",fifo_rate);
	printf("LRU Hit Rate: %f\n",lru_rate);
	printf("LRU Approx Hit Rate: %f\n",lru_approx_rate);
	printf("Random Hit Rate: %f\n",random_rate);

	printf("\n");

	//Random Workload
	type = RANDOM;

	//Generate workload of the type specified
	load = generate_workload(type, pages, size);

	//Generate CSV files and store hit rates of all policies for varying cache sizes
	generate_csv(load, cache_size);

	//Get hit rates of all policies for the specified cache size
	fifo_rate = policy_FIFO(load, cache_size);
	lru_rate = policy_LRU(load, cache_size);
	lru_approx_rate = policy_LRUapprox(load, cache_size);
	random_rate = policy_RANDOM(load, cache_size);

	//Print hit rates to standard output
	printf(GREEN "------------------RANDOM Workload--------------------\n" RESET);
	printf("FIFO Hit Rate: %f\n",fifo_rate);
	printf("LRU Hit Rate: %f\n",lru_rate);
	printf("LRU Approx Hit Rate: %f\n",lru_approx_rate);
	printf("Random Hit Rate: %f\n",random_rate);

	printf("\n");

	//Looping Workload	
	type = LOOP;

	//Generate workload of the type specified
	load = generate_workload(type, pages, size);

	//Generate CSV files and store hit rates of all policies for varying cache sizes
	generate_csv(load, cache_size);

	//Get hit rates of all policies for the specified cache size
	fifo_rate = policy_FIFO(load, cache_size);
	lru_rate = policy_LRU(load, cache_size);
	lru_approx_rate = policy_LRUapprox(load, cache_size);
	random_rate = policy_RANDOM(load, cache_size);

	//Print hit rates to standard output
	printf(GREEN "------------------LOOP Workload---------------------\n" RESET);
	printf("FIFO Hit Rate: %f\n",fifo_rate);
	printf("LRU Hit Rate: %f\n",lru_rate);
	printf("LRU Approx Hit Rate: %f\n",lru_approx_rate);
	printf("Random Hit Rate: %f\n",random_rate);

	return 0;
}