# Week3 Assignments

## Problems

### Canva Printing

`Huffman encoding`

Huffman encoding is an efficient method used for lossless data compression. It assigns variable-length codes to input characters based on their frequencies, with more frequent characters having shorter codes. This encoding technique minimizes the total number of bits required to represent the data, making it optimal for compression.

> The sum of weights of internal nodes are the total bits needed to encode the whole paragraph.

### Sim

`list`

- using `std::prev` and `std::next` to move iterator (std::ranges::prev/next in `C++20`)
- list only takes O(1) to insert at any position
- list may take much longer time for unable to utilize spacial locality

### Hex

`string`

- `std::tolower`
- `std::isxdigit` - checks if character is in `0123456789abcdefABCDEF`
- `std::from_chars` - transform a string into number with specified base (but need to skip 0x for hex case)

### Circuit

`stack` `postorder`

- `std::bitset`

### Ceremony

`greedy`

If we have chance to destroy a building, the best choice must be the highest one. Therefore, we only need to explore all the combinations of horizotal and vertical destruction.

### Bank

`greedy`

- `std::set`
- `std::set::upperbound` - find the first element that is greater than key
- `std::set::lowerbound` - find the first element that is not less than key

### Amoebas

`BFS`

Remove the loop utilizing BFS.

## Links

- [Opening Ceremony](https://open.kattis.com/problems/ceremony)
- [Backspace](https://open.kattis.com/problems/backspace)
- [Bacon, Eggs, and Spam](https://open.kattis.com/problems/baconeggsandspam)
- [Paring Hex](https://open.kattis.com/problems/parsinghex)
- [Canvas Painting](https://open.kattis.com/problems/canvas)
- [Bank Queue](https://open.kattis.com/problems/bank)
- [Gear Changing](https://open.kattis.com/problems/gearchanging)
- [Sim](https://open.kattis.com/problems/sim)
- [Delimiter Soup](https://open.kattis.com/problems/delimitersoup)
- [Circuit Math](https://open.kattis.com/problems/circuitmath)
- [Sheba's Amoebas](https://open.kattis.com/problems/amoebas)
