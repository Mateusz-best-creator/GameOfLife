#!/bin/bash

# Function to log messages with timestamp
log() {
    echo "$(date +'%Y-%m-%d %H:%M:%S') - $1"
}

# Check if CMake build directory exists
if [ ! -d "build" ]; then
    log "Error: CMake build directory not found. Please run 'cmake .' first."
    exit 1
fi

# Build the project using CMake
log "Building the project using CMake..."
if ! cmake --build build/; then
    log "Error: Failed to build the project."
    exit 1
fi

# Check if the executable exists
if [ ! -f "build/GameOfLife" ]; then
    log "Error: Executable 'GameOfLife' not found. Build may have failed."
    exit 1
fi

# Run the executable
log "Running the executable..."
if ! ./build/GameOfLife; then
    log "Error: Failed to run the executable."
    exit 1
fi

log "Script execution completed successfully."
