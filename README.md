# AdaptiveHuffman--Algorithm V

In static Huffman, we need to transmit someway the model used for compression and we need to pass over the data twice. Some resechers proposed adaptive huffman to solve this problem. For Example, Algorithm V[1].

The key idea is to build a Huffman tree that is optimal for the part of the message already seen, and to reorganize it when needed, to maintain its optimality. The basis for algorithm V is the Sibling Property:
  - A binary code tree with nonnegative weights has the sibling property if each node (except the root) has a sibling and if
    the nodes can be numbered in order of nondecreasing weight with each node adjacent to its sibling.
  - Moreover the parent of a node is higher in the numbering.

## References
[1] Vitter J S. Design and analysis of dynamic Huffman codes[J]. Journal of the ACM (JACM), 1987, 34(4): 825-845.
