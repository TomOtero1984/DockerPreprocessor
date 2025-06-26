

# 🐳 DockerPreprocessor

**DockerPreprocessor** is a lightweight C utility that injects environment variables into templated Dockerfiles. It’s part of the larger `Portfolio` ecosystem and was designed to support clean, secure Docker builds across environments like local dev, CI/CD, and VPS deployments.

## ✨ Features

- Parses `.env` files (`KEY=value` format)
- Replaces `${VAR}` placeholders in Dockerfile templates
- Outputs a production-ready `Dockerfile`
- Simple, dependency-free C implementation
- Portable across Linux and macOS

## 🚀 Usage

### 1. Prepare your files

- Create a `.env` file:
  ```env
  PORT=8080
  API_KEY=supersecret
  ```

- Create a `Dockerfile.in`:
  ```Dockerfile
  FROM alpine
  ENV PORT=${PORT}
  ```

### 2. Compile the tool

```bash
gcc -std=c11 -Wall -Wextra -o DockerPreprocessor main.c \
  lib/config_parser/src/config_parser.c \
  lib/logger/src/logger.c \
  -Ilib/config_parser/include \
  -Ilib/logger/include
```

### 3. Run the processor

```bash
./DockerPreprocessor
```

This will read `.env`, parse `Dockerfile.in`, and write a finalized `Dockerfile`.

## 🔧 Configuration

Optionally edit `config.ini` to adjust logging, verbosity, etc. (Logger module WIP)

## 🧠 Project Context

DockerPreprocessor is a utility within the [Portfolio](#) project, a full-stack deployment pipeline involving:

- A Vue/Vite frontend
- Docker Compose deployment
- Remote VPS hosting
- CI/CD via GitHub Actions
- OpenVPN containerization

## 📜 License

MIT (or insert license here)