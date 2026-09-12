FROM mcr.microsoft.com/vscode/devcontainers/python:3.13
WORKDIR /workspace

# Install system dependencies
RUN apt-get update && apt-get install -y \
    build-essential \
    curl \
    git \
    && rm -rf /var/lib/apt/lists/*

# Install Python dependencies

CMD ["sleep", "infinity"]