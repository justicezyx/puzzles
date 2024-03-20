package puzzles

import "fmt"

func merge(nums1 []int, m int, nums2 []int, n int) {
	i, j, k := m-1, n-1, m+n-1
	for i >= 0 && j >= 0 {
		fmt.Println("nums1: ", nums1)
		fmt.Println("nums2: ", nums2)
		if nums1[i] > nums2[j] {
			nums1[k] = nums1[i]
			i -= 1
		} else {
			nums1[k] = nums2[j]
			j -= 1
		}
		k -= 1
	}
	for j >= 0 && k >= 0 {
		nums1[k] = nums2[j]
		k -= 1
		j -= 1
	}
}
