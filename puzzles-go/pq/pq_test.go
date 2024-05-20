package pq

import (
	"testing"
)

type item struct {
	v int
	t string
}

func TestPQ(t *testing.T) {
	pq := New[item](func(a, b item) bool { return a.v < b.v })
	pq.Push(item{1, "test"})
	pq.Push(item{0, "0"})
	pq.Push(item{-1, "-1"})
	if pq.Pop().t != "-1" {
		t.Fail()
	}
}
