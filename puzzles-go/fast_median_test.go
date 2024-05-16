package puzzles

import (
	"fmt"
	"testing"
)

func TestFastMedia(t *testing.T) {
	mf := NewMedianFinder()
	mf.addNum(2)
	mf.addNum(3)
	mf.addNum(4)
	mf.addNum(5)
	mf.addNum(5)
	mf.addNum(5)
	mf.addNum(5)
	mf.addNum(5)
	mf.addNum(5)
	mf.addNum(5)
	mf.addNum(7)
	fmt.Println(mf.findMedian())
}
