package mempool

type MemRegion struct {
	offset int
	size int
}

type MemPool struct {
	// The actual memory
	mem []byte
}

func (p MemPool) Cap() int {
	return len(p.mem)
}

func NewMemPool(size int) (*MemPool, error) {
	res := MemPool {
		mem: make([]byte, size),
	}
	return &res, nil
}

func (p *MemPool) Allocate(size int) (MemRegion, error) {
	return MemRegion{}, nil
}
