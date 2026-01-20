#ifndef POINCARE_GYROVECTOR_H
#define POINCARE_GYROVECTOR_H

#include <vector>
#include <cmath>
#include <stdexcept>
#include <algorithm>
#include <numeric>
#include "poincare/version.h"

namespace poincare {

/**
 * @brief Perform Möbius addition on the Poincaré ball
 * 
 * Möbius addition: x ⊕ y = ((1 + 2⟨x,y⟩ + ||y||²)x + (1 - ||x||²)y) / (1 + 2⟨x,y⟩ + ||x||²||y||²)
 * 
 * @param x First vector (must be in the unit ball, ||x|| < 1)
 * @param y Second vector (must be in the unit ball, ||y|| < 1)
 * @return Result of Möbius addition
 */
std::vector<double> mobius_add(const std::vector<double>& x, const std::vector<double>& y);

/**
 * @brief Perform Möbius scalar multiplication
 * 
 * Möbius scalar multiplication: r ⊗ x = tanh(r * artanh(||x||)) * (x / ||x||)
 * 
 * @param r Scalar multiplier
 * @param x Vector (must be in the unit ball, ||x|| < 1)
 * @return Result of Möbius scalar multiplication
 */
std::vector<double> mobius_scalar_multiply(double r, const std::vector<double>& x);

/**
 * @brief Compute the exponential map at point x
 * 
 * Exponential map: exp_x(v) = x ⊕ (tanh(||v||) * (v / ||v||))
 * 
 * @param x Base point (must be in the unit ball, ||x|| < 1)
 * @param v Tangent vector
 * @return Point on the Poincaré ball
 */
std::vector<double> exp_map(const std::vector<double>& x, const std::vector<double>& v);

/**
 * @brief Compute the logarithmic map at point x
 * 
 * Logarithmic map: log_x(y) = artanh(||-x ⊕ y||) * ((-x ⊕ y) / ||-x ⊕ y||)
 * 
 * @param x Base point (must be in the unit ball, ||x|| < 1)
 * @param y Target point (must be in the unit ball, ||y|| < 1)
 * @return Tangent vector
 */
std::vector<double> log_map(const std::vector<double>& x, const std::vector<double>& y);

/**
 * @brief Compute the distance between two points on the Poincaré ball
 * 
 * Distance: d(x, y) = artanh(||-x ⊕ y||)
 * 
 * @param x First point
 * @param y Second point
 * @return Hyperbolic distance
 */
double distance(const std::vector<double>& x, const std::vector<double>& y);

/**
 * @brief Compute the norm of a vector
 */
double norm(const std::vector<double>& x);

/**
 * @brief Compute the dot product of two vectors
 */
double dot_product(const std::vector<double>& x, const std::vector<double>& y);

/**
 * @brief Check if a vector is in the unit ball (||x|| < 1)
 */
bool is_in_ball(const std::vector<double>& x, double epsilon = 1e-10);

/**
 * @brief Normalize a vector to have unit norm
 */
std::vector<double> normalize(const std::vector<double>& x);

} // namespace poincare

#endif // POINCARE_GYROVECTOR_H
