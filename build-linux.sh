set -e

mkdir -p build
cd build

cmake .. 
make

echo -e "\n============ Running CocCoc ============"
./CocCoc