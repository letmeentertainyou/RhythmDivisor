This is a tool I built out of curiosity. I wanted to know how many different strum patterns
I could make with a given number of eighth notes. This comes up fairly often for musicians
when we want to create a new rhythm instead of all of the ones we've already learned. 

Strum patterns are often subdivided into groups of notes, I have called the array containing
all possible groups of notes "start" it looks like [2, 3, 4] in the default case. I chose this
set because really most strum patterns are made up of twos and threes with the occasional fours
thrown in. But you could add any numbers to this array - if you wanted for instance patterns of
only twos and fives you would use start=[2, 5] and if you wanted those patterns to have 11 eighth
notes you would called rhythmic_permutations(start=[2, 5], size=11). 

Do not include duplicate numbers in start. This algorithm creates the permutations with duplicate
digits using a start array of unique digits. That is one of the major changes to the traditional
permutations algorithm that I made. The others are for speed because while this problem looks like
a permutation it searches a much smaller space than N factorial.

Please feel free to use this function for any music related project, you can use this technique for
calculating any kind of rhythms not just strum patterns. While I have written this code with eighth
notes in mind, you can apply the numbers to any kind of measures or notes you want to.

This project includes versions written Go/Python/JS/C and even a C Python module. Each version contains
a run.sh script with the commands you need to build/run it.

Please let me know if you find any bugs or have any feature requests.
