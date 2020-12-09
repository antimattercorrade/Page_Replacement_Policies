/*
INSTRUCTIONS:

This file will contain all the functions related to the generation of workload

*/

/*
	Include Headers
*/

#include "definitions.h"


// Note: The work must be generated for the returned pointer

/*
    Function to generate all workloads
*/
struct workload * generate_workload(WorkloadsT type, int pages, int size)
{
    //Initialize variables
    struct workload* load = malloc(sizeof(struct workload));
    load->type = type;
    load->pages = pages;
    load->size = size;

    //Check type of workload and call specific helper function
    if(type == LOOP)
    {
        load = generate_loop(load);
    }
    else if(type == RANDOM)
    {
        load = generate_random(load);
    }
    else if(type == LOCAL)
    {
        load = generate_local(load);
    }

//Return workload
return load;
}

//Function to generate random workload
struct workload * generate_random(struct workload * w)
{
    //Initialize the workload
    int* work = malloc((w->size)*sizeof(int));

    //Generate "size" number of pages
    for(int i = 0; i < w->size; i++)
    {
        //Each page is from the unique "pages" specified
        work[i] = rand() % (w->pages);
    }

    w->work = work;

//Return workload
return w;
}

//Function to generate loop workload
struct workload * generate_loop(struct workload * w)
{
    //Initialize the workload
    int* work = malloc((w->size)*sizeof(int));
    int i = 0;

    /*
        Generate "size" number of pages.
        It floors the division if size is not exactly divisible by pages.
    */
    for(i = 0; i < floor(w->size/w->pages); i++)     
    {
        for(int j = 0; j < w->pages; j++) 
        {
            //Generate the workload in a looping manner 
	        work[i*(w->pages)+j] = j;
	    }
    }

    //If size is not exactly divisible by pages, find pages left
    int left = w->size % w->pages;

    if(left != 0)
    {
        //For the left pages generate the workload
        for(int j = 0; j < left; j++)
        {
            work[i*w->pages + j] = j;
        }
    }

    w->work = work;

//Return workload
return w;
}

//Function to generate local workload
struct workload * generate_local(struct workload * w)
{
    //Initialize the workload
    int* work = malloc((w->size)*sizeof(int));

    //Find number of hot and cold pages
    int hot_pages = floor(w->pages*0.2);
    int cold_pages = floor(w->pages*0.8);

    //Generate 80% hot pages
    for(int i = 0; i < floor(w->size*0.8); i++)    
    {
        work[i] = rand() % hot_pages;
    } 

    //Generate 20% cold pages
    for(int i = 0; i < ceil(w->size*0.2); i++) 
    {
        work[i + (int)floor(w->size*0.8)] = (rand()%(cold_pages)) + hot_pages;
    }

    //Mix hot and cold pages inside the workload
    for(int i = 0; i < w->size; i++) 
    {
        int index = rand() % (w->size);
        int element = work[i];
        work[i] = work[index];
        work[index] = element;    
    }
    w->work = work;

//Return workload
return w;
}