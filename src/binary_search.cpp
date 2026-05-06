#include "binary_search.hpp"

int binarySearch(const std::vector<Customer>& arr, int left, int right, int k) {
    if (left > right) {
        return -1; 
    }

    int mid = left + (right - left) / 2;
    
    if (arr[mid].tenure == k) {
        return mid;
    }
    
    if (arr[mid].tenure > k) {
        return binarySearch(arr, mid + 1, right, k);
    } 
    else {
        return binarySearch(arr, left, mid - 1, k);
    }
}