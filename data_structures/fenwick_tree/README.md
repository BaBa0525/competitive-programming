# Fenwick Tree

## Usage

Prefix sum or range sum with all the actions in complexity `O(logn)`.

Complexity:

- initial build `O(n)`
- query `O(logn)`
- update `O(logn)`

## Comparison

If no updates, we can do prefix sum by an array.

```cpp
std::vector<int> s;

for (int i = 0; i < s.size(); i++) {
  if (i == 0) continue;
  s[i] += s[i - 1];
}
```

Complexity:

- initial build `O(n)`
- query `O(1)`
- update `O(n)`

## Reference

- [hackmd](https://hackmd.io/@wiwiho/cp-note/%2F%40wiwiho%2FCPN-binary-indexed-tree)
- [geeksforgeeks](https://www.geeksforgeeks.org/binary-indexed-tree-or-fenwick-tree-2/)
