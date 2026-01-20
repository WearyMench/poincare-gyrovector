# Poincaré Ball Gyrovector Algebra Library

[![Version](https://img.shields.io/badge/version-1.0.0-blue.svg)](https://github.com/yourusername/poincare-gyrovector)
[![License](https://img.shields.io/badge/license-MIT-green.svg)](LICENSE)
[![C++17](https://img.shields.io/badge/C++-17-blue.svg)](https://en.cppreference.com/w/cpp/17)

A high-performance C++ library with Python bindings for performing Gyrovector Algebra operations on the Poincaré Ball model of hyperbolic space.

## Features

- **Möbius Addition**: Non-commutative addition operation on the Poincaré ball
- **Möbius Scalar Multiplication**: Scalar multiplication preserving hyperbolic geometry
- **Exponential Map**: Maps tangent vectors to points on the Poincaré ball
- **Logarithmic Map**: Maps points on the Poincaré ball to tangent vectors
- **Hyperbolic Distance**: Compute distances between points in hyperbolic space
- **High Performance**: Optimized C++ implementation with Python bindings via pybind11

## Mathematical Background

The Poincaré Ball model represents hyperbolic space as the interior of a unit ball in Euclidean space. Key operations:

- **Möbius Addition**: `x ⊕ y = ((1 + 2⟨x,y⟩ + ||y||²)x + (1 - ||x||²)y) / (1 + 2⟨x,y⟩ + ||x||²||y||²)`
- **Möbius Scalar Multiplication**: `r ⊗ x = tanh(r * artanh(||x||)) * (x / ||x||)`
- **Exponential Map**: `exp_x(v) = x ⊕ (tanh(||v||) * (v / ||v||))`
- **Logarithmic Map**: `log_x(y) = artanh(||-x ⊕ y||) * ((-x ⊕ y) / ||-x ⊕ y||)`
- **Distance**: `d(x, y) = artanh(||-x ⊕ y||)`

## Building the Library

### Prerequisites

- CMake 3.12 or higher
- C++17 compatible compiler (GCC, Clang, or MSVC)
- Python 3.6+ (for Python bindings)
- pybind11 (automatically fetched if not found)

### Installing CMake on Windows

If CMake is not installed, use one of these methods:

**Option 1: Using Chocolatey (recommended)**
```powershell
choco install cmake
```

**Option 2: Using winget**
```powershell
winget install Kitware.CMake
```

**Option 3: Download installer**
- Visit https://cmake.org/download/
- Download the Windows x64 Installer
- Run the installer and **make sure to check "Add CMake to system PATH"** during installation

**Option 4: Via Visual Studio**
- Open Visual Studio Installer
- Modify your installation
- Add "Desktop development with C++" workload (includes CMake)

After installation, restart your terminal/PowerShell and verify:
```powershell
cmake --version
```

### Build Instructions

```bash
# Create build directory
mkdir build
cd build

# Configure with CMake
cmake ..

# Build the library
cmake --build .

# (Optional) Install
cmake --install . --prefix /path/to/install
```

### Build Options

- `BUILD_PYTHON_BINDINGS`: Build Python bindings (default: ON)
- `BUILD_EXAMPLES`: Build example programs (default: ON)
- `BUILD_TESTS`: Build test suite (default: OFF)

Example:
```bash
cmake -DBUILD_TESTS=ON ..
```

## Usage

### C++ API

```cpp
#include "poincare/poincare.h"
#include <vector>

using namespace poincare;

// Möbius addition
std::vector<double> x = {0.3, 0.4};
std::vector<double> y = {0.2, 0.1};
std::vector<double> result = mobius_add(x, y);

// Möbius scalar multiplication
double r = 0.5;
std::vector<double> scaled = mobius_scalar_multiply(r, x);

// Exponential map
std::vector<double> base = {0.2, 0.1};
std::vector<double> tangent = {0.1, 0.15};
std::vector<double> exp_result = exp_map(base, tangent);

// Logarithmic map
std::vector<double> log_result = log_map(base, exp_result);

// Distance
double dist = distance(x, y);
```

### Python API

```python
import sys
sys.path.insert(0, 'build/python')
import poincare_gyrovector_py as poincare

# Möbius addition
x = [0.3, 0.4]
y = [0.2, 0.1]
result = poincare.mobius_add(x, y)

# Möbius scalar multiplication
r = 0.5
scaled = poincare.mobius_scalar_multiply(r, x)

# Exponential map
base = [0.2, 0.1]
tangent = [0.1, 0.15]
exp_result = poincare.exp_map(base, tangent)

# Logarithmic map
log_result = poincare.log_map(base, exp_result)

# Distance
dist = poincare.distance(x, y)
```

## Running Examples

### C++ Example

```bash
./build/examples/example_cpp
```

### Python Example

```bash
python examples/example.py
```

## API Reference

### Core Functions

- `mobius_add(x, y)`: Perform Möbius addition
- `mobius_scalar_multiply(r, x)`: Perform Möbius scalar multiplication
- `exp_map(x, v)`: Compute exponential map at point x with tangent vector v
- `log_map(x, y)`: Compute logarithmic map from x to y
- `distance(x, y)`: Compute hyperbolic distance between x and y

### Utility Functions

- `norm(x)`: Compute Euclidean norm
- `dot_product(x, y)`: Compute dot product
- `is_in_ball(x, epsilon)`: Check if vector is in unit ball
- `normalize(x)`: Normalize vector to unit length

## Important Notes

- All input vectors must be in the unit ball: `||x|| < 1`
- Vectors must have the same dimension for binary operations
- The library uses double precision floating point arithmetic
- Numerical stability is maintained with epsilon checks (default: 1e-10)

## Performance Considerations

- The library is optimized for performance with minimal allocations
- Operations are vectorized where possible
- Python bindings have minimal overhead due to pybind11's efficient design

## Version

Current version: **1.0.0**

You can check the version programmatically:

**C++:**
```cpp
#include "poincare/version.h"
std::cout << "Version: " << poincare::get_version_string() << std::endl;
```

**Python:**
```python
import poincare_gyrovector_py as poincare
print(f"Version: {poincare.__version__}")
print(f"Version: {poincare.get_version()}")
```

## License

This library is licensed under the MIT License. See [LICENSE](LICENSE) for details.

## References

- Ungar, A. A. (2005). *Analytic Hyperbolic Geometry: Mathematical Foundations and Applications*
- Ganea, O., Bécigneul, G., & Hofmann, T. (2018). *Hyperbolic Neural Networks*
