

/**
 * Given an array of jobs with different time requirements,
 * K workers and how much time a worker takes to do one unit of the job,
 * find the minimum time to finish all jobs
 * 
 * Constraints : {
 *  1) a worker can be assigned only contiguous jobs
 *  2) 2 workers can't share a job
 * }
 * 
*/

#include<iostream> 
using namespace std; 

int getMin(int x, int y) {
    return x < y ? x : y;
}

/**
 * Find the job with max required time 
*/
int getMax(int arr[], int n) 
{ 
   int result = arr[0]; 
   for (int i=1; i<n; i++) 
      if (arr[i] > result) 
         result = arr[i]; 
    return result; 
} 

/**
 * Find if it's possible to finish a jobs that requires "TIME" time, considering the number
 * of available workers
*/
bool is_possible(int time, int total_workers ,int job[], int n) {
    // When a job starts, a workers is assigned to it
    int workers = 1;
    int current_time = 0;

    int i =0;
    for(;i < n;) {
        // If the time accumulated and the time for the current job exceeds the given time
        if(current_time + job[i] > time) {
            // Then we need another worker
            workers++;
            current_time = 0;
        } else {
            // The worker can handle the current job
            current_time += job[i];
            // Check for the following jobs
            i++;
        }
    }

    // If the jobs have been finished with all the available workers
    return workers <= total_workers;
}

int findMinTime(int nr_workers, int time_for_each_worker, int job[], int len) {
    int maxValue = getMax(job,len);
    int start = 0, end = 0; 

    for(int i = 0; i < len; i++)
        end += job[i];

    int result = end;
    while(start <= end) {
        int mid = (start + end) / 2;
        if(mid >= maxValue && is_possible(mid,nr_workers,job,len)) {
            result = min(result,mid);
            // Search left
            end = mid - 1;
        } else {
            // Search right
            start = mid + 1;
        }
    }

    return result * time_for_each_worker;
}  
  
int main() {
    int job[] =  {10, 7, 8, 12, 6, 8}; 
    int n = sizeof(job)/sizeof(job[0]); 
    int k = 4, T = 5; 
    cout << findMinTime(k, T, job, n) << endl; 
    return 0; 
} 