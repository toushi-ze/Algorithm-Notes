#!/bin/bash

# CMake build script for list algorithms project

set -e

# Colors
RED='\033[0;31m'
GREEN='\033[0;32m'
YELLOW='\033[1;33m'
NC='\033[0m'

# Directories
BUILD_DIR="build"

# Functions
print_info() {
  echo -e "${GREEN}[INFO]${NC} $1"
}

print_warn() {
  echo -e "${YELLOW}[WARN]${NC} $1"
}

print_error() {
  echo -e "${RED}[ERROR]${NC} $1"
}

# Show help
show_help() {
  echo "Usage: $0 [command]"
  echo ""
  echo "Commands:"
  echo "  all       Configure and build (default)"
  echo "  config    Run CMake configuration"
  echo "  build     Build the project"
  echo "  clean     Remove build directory"
  echo "  test      Run tests"
  echo "  format    Format code with clang-format"
  echo "  help      Show this help message"
}

# Configure CMake
cmake_config() {
  print_info "Configuring CMake..."
  cmake -S . -B "$BUILD_DIR"
}

# Build project
cmake_build() {
  print_info "Building project..."
  cmake --build "$BUILD_DIR"
}

# Clean build directory
cmake_clean() {
  print_info "Cleaning build directory..."
  rm -rf "$BUILD_DIR"
}

# Run tests
run_tests() {
  if [ ! -f "$BUILD_DIR/Debug/list_algo.exe" ]; then
    print_error "Executable not found. Build first."
    exit 1
  fi
  print_info "Running tests..."
  "$BUILD_DIR/Debug/list_algo.exe"
}

# Format code
format_code() {
  if ! command -v clang-format &> /dev/null; then
    print_warn "clang-format not found. Skipping formatting."
    return
  fi
  print_info "Formatting code..."
  clang-format -i inc/list/*.h src/list/*.c test/main.c
}

# Main
main() {
  local command="${1:-all}"

  case "$command" in
    all)
      cmake_config
      cmake_build
      print_info "Build complete. Executable: $BUILD_DIR/list_algo"
      ;;
    config)
      cmake_config
      ;;
    build)
      cmake_build
      ;;
    clean)
      cmake_clean
      ;;
    test)
      run_tests
      ;;
    format)
      format_code
      ;;
    help|--help|-h)
      show_help
      ;;
    *)
      print_error "Unknown command: $command"
      show_help
      exit 1
      ;;
  esac
}

main "$@"
