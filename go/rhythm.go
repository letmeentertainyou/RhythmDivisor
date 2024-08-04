package main

import (
    "fmt"
)


func sum(iterable[]int) int {
    /* Sums an array. */
    result := 0
    for _, num := range iterable {
        result += num
    }
    return result
}

func rhythmPermutations(start[]int, size int) [][]int {
    /*
    Returns an array of all permutations including duplicates of the starting array with a given size.
    start = starting array of unique digits
    size = desired sum of the output permutations
    */
    max_length  := size / 2
    old    := [][]int{}
    results := [][]int{}
    
    for _, i := range start {
        old    = append(old,    []int{i})
        if i == size {
            results = append(results, []int{i})
        }
    }

    for length := 1; length < max_length; length++ {
        tmp := [][]int{}
        for _, digit := range start {
            for _, tail := range old {
                perm := append([]int{digit}, tail...)
                sum_perm := sum(perm)

                if sum_perm == size {
                    results = append(results, perm)
                    continue
                }
                if sum_perm == size -1 {
                    continue
                }
                if sum_perm < size {
                    tmp = append(tmp, perm)
                }
            }
        }
        old = tmp
    }
    return results
}


// This is just a demo, you can modify or remove it.
func main() {
    start := []int{2, 3, 4}
    size := 8
    fmt.Println(rhythmPermutations(start, size))
}
