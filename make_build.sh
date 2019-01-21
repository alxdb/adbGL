mkdir -p build
cmake -B build -S .
ln -sf build/compile_commands.json compile_commands.json
