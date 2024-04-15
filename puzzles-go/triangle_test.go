package puzzles

import "testing"

func TestMinTotal(t *testing.T) {
	triangle := [][]int{{2}, {3, 4}, {6, 5, 7}, {4, 1, 8, 3}}
	if got := minimumTotal(triangle); got != 11 {
		t.Errorf("wrong minimal total, got: %d", got)
	}
}
