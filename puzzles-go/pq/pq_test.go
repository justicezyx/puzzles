package pq

import (
	"fmt"
	"testing"
)

type item struct {
	v int
	t string
}

func TestHelloWorld(t *testing.T) {
	pq := New[item](func(a, b item) bool { return a.v < b.v })
	pq.Push(item{1, "test"})
	fmt.Println(pq.Pop())
}
