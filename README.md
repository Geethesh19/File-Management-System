# File Management System Using Threaded Binary Search Tree
## Overview
This project is a **File Management System** implemented using a **Threaded Binary Search Tree (TBST)** in C. The system allows users to manage files by adding, deleting, and displaying them in sorted order (inorder traversal). The application is menu-driven, providing an interactive way to perform operations on the files.

## Features
- **Add File**: Insert a file into the tree. Files are stored in sorted order by name.
- **Delete File**: Remove a file from the tree using its name.
- **Display All Files**: List all files in sorted order (inorder traversal).
- **Exit**: Quit the application.

## File Structure
Each file in the system is represented by the `File` class, which includes the following attributes:
- **Name**: The name of the file.
- **Size**: The size of the file in KB.
- **Type**: The type of the file (e.g., `.txt`, `.jpg`, etc.).

## Implementation Details

### Threaded Binary Search Tree (TBST)
- Uses threads to maintain links to predecessor and successor nodes.
- Ensures efficient inorder traversal without requiring recursion or a stack.

### Node Class
- Represents individual nodes in the TBST.
- Contains file information, left and right pointers, and thread flags (`lthread` and `rthread`).

### Operations
1. **Insertion**: Adds a new file while maintaining TBST properties.
2. **Deletion**: Handles three cases:
   - Node with no children (leaf).
   - Node with one child.
   - Node with two children (replaced by its inorder successor).
3. **Inorder Traversal**: Displays files in sorted order.

---

## How to Run
### Compile the code using a C compiler:
```bash
gcc -o FileManagementSystem FileManagementSystem.c
```
### Run the executable:
```bash
./FileManagementSystem
```

## User Guide

### Menu Options:
Select options from the menu to perform desired operations:
1. **Add File**: Add a file by providing its name, size, and type.
2. **Delete File**: Delete a file by entering its name.
3. **Display All Files**: Display all files in sorted order (inorder traversal).
4. **Exit**: Exit the program.

### Input/Output Example:

#### Add File:
```plaintext
Enter file name: file1  
Enter file size (in KB): 100  
Enter file type: txt

File "file1" inserted successfully.  
```

### Delete File:
```plaintext
Enter the file name to delete: file1

File "file1" deleted successfully.
```

### Display Files:
```plaintext
File Name: file1  
Size: 100 KB  
Type: txt
```

## Example Run:
```plaintext
File Management System  
1. Add File  
2. Delete File  
3. Display All Files (Inorder)  
4. Quit  
Enter your choice: 1  
Enter file name: file1  
Enter file size (in KB): 100  
Enter file type: txt

File "file1" inserted successfully.  

Enter your choice: 1  
Enter file name: file2  
Enter file size (in KB): 200  
Enter file type: jpg

File "file2" inserted successfully.  

Enter your choice: 3
 
File Name: file1  
Size: 100 KB  
Type: txt

File Name: file2  
Size: 200 KB  
Type: jpg  

Enter your choice: 2  
Enter the file name to delete: file1

File "file1" deleted successfully.  

Enter your choice: 3

File Name: file2  
Size: 200 KB  
Type: jpg  

Enter your choice: 4

Exiting...  
```

## Key Functions

### `insert(const File& file)`
- Adds a new file to the tree.
- Maintains the TBST structure.

### `remove(const string& fname)`
- Deletes a file by name.
- Handles all edge cases for TBST deletion.

### `displayInorder()`
- Traverses the tree in sorted order using threads.

### Helper Functions:
- **`inSucc(Node* ptr)`**: Finds the inorder successor.
- **`inPred(Node* ptr)`**: Finds the inorder predecessor.
- **`caseA`, `caseB`, `caseC`**: Handle deletion cases.

## Requirements:
- **Compiler:** Any modern C compiler (e.g., GCC, Clang).
- **OS:** Platform-independent (Windows, macOS, Linux).

## Future Enhancements
- Support for searching files by attributes (e.g., size, type).
- Add functionality to update file attributes.
- Improve UI for better user interaction.
