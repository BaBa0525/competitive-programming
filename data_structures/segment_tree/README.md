# Segment Tree

## Usage

Segment Tree can be used to provide efficient range query (usually min/max/consecutive sum) and update for an query.

## Complexity

- Initial build: `O(n)`
- Update: `O(logn)`
- Query: `O(logn)`

## Comparison

In fact, we can do range sum using two fenwick tree. However, segment tree can also be used in invertible actions, such as min and max.

## Implementation

- [Top down approach](top_down.cpp)
- Binary indexed tree (TODO)
