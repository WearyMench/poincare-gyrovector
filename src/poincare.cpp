#include "poincare/poincare.h"
#include <cmath>
#include <stdexcept>
#include <algorithm>
#include <numeric>

namespace poincare {

namespace {
    const double EPSILON = 1e-10;
    const double MAX_NORM = 1.0 - EPSILON;
}

double norm(const std::vector<double>& x) {
    double sum = 0.0;
    for (double val : x) {
        sum += val * val;
    }
    return std::sqrt(sum);
}

double dot_product(const std::vector<double>& x, const std::vector<double>& y) {
    if (x.size() != y.size()) {
        throw std::invalid_argument("Vectors must have the same dimension");
    }
    double sum = 0.0;
    for (size_t i = 0; i < x.size(); ++i) {
        sum += x[i] * y[i];
    }
    return sum;
}

bool is_in_ball(const std::vector<double>& x, double epsilon) {
    double n = norm(x);
    return n < (1.0 - epsilon);
}

std::vector<double> normalize(const std::vector<double>& x) {
    double n = norm(x);
    if (n < EPSILON) {
        return std::vector<double>(x.size(), 0.0);
    }
    std::vector<double> result(x.size());
    for (size_t i = 0; i < x.size(); ++i) {
        result[i] = x[i] / n;
    }
    return result;
}

std::vector<double> mobius_add(const std::vector<double>& x, const std::vector<double>& y) {
    if (x.size() != y.size()) {
        throw std::invalid_argument("Vectors must have the same dimension");
    }
    
    double x_norm_sq = dot_product(x, x);
    double y_norm_sq = dot_product(y, y);
    double xy_dot = dot_product(x, y);
    
    // Check if points are in the unit ball
    if (x_norm_sq >= 1.0 - EPSILON || y_norm_sq >= 1.0 - EPSILON) {
        throw std::domain_error("Points must be in the unit ball (||x|| < 1)");
    }
    
    double denominator = 1.0 + 2.0 * xy_dot + x_norm_sq * y_norm_sq;
    
    if (std::abs(denominator) < EPSILON) {
        throw std::runtime_error("Denominator too small in Möbius addition");
    }
    
    std::vector<double> result(x.size());
    double coeff_x = 1.0 + 2.0 * xy_dot + y_norm_sq;
    double coeff_y = 1.0 - x_norm_sq;
    
    for (size_t i = 0; i < x.size(); ++i) {
        result[i] = (coeff_x * x[i] + coeff_y * y[i]) / denominator;
    }
    
    return result;
}

std::vector<double> mobius_scalar_multiply(double r, const std::vector<double>& x) {
    if (x.empty()) {
        throw std::invalid_argument("Vector cannot be empty");
    }
    
    double x_norm = norm(x);
    
    if (x_norm >= 1.0 - EPSILON) {
        throw std::domain_error("Point must be in the unit ball (||x|| < 1)");
    }
    
    // Handle zero vector
    if (x_norm < EPSILON) {
        return std::vector<double>(x.size(), 0.0);
    }
    
    // Compute artanh(||x||)
    double artanh_x = std::atanh(x_norm);
    
    // Compute tanh(r * artanh(||x||))
    double new_norm = std::tanh(r * artanh_x);
    
    // Scale the normalized vector
    std::vector<double> result(x.size());
    double scale = new_norm / x_norm;
    for (size_t i = 0; i < x.size(); ++i) {
        result[i] = scale * x[i];
    }
    
    return result;
}

std::vector<double> exp_map(const std::vector<double>& x, const std::vector<double>& v) {
    if (x.size() != v.size()) {
        throw std::invalid_argument("Base point and tangent vector must have the same dimension");
    }
    
    double x_norm_sq = dot_product(x, x);
    if (x_norm_sq >= 1.0 - EPSILON) {
        throw std::domain_error("Base point must be in the unit ball (||x|| < 1)");
    }
    
    double v_norm = norm(v);
    
    // Handle zero tangent vector
    if (v_norm < EPSILON) {
        return x;
    }
    
    // Normalize the tangent vector
    std::vector<double> v_normalized = normalize(v);
    
    // Scale by tanh(||v||)
    double scale = std::tanh(v_norm);
    std::vector<double> scaled_v(v.size());
    for (size_t i = 0; i < v.size(); ++i) {
        scaled_v[i] = scale * v_normalized[i];
    }
    
    // Apply Möbius addition: x ⊕ scaled_v
    return mobius_add(x, scaled_v);
}

std::vector<double> log_map(const std::vector<double>& x, const std::vector<double>& y) {
    if (x.size() != y.size()) {
        throw std::invalid_argument("Base point and target point must have the same dimension");
    }
    
    double x_norm_sq = dot_product(x, x);
    double y_norm_sq = dot_product(y, y);
    
    if (x_norm_sq >= 1.0 - EPSILON || y_norm_sq >= 1.0 - EPSILON) {
        throw std::domain_error("Points must be in the unit ball (||x|| < 1)");
    }
    
    // Compute -x (negation)
    std::vector<double> neg_x(x.size());
    for (size_t i = 0; i < x.size(); ++i) {
        neg_x[i] = -x[i];
    }
    
    // Compute -x ⊕ y
    std::vector<double> mobius_result = mobius_add(neg_x, y);
    double mobius_norm = norm(mobius_result);
    
    // Handle case where result is at the origin
    if (mobius_norm < EPSILON) {
        return std::vector<double>(x.size(), 0.0);
    }
    
    // Compute artanh(||-x ⊕ y||)
    double artanh_norm = std::atanh(mobius_norm);
    
    // Scale the normalized vector
    std::vector<double> result(x.size());
    double scale = artanh_norm / mobius_norm;
    for (size_t i = 0; i < x.size(); ++i) {
        result[i] = scale * mobius_result[i];
    }
    
    return result;
}

double distance(const std::vector<double>& x, const std::vector<double>& y) {
    if (x.size() != y.size()) {
        throw std::invalid_argument("Points must have the same dimension");
    }
    
    // Compute -x
    std::vector<double> neg_x(x.size());
    for (size_t i = 0; i < x.size(); ++i) {
        neg_x[i] = -x[i];
    }
    
    // Compute -x ⊕ y
    std::vector<double> mobius_result = mobius_add(neg_x, y);
    double mobius_norm = norm(mobius_result);
    
    // Distance is artanh(||-x ⊕ y||)
    return std::atanh(mobius_norm);
}

} // namespace poincare
