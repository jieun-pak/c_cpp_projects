# CPP06 — C++ Casts

## The 4 C++ Casts (know these cold for defense)

| Cast | Use case | Fails at |
|------|----------|----------|
| `static_cast` | Numeric conversions, upcasts/downcasts with no runtime check | Compile-time if types are incompatible |
| `dynamic_cast` | Safe downcast in polymorphic hierarchy (needs virtual destructor) | Returns `nullptr` (pointer) or throws `std::bad_cast` (reference) at runtime |
| `reinterpret_cast` | Bit-level reinterpretation (pointer ↔ integer) | Never fails — you're on your own |
| `const_cast` | Remove/add `const`/`volatile` | Undefined behavior if you write through a genuinely-const object |

**Rule for this module:** every exercise uses ONE specific cast. Be ready to justify your choice.

---

## Exercise 00 — ScalarConverter

### Checklist
- [ ] Class `ScalarConverter` is **not instantiable** (private ctor/copy/assign/dtor)
- [ ] Single static method `void convert(std::string const &literal)`
- [ ] Detects the literal's original type (char / int / float / double)
- [ ] Outputs `char`, `int`, `float`, `double` conversions in that order
- [ ] Handles special float pseudo-literals: `nanf`, `+inff`, `-inff`
- [ ] Handles special double pseudo-literals: `nan`, `+inf`, `-inf`
- [ ] Prints `impossible` when conversion is meaningless (NaN/Inf → char or int)
- [ ] Prints `Non displayable` for non-printable chars (ASCII 0–31, 127)
- [ ] Float output ends with `f` (e.g. `42.0f`)
- [ ] At least 1 decimal place shown for float and double
- [ ] Include `<limits>`, `<cmath>`, `<iomanip>`, `<climits>`

### Detection order (important — order matters)
1. `"nan"` / `"+inf"` / `"-inf"` → **double** pseudo-literal
2. `"nanf"` / `"+inff"` / `"-inff"` → **float** pseudo-literal
3. Length == 1 and not a digit → **char**
4. Length == 3 and wrapped in single quotes `'x'` → **char**
5. Ends with `'f'` → **float** (strip the `f`, then parse as double)
6. Contains `'.'` → **double**
7. Otherwise → **int**

### Cast to use: `static_cast`
Scalar type conversions are known at compile time — `static_cast` is correct.

### Output rules
```
char: 'a'           ← printable
char: Non displayable ← ASCII 0-31 or 127
char: impossible    ← NaN, Inf, out of 0-127 range
int: 42
int: impossible     ← NaN, Inf, overflow
float: 42.0f
float: nanf
float: +inff / -inff
double: 42.0
double: nan
double: +inf / -inf
```

---

## Exercise 01 — Serialization

### Checklist
- [ ] `Serializer` class is **not instantiable**
- [ ] `static uintptr_t serialize(Data* ptr)` — pointer → integer
- [ ] `static Data* deserialize(uintptr_t raw)` — integer → pointer
- [ ] `Data` struct is **non-empty** (has at least one data member)
- [ ] `Data.hpp` is turned in
- [ ] Test: `deserialize(serialize(&data)) == &data`
- [ ] Include `<stdint.h>` for `uintptr_t`

### Cast to use: `reinterpret_cast`
Pointer ↔ integer conversion. `reinterpret_cast` is the only cast that handles this.
`static_cast` won't compile here — types are not related.

---

## Exercise 02 — Identify real type

### Checklist
- [ ] `Base` has a **public virtual destructor** only (no OCF required)
- [ ] `A`, `B`, `C` inherit publicly from `Base` (no OCF required)
- [ ] `Base* generate(void)` — randomly returns new A, B, or C
- [ ] `void identify(Base* p)` — prints `"A"`, `"B"`, or `"C"` using pointer cast
- [ ] `void identify(Base& p)` — same, but NO pointer used inside, uses reference cast
- [ ] `<typeinfo>` header is **forbidden** (`std::typeinfo` / `typeid` operator forbidden)
- [ ] Test both overloads

### Cast to use: `dynamic_cast`
- With pointer: `dynamic_cast<A*>(p)` returns `nullptr` on failure — use as condition
- With reference: `dynamic_cast<A&>(r)` throws `std::bad_cast` on failure — use try/catch

### Reference identify trick
```cpp
void identify(Base& p) {
    try { (void)dynamic_cast<A&>(p); std::cout << "A" << std::endl; return; }
    catch (std::exception&) {}
    try { (void)dynamic_cast<B&>(p); std::cout << "B" << std::endl; return; }
    catch (std::exception&) {}
    // C is the fallthrough
    std::cout << "C" << std::endl;
}
```

---

## Things Junior Devs Should Know

### Why `static_cast` and not C-style `(int)x`?
C-style casts are ambiguous — the compiler silently tries multiple cast strategies.
`static_cast` is explicit and checked at compile time, so errors are caught earlier.

### Why does `dynamic_cast` need a virtual destructor?
`dynamic_cast` requires RTTI (Run-Time Type Information). RTTI is only generated for
polymorphic types — a class becomes polymorphic only when it has at least one virtual function.
The virtual destructor in `Base` makes the whole hierarchy polymorphic.

### `reinterpret_cast` is dangerous
It bypasses the type system entirely. It's valid for pointer ↔ integer only when using
`uintptr_t` (guaranteed large enough to hold a pointer). Never use it between unrelated
struct types without careful alignment checks.

### Orthodox Canonical Form reminder
- Default constructor
- Copy constructor
- Assignment operator
- Destructor

For ex02, the subject explicitly says OCF is NOT required for Base/A/B/C.

### `uintptr_t` vs `size_t`
Both are typically the same size on a given platform, but `uintptr_t` is semantically
"an integer that can hold a pointer" — always prefer it for pointer ↔ integer conversions.

---

## Things to Consider

- **`strtod` over `atof`**: `atof` has no error detection. `strtod` lets you check if
  the whole string was consumed and detect overflow/underflow.
- **Float precision**: Stripping `f` suffix before parsing with `strtod` avoids locale
  issues and is safe for C++98 (no `strtof` guaranteed in C++98).
- **`isprint` uses `unsigned char`**: Passing a plain `char` to `isprint` is UB when
  the value is negative. Always cast: `isprint(static_cast<unsigned char>(c))`.
- **INT overflow check**: Compare the double value against `INT_MIN` and `INT_MAX`
  before casting — double can represent values way outside int range.
- **`std::isnan`/`std::isinf`**: Include `<cmath>`. In C++98 these may not be in `std::`
  on all compilers; `val != val` detects NaN portably if needed.
- **Seed `rand()`**: Call `srand(time(NULL))` in `main()` for ex02 so generate() is
  actually random each run.
- **Memory**: `generate()` returns `new` — the caller must `delete` it.
