#include <cfloat>
#include <cmath>
#include <cstdio>
#include <cstdlib>
#include <fstream>
#include <string>
#include <sys/time.h>

#define DEFAULT_K 5
#define DEFAULT_NITERS 20

//point structure AoS
struct point_soa_t {
    
    double *x;
    double *y;
    
};

struct point_t {
  double x;
  double y;
};

double get_time() {
  struct timeval tv;
  gettimeofday(&tv, (struct timezone *)0);
  return ((double)tv.tv_sec + (double)tv.tv_usec / 1000000.0);
}

void read_points(std::string filename, point_t *p, int n) {
  std::ifstream infile{filename};
  double x, y;
  int i = 0;
  while (infile >> x >> y) {
    if (i >= n) {
      printf(
          "WARNING: more points in input file '%s' than read: stopping after "
          "%d lines\n",
          filename.c_str(), i);
      return;
    }
    p[i].x = x;
    p[i].y = y;
    i++;
  }
}

void write_result(std::string filename, int niters, point_t *result, int k) {
  std::ofstream outfile{filename};
  for (int iter = 0; iter < niters + 1; ++iter) {
    for (int i = 0; i < k; ++i) {
      outfile << iter << ' ' << result[iter * k + i].x << ' '
              << result[iter * k + i].y << '\n';
    }
  }
}

void init_centroids(point_t *centroids, int k) {
  for (int i = 0; i < k; ++i) {
    centroids[i].x = rand() % 100;
    centroids[i].y = rand() % 100;
  }
}

// TODO: task 1.2
// Implemente the k-means algorithm
void k_means(int niters, point_t *points, point_t *centroids, int *assignment,
             point_t *result, int n, int k) {
    
  printf("now in the kmeans function");
  //temporary array of double to store the distances
    point_t *distances = static_cast<point_t *>(malloc(k * sizeof(point_t)));
    point_t *sum = static_cast<point_t *>(malloc(k * sizeof(point_t)));
    double *count = static_cast<double *>(malloc(k * sizeof(double)));
  
    
  for (int i = 0; i < k; ++i){
        
        distances[i].x = 0;
        distances[i].y = 0;
        sum[i].x = 0;
        sum[i].y = 0;
        count[i] = 0;
        
  }
  printf("initialization complete distances and assignment count");
    
  for (int iter = 0; iter < niters; ++iter) {
    // TODO: task 1.2
    // Assignment step: each data point is assigned to the nearest mean.
    // TODO: task 1.2
    // Update step: each mean is recalculated based on the new assignments.
    /*
     1. calculate the distance of each data point to the centroids
     2. assign the data point to the closest centroid
     3. calculate the mean of data points and update the centroids
     */
      //run every n data points
      for (int i = 0; i < n; ++i) {
          
          //point_t current_pt = points[i];
          for (int j = 0; j < k; ++j){
              
              // store the distance from the i-th point to the centroid
              //do not use pow function because it increases the computational expense
              distances[j].x = (points[i].x - centroids[j].x)*(points[i].x - centroids[j].x);
              distances[j].y  = (points[i].y - centroids[j].y)*(points[i].y - centroids[j].y);
              
          }
          
          //find the closest centroid
          
          int min_index = 0;
          
          for (int j = 0; j < k; ++j){
              
              if(distances[j].x + distances[j].y <= distances[min_index].x + distances[min_index].y){
                  
                  min_index = j;
                  
              }
              
          }
          //assign this centroid index to the assignment
          assignment[i] = min_index;
          count[min_index] += 1;
          sum[min_index].x += distances[min_index].x;
          sum[min_index].y += distances[min_index].y;
          
      }
      //update new centroids
      for (int i = 0; i < k; ++i) {
          
          if(count[i] != 0){
              
              centroids[i].x = sum[i].x/count[i];
              centroids[i].y = sum[i].y/count[i];
              
          }
          
          result[(iter + 1) * k + i].x = centroids[i].x;
          result[(iter + 1) * k + i].y = centroids[i].y;
      }
    
  }
    
}


int main(int argc, const char *argv[]) {
  // Handle input arguments
  if (argc < 3 || argc > 5) {
    printf("Usage: %s <input file> <num points> <num centroids> <num iters>\n",
           argv[0]);
    return EXIT_FAILURE;
  }
    const char *input_file = argv[1];
    const int n = atoi(argv[2]);
    const int k = (argc > 3 ? atoi(argv[3]) : DEFAULT_K);
    const int niters = (argc > 4 ? atoi(argv[4]) : DEFAULT_NITERS);


  // Allocate and initialize data
  point_t *points = static_cast<point_t *>(malloc(n * sizeof(point_t)));
  point_soa_t point_soa;
  point_soa.x = (double*) malloc(n*sizeof(double));
  point_soa.y = (double*) malloc(n*sizeof(double));
    
  point_t *centroids = static_cast<point_t *>(malloc(k * sizeof(point_t)));
  int *assignment = static_cast<int *>(malloc(n * sizeof(int)));
  srand(1234);
  read_points("small.in", points, n);
  init_centroids(centroids, k);

  // TODO: task 1.3
  // Verify the results by visualization. Result contains space for the
  // position of the centroids of the initial configuration and at every
  // iteration of the algorithm. For debugging purposes, the array is set to
  // values outside the domain.
  point_t *result =
      static_cast<point_t *>(malloc((niters + 1) * k * sizeof(point_t)));

  for (int i = 0; i < (niters + 1) * k; ++i) {
    result[i].x = -1.0;
    result[i].y = -1.0;
  }
    
  point_soa_t result_soa;
  result_soa.x = (double*) malloc(n*sizeof(double));
  result_soa.y = (double*) malloc(n*sizeof(double));
  
  for (int i = 0; i < k; ++i) {
        
        result_soa->x[i] = centroids[i].x;
        result_soa->y[i] = centroids[i].y;
      
   }
  
  
  for (int i = 0; i < k; ++i) {
      
      result[i].x = centroids[i].x;
      result[i].y = centroids[i].y;
    
  }

  printf("Executing k-means clustering with %d iterations, %d points, and %d "
         "centroids...\n",
         niters, n, k);

  double runtime = get_time();
  /*
   niter, k, n are given from the input data
   points : array of struct point_t with length n
   centroids : array of struct point_t with length k
   result : array of struct point_t with length k*(niter + 1)
   assignment : array of int with length n
   
   
   */
  printf("start to execute kmeans");
  k_means(niters, points, centroids, assignment, result, n, k);
  runtime = get_time() - runtime;

  printf("Time Elapsed: %f s\n", runtime);

  // TODO: task 1.3
  // Verify the results by visualization
  write_result("result.out", niters, result, k);

  free(assignment);
  free(centroids);
  free(points);
  free(result);

  return EXIT_SUCCESS;
}
