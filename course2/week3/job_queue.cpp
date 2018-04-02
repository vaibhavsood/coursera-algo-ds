#include <iostream>
#include <vector>
#include <algorithm>
#include <queue>

using std::vector;
using std::cin;
using std::cout;
using std::priority_queue;

struct Worker {
  int index;
  long long next_free_time;
};

class CompareWorker {
public:
  bool operator() (Worker w1, Worker w2) {
    if (w1.next_free_time == w2.next_free_time)
      return w1.index > w2.index;
    else
      return w1.next_free_time > w2.next_free_time;
  } 
};

class JobQueue {
 private:
  int num_workers_;
  vector<int> jobs_;

  vector<int> assigned_workers_;
  vector<long long> start_times_;

  void WriteResponse() const {
    for (int i = 0; i < jobs_.size(); ++i) {
      cout << assigned_workers_[i] << " " << start_times_[i] << "\n";
    }
  }

  void ReadData() {
    int m;
    cin >> num_workers_ >> m;
    jobs_.resize(m);
    for(int i = 0; i < m; ++i)
      cin >> jobs_[i];
  }

  void AssignJobs() {
    // TODO: replace this code with a faster algorithm.
    assigned_workers_.resize(jobs_.size());
    start_times_.resize(jobs_.size());
    //vector<long long> next_free_time(num_workers_, 0);
    priority_queue<Worker, vector<Worker>, CompareWorker> next_free_time;
    for (int i = 0; i < num_workers_; i++) {
      Worker worker;
      worker.index = i;
      worker.next_free_time = 0;
      next_free_time.push(worker);
    }
      
    for (int i = 0; i < jobs_.size(); ++i) {
      int duration = jobs_[i];
/*      int next_worker = 0;
      for (int j = 0; j < num_workers_; ++j) {
        if (next_free_time[j] < next_free_time[next_worker])
          next_worker = j;
      }
*/
      Worker next_worker = next_free_time.top();
      next_free_time.pop();
      assigned_workers_[i] = next_worker.index;
      start_times_[i] = next_worker.next_free_time;
      next_worker.next_free_time += duration;
      next_free_time.push(next_worker);
    }
  }

 public:
  void Solve() {
    ReadData();
    AssignJobs();
    WriteResponse();
  }
};

int main() {
  std::ios_base::sync_with_stdio(false);
  JobQueue job_queue;
  job_queue.Solve();
  return 0;
}
