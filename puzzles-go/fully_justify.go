package puzzles

import (
	"fmt"
	"strings"
)

func findLineWords(words []string, maxWidth int) []string {
	if len(words) == 0 {
		return nil
	}
	curLen := len(words[0])
	for i := 1; i < len(words); i++ {
		newLen := curLen + len(words[i]) + 1
		if newLen == maxWidth {
			return words[:i+1]
		}
		if newLen > maxWidth {
			return words[:i]
		}
		curLen = newLen
	}
	return words
}

func repeat(r rune, count int) string {
	var b strings.Builder
	b.Grow(count)
	for i := 0; i < count; i++ {
		b.WriteRune(r)
	}
	return b.String()
}

func getWordsLen(words []string) int {
	res := 0
	for _, word := range words {
		res += len(word)
	}
	return res
}

func rightPad(word string, maxWidth int) string {
	return word + repeat(' ', maxWidth-len(word))
}

func formatLine(words []string, maxWidth int) string {
	if len(words) == 0 {
		return repeat(' ', maxWidth)
	}
	if len(words) == 1 {
		return rightPad(words[0], maxWidth)
	}
	wordsLen := getWordsLen(words)
	avgLen := (maxWidth - wordsLen) / (len(words) - 1)
	reminder := (maxWidth - wordsLen) % (len(words) - 1)
	var b strings.Builder
	b.Grow(maxWidth)
	b.WriteString(words[0])
	for i := 1; i < len(words); i++ {
		if i <= reminder {
			b.WriteString(repeat(' ', avgLen+1))
		} else {
			b.WriteString(repeat(' ', avgLen))
		}
		b.WriteString(words[i])
	}
	fmt.Println("b.String():", b.String())
	return rightPad(b.String(), maxWidth)
}

func fullJustify(words []string, maxWidth int) []string {
	res := make([]string, 0)
	// Find words on one line with length not exceeding maxWidth
	lines := make([][]string, 0)
	for len(words) > 0 {
		line := findLineWords(words, maxWidth)
		lines = append(lines, line)
		if len(line) <= len(words) {
			words = words[len(line):]
		} else {
			words = nil
		}
	}
	for i := 0; i < len(lines)-1; i++ {
		line := formatLine(lines[i], maxWidth)
		fmt.Printf("line: '%s' lines[i]: '%s' maxWidth=%d\n", line, lines[i], maxWidth)
		res = append(res, line)
	}
	res = append(res, rightPad(strings.Join(lines[len(lines)-1], " "), maxWidth))
	return res
}
