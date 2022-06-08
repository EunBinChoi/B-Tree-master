# B-Tree-master
- B-Tree is implemented which is used for indexing in Database.

## What is B-tree?
- B-tree is a data structure that provides sorted data and allows searches, sequential access, attachments, and removals in sorted order. The B-tree is highly capable of storage systems that write large blocks of data. The B-tree simplifies the binary search tree by allowing nodes with more than two children.

## Why is Indexing Used in the Database?
- Imagine you need to store a list of numbers in a file and search a given number on that list. The simplest solution is to store data in an array and append values when new values come. But if you need to check if a given value exists in the array, then you need to search through all of the array elements one by one and check whether the given value exists. 

- How could you improve this time? The easiest solution is to sort the array and use binary search to find the value. Whenever you insert a value into the array, it should maintain order. Searching start by selecting a value from the middle of the array. Then compare the selected value with the search value. If the selected value is greater than search value, ignore the left side of the array and search the value on the right side and vice versa.

