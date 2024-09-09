


The `extern` keyword in C is used to declare a global variable or function that is defined in another file or translation unit. It tells the compiler that the variable or function exists and is defined elsewhere. This is primarily used for **sharing global variables or functions** between multiple files.

### **Key Uses of `extern`**

1. **Access Global Variables Across Multiple Files**:
   - When working on large programs that span multiple source files, you can use `extern` to access a global variable defined in one file from another file.

2. **Function Declarations**:
   - Functions in C are implicitly declared as `extern` by default, meaning you don’t need to explicitly use `extern` for function declarations. However, you can still use it for clarity.

3. **Linkage**:
   - The `extern` keyword specifies **external linkage**, meaning the variable or function can be referenced by other translation units (source files).

### **How `extern` Works**

- **Without `extern`**, a global variable or function is limited to the file in which it is defined (internal linkage with `static`).
- **With `extern`**, the variable or function can be used in multiple files by declaring it as `extern` where needed.

### **Example of Using `extern`**

#### 1. **Global Variable Across Multiple Files**

Let’s see an example of sharing a global variable across two files using `extern`.

- **file1.c** (Defines the variable):
  ```c
  // file1.c
  #include <stdio.h>

  // Define the global variable
  int shared_variable = 10;

  void print_from_file1() {
      printf("shared_variable in file1.c: %d\n", shared_variable);
  }
  ```

- **file2.c** (Uses `extern` to declare the variable):
  ```c
  // file2.c
  #include <stdio.h>

  // Declare the global variable from file1.c
  extern int shared_variable;

  void print_from_file2() {
      printf("shared_variable in file2.c: %d\n", shared_variable);
  }
  ```

- **main.c** (Main program to use the variable across files):
  ```c
  // main.c
  void print_from_file1();
  void print_from_file2();

  int main() {
      print_from_file1();  // Access from file1.c
      print_from_file2();  // Access from file2.c
      return 0;
  }
  ```

In this example:
- **file1.c** defines the global variable `shared_variable`.
- **file2.c** uses `extern` to reference `shared_variable`, allowing it to access the variable without redefining it.
- The **main.c** file calls functions from both files to demonstrate shared access to the global variable.

#### **Compiling**:
You can compile these files together like this:
```bash
gcc file1.c file2.c main.c -o program
```

#### **Output**:
```
shared_variable in file1.c: 10
shared_variable in file2.c: 10
```

#### 2. **Extern with Function Declaration**:
Even though functions in C are implicitly `extern` by default, you can explicitly declare them as `extern` for clarity.

- **file1.c**:
  ```c
  #include <stdio.h>

  void func() {
      printf("Hello from func in file1.c!\n");
  }
  ```

- **file2.c**:
  ```c
  extern void func();  // Explicit extern declaration

  int main() {
      func();  // Calls func from file1.c
      return 0;
  }
  ```

This allows `func()` defined in **file1.c** to be called from **file2.c** using the `extern` declaration.

### **When to Use `extern`**

1. **Global Variables Across Multiple Files**:
   - When you need to access a global variable across different source files, `extern` is necessary.

2. **Shared Functions (Optional)**:
   - Though functions are `extern` by default, it can sometimes help to explicitly declare them as `extern` for clarity or style.

3. **Avoiding Redefinition Errors**:
   - Use `extern` to declare a variable without allocating memory for it multiple times. Defining a variable in multiple files without `extern` will lead to a linker error (duplicate definition).

### **Common Pitfalls**

1. **Multiple Definitions**:
   - A variable should be **defined** only once in a program. If it is defined in multiple files, you will get linker errors. Use `extern` in all but one file to avoid this.
   
2. **Uninitialized `extern` Variables**:
   - If you declare a variable as `extern` without defining it somewhere, you’ll get a linker error when trying to use it.
   
   ```c
   extern int var;  // Declared but not defined anywhere
   ```

3. **Static vs Extern**:
   - A variable declared as `static` in a file has internal linkage, meaning it cannot be accessed by other files. If you need a variable to be accessed across files, don’t use `static`, use `extern`.

---

### **Conclusion**

- **`extern`** is used to declare variables or functions defined in other files.
- It enables **sharing global variables** and **functions across multiple source files**.
- **Global variables** should be declared with `extern` in all files except the one in which they are defined.
- Functions are implicitly `extern`, but you can declare them explicitly for clarity.

`extern` is crucial in C when working with large programs split across multiple files, allowing you to manage global data and functions cleanly across different translation units.