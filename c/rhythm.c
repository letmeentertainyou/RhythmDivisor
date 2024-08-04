#include "rhythm.h"


Array *rhythm_permutations(Array* start, int size) {
    /* 
    Returns an array of all permutations including duplicates of the starting array with a given size.
    start = starting array of unique digits
    size = desired sum of the output permutations
    */
    Array *old = empty_array(1);
    Array *tmp = empty_array(1);
    Array *tail = empty_array(1);
    Array *perm = empty_array(1);
    Array *results = empty_array(1);
    int max_length = size / 2;

    for (int i = 0; i < start->length; i++) {
        old = append_pad(old, start->values[i]);
    }

    for (int length = 0; length < max_length; length++) {
        for (int start_idx = 0; start_idx < start->length; start_idx ++) {
            int digit = start->values[start_idx];

            for (int old_idx = 0; old_idx < old->length; old_idx++) {
                int value = old->values[old_idx];
                
                if (value != 0) {
                    tail = append(tail, value);
                } else {
                    clear_array(perm);
                    perm = append(perm, digit);
                    perm = extend(perm, tail);
                    clear_array(tail);

                    int sum_perm = sum_array(perm);
                    if (sum_perm == size) {
                        results = extend_pad(results, perm);
                        continue;
                    }
                    if (sum_perm == size - 1) {
                        continue;
                    }
                    if (sum_perm < size) {
                        tmp = extend_pad(tmp, perm);
                    }
                }
            }
            clear_array(tail);
        }
        Array* swap = old;
        old = tmp;
        tmp = swap;
        clear_array(tmp);
    }
    free(start);
    free(old);
    free(tmp);
    free(tail);
    free(perm);
    return results;
}


// This is just a demo, you can modify or remove it.
int main()  {
    Array *start = array_from_array((int[]){2, 3, 4}, 3);
    int size = 8;
    print_array(rhythm_permutations(start, size));
    return 0;
}
