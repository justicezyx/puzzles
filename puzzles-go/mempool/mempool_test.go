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

	_, err = p.Allocate(100)
	if err != nil {
		t.Fatalf("Failed to allocate memory with size 100, error %v", err)
	}
}
