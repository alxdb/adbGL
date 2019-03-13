rm -r build
mkdir -p build
cmake -DCMAKE_BUILD_TYPE=Debug -B build -S .
ln -sf build/compile_commands.json compile_commands.json
