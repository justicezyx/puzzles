package puzzles

import "fmt"

func searchInsert(nums []int, target int) int {
	left := 0
	right := len(nums) - 1

	for left <= right {
		mid := (left + right) / 2

		if nums[mid] == target {
			return mid
		} else if nums[mid] < target {
			left = mid + 1
		} else {
			right = mid - 1
		}
	}

	return left
}

func lengthOfLIS(nums []int) int {
	seq := make([]int, 0)
	for _, x := range nums {
		if len(seq) == 0 {
			seq = append(seq, x)
		} else {
			ind := searchInsert(seq, x)
			if ind == len(seq) {
				seq = append(seq, x)
			} else {
				seq[ind] = x
			}
		}
		fmt.Println("x:", x, "seq:", seq)
	}
	return len(seq)
}
