package puzzles

import (
	"container/list"
	"fmt"
	"testing"
)

func TestHelloWorld(t *testing.T) {
	c := lruCache{
		items:     make(map[int]item),
		keyTsList: list.New(),
		capacity:  3,
	}

	c.setVal(1, 1)
	if v, ok := c.getVal(1); !ok || v != 1 {
		t.Fail()
	}

	c.setVal(2, 1)
	fmt.Println(c)
}
