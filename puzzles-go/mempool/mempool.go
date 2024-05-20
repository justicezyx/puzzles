package mempool

import (
	"fmt"
)

type MemRegion struct {
	Offset int
	Size int
}

type MemPool struct {
	// The actual memory
	mem []byte

	// Key is the offset of the MemRegion
	free map[int]MemRegion
	used map[int]MemRegion
}

func (p MemPool) Cap() int {
	return len(p.mem)
}

func NewMemPool(size int) (*MemPool, error) {
	res := MemPool {
		mem: make([]byte, size),
		free: make(map[int]MemRegion),
		used: make(map[int]MemRegion),
	}
	res.free[0] = MemRegion {
		Offset: 0,
		Size: size,
	}
	return &res, nil
}

func (p *MemPool) recordUsed(r MemRegion) {
	p.used[r.Offset] = r
}

func (p *MemPool) clearUsed(r MemRegion) {
	delete(p.used, r.Offset)
}

func (p *MemPool) recordFree(r MemRegion) {
	p.free[r.Offset] = r
}

func (p *MemPool) clearFree(r MemRegion) {
	delete(p.free, r.Offset)
}

func (p *MemPool) Allocate(size int) (MemRegion, error) {
	for _, r := range p.free {
		if r.Size >= size {
			leftOver := MemRegion {
				Offset: r.Offset + size,
				Size: r.Size - size,
			}

			p.clearFree(r)

			if leftOver.Size > 0 {
				p.free[leftOver.Offset] = leftOver
			}
			res := MemRegion {
				Offset: r.Offset,
				Size: size,
			}
			p.recordUsed(res)
			return res, nil
		}
	}
	return MemRegion{}, fmt.Errorf("Not enough space to allocate %d bytes", size)
}

func (p *MemPool) Free(ptr int) error {
	r, ok := p.used[ptr]
	if !ok {
		return fmt.Errorf("PTR %d does not belong to allocated memory region", ptr)
	}
	p.clearUsed(r)
	p.recordFree(r)
	return nil
}
