package puzzles

import (
	"fmt"
	"testing"
)

func TestCanCompleteCircuit(t *testing.T) {
	gas := []int{5, 1, 2, 3, 4}
	cost := []int{4, 4, 1, 5, 1}
	fmt.Println("gas:", gas)
	fmt.Println("cost:", cost)
	if got := canCompleteCircuit(gas, cost); got != 4 {
		t.Fatal("error 2, got: ", got)
	}
}
