package puzzles

import (
	"reflect"
	"strings"
	"testing"
)

func TestFindLineWords(t *testing.T) {
	words := []string{"I", "am", "a", "hero"}
	line := findLineWords(words, 4)
	if reflect.DeepEqual(line, []string{"I", "am"}) {
		t.Errorf("failed to get line, got: %v", line)
	}
}

func TestRepeat(t *testing.T) {
	if got := repeat(' ', 5); got != "     " {
		t.Errorf("Repeating space 5 times, got: %s", got)
	}
}

func TestFormat(t *testing.T) {
	if got := formatLine([]string{"I", "am", "a", "hero"}, 21); got != "I     am    a    hero" || len(got) != 21 {
		t.Errorf("Format I am failed, got: %s", got)
	}
}

func TestFullJustify(t *testing.T) {
	words := []string{
		"What", "must", "be", "acknowledgment", "shall", "be",
	}
	if got := fullJustify(words, 16); len(got) != 21 {
		t.Errorf("Format I am failed, got: %s", strings.Join(got, ", "))
	}
}
