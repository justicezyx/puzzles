package puzzles

import "math/rand"

func fill(ints []int, max int) {
	for i := 0; i < len(ints); i++ {
		ints[i] = rand.Int() % max
	}
}
