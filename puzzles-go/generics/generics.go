package main

import "fmt"

func sumInts(ints []int) int {
	res := 0
	for _, i := range ints {
		res += i
	}
	return res
}

func sumStrInts(m map[string]int64) int64 {
	var res int64 = 0
	for _, v := range m {
		res += v
	}
	return res
}

func sumStrFloats(m map[string]float64) float64 {
	var res float64 = 0.0
	for _, v := range m {
		res += v
	}
	return res
}

func sumMap[K comparable, V int64|float64](m map[K]V) V {
	var res V
	for _, v := range m {
		res += v
	}
	return res
}

func main() {
	ints := []int{1, 2, 3, 4, 5}
	int64M := map[string]int64{"a":1, "b":2, "c":3, "d":4, "e":5}
	float64M := map[string]float64{"a":1, "b":2, "c":3, "d":4, "e":5}
	fmt.Println(sumInts(ints))
	fmt.Println(sumStrInts(int64M))
	fmt.Println(sumStrFloats(float64M))
	fmt.Println(sumMap[string, int64](int64M))
	fmt.Println(sumMap[string, float64](int64M))
}
