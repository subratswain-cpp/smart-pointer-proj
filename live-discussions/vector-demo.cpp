// Vector Demo

#include <iostream>
#include <vector>
#include <algorithm>

// Q: ++i vs i++: Overloading....
// STL
// Dynamic Array.

int main() {
    // int arr[] {1,2,3,4,5};
    std::vector<int> arr{1,2,3,4,5}; // Uniform initializarion
    // for(int i = 0; i < 5; ++i) {
    //     std::cout << arr[i] << ' ';
    // }
    
    arr.push_back(100);
    arr.push_back(200);
    arr.push_back(300);
    arr.push_back(400);
    arr.push_back(500);
        std::cout << "\nNo of elemets in vector: " << arr.size() << '\n';

    arr.emplace_back(10);
    arr.emplace_back(20); // Use this if possible.
    arr.emplace_back(30);
    arr.emplace_back(40);
    arr.emplace_back(50);
    
    // Print all elements
    for(auto& itm : arr) {
        std::cout << itm << ' ';
    }
    
    std::cout << "\nNo of elemets in vector: " << arr.size() << '\n';

    // std::vector<int> arr{1,2,3,4,5}; // Uniform initializarion

    // Another way of accessing vector elements.
    // for(auto itr = arr.begin(); itr != arr.end(); ++itr) {
    //     *itr = *itr + 2; // Changing the value
    // }

    for(auto& itm : arr) {
        itm *= 2;
    }
    

    // Print all elements
    for(auto& itm : arr) {
        std::cout << itm << ' ';
    }
    
    // Sort the elements
    std::sort(arr.begin(), arr.end());
    std::cout << "\nAfter sorting elements... :\n";
    // Print all elements
    for(auto& itm : arr) {
        std::cout << itm << ' ';
    }
    
    
}