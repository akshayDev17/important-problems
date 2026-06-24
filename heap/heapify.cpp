#include<iostream>
#include<vector>

using namespace std;

// max heap
void heapify(vector<int> &arr, int pos, int size) {
    // heapify only is nodular in nature, makes the current node obey 
    // requisite heap structure (max or min heap)
    int right = 2* pos + 2, left = 2*pos + 1;
    int largest_idx = pos;
    if (right < size && arr[pos] < arr[right]) largest_idx = right;
    if (left < size && arr[largest_idx] < arr[left]) largest_idx = left;
    if (largest_idx != pos) {
        // swap and return
        arr[pos] += arr[largest_idx];
        arr[largest_idx] = arr[pos] - arr[largest_idx];
        arr[pos] -= arr[largest_idx];

        // call heapify at the "disturbed" branch
        heapify(arr, largest_idx, size);
    }
}

void buildMaxHeap(vector<int> &arr, int size){
    // start from the reverse , from the first non-leaf node.
    for (int i = size / 2 - 1; i >=0; i --) heapify(arr, i, size);
}

void printArr(vector<int> arr){
    for(vector<int>::iterator it = arr.begin();it != arr.end();it++){
        cout << *it << " , ";
    }
    cout << endl;
}

void heapSort(vector<int> &arr){
    // keep popping the largest element and reducing the size, 
    // so as to obtain the ascending sorted array
    for (int sz = arr.size();sz > 1;sz--){
        buildMaxHeap(arr, sz);

        // arr[0] = highest element in arr[0]...arr[sz-1]
        arr[sz-1] += arr[0];
        arr[0] = arr[sz-1] - arr[0];
        arr[sz-1] -= arr[0];
    }
}



int main() {
    
    int arr_array[] = {1,56,-439,123,1000,-233,11,9,10,-1232};
    vector<int> arr(arr_array, arr_array + 10);
    int N = arr.size();
    heapSort(arr);
    printArr(arr);

    return 0;
}