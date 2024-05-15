package tracker

import (
	"fmt"
	"reflect"
	"testing"
)

func TestParseMachineID(t *testing.T) {
	mID, err := parseMachineID("test-1")
	if err != nil {
		t.Fail()
	}
	if !reflect.DeepEqual(mID, MachineID{"test", 1}) {
		t.Fail()
	}
}

func TestMachineIndexAllocate(t *testing.T) {
	tracker := newMachineIndexTracker()
	got := tracker.allocate()
	if got != 1 {
		t.Fail()
	}
	tracker.deallocate(1)
	got = tracker.allocate()
	if got != 1 {
		t.Fail()
	}
	fmt.Println(tracker)
}

func TestMachineIDTracker(t *testing.T) {
	tracker := newMachineIDTracker(nil)
	mID := tracker.allocate("web")
	if mID != "web-1" {
		t.Fail()
	}
	if tracker.allocate("web") != "web-2" {
		t.Fail()
	}
	tracker.deallocate("web-1")
	if tracker.allocate("web") != "web-1" {
		t.Fail()
	}
}

