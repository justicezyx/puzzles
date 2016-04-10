#include "common/common.h"

/**
 * Selection the k-th smallest/largest element from multiple unsorted arrays
 */

/**
 * Return the position of the pivot value in the given range of values
 * [begin, end), such that for any i < [return value], the value is less than
 * the pivot; for any i > [return value] the value is larger than the pivot.
 *
 * This means that the input and pivot are all unique.
 */
template<typename vector>
int partition(vector& array, int begin, int end, int pivot) {
    int i = begin;
    int j = end-1;
    while (i < j) {
        while (i < end && array[i] < pivot) { i++; }
        while (j >= begin && array[j] > pivot) { j--; }
        if (i < j) {
            swap(array[i], array[j]);
        }
    }
    return i;
}

int random(int begin, int end) {
    int num = end - begin;
    return begin + rand() % num;
}

/**
 * multi-way selection. Select the k-th smallest element from multiple
 * non-sorted arrays. 
 *
 * Maintain an interval for each array, such that the k-th element could be in
 * the elements of the intervals of all arrays. Select randomly from these
 * elements and counting the position of the pivot in all arrays's intervals.
 * Continue until find the value that is the k-th element.
 *
 * This implementation only works with all elements of all arrays are unique.
 */
int multi_way_selection(vector<vector<int>>& arrays, int k) {
    int array_num = arrays.size();
    vector<pair<int, int>> intervals(array_num);
    for (int i = 0; i < array_num; ++i) {
        intervals[i].first = 0;
        intervals[i].second = arrays[i].size();
    }
    while (true) {
        cout<<"iteration"<<endl;
        for (int i = 0; i < intervals.size(); ++i) {
            cout<<i<<"-th array, begin:"<<intervals[i].first<<" end:"<<intervals[i].second<<endl;
            if (intervals[i].first >= intervals[i].second) {
                continue;
            }
            int pos = random(intervals[i].first, intervals[i].second);
            int pivot = arrays[i][pos];

            // Special treatment to the array the global pivot is drawn from.
            // The pivot needs to the same position as in a sorted array. 
            // To achieve this, find its position by counting, and swap in the
            // correct position.
            swap(arrays[i][intervals[i].first], arrays[i][pos]);
            int tmp = partition(arrays[i], intervals[i].first+1, intervals[i].second, pivot);
            swap(arrays[i][intervals[i].first], arrays[i][tmp-1]);

            // intervals[i].first++;
            cout<<"random pos:"<<pos<<" pivot value:"<<pivot<<endl;
            int sum = 0;
            vector<int> mids;
            mids.reserve(intervals.size());

            // Note that the array that the global pivot is drawm from has been
            // paritioned again, but the paritition implemention will keep the
            // array intact. 
            //
            // Keep this redundant partition call to make it looks better.
            for (int k = 0; k < intervals.size(); ++k) {
                int begin = intervals[k].first;
                int end = intervals[k].second;
                int tmp = partition(arrays[k], begin, end, pivot);
                sum += tmp;
                mids.push_back(tmp);
            }
            cout<<"number of elements preceding pivot:"<<sum<<endl;
            if (sum+1 == k) {
                return pivot;
            } else if (sum+1 < k) {
                cout<<"new lower bound"<<endl;
                for (int k = 0; k < mids.size(); ++k) {
                    intervals[k].first = mids[k];
                }
            } else {
                cout<<"new upper bound"<<endl;
                for (int k = 0; k < mids.size(); ++k) {
                    intervals[k].second = mids[k];
                }
            }
        }
    }
    return -1;
}
                    
void test_partition() {
    int array[] = {4, 3, 2, 1};
    assert (partition(array, 0, 4, 1) == 0);
    assert (partition(array, 0, 4, 3) == 2);
}

void test_selection() {
    vector<int> a{4, 3, 2, 1};
    vector<int> b{8, 7, 6, 5};
    vector<vector<int>> arrays{a, b};
    cout<<multi_way_selection(arrays, 1);
}

int main() {
    test_partition();
    test_selection();
}
        
