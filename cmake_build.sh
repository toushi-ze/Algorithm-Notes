#!/bin/bash
# cmake_build.sh - Build and test script for Generic Linked List Library
# Usage: ./cmake_build.sh [build|test|clean|all]

set -euo pipefail

BUILD_DIR="build"
BUILD_TYPE="Release"

# Colors
RED='\033[0;31m'
GREEN='\033[0;32m'
YELLOW='\033[1;33m'
NC='\033[0m'

info() {
    echo -e "${GREEN}[INFO]${NC} $1"
}

warn() {
    echo -e "${YELLOW}[WARN]${NC} $1"
}

error() {
    echo -e "${RED}[ERROR]${NC} $1"
}

# 自动查找可执行文件路径
find_executable() {
    local base_name="$1"
    local path1="${BUILD_DIR}/bin/${base_name}"
    local path2="${BUILD_DIR}/bin/${BUILD_TYPE}/${base_name}"
    local path3="${BUILD_DIR}/bin/${base_name}.exe"
    local path4="${BUILD_DIR}/bin/${BUILD_TYPE}/${base_name}.exe"

    if [ -f "$path1" ]; then
        echo "$path1"
    elif [ -f "$path2" ]; then
        echo "$path2"
    elif [ -f "$path3" ]; then
        echo "$path3"
    elif [ -f "$path4" ]; then
        echo "$path4"
    else
        echo ""
    fi
}

do_build() {
    info "Building project..."
    mkdir -p "$BUILD_DIR"
    cd "$BUILD_DIR"
    cmake -DCMAKE_BUILD_TYPE="$BUILD_TYPE" ..
    cmake --build . --config "$BUILD_TYPE"
    cd ..
    info "Build completed successfully."
}

do_test() {
    info "Running algorithm tests..."

    EXEC=$(find_executable "algorithms_test")
    if [ -z "$EXEC" ]; then
        warn "Tests not built. Building first..."
        do_build
        EXEC=$(find_executable "algorithms_test")
        if [ -z "$EXEC" ]; then
            error "Test executable still not found after build!"
            exit 1
        fi
    fi

    info "Running: $EXEC"
    "$EXEC"
}

do_list_test() {
    info "Running list unit tests..."

    EXEC=$(find_executable "list_test")
    if [ -z "$EXEC" ]; then
        warn "Tests not built. Building first..."
        do_build
        EXEC=$(find_executable "list_test")
        if [ -z "$EXEC" ]; then
            error "Test executable still not found after build!"
            exit 1
        fi
    fi

    info "Running: $EXEC"
    "$EXEC"
}

do_clean() {
    info "Cleaning build directory..."
    rm -rf "$BUILD_DIR"
    info "Clean done."
}

do_all() {
    do_build
    echo
    do_test
    echo
    do_list_test
}

show_help() {
    echo "Generic Linked List Library - Build & Test Script"
    echo "Usage: $0 [command]"
    echo
    echo "Commands:"
    echo "  build       仅编译项目"
    echo "  test        运行算法测试"
    echo "  list-test   运行链表单元测试(共118项)"
    echo "  clean       删除构建目录"
    echo "  all         编译 + 运行全部测试"
    echo "  help        显示帮助"
}

case "${1:-all}" in
    build) do_build ;;
    test) do_test ;;
    list-test) do_list_test ;;
    clean) do_clean ;;
    all) do_all ;;
    help|--help|-h) show_help ;;
    *) error "Unknown command: $1"; show_help; exit 1 ;;
esac