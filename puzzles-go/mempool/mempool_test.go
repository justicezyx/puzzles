package mempool

import (
	"testing"
)

func TestMemPool(t *testing.T) {
	p, err := NewMemPool(100)
	if err != nil {
		t.Fatalf("Failed to create memory pool with size 100, error %v", err)
	}
	if p.Cap() != 100 {
		t.Fatalf("Memory pool capacity should be 100, got %d", p.Cap())
	}

	r, err := p.Allocate(100)
	if err != nil {
		t.Fatalf("Failed to allocate memory with size 100, error %v", err)
	}
	if r.Offset != 0 {
		t.Errorf("Failed to allocate memory with size 100, got wrong memory region %v", r)
	}

	_, err = p.Allocate(100)
	if err == nil {
		t.Fatalf("Should fail to allocate memory with size 100, got no error")
	}

	err = p.Free(r.Offset)
	if err != nil {
		t.Fatalf("Failed to free memory with memory region %v", r)
	}

	r, err = p.Allocate(100)
	if err != nil {
		t.Fatalf("Failed to allocate memory with size 100, error %v", err)
	}
	if r.Offset != 0 {
		t.Errorf("Failed to allocate memory with size 100, got wrong memory region %v", r)
	}
}
