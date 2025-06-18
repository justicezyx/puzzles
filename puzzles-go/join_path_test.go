package puzzles

import (
	"testing"

	"github.com/stretchr/testify/assert"
)

func TestCD(t *testing.T) {
	assert.Equal(t, cd("/a/b/c/d", "/a/b/c/d"), "/a/b/c/d/a/b/c/d")
	assert.Equal(t, cd("/home/bugs", "lola/basketball"), "")
	assert.Equal(t, cd("/home/bugs", "."), "")
	assert.Equal(t, cd("/home/bugs", "bunny"), "")
	assert.Equal(t, cd("/home/bugs", "../daffy"), "")
	assert.Equal(t, cd("/home/foo/bar/baz", ".."), "")
}
