// This program demonstrates how to use Taskflow to
// write loop-based parallelism.

#include <taskflow/taskflow.hpp>
#include <cassert>
#include <numeric>

// Procedure: parallel_for_on_range
void parallel_for_on_range(int N) {

  tf::Executor executor;
  tf::Taskflow taskflow;

  std::vector<int> range(N);
  std::iota(range.begin(), range.end(), 0);

  taskflow.parallel_for_static(range.begin(), range.end(), [&] (const int i) { 
    printf("parallel_for on container item: %d\n", i);
  });

  executor.run(taskflow).get();
  taskflow.dump(std::cout);
}

// Procedure: parallel_for_on_index
void parallel_for_on_index(int N) {
  
  tf::Executor executor;
  tf::Taskflow taskflow;

  // [3, N) with step size 2
  taskflow.parallel_for_static(3, N, 2, [] (int i) {
    printf("parallel_for on index: %d\n", i);
  });

  executor.run(taskflow).get();
  taskflow.dump(std::cout);
}

// ----------------------------------------------------------------------------

// Function: main
int main() {
  
  parallel_for_on_range(100);
  parallel_for_on_index(100);

  return 0;
}






