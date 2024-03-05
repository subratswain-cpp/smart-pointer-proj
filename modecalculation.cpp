// #include "../myExperiments/performance/benchmark.h"
#include <cassert>
#include <iostream>
#include <unordered_map>
#include <vector>

#include "/Users/subrat/sandbox/myExperiments/performance/benchmark.h"

using namespace std;

#include <iostream>
#include <vector>
using namespace std;

#include <chrono>
// #include <ostream>

template <typename Func, typename Expect, typename... Args>
auto TEST_MY_CODE(Func&& func, unsigned T, Expect&& expects, Args&&... args) {
  // auto TEST_MY_CODE(Func&& func, unsigned T) {
  // Start Time
  auto start = std::chrono::high_resolution_clock::now();

  for (unsigned i = 0; i < T; i++) {
    auto res = func(std::forward<Args>(args)...);
    // std::copy(res.begin(), res.end(), std::ostream_iterator<int>(std::cout, "
    // "));
    assert(res == expects);
  }
  // End Time
  auto end = std::chrono::high_resolution_clock::now();
  // Duration
  auto duration =
      std::chrono::duration_cast<std::chrono::microseconds>(end - start)
          .count();
  std::cout << "Time taken by function: " << duration << " microseconds"
            << '\n';
  return duration;
}

vector<int> findModeSorted(const vector<int>& sortedArray) {
  vector<int> modes;
  int maxCount = 0;
  int currentCount = 1;

  for (int i = 1; i < sortedArray.size(); ++i) {
    if (sortedArray[i] == sortedArray[i - 1]) {
      ++currentCount;
    } else {
      if (currentCount > maxCount) {
        maxCount = currentCount;
        modes.clear();
        modes.push_back(sortedArray[i - 1]);
      } else if (currentCount == maxCount) {
        modes.push_back(sortedArray[i - 1]);
      }
      currentCount = 1;
    }
  }

  // Check for mode at the end of the array
  if (currentCount > maxCount) {
    modes.clear();
    modes.push_back(sortedArray.back());
  } else if (currentCount == maxCount) {
    modes.push_back(sortedArray.back());
  }

  return modes;
}

vector<int> findModeHashMap(const vector<int>& unsortedArray) {
  unordered_map<int, int> countMap;
  int maxCount = 0;
  vector<int> modes;

  for (const int& num : unsortedArray) {
    ++countMap[num];
    if (countMap[num] > maxCount) {
      maxCount = countMap[num];
      modes.clear();
      modes.push_back(num);
    } else if (countMap[num] == maxCount) {
      modes.push_back(num);
    }
  }

  return modes;
}

int main() {
  vector<int> unsortedArray = {20, 10, 30, 20, 10};  // Example input
  vector<int> modes =
      findModeHashMap(unsortedArray);  // Output will be in unsorted. We can
                                       // sort the vector if required.

  cout << "Modes (hash map): ";
  for (const int& mode : modes) {
    cout << mode << " ";
  }
  cout << endl;

  vector<int> sortedArray = {10, 10, 20, 20, 30};  // Example input
  vector<int> modes_array = findModeSorted(sortedArray);

  cout << "Modes (sorted array): ";
  for (const int& mode : modes_array) {
    cout << mode << " ";
  }
  cout << endl;

  // Bench Mark test.
  // TEST_MY_CODE(findModeHashMap, unsortedArray, 10);

  // auto myfun = std::bind(findModeHashMap, 10, 10, 20, 20, 30, 10);
  // TEST_MY_CODE(findModeHashMap, 10, 10, 20, 20, 30, 10);
  auto expect_hash = std::vector<int>({20, 10});
  TEST_MY_CODE(findModeHashMap, 1, expect_hash, unsortedArray);

  auto expect = std::vector<int>({10, 20});
  TEST_MY_CODE(findModeSorted, 1, expect, sortedArray);

  return 0;
}
