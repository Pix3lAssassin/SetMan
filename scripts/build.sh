SCRIPT=$(readlink -f "$0")
SCRIPT_DIR=$(dirname "$SCRIPT")
PROJECT_DIR=${SCRIPT_DIR/\/scripts/}
if [ ! -d "$PROJECT_DIR/target" ]; then
  mkdir -p "$PROJECT_DIR/target"
fi
/usr/bin/clang++ -fcolor-diagnostics -fansi-escape-codes -std=c++20 -g $PROJECT_DIR/src/main.cpp -o $PROJECT_DIR/target/setman