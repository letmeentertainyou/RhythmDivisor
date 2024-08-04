/*
The intDiv function comes from random.js linked below.
https://github.com/oittaa/random-browser-js/

It is licensed under MIT here:
https://github.com/oittaa/random-browser-js/blob/main/LICENSE

Copyright (c) 2022 oittaa
*/
const intDiv = (a, b) => (a - (a % b)) / b;

function sum(iterable) {
    /* Sums an array. */
    var total = 0;
    for (let x of iterable) {
        total += x;
    }
    return total;
}

function rhythmPermutations(start = [2, 3, 4], size = 8) {
    /* 
    Returns an array of all permutations including duplicates of the starting array with a given size.
    start = starting array of unique digits
    size = desired sum of the output permutations
    */
    var max_length = intDiv(size, 2);
    var old = [];
    var results = [];

    for (let i of start) {
        old.push([i]);
        if (i == size) {
            results.push([i]);
        }
    }

    for (let length = 1; length < max_length; length++) {
        var tmp = [];
        for (let digit of start) {
            for (let tail of old) {
                var perm = [digit, ...tail];
                var sum_perm = sum(perm);

                if (sum_perm == size) {
                    results.push(perm);
                    continue;
                }
                if (sum_perm == size - 1) {
                    continue;
                }
                if (sum_perm < size) {
                    tmp.push(perm);
                }
            }
        }
        old = tmp;
    }
    return results;
}


// This is just a demo, you can modify or remove it.
var start = [2, 3, 4]
var size = 8
console.log(rhythmPermutations(start, size))
