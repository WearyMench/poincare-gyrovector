# Versioning Guide

This project follows [Semantic Versioning](https://semver.org/) (SemVer).

## Version Format

Version numbers follow the pattern: `MAJOR.MINOR.PATCH`

- **MAJOR**: Incremented for incompatible API changes
- **MINOR**: Incremented for new functionality in a backwards-compatible manner
- **PATCH**: Incremented for backwards-compatible bug fixes

## Current Version

The current version is defined in:
- `include/poincare/version.h` - C++ header with version constants
- `CMakeLists.txt` - CMake project version
- `CHANGELOG.md` - Release notes

## Updating the Version

When releasing a new version:

1. **Update version numbers:**
   - `include/poincare/version.h` - Update `POINCARE_GYROVECTOR_VERSION_*` macros
   - `CMakeLists.txt` - Update `project(... VERSION ...)`

2. **Update CHANGELOG.md:**
   - Add a new section for the version
   - Document all changes (Added, Changed, Deprecated, Removed, Fixed, Security)

3. **Commit and tag:**
   ```bash
   git add include/poincare/version.h CMakeLists.txt CHANGELOG.md
   git commit -m "Bump version to X.Y.Z"
   git tag -a vX.Y.Z -m "Version X.Y.Z - Description"
   ```

4. **Push to remote:**
   ```bash
   git push origin master
   git push origin vX.Y.Z
   ```

## Version Access

### C++ API
```cpp
#include "poincare/version.h"

int major = poincare::get_version_major();
int minor = poincare::get_version_minor();
int patch = poincare::get_version_patch();
const char* version = poincare::get_version_string();
```

### Python API
```python
import poincare_gyrovector_py as poincare

# Access version
print(poincare.__version__)
print(poincare.get_version())
print(poincare.get_version_major())
print(poincare.get_version_minor())
print(poincare.get_version_patch())
```

## Git Tags

All releases are tagged in git. To list all tags:
```bash
git tag -l
```

To checkout a specific version:
```bash
git checkout v1.0.0
```
