package kv

import "fmt"

var outOfRangeError error = fmt.Errorf("value is out of range")
var beginNotFoundError error = fmt.Errorf("There is no begin op")

// op describes an operation performed on the KV store
type op struct {
	isBegin bool
	isCommit bool
	action func()
}

func (o op) exec() {
	if o.isBegin || o.isCommit {
		return
	}
	o.action()
}

type transLog struct {
	logs []op
}

func newTransLog() transLog {
	return transLog {
		logs: make([]op, 0),
	}
}

func (t *transLog) isEmpty() bool {
	return len(t.logs) == 0
}

func (t *transLog) do(o op) {
	t.logs = append(t.logs, o)
}

func (t *transLog) peek(i int) op {
	return t.logs[i]
}

func (t *transLog) pop() {
	t.logs = t.logs[:len(t.logs)-1]
}

func (t *transLog) findBegin() (int, error) {
	for i := len(t.logs)-1; i >= 0; i-- {
		if t.logs[i].isBegin {
			return i, nil
		}
	}
	return -1, beginNotFoundError
}

// Clear all ops after the op at pos, include the op at pos.
func (t *transLog) clearAt(pos int) error {
	if pos < 0 || pos >= len(t.logs) {
		return outOfRangeError
	}
	t.logs = t.logs[:pos]
	return nil
}

type Store[ValT any] struct {
	// Stored items
	items map[string]ValT

	// Transactional logs
	logs transLog
}

func New[ValT any]() Store[ValT] {
	return Store[ValT] {
		items: make(map[string]ValT),
		logs: newTransLog(),
	}
}

func (s *Store[T]) get(k string) (T, bool) {
	v, ok := s.items[k]
	return v, ok
}

func (s *Store[T]) put(k string, v T) {
	s.items[k] = v
}

func (s *Store[T]) delete(k string) {
	delete(s.items, k)
}

func (s *Store[T]) Put(k string, v T) {
	o := op {
		action: func() { s.put(k, v) },
	}
	s.logs.do(o)
}

func (s *Store[T]) Delete(k string) {
	o := op {
		action: func() { s.delete(k) },
	}
	s.logs.do(o)
}

func (s *Store[T]) Begin() {
	o := op {
		isBegin: true,
	}
	s.logs.do(o)
}

func (s *Store[T]) Rollback() {
	b, err := s.logs.findBegin()
	if err != nil {
		return
	}
	s.logs.clearAt(b)
}

func (s *Store[T]) Commit() error {
	o := op {
		isCommit: true,
	}
	s.logs.do(o)

	bCount := 0
	cCount := 0
	for _, o := range s.logs.logs {
		if o.isBegin {
			bCount += 1
		}
		if o.isCommit {
			cCount += 1
		}
	}
	if cCount > bCount {
		s.logs.pop()
		return fmt.Errorf("Commit without beginning transaction")
	}
	if bCount == cCount {
		for _, o := range s.logs.logs {
			o.exec()
		}
		s.logs.clearAt(0)
		return nil
	}
	return nil
}
