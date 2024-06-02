package memalloc

import (
	"testing"

	"github.com/stretchr/testify/assert"
)

func TestMemAlloc(t *testing.T) {
	a := NewAllocator(10)
	r := a.Allocate(10)
	assert.Equal(t, r, Region{0, 10})
	assert.Nil(t, a.Free(Region{0, 10}))
}
