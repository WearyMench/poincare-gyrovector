# Changelog

All notable changes to the Poincaré Ball Gyrovector Algebra Library will be documented in this file.

The format is based on [Keep a Changelog](https://keepachangelog.com/en/1.0.0/),
and this project adheres to [Semantic Versioning](https://semver.org/spec/v2.0.0.html).

## [1.0.0] - 2024-12-XX

### Added
- Initial release of the Poincaré Ball Gyrovector Algebra Library
- Core operations:
  - Möbius addition (`mobius_add`)
  - Möbius scalar multiplication (`mobius_scalar_multiply`)
  - Exponential map (`exp_map`)
  - Logarithmic map (`log_map`)
  - Hyperbolic distance calculation (`distance`)
- Utility functions:
  - Vector norm calculation (`norm`)
  - Dot product (`dot_product`)
  - Unit ball validation (`is_in_ball`)
  - Vector normalization (`normalize`)
- Python bindings via pybind11
- C++ API with comprehensive documentation
- Example programs in both C++ and Python
- CMake build system with automatic dependency management
- Cross-platform support (Windows, Linux, macOS)
- Version information API

### Features
- High-performance C++ implementation
- Support for arbitrary-dimensional vectors
- Numerical stability with epsilon checks
- Comprehensive error handling
- Full Python integration

[1.0.0]: https://github.com/yourusername/poincare-gyrovector/releases/tag/v1.0.0
