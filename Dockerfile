# Use a base image with GTK4 and development tools
FROM ubuntu:22.04

# Install dependencies
RUN apt-get update && apt-get install -y \
    build-essential \
    gcc \
    libgtk-4-dev \
    git \
    pkg-config \
    && rm -rf /var/lib/apt/lists/*

# Set the working directory
WORKDIR /app

# Copy the project files into the container
COPY . /app

# Expose any necessary ports (if needed)
EXPOSE 8080

# Default command (can be overridden in docker-compose)
CMD ["make", "run"]
