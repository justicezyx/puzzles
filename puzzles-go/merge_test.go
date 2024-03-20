package puzzles

import (
	"fmt"
	"sort"
	"testing"
)

func TestMerge(t *testing.T) {
	m, n := 10, 20
	nums1 := make([]int, m+n)
	nums2 := make([]int, n)

	fill(nums1, 100)
	sort.Ints(nums1)
	fill(nums2, 100)
	sort.Ints(nums2)

	fmt.Println(nums1)
	fmt.Println(nums2)
	merge(nums1, m, nums2, n)
	fmt.Println(nums1)
	fmt.Println(nums2)
}
