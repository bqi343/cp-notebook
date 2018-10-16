# Template Notes

- The header files will not compile with clang; use gcc instead.
- If you don't know what the following line does, see Range Queries --> README --> C++ STL for more information.

```cpp
template <class T> using Tree = tree<T, null_type, less<T>, rb_tree_tag,tree_order_statistics_node_update>;
```
