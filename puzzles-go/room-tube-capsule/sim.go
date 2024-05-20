package rtc

import "fmt"

type Capsule struct {
	opts []string
}

type Tube struct {
	s *Room
	d *Room
}

type Room struct {
	opt *Operator
	tubes []Tube
}

type Operator struct {
	room *Room
}

// Send a capsule to start the process to collect the names of all operators.
func (o *Operator) Init() {
	// TBA
}
