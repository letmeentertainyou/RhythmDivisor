def rhythm_permutations(start=[2, 3, 4], size=8):
    """
    Returns an array of all permutations including duplicates of the starting array with a given size.
    start = starting array of unique digits
    size = desired sum of the output permutations
    """

    max_length = size // 2
    old = []
    results = []

    for i in start:
        old.append([i])
        if i == size:
            results.append([i])

    for length in range(1, max_length):
        tmp = []
        for digit in start:
            for tail in old:
                perm = [digit] + tail
                sum_perm = sum(perm)

                if sum_perm == size:
                    results.append(perm)
                    continue

                if sum_perm == size - 1:
                    continue

                if sum_perm < size:
                    tmp.append(perm)

        old = tmp
    return results


# This is just a demo, you can modify or remove it.
if __name__ == "__main__":
    start = [2, 3, 4]
    print(rhythm_permutations(start, 8))
