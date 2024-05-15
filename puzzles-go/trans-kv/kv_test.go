package kv

import (
	"fmt"
	"testing"
)

func TestTransLog(t *testing.T) {
	l := newTransLog()
	o := op {
		isBegin: true,
	}
	l.do(o)
	l.do(o)
	l.do(o)

	fmt.Println("l:", l)

	if err := l.clearAt(3); err != outOfRangeError {
		t.Errorf("Expect error, got %v expected %v", err, outOfRangeError)
	}

	if err := l.clearAt(0); err != nil || !l.isEmpty() {
		t.Errorf("Expect empty")
	}
}

func TestStoreTrans(t *testing.T) {
	s := New[int]()
	s.Begin()
	s.Put("a", 50)
	s.Begin()
	s.Put("a", 60)
	s.Rollback()
	s.Begin()
	s.Begin()
	s.Commit()
	s.Commit()
	s.Begin()
	s.Commit()
	s.Commit()

	if v, ok := s.get("a"); !ok || v != 50 {
		t.Errorf("key 'a' should return 50, got %d", v)
	}

	if err := s.Commit(); err == nil {
		t.Errorf("Commit without begin should return error, got nil")
	}
}
