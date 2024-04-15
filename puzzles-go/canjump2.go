package puzzles

import "fmt"

// Recursively calculate the jump counts from position i in nums slice
func jumpCountRecur(nums, jumpCount []int, i int) int {
	fmt.Println(nums, jumpCount, i)
	if i == len(nums)-1 {
		fmt.Println("already reached: ", jumpCount)
		jumpCount[i] = 0
		return 0
	}
	if i+nums[i] >= len(nums)-1 {
		fmt.Println("can reach now: ", jumpCount)
		jumpCount[i] = 1
		return 1
	}
	min := len(nums)
	fmt.Println("search, min: ", min)
	for v := 1; v <= nums[i]; v += 1 {
		fmt.Println("search, v: ", v)
		c := jumpCount[i+v]
		if c == -1 {
			c = jumpCountRecur(nums, jumpCount, i+v)
		}
		if c+1 < min {
			min = c + 1
		}
	}
	jumpCount[i] = min
	fmt.Println("searched i: ", i, jumpCount)
	return min
}

// Return the minimal count to jump to the last position
func jump(nums []int) int {
	// Sotres the min jump count form each position to the last position
	jumpCount := make([]int, len(nums))
	for i := 0; i < len(jumpCount); i += 1 {
		// -1 means uninitilaized
		jumpCount[i] = -1
	}
	return jumpCountRecur(nums, jumpCount, 0)
}
