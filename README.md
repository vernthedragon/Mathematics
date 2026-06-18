# Mathematics

A modular header-only C++ mathematics library providing generic types (such as complex numbers and dual numbers) and functions for general use.

---

## Features

- **Header-only** — no build system required, just `#include` what you need
- **Generic** — all types are templated over any numeric type (`float`, `double`, `long double`, etc.)
- **Operator-overloaded** — arithmetic works naturally with `+`, `-`, `*`, `/`, `==`, `!=`
- **No dependencies** — only the C++ standard library (`<cmath>`)
- **Modular** — each type lives in its own header; include only what you use

---

## Modules

### `Complex<T>` — Complex numbers (`Complex.hpp`)

Represents numbers of the form **a + bi** where **i² = −1**.

| Method / Operator | Description |
|---|---|
| `+`, `-`, `*`, `/` | Arithmetic between two complex numbers |
| `+`, `-`, `*`, `/` with scalar | Mixed arithmetic with real scalars |
| `==`, `!=` | Equality testing |
| `~`, `.Conj` | Conjugate |
| `.abs()` | Modulus \|z\| = √(a² + b²) |
| `.abssqr()` | Squared modulus a² + b² |
| `.ang()` | Argument θ = atan2(b, a) in radians |
| `.re` | The real part *a* |
| `.im` | The imaginary part *b* |

```cpp
#include "Complex.hpp"

Complex<double> z1(3.0, 4.0);   // 3 + 4i
Complex<double> z2(1.0, -2.0);  // 1 - 2i

auto sum  = z1 + z2;            // 4 + 2i
auto prod = z1 * z2;            // 11 - 2i
double r  = z1.abs();           // 5.0
double th = z1.ang();           // atan2(4, 3)
```

---

### `Dual<T>` — Dual numbers (`Dual.hpp`)

Represents numbers of the form **a + bε** where **ε² = 0**.

Dual numbers propagate derivatives automatically through arithmetic, making them ideal for **forward-mode automatic differentiation** — compute a function and its exact derivative in a single pass, with no numerical error.

| Method / Operator | Description |
|---|---|
| `+`, `-`, `*`, `/` | Arithmetic between two dual numbers |
| `+`, `-`, `*`, `/` with scalar | Mixed arithmetic with real scalars |
| `==`, `!=` | Equality testing |
| `~`, `.Conj` | Conjugate |
| `.re` | The real part *a* |
| `.eps` | The dual (infinitesimal) part *b* |

```cpp
#include "Dual.hpp"

// Differentiate f(x) = x² + 3x at x = 2
// Seed with Dual(x, 1) — the 1 seeds the derivative
Dual<double> x(2.0, 1.0);
Dual<double> f = x * x + x * 3.0;

double value = f.re;  // f(2)  = 10.0
double derivative = f.eps; // f'(2) = 7.0
```

---

## Usage

Since this is a header-only library, simply copy the headers you need into your project and include them:

```cpp
#include "Complex.hpp"
#include "Dual.hpp"
```

No installation, no `cmake`, no linking required.

---

## Requirements

- A standard-conforming C++ compiler (GCC, Clang, MSVC)

---

## Roadmap

Planned additions to the library:

- Split-complex (hyperbolic) numbers
- Gegenbauer polynomials
- Common mathematical functions extended to all numeric types

---

## License

See [LICENSE](LICENSE) for details.
