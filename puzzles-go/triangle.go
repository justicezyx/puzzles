package puzzles

type position struct {
	row, col int
}

func min(values []int) int {
	if len(values) == 0 {
		panic("empty value")
	}
	min := values[0]
	for i := 1; i < len(values); i++ {
		if values[i] < min {
			min = values[i]
		}
	}
	return min
}

// Return the minimal sum of values from 0,0 to i-th row and j-th column
func minTotalRecur(triangle [][]int, dest position, table map[position]int) int {
	dist, ok := table[dest]
	if ok {
		return dist
	}
	source := position{0, 0}
	if dest == source {
		return triangle[0][0]
	}
	prevRow := dest.row - 1
	prevCol := dest.col
	values := make([]int, 0)
	// The position is legitimate
	if prevCol <= prevRow {
		min := minTotalRecur(triangle, position{prevRow, prevCol}, table)
		values = append(values, min)
	}
	prevCol = dest.col - 1
	if prevCol >= 0 {
		min := minTotalRecur(triangle, position{prevRow, prevCol}, table)
		values = append(values, min)
	}
	res := min(values) + triangle[dest.row][dest.col]
	table[dest] = res
	return res
}

func minimumTotal(triangle [][]int) int {
	table := make(map[position]int)
	rowCount := len(triangle)
	partialMin := minTotalRecur(triangle, position{rowCount - 1, 0}, table)
	for i := 1; i < rowCount; i++ {
		min := minTotalRecur(triangle, position{rowCount - 1, i}, table)
		if min < partialMin {
			partialMin = min
		}
	}
	return partialMin
}
