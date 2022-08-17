#include<vector>
#include<iostream>
#include<limits.h>
#include<stdlib.h>
#include<ctime>

using namespace std;

void bucketSort(vector<double> &arr){
    int n = arr.size();
    double min_elem = *min_element(arr.begin(), arr.end()), max_elem = *max_element(arr.begin(), arr.end());
    double range = (max_elem-min_elem)/n;
    // cout << "Smallest = " << min_elem << ", largest = " << max_elem << ", range = " << range << endl;
    vector<vector<double> > buckets = vector<vector<double> >(n, vector<double>());
    for(int i=0;i<n;i++){
        int idx = (arr[i]-min_elem)/range;
        if(idx == n) buckets[idx-1].push_back(arr[i]);
        else buckets[idx].push_back(arr[i]);
    }
    for(int i=0;i<n;i++) sort(buckets[i].begin(), buckets[i].end());
    int counter = 0;
    for(auto it: buckets){
        for(auto jt: it){
            arr[counter] = jt;
            counter++;
        }
    }
}

int main(){
    // int n = rand();
    int n = 1000000;
    cout << n << endl;
    // int n = 10;
    vector<double> vec(n, 0.0);
    for(int i=0;i<n;i++){
        double integer_part = (double)(rand() % 10 + 1);
        double decimal = (double)(rand()/(double)RAND_MAX);
        vec[i] = integer_part+decimal;
    }
    // cout << "Original Array:\n";
    // for(auto it: vec) cout << it << " ";
    // cout << endl << endl;
    auto start = std::chrono::system_clock::now();
    bucketSort(vec);
    auto end = std::chrono::system_clock::now();

    std::chrono::duration<double> elapsed_seconds = end-start;

    cout << "\nTime Taken = " << elapsed_seconds.count() << "\n\n";

    // cout << "Sorted Array:\n";
    // for(auto it: vec) cout << it << " ";
    cout << endl << endl;
    return 0;
}