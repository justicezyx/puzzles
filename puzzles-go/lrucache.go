package puzzles

import (
	"container/list"
	"time"
)

type item struct {
	v int
	// The pointer to the key and ts entry in the back reference.
	// Back reference is a convenient way to find the oldest elements.
	backRef *list.Element
}

func Now() int64 {
	// UnixNano returns t as a Unix time, the number of nanoseconds elapsed since January 1, 1970 UTC.
	return time.Now().UnixNano()
}

type keyTs struct {
	k  int
	ts int64
}

type lruCache struct {
	items     map[int]item
	keyTsList *list.List
	capacity  int
}

func (c *lruCache) setVal(k, v int) {
	if _, ok := c.items[k]; !ok && len(c.items) >= c.capacity {
		// Remove back reference
		backRef := c.keyTsList.Front()
		c.keyTsList.Remove(backRef)
		delete(c.items, backRef.Value.(keyTs).k)
	}
	now := Now()
	c.keyTsList.PushBack(keyTs{k, now})
	c.items[k] = item{v, c.keyTsList.Back()}
}

func (c *lruCache) getVal(k int) (int, bool) {
	if item, ok := c.items[k]; ok {
		return item.v, true
	}
	return 0, false
}
