package puzzles

import (
	"container/ring"
	"fmt"
	"testing"
)

func printRing(r *ring.Ring) {
	for i := 0; i < r.Len(); i++ {
		fmt.Println("r.Value:", r.Value)
		r = r.Next()
	}
}

func TestArrayOfArraies(t *testing.T) {
	arrayOfArraies := [1][1]int{
		{1},
	}
	arrayOfSlices := [1][]int{
		{1},
	}
	sliceOfSlices := [][]int{
		{1},
	}
	fmt.Println("arrayOfArraies", arrayOfArraies)
	fmt.Println("arrayOfSlices", arrayOfSlices)
	fmt.Println("sliceOfSlices", sliceOfSlices)

	r := ring.New(2)
	for i := 0; i < r.Len(); i++ {
		r.Value = i
		r = r.Next()
	}

	for i := 0; i < r.Len(); i++ {
		fmt.Println("value:", r.Value)
		r = r.Next()
	}

	r1 := ring.New(2)
	for i := 0; i < r1.Len(); i++ {
		r1.Value = i
		r1 = r1.Next()
	}

	r.Link(r1)
	fmt.Println("r.Len():", r.Len(), "r1.Len()", r1.Len())

	for i := 0; i < r.Len(); i++ {
		r.Value = i
		r = r.Next()
	}

	printRing(r)
	r = r.Move(-1)
	printRing(r)
}
