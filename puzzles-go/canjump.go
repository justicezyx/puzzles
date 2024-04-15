package puzzles

import "log"

func canJump(nums []int) bool {
	table := make(map[int]bool)
	return canJumpRecur(nums, 0, table)
}

func canJumpRecur(nums []int, i int, table map[int]bool) bool {
	log.Println("calling on ", i)
	if i >= len(nums)-1 {
		return true
	}
	if nums[i] >= len(nums)-i-1 {
		return true
	}
	for v := 1; v <= nums[i] && v < len(nums)-i; v += 1 {
		if can, ok := table[i+v]; ok {
			if can {
				return true
			}
		} else {
			can := canJumpRecur(nums, i+v, table)
			table[i+v] = can
			if can {
				return true
			}
		}
	}
	table[i] = false
	return false
}
