# 📘 ft_containers

This project was written as part of [42](https://www.42.fr) curriculum.

The main goal is to implement the following containers from the C++ standard library:
- [map](inc/map.hpp)
- [set](inc/set.hpp)
- [stack](inc/stack.hpp)
- [vector](inc/vector.hpp)

We had to follow the specifications from the [C++98 standard](https://www.lirmm.fr/~ducour/Doc-objets/ISO+IEC+14882-1998.pdf).

💡 See the [subject](doc/en.subject.pdf) for more details.

## 📦 Prerequisites

⚠️ These dependencies are only required to run the tests!

- [Clang](https://clang.llvm.org) or [GCC](https://gcc.gnu.org)
	- 💡 If you want to use GCC, you will have to change the `CXX` variable in the [Makefile](Makefile) to `g++`.
- [Cpputest](https://cpputest.github.io)

## 📖 Usage

The source code is located in the [inc](inc) directory as a header-only library.
All classes and functions are in the `ft` namespace.

The test suite is located in the [test](test) directory.
In order to compare the results, a variable named `NAMESPACE` is defined in the [Makefile](Makefile), to compile tests with the standard library using `NAMESPACE=std` or with ft_containers using `NAMESPACE=ft`.

### 🔬 Run tests

```sh
make run
```

### 🧪 Example with `ft::vector`

```cpp
#include <iostream>
#include "vector.hpp"

int main() {
	// Declare a vector of int
	ft::vector<int> v;

	// Reserve memory for 12 elements
	v.reserve(12);

	// Add 10 elements with value from 0 to 9
	for (int i = 0; i < 10; ++i)
		v.push_back(i);

	// Insert 2 elements with value 42 between the 5th and 6th element
	v.insert(v.begin() + 5, 2, 42);

	// Print all elements
	for (ft::vector<int>::iterator it = v.begin(); it != v.end(); ++it)
		std::cout << ' ' << *it;
	std::cout << std::endl;
}
```

## ⚖️ License

This project is licensed under the GNU General Public License v3.0 - see the [LICENSE](LICENSE) file for details.
