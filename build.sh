#!/bin/bash
# Build script for Poincaré Ball Gyrovector Algebra Library

set -e

echo "Building Poincaré Ball Gyrovector Algebra Library..."

# Create build directory
mkdir -p build
cd build

# Configure with CMake
echo "Configuring with CMake..."
cmake ..

# Build
echo "Building..."
cmake --build . --config Release

echo "Build complete!"
echo ""
echo "To run C++ example:"
echo "  ./build/examples/example_cpp"
echo ""
echo "To run Python example:"
echo "  python examples/example.py"
