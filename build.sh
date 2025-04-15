# Thoát nếu có lỗi
set -e

# Tạo thư mục build nếu chưa có
mkdir -p build
cd build

# Chạy cmake và build
cmake .. 
make

# Chạy chương trình sau khi build
echo -e "\n=== Running CocCoc ==="
./CocCoc