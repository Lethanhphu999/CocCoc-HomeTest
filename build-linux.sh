set -e

BUILD_TYPE="Release"
ENABLE_TEST=OFF

for arg in "$@"
do
  case $arg in
    --debug)
      BUILD_TYPE="Debug"
      ;;
    --test)
      ENABLE_TEST=ON
      ;;
  esac
done

echo "Configuring with BUILD_TYPE=$BUILD_TYPE, ENABLE_TEST=$ENABLE_TEST"

mkdir -p build
cd build

cmake -DCMAKE_BUILD_TYPE=$BUILD_TYPE ..
cmake --build .

if [[ "$ENABLE_TEST" == "ON" ]]; then
  echo "Running tests..."
  ctest
else  
  echo -e "\n============ Running CocCoc-HomeTest ============"
  ./CocCoc-HomeTest
fi