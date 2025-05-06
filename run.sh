CC=gcc

$CC -o out/main.exe main.c bintree.c

if [ $? -eq 0 ]; then
    echo "Compilation successful. Running the program..."
    ./out/main.exe
else
    echo "Compilation failed."
fi