set -e

BUILD_TYPE="Release"
if [[ "$1" == "--debug" ]]; then
  BUILD_TYPE="Debug"
fi

echo "-- Build type: $BUILD_TYPE"

mkdir -p build
cd build

cmake -DCMAKE_BUILD_TYPE=$BUILD_TYPE -G Ninja ..
ninja -j8

echo -e "\n============ Running CocCoc-HomeTest ============"

./CocCoc-HomeTest