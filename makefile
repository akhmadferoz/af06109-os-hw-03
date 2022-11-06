compile:
	@echo "Compiling..."
	gcc -Wall -lpthread ./**/*.c -o LazyShell.out -v
	@echo "Done."

run:
	@echo "Starting lazy shell..."
	./LazyShell.out