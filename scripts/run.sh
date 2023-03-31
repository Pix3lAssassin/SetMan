SCRIPT=$(readlink -f "$0")
SCRIPT_DIR=$(dirname "$SCRIPT")
PROJECT_DIR=${SCRIPT_DIR/\/scripts/}
if [ -f "$PROJECT_DIR/target/setman" ]; then
  $PROJECT_DIR/target/setman
else
  echo "Could not find executable script \"setman\""
fi
