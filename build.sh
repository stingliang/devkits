#!/bin/bash

# 默认使用的CPU核心数
core_count=4
# 默认的编译类型
build_type="Release"
# 是否清除编译缓存的标志
clear_cache=false

# 显示帮助信息
function show_help() {
    echo "用法: $0 [--cores <核心数>] [--build-type <类型>] [-c|--clear] [-h|--help]"
    echo "指定编译时使用的CPU核心数、编译类型和项目。"
    echo "  --cores <核心数>         指定使用的CPU核心数（默认为4）。"
    echo "  --build-type <类型>      指定编译类型（默认为Release），可选值为Release/RelWithDebInfo/Debug。"
    echo "  -c, --clear             清除编译缓存并重新编译。"
    echo "  -h, --help              显示帮助信息。"
    exit 1
}

function parse_args() {
    while [[ $# -gt 0 ]]; do
        key="$1"

        case $key in
            --cores)
                core_count="$2"
                shift
                shift
                ;;
            --build-type)
                build_type="$2"
                shift
                shift
                ;;
            -c|--clear)
                clear_cache=true
                shift
                ;;
            -h|--help)
                show_help
                ;;
            *)
                echo "未知选项: $1"
                show_help
                exit 1
                ;;
        esac
    done
}

function build() {
    # 检查编译类型的合法性
    if [[ ! $build_type =~ ^(Release|RelWithDebInfo|Debug)$ ]]; then
        echo "错误：不支持的编译类型: $build_type"
        exit 1
    fi

    # 转换为小写
    build_dir=cmake-build-$(echo ${build_type} | tr '[A-Z]' '[a-z]')

    # 获取当前目录
    DIR="$( cd "$( dirname "${BASH_SOURCE[0]}" )" && pwd )"

    # CMAKE选项
    CMAKE_OPTIONS="-DCMAKE_BUILD_TYPE=${build_type}"

    # 编译命令
    COMMAND="mkdir -p ${build_dir} && cd ${build_dir} && cmake ${CMAKE_OPTIONS} .. && make -j${core_count}"

    # 清除编译缓存
    if [ "$clear_cache" = true ]; then
        echo "清除编译缓存..."
        rm -rf ${build_dir} output
    fi

    bash -c "${COMMAND}"
    ret=$?
    return $ret
}

function main() {
    parse_args $@
    build
}

main $@
