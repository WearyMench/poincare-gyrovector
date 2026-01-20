#!/usr/bin/env python3
"""
Example usage of the Poincaré Ball Gyrovector Algebra library
"""

import sys
import os

# Add the build directory to the path
sys.path.insert(0, os.path.join(os.path.dirname(__file__), '..', 'build', 'python'))

try:
    import poincare_gyrovector_py as poincare
except ImportError:
    print("Error: Could not import poincare_gyrovector_py")
    print("Please build the library first using CMake")
    sys.exit(1)

import numpy as np

def print_vector(v, name):
    """Print a vector in a readable format"""
    print(f"{name} = {v}")
    print(f"||{name}|| = {poincare.norm(v):.6f}")

def main():
    print("=== Poincaré Ball Gyrovector Algebra Example (Python) ===\n")

    # Example 1: Möbius addition
    print("Example 1: Möbius Addition")
    x = [0.3, 0.4]
    y = [0.2, 0.1]
    
    print_vector(x, "x")
    print_vector(y, "y")
    
    result = poincare.mobius_add(x, y)
    print_vector(result, "x ⊕ y")
    print()

    # Example 2: Möbius scalar multiplication
    print("Example 2: Möbius Scalar Multiplication")
    r = 0.5
    z = [0.5, 0.3]
    
    print_vector(z, "z")
    print(f"r = {r}")
    
    scaled = poincare.mobius_scalar_multiply(r, z)
    print_vector(scaled, "r ⊗ z")
    print()

    # Example 3: Exponential map
    print("Example 3: Exponential Map")
    base = [0.2, 0.1]
    tangent = [0.1, 0.15]
    
    print_vector(base, "base point x")
    print_vector(tangent, "tangent vector v")
    
    exp_result = poincare.exp_map(base, tangent)
    print_vector(exp_result, "exp_x(v)")
    print()

    # Example 4: Logarithmic map
    print("Example 4: Logarithmic Map")
    x_base = [0.1, 0.2]
    y_target = [0.3, 0.25]
    
    print_vector(x_base, "base point x")
    print_vector(y_target, "target point y")
    
    log_result = poincare.log_map(x_base, y_target)
    print_vector(log_result, "log_x(y)")
    print()

    # Example 5: Distance
    print("Example 5: Hyperbolic Distance")
    p1 = [0.1, 0.1]
    p2 = [0.4, 0.3]
    
    print_vector(p1, "p1")
    print_vector(p2, "p2")
    
    dist = poincare.distance(p1, p2)
    print(f"d(p1, p2) = {dist:.6f}\n")

    # Example 6: Verify exp and log are inverses
    print("Example 6: Verifying exp and log are inverses")
    x0 = [0.2, 0.15]
    v0 = [0.1, 0.08]
    
    y0 = poincare.exp_map(x0, v0)
    v_recovered = poincare.log_map(x0, y0)
    
    print_vector(v0, "original tangent vector v")
    print_vector(v_recovered, "recovered tangent vector log_x(exp_x(v))")
    
    diff = np.sqrt(sum((v0[i] - v_recovered[i])**2 for i in range(len(v0))))
    print(f"||v - log_x(exp_x(v))|| = {diff:.10f}\n")

    # Example 7: Working with higher dimensions
    print("Example 7: 3D Poincaré Ball")
    x3d = [0.2, 0.1, 0.15]
    y3d = [0.1, 0.2, 0.1]
    
    print_vector(x3d, "x (3D)")
    print_vector(y3d, "y (3D)")
    
    result_3d = poincare.mobius_add(x3d, y3d)
    print_vector(result_3d, "x ⊕ y (3D)")
    
    dist_3d = poincare.distance(x3d, y3d)
    print(f"d(x, y) = {dist_3d:.6f}")

if __name__ == "__main__":
    main()
