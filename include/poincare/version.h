#ifndef POINCARE_GYROVECTOR_VERSION_H
#define POINCARE_GYROVECTOR_VERSION_H

/**
 * @file version.h
 * @brief Version information for Poincaré Ball Gyrovector Algebra Library
 */

#define POINCARE_GYROVECTOR_VERSION_MAJOR 1
#define POINCARE_GYROVECTOR_VERSION_MINOR 0
#define POINCARE_GYROVECTOR_VERSION_PATCH 0

#define POINCARE_GYROVECTOR_VERSION_STRING "1.0.0"

namespace poincare {

/**
 * @brief Get the major version number
 * @return Major version number
 */
inline int get_version_major() {
    return POINCARE_GYROVECTOR_VERSION_MAJOR;
}

/**
 * @brief Get the minor version number
 * @return Minor version number
 */
inline int get_version_minor() {
    return POINCARE_GYROVECTOR_VERSION_MINOR;
}

/**
 * @brief Get the patch version number
 * @return Patch version number
 */
inline int get_version_patch() {
    return POINCARE_GYROVECTOR_VERSION_PATCH;
}

/**
 * @brief Get the version string
 * @return Version string (e.g., "1.0.0")
 */
inline const char* get_version_string() {
    return POINCARE_GYROVECTOR_VERSION_STRING;
}

} // namespace poincare

#endif // POINCARE_GYROVECTOR_VERSION_H
