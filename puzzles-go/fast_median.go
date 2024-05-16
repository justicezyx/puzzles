/*
The median is the middle value in an ordered integer list. If the size of the list is even, there is no middle value and
the median is the mean of the two middle values.
- For example, for arr = [2,3,4], the median is 3.
- For example, for arr = [2,3], the median is (2 + 3) / 2 = 2.5.
Implement the MedianFinder class:
- MedianFinder() initializes the MedianFinder object.
- void addNum(int num) adds the integer num from the data stream to the data structure.
- double findMedian() returns the median of all elements so far.
*/
package puzzles

import (
	"container/heap"
	"fmt"
)

type minIntHeap []int

func (h minIntHeap) Len() int           { return len(h) }
func (h minIntHeap) Less(i, j int) bool { return h[i] < h[j] }
func (h minIntHeap) Swap(i, j int)      { h[i], h[j] = h[j], h[i] }

func (h *minIntHeap) Pop() any {
	v := (*h)[len(*h)-1]
	*h = (*h)[:(len(*h) - 1)]
	return v
}

func (h *minIntHeap) Push(v any) {
	*h = append(*h, v.(int))
}

type maxIntHeap []int

func (h maxIntHeap) Len() int           { return len(h) }
func (h maxIntHeap) Less(i, j int) bool { return h[i] > h[j] }
func (h maxIntHeap) Swap(i, j int)      { h[i], h[j] = h[j], h[i] }

func (h *maxIntHeap) Pop() any {
	v := (*h)[len(*h)-1]
	*h = (*h)[:(len(*h) - 1)]
	return v
}

func (h *maxIntHeap) Push(v any) {
	*h = append(*h, v.(int))
}

type MedianFinder struct {
	left  maxIntHeap
	right minIntHeap
}

func NewMedianFinder() MedianFinder {
	return MedianFinder{
		left:  make([]int, 0),
		right: make([]int, 0),
	}
}
func (this *MedianFinder) addNum(v int) {
	if len(this.left) > 0 && v < this.left[0] {
		// Smaller than the largest of the lesser group
		heap.Push(&this.left, v)
	} else if len(this.right) > 0 && v > this.right[0] {
		// Larger than the smallest of the greater group
		heap.Push(&this.right, v)
	} else {
		// Not in lesser or greater, in between, push to the smaller group
		if len(this.left) <= len(this.right) {
			heap.Push(&this.left, v)
		} else {
			heap.Push(&this.right, v)
		}
	}

	fmt.Println("this.left:", this.left, "this.right", this.right)

	// Rebalance 2 parts such that their size difference is at most 1
	for len(this.left)-len(this.right) > 1 {
		v := heap.Pop(&this.left)
		heap.Push(&this.right, v)
	}
	for len(this.right)-len(this.left) > 1 {
		v := heap.Pop(&this.right)
		heap.Push(&this.left, v)
	}
}

func (this *MedianFinder) findMedian() float64 {
	fmt.Println("findMedian, this.left: ", this.left, "this.right: ", this.right)
	lSize := len(this.left)
	rSize := len(this.right)
	if lSize < rSize {
		return float64(this.right[0])
	} else if rSize < lSize {
		return float64(this.left[0])
	} else {
		return (float64(this.left[0]) + float64(this.right[0])) / 2
	}
}
