# Code Review for Project 2

## 1. Project information

Project name: Sistem de gestionare a proprietatilor  
Author: Merdanov Ylham  
GitHub repository: https://github.com/MerdanovYlham/OOP-property-system  
Reviewer: Gurbanov Gadam

## 2. Short description of the project

This project is a simple property management system. The project tries to manage different types of real estate properties. The main examples are apartments, houses, and villas. The program can store these properties in an agency, display them, and calculate the total rent for a number of months.

In `main.cpp`, the program creates one `Apartament`, one `Casa`, and one `Vila`. These objects are added to an `Agentie` object. After that, the program displays all properties, calculates rent for 6 months, tests `dynamic_cast`, and prints the number of created properties. The README explains the basic idea, but the description is short and could give more details about the problem and the expected behavior.

## 3. General structure of the repository

The repository is small and easy to navigate. I found these important files: `README.md`, `main.cpp`, `Proprietate.h`, `Proprietate.cpp`, `Apartament.h`, `Apartament.cpp`, `Casa.h`, `Casa.cpp`, `Vila.h`, `Vila.cpp`, `Agentie.h`, `Agentie.cpp`, and `Exceptii.h`.

All files are placed directly in the root folder. For a small project this is acceptable, but for a larger project it would be clearer to separate header files and source files into folders.

The project has good code separation overall. Most class declarations are in `.h` files, and most function implementations are in `.cpp` files. One exception is `Exceptii.h`, where the exception classes implement `what()` directly inside the class declarations. The functions are small, so this is not a big problem.

I did not find `CMakeLists.txt` or another build file. The README gives a `g++` command, so the project can still be compiled. I also did not find data files or input files. The test data is written directly in `main.cpp`.

## 4. Analysis of the OOP design

The main base class is `Proprietate`. It contains common fields: `oras`, `pret`, and `suprafata`. The derived classes are `Apartament`, `Casa`, and `Vila`. This hierarchy makes sense because all three are types of property.

`Casa` adds the field `etaje`, and `Vila` adds the field `piscina`. `Apartament` does not add another field, but it still has its own implementation for rent calculation and display. In my opinion, the hierarchy is simple and natural for this theme.

The class `Agentie` uses composition. It contains a `std::vector<std::shared_ptr<Proprietate>>`, so an agency stores many properties. This is a good design because an agency is not a property, but it manages properties.

Encapsulation is mostly respected. The fields in `Agentie`, `Casa`, and `Vila` are private. In `Proprietate`, the common fields are protected, so derived classes can access them. This is common in student projects, although private fields with protected helper functions could be safer.

## 5. Inheritance and polymorphism

The project has a clear base class created: `Proprietate`. There are three derived classes from it: `Apartament`, `Casa`, and `Vila`. This satisfies the inheritance requirement.

The base class has pure virtual functions. In `Proprietate.h`, `calculeazaChirie(int luni) const` and `clone() const` are pure virtual. There is also a private pure virtual function called `afiseazaImpl`. The function `calculeazaChirie` is specific to the project theme, not only a display function, so this is a good use of polymorphism.

The derived classes use `override` for their virtual functions. The base class also has a virtual destructor: `virtual ~Proprietate();`. This is important because the project stores derived objects through base smart pointers.

Virtual functions are really called through base pointers. In `Agentie::chirieTotala`, the code calls `p->calculeazaChirie(luni)` where `p` is a `std::shared_ptr<Proprietate>`. This means the correct derived version is called at runtime. The constructors of the derived classes also call the base constructor, for example `Casa` calls `Proprietate(oras, pret, suprafata)`.

## 6. Memory management and copying

The project uses `std::shared_ptr` and `std::vector`, which is good. I did not see raw `new` or `delete`. This reduces the risk of memory leaks and makes the code easier to manage.

The `Agentie` class stores properties as `std::shared_ptr<Proprietate>`. This allows it to store apartments, houses, and villas in the same vector. The project also uses a `clone()` function. In the copy constructor of `Agentie`, the code does `proprietati.push_back(p->clone())`. This is a good deep copy solution for polymorphic objects.

`Agentie` also has an assignment operator using copy-and-swap style: `Agentie &Agentie::operator=(Agentie other)`. This is a correct and clean approach.

One possible issue is the static counter `numarProprietati`. It increases in the constructor and copy constructor, but the destructor does not decrease it. In the demo, the program prints 6 properties even though only 3 are displayed, because the objects are cloned when added to the agency. This may be intended, but the meaning of the counter is not very clear.

Another small issue is that `adaugaProprietate` does not check if the pointer is null before calling `p->clone()`.

## 7. Exceptions

The project has a custom exception hierarchy in `Exceptii.h`. The base exception is `EroareProprietate`, derived from `std::exception`. There are three specific exception classes: `EroarePret`, `EroareSuprafata`, and `EroareOras`.

The exceptions override `what()` and give simple messages. In `main.cpp`, exceptions are caught by const reference with `catch (const EroareProprietate &e)`, which is good.

However, I think the exceptions are not used very meaningfully yet. The only throw I found is a test in `main.cpp`:

```cpp
if (a1->calculeazaChirie(6) < 0)
    throw EroarePret();
```

With the current data, this condition is false. I did not find validation in constructors for invalid price, invalid area, or empty city. The project could be better if these exception classes were used in real validation logic.

## 8. Static, const, and operators

The project uses a static field `numarProprietati` and a static function `getNumarProprietati()`. The purpose seems to be counting created property objects. This is a reasonable use of static data, but the exact meaning should be clearer.

Const correctness is used well in many places. For example, `calculeazaChirie`, `clone`, `afiseaza`, `afiseazaTot`, and `chirieTotala` are marked `const`. Parameters like `const std::string &oras` are also passed by const reference.

I did not find an `operator<<` overload. The project uses `afiseaza(std::ostream &out)` instead. This works, but if operator overloading is required, then this part is missing. I did not find other meaningful operators except assignment operators.

## 9. README and documentation

The README explains the project shortly and lists the main OOP concepts used. It also includes a compile and run command using `g++`. This is useful because the project has no CMake file.

Still, the README could be more complete. I could not clearly find a detailed problem statement, a clear explanation of what is given and what is required, or a bibliography/resources section. The README could also explain the role of `clone()`, `Agentie`, and the inheritance hierarchy.

## 10. Good parts of the project

The strongest part of the project is the clear class hierarchy. `Proprietate` is a good base class, and the derived classes match the real estate theme.

Another good part is that polymorphism is actually used. The agency stores base pointers and calls virtual functions through them. This shows that the inheritance is not only written for the requirement, but also used in the program logic.

I also liked the use of `std::vector`, `std::shared_ptr`, and `clone()`. These choices make memory management cleaner and make copying safer.

The code is also easy to read. The files are short, names are understandable, and the demo in `main.cpp` is simple to run.

## 11. Problems and suggestions

One possible improvement is to use the exception classes inside constructors or functions, not only in a small test in `main.cpp`.

The project could be clearer if the static counter explained whether it counts current objects or all created objects.

I think this part can be improved because `operator<<` is missing. Adding it would make output more idiomatic and would satisfy the operator overloading requirement better.

One possible improvement is to add a `CMakeLists.txt` file. This would make the project easier to build.

The README could also be expanded with a clearer problem statement, solution explanation, and bibliography.

## 12. Conclusion

In my opinion, the project mostly respects the project requirements. It has code separation, inheritance, three derived classes, pure virtual functions, a virtual destructor, smart pointers, base pointer storage, polymorphic calls, cloning, custom exceptions, static data, and const functions.

The main strengths are the simple design, clear inheritance hierarchy, and correct use of polymorphism through `Agentie`. The weaker parts are the limited exception usage, missing `operator<<`, missing CMake file, and short README. Overall, it is a good beginner/intermediate OOP project, but it could be improved by making the requirements more complete and better connected to the project logic.
