package mempool

import (
	"testing"
)

func TestMemPool(t *testing.T) {
	_, err := NewMemPool(100)
	if err != nil {
		t.Fatalf("Failed to create memory pool with size 100, error %v", err)
	}
}
