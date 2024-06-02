package memalloc

import (
	"container/list"
	"fmt"
)

type Region struct {
	begin int
	size  int
}

func (r *Region) allocate(size int) Region {
	res := Region{
		begin: r.begin,
		size:  size,
	}
	r.begin += size
	return res
}

type Allocator struct {
	capacity int
	allocs   *list.List
	frees    *list.List
}

func NewAllocator(c int) Allocator {
	res := Allocator{
		capacity: c,
		allocs:   list.New(),
		frees:    list.New(),
	}
	res.frees.PushBack(Region{0, c})
	return res
}

func (a *Allocator) Allocate(size int) Region {
	var res Region
	for r := a.frees.Front(); r != nil; r = r.Next() {
		region := r.Value.(Region)
		if region.size >= size {
			res = region.allocate(size)
			r.Value = region
			break
		}
	}
	// Insert res into allocs
	for r := a.allocs.Front(); r != nil; r = r.Next() {
		if r.Value.(Region).begin > res.begin {
			a.allocs.InsertBefore(res, r)
			break
		}
	}
	a.allocs.PushBack(res)
	return res
}

func (a *Allocator) Free(toBeFree Region) error {
	for r := a.allocs.Front(); r != nil; r = r.Next() {
		region := r.Value.(Region)
		if region.begin == toBeFree.begin {
			if region.size != toBeFree.size {
				return fmt.Errorf("Invalid input, found alloc %v, to free %v", region, toBeFree)
			}
			a.frees.Remove(r)
			return nil
		}
	}
	return fmt.Errorf("Invalid input, found no alloc for %v", toBeFree)
}
