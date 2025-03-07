#!/bin/bash

function normal_msg() {
    echo $1
}

function info_msg() {
    echo -e "\e[32mINFO: $1\e[0m"
}

function warning_msg() {
    echo -e "\e[33mWARNING: $1\e[0m"
}

function error_msg() {
    echo -e "\e[31mERROR: $1\e[0m"
}

function install_docker() {
    # check if docker is installed
    if docker --version > /dev/null 2>&1; then
        normal_msg "Docker is already installed."
        return
    fi
    # Install Docker
    info_msg "Installing Docker..."
    apt-get update
    apt-get install -y apt-transport-https ca-certificates curl software-properties-common
    curl -fsSL https://download.docker.com/linux/ubuntu/gpg | apt-key add -
    add-apt-repository "deb [arch=amd64] https://download.docker.com/linux/ubuntu $(lsb_release -cs) stable"
    apt-get update
    apt-get install -y docker-ce containerd.io docker-ce-cli docker-compose
    # Check if Docker is installed successfully
    if [ $? -eq 0 ]; then
        info_msg "Docker installed successfully."
    else
        error_msg "Failed to install Docker."
        exit 1
    fi
}

function build_docker_image() {
    # Define variables
    IMAGE_NAME=$1
    IMAGE_TAG=$2
    BUILD_CORES=$3
    # check if Docker is installed
    install_docker
    # Build the Docker image by buildx
    export DOCKER_BUILDKIT=1
    BUILDER_NAME="app_image_builder"
    EXISTING_BUILDER=$(docker buildx ls --format '{{.Name}}' | grep -w "$BUILDER_NAME")
    if [ -z "$EXISTING_BUILDER" ]; then
        info_msg "creating builder $BUILDER_NAME"
        docker buildx create --name $BUILDER_NAME --use
    else
        info_msg "using existing builder $BUILDER_NAME"
        docker buildx use $BUILDER_NAME
    fi
    docker build -t $IMAGE_NAME:$IMAGE_TAG \
        --build-arg BUILD_CORES=$BUILD_CORES \
        --build-arg http_proxy=$http_proxy \
        --build-arg https_proxy=$https_proxy \
        --build-arg all_proxy=$all_proxy .
    # Check if the build was successful
    if [ $? -eq 0 ]; then
        info_msg "Docker image '$IMAGE_NAME':$IMAGE_TAG built successfully."
    else
        error_msg "Failed to build Docker image '$IMAGE_NAME':$IMAGE_TAG."
        exit 1
    fi
}

function check_root() {
    # Check if the script is running as root
    if [ "$EUID" -ne 0 ]; then
        error_msg "Please run as root."
        exit 1
    fi
}

function set_proxy() {
    # Define variables
    PROXY_IP=$1
    PROXY_PORT=$2
    if [ -z "$PROXY_IP" ] || [ -z "$PROXY_PORT" ]; then
        return
    fi
    # Set the proxy
    export http_proxy="http://$PROXY_IP:$PROXY_PORT"
    export https_proxy="http://$PROXY_IP:$PROXY_PORT"
    export all_proxy="http://$PROXY_IP:$PROXY_PORT"
}

function main() {
    # Check if the script is running as root
    check_root
    # Define variables
    IMAGE_NAME="app_image"
    IMAGE_TAG="v1.0"
    BUILD_CORES=12
    PROXY_IP="172.24.192.1"
    PROXY_PORT="5001"
    # Set the proxy
    set_proxy $PROXY_IP $PROXY_PORT
    # Build the Docker image
    info_msg "Building Docker image '$IMAGE_NAME':$IMAGE_TAG..."
    build_docker_image $IMAGE_NAME $IMAGE_TAG $BUILD_CORES
}

# Run the main function
main
