## Plots

* Workload of size 10000 pages
* Cache Size of 100

### Local Workload

* Plot for 100 Unique pages
![alt text](./LOCAL_100_Unique.png "Local 100 Unique")

* Plot for 50 Unique pages
![alt text](./LOCAL_50_Unique.png "Local 50 Unique")

### Loop Workload

* Plot for 100 Unique pages
![alt text](./LOOP_100_Unique.png "Loop 100 Unique")

* Plot for 50 Unique pages
![alt text](./LOOP_50_Unique.png "Loop 50 Unique")

### Random Workload

* Plot for 100 Unique pages
![alt text](./RAND_100_Unique.png "Random 100 Unique")

* Plot for 50 Unique pages
![alt text](./RAND_50_Unique.png "Random 50 Unique")

## Complexity Analysis

### FIFO Policy

* Using array for maintaining cache
* Space Complexity: O(cache_size)
* Time Complexity: O(cache_size*size)

### LRU Policy

* Using array for maintaining cache and last accessed time
* Space Complexity: 2*O(cache_size)
* Time Complexity: O(cache_size*size)

### LRU Approx Policy

* Using array for maintaining cache and bit references
* Space Complexity: 2*O(cache_size)
* Time Complexity: O(cache_size*size)

### Random Policy

* Using array for maintaining cache
* Space Complexity: O(cache_size)
* Time Complexity: O(cache_size*size)