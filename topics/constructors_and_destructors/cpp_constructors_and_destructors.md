# C++ constructors and destructors

## Table of contents

- [Introduction](#introduction)
- [Constructors and operators](#constructors-and-operators)
    - [Default constructor](#default-constructor)
    - [Parameterized constructor](#parameterized-constructor)
    - [Copy constructor](#copy-constructor)
    - [Copy assignment operator](#copy-assignment-operator)
    - [Move constructor](#move-constructor)
    - [Move assignment operator](#move-assignment-operator)
- [Destructor](#destructor)
- [Rules of Zero, Three, and Five](#rules-of-zero-three-and-five)
    - [Rule of Zero](#rule-of-zero)
    - [Rule of Three](#rule-of-three)
    - [Rule of Five](#rule-of-five)
- [Compiler-generated special member functions](#compiler-generated-special-member-functions)
- [Using `= default` and `= delete`](#using--default-and--delete)
- [Best practices](#best-practices)
- [Code example](#code-example)

## Introduction

In C++, **constructors** and **destructors** are special member functions that control the lifetime of objects. They define:

- How objects are created.
- How objects are copied.
- How objects are moved.
- How objects are assigned.
- How objects are destroyed.

Modern C++ (C++11 and later) defines six special member functions:

- Default constructor.
- Parameterized constructor.
- Copy constructor.
- Copy assignment operator.
- Move constructor.
- Move assignment operator.
- Destructor.

The following class will be used throughout this guide:

```c++
class Person {
public:
    // Default constructor.
    Person();
    // Parameterized constructor.
    Person(std::string name, int age);

    // Copy constructor.
    Person(const Person& other);
    // Copy assignment operator.
    Person& operator=(const Person& other);

    // Move constructor.
    Person(Person&& other) noexcept;
    // Move assignment operator.
    Person& operator=(Person&& other) noexcept;

    // Destructor.
    ~Person();

private:
    std::string name_;
    int age_;
};
```

`std::string` already manages its own memory, so this class does not manually manage resources.

In a real C++ project, this class would normally use the **Rule of Zero** (this concept will be explained later) and allow the compiler to generate most of these functions automatically. However, they are explicitly declared here to demonstrate how each special member function works.

## Constructors and operators

### Default constructor

The default constructor creates an object without receiving any argument.

Declaration:

```c++
Person();
```

Implementation:

```c++
Person::Person()
    : name_{"Unknown"}
    , age_{0}
{
}
```

Usage:

```c++
Person person;
```

The object is initialized with default values.

If no constructor is declared, the compiler automatically generates a default constructor.

### Parameterized constructor

A parameterized constructor initializes an object using the arguments provided to it.

Declaration:

```c++
Person(std::string name, int age);
```

Implementation:

```c++
Person::Person(std::string name, int age)
    : name_{std::move(name)}
    , age_{age}
{
}
```

Usage:

```c++
Person person{"Harry", 42};
```

### Copy constructor

The copy constructor creates a **new object** from another object.

Declaration:

```c++
Person(const Person& other);
```

Implementation:

```c++
Person::Person(const Person& other)
    : name_{other.name_}
    , age_{other.age_}
{
}
```

Usage:

```c++
Person person1{"Harry", 42};
Person person2{person1};
// Or "Person person2 = person1;"
```

A copy constructor is called because `person2` is being created.

### Copy assignment operator

The copy assignment operator copies data into an object that already exists.

Declaration:

```c++
Person& operator=(const Person& other);
```

Implementation:

```c++
Person& Person::operator=(const Person& other)
{
    if (this != &other) {
        name_ = other.name_;
        age_ = other.age_;
    }

    return *this;
}
```

Usage:

```c++
Person person1{"Harry", 42};
Person person2{"Alice", 21};
person2 = person1;
```

The condition `if (this != &other)` is called a *self-assignment check*, and it prevents problems when an object is assigned to itself:

```c++
Person person("Harry", 42);
person = person;
```

For simple classes like `Person`, self-assignment is safe because `std::string` handles it correctly, so this condition would not be needed here. However, the check was used just to mention that it is commonly used in custom assignment operators when classes manually manage resources, because this assignment may fail without this check on this situation.

### Move constructor

The move constructor creates a new object by transferring data from another object.

Declaration:

```c++
Person(Person&& other) noexcept;
```

Implementation:

```c++
Person::Person(Person&& other) noexcept
    : name_{std::move(other.name_)}
    , age_{other.age_}
{
}
```

Usage:

```c++
Person person1{"Harry", 42};
Person person2{std::move(person1)};
```

Move construction avoids unnecessary copying and the original object remains valid, but its contents may no longer be the same, so it should **not** be used after moving it.

### Move assignment operator

The move assignment operator transfers data into an already existing object.

Declaration:

```c++
Person& operator=(Person&& other) noexcept;
```

Implementation:

```c++
Person& Person::operator=(Person&& other) noexcept
{
    if (this != &other) {
        name_ = std::move(other.name_);
        age_ = other.age_;
    }

    return *this;
}
```

Usage:

```c++
Person person1{"Harry", 42};
Person person2{"Alice", 21};
person2 = std::move(person1);
```

## Destructor

The destructor is called automatically when an object is destroyed.

Declaration:

```c++
~Person();
```

For this class, the default destructor is enough (`std::string` manages its own resources, so `Person` does not need a custom destructor):

```c++
~Person() = default;
```

A destructor:

- Has no return type.
- Has no parameters.
- Cannot be overloaded.
- Is automatically called.

Example:

```c++
{
    Person person("Harry", 42);
}
// Destructor is called here because person goes out-of-scope.
```

## Rules of Zero, Three, and Five

These rules describe when a class should define special member functions.

### Rule of Zero

A class should avoid manually defining special member functions when it does not directly manage resources. When possible, use types that already manage resources, like `std::string`, `std::vector`, `std::unique_ptr` or `std::shared_ptr`. For example, the compiler-generated functions for the `Person` class are already correct.

The Rule of Zero is the preferred Modern C++ approach because it allows:

- Less code.
- Fewer bugs.
- Easier maintenance.
- Safer resource management.

### Rule of Three

The Rule of Three states that if a class defines any of the following then it should probably explicitly define all three:

- Destructor,
- Copy constructor.
- Copy assignment operator.

### Rule of Five

The Rule of Five extends the Rule of Three by adding move semantics:

- Destructor.
- Copy constructor.
- Copy assignment operator.
- Move constructor.
- Move assignment operator.

## Compiler-generated special member functions

The compiler automatically generates special member functions when possible. Declaring one special member function can prevent others from being generated, as shown in the table below.

| What you write \ What you get | Default constructor |  Destructor | Copy constructor | Copy assignment | Move constructor | Move assignment |
| --- | :---: | :---: | :---: | :---: | :---: | :---: |
| **Nothing** | Defaulted | Defaulted | Defaulted | Defaulted | Defaulted | Defaulted |
| **Any constructor** | Not declared | Defaulted | Defaulted | Defaulted | Defaulted | Defaulted |
| **Default constructor** | User declared | Defaulted | Defaulted | Defaulted | Defaulted | Defaulted |
| **Destructor** | Defaulted | User declared | Deprecated | Deprecated | Not declared | Not declared |
| **Copy constructor** | Not declared | Defaulted | User declared | Deprecated | Not declared | Not declared |
| **Copy assignment** | Defaulted | Defaulted | Deprecated | User declared | Not declared | Not declared |
| **Move constructor** | Not declared | Defaulted | Not declared | Not declared | User declared | Not declared |
| **Move assignment** | Defaulted | Defaulted | Not declared | Not declared | Not declared | User declared |

## Using `= default` and `= delete`

C++ allows explicit control over compiler-generated functions.

Use `= default` when the compiler-generated implementation is correct. For example:

```c++
class Person {
public:
    Person() = default;
    ~Person() = default;
};
```

Use `= delete` when an operation should not be allowed. For example:

```c++
class Person {
public:
    Person(const Person&) = default;
    Person& operator=(const Person&) = delete;
};
```

## Best practices

- Prefer the **Rule of Zero** whenever possible.
- Use standard library types instead of manually managing resources.
- Only implement the Rule of Five when a class truly owns a resource.
- Use constructor initializer lists.
- Prefer moving expensive objects when appropriate.
- Mark move constructors and move assignment operators as `noexcept` when possible.
- Use `= default` to explicitly request compiler behavior.
- Use `= delete` to disable unwanted operations.
- Use self-assignment checks in custom assignment operators.

## Code example

A code example that is based on the example class used in this guide is available [here](src/main.cpp).
