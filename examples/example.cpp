#include <iostream>
#include <vector>
#include <iomanip>
#include "poincare/poincare.h"

using namespace poincare;

void print_vector(const std::vector<double>& v, const std::string& name) {
    std::cout << name << " = [";
    for (size_t i = 0; i < v.size(); ++i) {
        std::cout << std::fixed << std::setprecision(6) << v[i];
        if (i < v.size() - 1) std::cout << ", ";
    }
    std::cout << "]" << std::endl;
}

int main() {
    std::cout << "=== Poincaré Ball Gyrovector Algebra Example ===" << std::endl << std::endl;

    // Example 1: Möbius addition
    std::cout << "Example 1: Möbius Addition" << std::endl;
    std::vector<double> x = {0.3, 0.4};
    std::vector<double> y = {0.2, 0.1};
    
    print_vector(x, "x");
    print_vector(y, "y");
    
    std::vector<double> result = mobius_add(x, y);
    print_vector(result, "x ⊕ y");
    std::cout << "||x ⊕ y|| = " << norm(result) << std::endl << std::endl;

    // Example 2: Möbius scalar multiplication
    std::cout << "Example 2: Möbius Scalar Multiplication" << std::endl;
    double r = 0.5;
    std::vector<double> z = {0.5, 0.3};
    
    print_vector(z, "z");
    std::cout << "r = " << r << std::endl;
    
    std::vector<double> scaled = mobius_scalar_multiply(r, z);
    print_vector(scaled, "r ⊗ z");
    std::cout << "||r ⊗ z|| = " << norm(scaled) << std::endl << std::endl;

    // Example 3: Exponential map
    std::cout << "Example 3: Exponential Map" << std::endl;
    std::vector<double> base = {0.2, 0.1};
    std::vector<double> tangent = {0.1, 0.15};
    
    print_vector(base, "base point x");
    print_vector(tangent, "tangent vector v");
    
    std::vector<double> exp_result = exp_map(base, tangent);
    print_vector(exp_result, "exp_x(v)");
    std::cout << "||exp_x(v)|| = " << norm(exp_result) << std::endl << std::endl;

    // Example 4: Logarithmic map
    std::cout << "Example 4: Logarithmic Map" << std::endl;
    std::vector<double> x_base = {0.1, 0.2};
    std::vector<double> y_target = {0.3, 0.25};
    
    print_vector(x_base, "base point x");
    print_vector(y_target, "target point y");
    
    std::vector<double> log_result = log_map(x_base, y_target);
    print_vector(log_result, "log_x(y)");
    std::cout << "||log_x(y)|| = " << norm(log_result) << std::endl << std::endl;

    // Example 5: Distance
    std::cout << "Example 5: Hyperbolic Distance" << std::endl;
    std::vector<double> p1 = {0.1, 0.1};
    std::vector<double> p2 = {0.4, 0.3};
    
    print_vector(p1, "p1");
    print_vector(p2, "p2");
    
    double dist = distance(p1, p2);
    std::cout << "d(p1, p2) = " << dist << std::endl << std::endl;

    // Example 6: Verify exp and log are inverses
    std::cout << "Example 6: Verifying exp and log are inverses" << std::endl;
    std::vector<double> x0 = {0.2, 0.15};
    std::vector<double> v0 = {0.1, 0.08};
    
    std::vector<double> y0 = exp_map(x0, v0);
    std::vector<double> v_recovered = log_map(x0, y0);
    
    print_vector(v0, "original tangent vector v");
    print_vector(v_recovered, "recovered tangent vector log_x(exp_x(v))");
    
    double diff = 0.0;
    for (size_t i = 0; i < v0.size(); ++i) {
        diff += (v0[i] - v_recovered[i]) * (v0[i] - v_recovered[i]);
    }
    diff = std::sqrt(diff);
    std::cout << "||v - log_x(exp_x(v))|| = " << diff << std::endl;

    return 0;
}
