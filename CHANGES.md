# CHANGELOG.md

VERSION: 2.0.1
DATE: July 11th, 2022

## Bug Fixes
- Use float instead of double. Double seemed to fail on UNIXWare. Who knows why.

## Breaking Changes
- Completely new implementation of the `chash_iter` and `chash_skip`
  (now known as `chash_get`) macros. They are now more maintainable,
  and do not rely on weird for loop hacks.
