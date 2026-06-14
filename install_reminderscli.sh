#!/usr/bin/env bash
set -e

# ─────────────────────────────────────────────
#  Instalador de reminderscli
#  https://github.com/AriSophDev/reminderscli
# ─────────────────────────────────────────────

REPO_URL="https://github.com/AriSophDev/reminderscli.git"
BUILD_DIR="reminderscli/build"
INSTALL_BIN="/usr/local/bin/reminders_app"

GREEN="\033[0;32m"
RED="\033[0;31m"
YELLOW="\033[1;33m"
NC="\033[0m"

info()    { echo -e "${GREEN}[✔]${NC} $1"; }
warn()    { echo -e "${YELLOW}[!]${NC} $1"; }
error()   { echo -e "${RED}[✘]${NC} $1"; exit 1; }

# ── 1. Detectar gestor de paquetes y dependencias ──
install_deps() {
  echo ""
  warn "Comprobando dependencias (git, cmake, g++, make)..."

  if command -v apt-get &>/dev/null; then
    sudo apt-get update -qq
    sudo apt-get install -y git cmake g++ make
  elif command -v dnf &>/dev/null; then
    sudo dnf install -y git cmake gcc-c++ make
  elif command -v pacman &>/dev/null; then
    sudo pacman -Sy --noconfirm git cmake gcc make
  elif command -v brew &>/dev/null; then
    brew install git cmake
    # g++ y make vienen con Xcode CLT en macOS
  else
    warn "No se reconoció tu gestor de paquetes."
    warn "Asegúrate de tener instalados: git, cmake, g++ (o clang++), make."
  fi
}

# ── 2. Verificar herramientas mínimas ──
check_tools() {
  for tool in git cmake; do
    command -v "$tool" &>/dev/null || { warn "Falta '$tool', intentando instalar dependencias..."; install_deps; break; }
  done

  for tool in git cmake; do
    command -v "$tool" &>/dev/null || error "'$tool' no encontrado tras intentar instalar dependencias."
  done

  # Verificar compilador C++
  if ! command -v g++ &>/dev/null && ! command -v clang++ &>/dev/null; then
    warn "No se encontró compilador C++, intentando instalar..."
    install_deps
  fi
}

# ── 3. Clonar o actualizar repo ──
fetch_repo() {
  if [ -d "reminderscli" ]; then
    warn "El directorio 'reminderscli' ya existe. Actualizando..."
    cd reminderscli && git pull && cd ..
  else
    info "Clonando repositorio..."
    git clone "$REPO_URL"
  fi
}

# ── 4. Compilar ──
build() {
  info "Configurando con CMake (esto puede tardar unos minutos la primera vez)..."
  cmake -S reminderscli -B "$BUILD_DIR" -DCMAKE_BUILD_TYPE=Release

  info "Compilando..."
  cmake --build "$BUILD_DIR" --parallel "$(nproc 2>/dev/null || sysctl -n hw.logicalcpu 2>/dev/null || echo 2)"
}

# ── 5. Instalar binario ──
install_bin() {
  BINARY="$BUILD_DIR/reminders_app"

  if [ ! -f "$BINARY" ]; then
    error "No se encontró el binario compilado en '$BINARY'."
  fi

  info "Instalando binario en $INSTALL_BIN ..."
  sudo cp "$BINARY" "$INSTALL_BIN"
  sudo chmod +x "$INSTALL_BIN"
}

# ── Main ──
echo ""
echo "════════════════════════════════════════"
echo "   Instalador de reminderscli"
echo "════════════════════════════════════════"
echo ""

check_tools
fetch_repo
build
install_bin

echo ""
echo "════════════════════════════════════════"
info "¡Instalación completada!"
echo ""
echo "  Ejecuta:  reminders_app"
echo "════════════════════════════════════════"
echo ""
