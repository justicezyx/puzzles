package puzzles

import "testing"

func TestLengthOfLIS(t *testing.T) {
	if got := lengthOfLIS([]int{10, 9, 2, 5, 3, 7, 101, 18, 1}); got != 4 {
		t.Fatal("got:", got)
	}
}
