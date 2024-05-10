package pq

import (
	"container/heap"
)

type pq[T any] struct {
	items []T
	less  func(a, b T) bool
}

func (pq pq[T]) Len() int {
	return len(pq.items)
}

func (pq pq[T]) Less(i, j int) bool {
	return pq.less(pq.items[i], pq.items[j])
}

func (pq pq[T]) Swap(i, j int) {
	pq.items[i], pq.items[j] = pq.items[j], pq.items[i]
}

func (pq *pq[T]) Push(x any) {
	pq.items = append(pq.items, x.(T))
}

func (pq *pq[T]) Pop() any {
	res := pq.items[len(pq.items)-1]
	pq.items = pq.items[:len(pq.items)-1]
	return res
}

type PriorityQueue[T any] struct {
	q *pq[T]
}

func New[T any](f func(a, b T) bool) *PriorityQueue[T] {
	return &PriorityQueue[T]{
		q: &pq[T]{
			items: make([]T, 0),
			less:  f,
		},
	}
}

func (pq *PriorityQueue[T]) Push(v T) {
	heap.Push(pq.q, v)
}

func (pq *PriorityQueue[T]) Pop() T {
	return heap.Pop(pq.q).(T)
}
