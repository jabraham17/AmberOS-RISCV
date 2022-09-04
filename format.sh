#!/usr/bin/env bash

find . -name "*.c" -type f -exec clang-format -i {} +
find . -name "*.cpp" -type f -exec clang-format -i {} +
find . -name "*.cc" -type f -exec clang-format -i {} +
find . -name "*.h" -type f -exec clang-format -i {} +
