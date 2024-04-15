package puzzles

import "fmt"

func sum(ints []int) int {
	res := 0
	for _, i := range ints {
		res += i
	}
	return res
}

func canCompleteCircuit(gas []int, cost []int) int {
	if sum(gas) < sum(cost) {
		return -1
	}
	total := 0
	res := 0
	for i := 0; i < len(gas); i++ {
		fmt.Println("i:", i, "total", total)
		total += (gas[i] - cost[i])
		fmt.Println("i:", i, "total", total)
		if total < 0 {
			fmt.Println("resetting total i:", i, "total", total)
			total = 0
			res = i + 1
		}
	}
	return res
}
