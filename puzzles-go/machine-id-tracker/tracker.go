package tracker

import (
	"fmt"
	"log"
	"strings"
	"strconv"
	"container/heap"
)

// The ID of the machine
type MachineID struct {
	// Example: app, web, db etc.
	category string

	// The index of the machine in the category of the machines
	index int
}

func parseMachineID(mID string) (MachineID, error) {
	fields := strings.Split(mID, "-")
	if len(fields) != 2 {
		return MachineID{}, fmt.Errorf("Invalid format, expect <type>-<index>, got %s", mID)
	}
	idx, err := strconv.Atoi(fields[1])
	if err != nil {
		return MachineID{}, err
	}
	return MachineID {fields[0], idx}, nil
}

type minIntHeap []int

func (h minIntHeap) Less(i, j int) bool {
	return h[i] < h[j]
}

func (h minIntHeap) Len() int {
	return len(h)
}

func (h minIntHeap) Swap(i, j int) {
	h[i], h[j] = h[j], h[i]
}

func (h *minIntHeap) Push(v any) {
	*h = append(*h, v.(int))
}

func (h *minIntHeap) Pop() any {
	v := (*h)[h.Len()-1]
	*h = (*h)[0:h.Len()-1]
	return v
}

type MachineIndexTracker struct {
	maxIndex int
	recycledIndex minIntHeap
}

func newMachineIndexTracker() *MachineIndexTracker {
	return &MachineIndexTracker {
		maxIndex: 0,
		recycledIndex: make(minIntHeap, 0),
	}
}

func (t *MachineIndexTracker) allocate() int {
	if len(t.recycledIndex) == 0 {
		t.maxIndex += 1
		return t.maxIndex
	}
	idx := heap.Pop(&t.recycledIndex).(int)
	return idx
}

func (t *MachineIndexTracker) deallocate(i int) {
	heap.Push(&t.recycledIndex, i)
}

// Add an used index
func (t *MachineIndexTracker) add(i int) {
	t.maxIndex = max(t.maxIndex, i)
}

type MachineIDTracker struct {
	catIDMap map[string]*MachineIndexTracker
}

func (t *MachineIDTracker) getOrCreateIdxTracker(cat string) *MachineIndexTracker {
	if tracker, ok := t.catIDMap[cat]; ok {
		return tracker
	}
	tracker := newMachineIndexTracker()
	t.catIDMap[cat] = tracker
	return tracker
}

// Input machines' index must start from 1 and ends at n, no missing numbers in middle.
func newMachineIDTracker(machineIDs []string) *MachineIDTracker {
	t := &MachineIDTracker {
		catIDMap: make(map[string]*MachineIndexTracker),
	}
	for _, id := range machineIDs {
		mID, err := parseMachineID(id)
		if err != nil {
			log.Printf("Failed to parse machine ID: %s", id)
			continue
		}
		t.getOrCreateIdxTracker(mID.category)
	}
	return t
}

func (t *MachineIDTracker) allocate(cat string) string {
	idxTracker := t.getOrCreateIdxTracker(cat)
	idx := idxTracker.allocate()
	return cat + "-" + strconv.Itoa(idx)
}

func (t *MachineIDTracker) deallocate(id string) error {
	mID, err := parseMachineID(id)
	if err != nil {
		return fmt.Errorf("While deallocating ID %s, failed to parse the ID, error: %v", id, err)
	}
	idxTracker := t.getOrCreateIdxTracker(mID.category)
	idxTracker.deallocate(mID.index)
	return nil
}
