A C++ console application that lets you manage a collection of students through a simple menu-driven interface.
It demonstrates binary search tree concepts using two core classes: `Node` and `BinTree`.

## Project Structure

| File | Description |
|------|-------------|
| `node.h` / `node.cpp` | Defines the `Node` class, which holds a `Student` and handles BST logic |
| `bin_tree.h` / `bin_tree.cpp` | Defines the `BinTree` class, which manages the tree as a whole |
| `main.cpp` | Handles the menu and user interaction |

## How It Works

On startup, the program creates an empty binary search tree.
The user is presented with a menu of 7 options:

| Option | Description |
|--------|-------------|
| 1 - Insert a student | Prompts for a student number and name, then inserts them into the tree |
| 2 - Check minimum tree height | Displays the theoretical minimum height of the tree given its size |
| 3 - Check number of students | Displays the total number of students currently in the tree |
| 4 - Check number existence | Checks whether a student with a given number exists in the tree |
| 5 - Check student information, by order | Lists all students in ascending order by student number |
| 6 - Delete a student | Removes the student associated with a given number from the tree |
| 7 - Exit | Ends the program |

## Classes Overview

### `Node`
- Stores a `Student` (number and name) and pointers to `left` and `right` children
- Handles recursive BST insertion, removal, search, and in-order traversal
- Supports: `add`, `remove`, `contains`, and `inOrder`

### `BinTree`
- Manages the root node and tracks `_size` and `_height`
- Validates that names are non-empty, contain only letters and spaces, and have no leading or trailing spaces
- Minimum height is calculated as `log2(size)`, updated on each insertion or removal
- Supports: `add`, `remove`, `contains`, `size`, `height`, and `inOrder`

## Building

### Windows (Git Bash)
```bash
mingw32-make
```

### Linux/macOS
```bash
make
```

## Running

### Windows (Git Bash)
```bash
./student-bst
```

### Linux/macOS
```bash
./student-bst
```

## Notes

- Student numbers must be unique. Duplicate entries are rejected.
- Names must contain only letters and spaces, with no leading or trailing spaces.
- Input validation is handled throughout. Invalid entries prompt the user to try again without crashing.
