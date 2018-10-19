# Matilda
Matilda is a new programming language that's not designed to be unique or groundbreaking. Instead, Matilda takes already 
established technologies and paradigms and just makes them **nicer**.

## Example
This is a very trivial example, but it displays Matilda's philosophy quite well. Take a simple matching function.
**Java**:
```
bool matchWith(Object x, Object y) {
    return x == y;
}

matchWith(2, 2); // true
```

**Matilda**:
```
fun match (x) with (y):
    return x == y
end

match 2 with 2 // true
```
