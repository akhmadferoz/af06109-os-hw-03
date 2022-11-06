build:
	@echo "Compiling..."
	gcc -Wall -lpthread ./**/*.c -o LazyShell.out -v
	@echo "Done."

rebuild:
	@echo "Rebuilding..."
	rm -rf LazyShell.out
	gcc -Wall -lpthread ./**/*.c -o LazyShell.out -v
	@echo "Done."

clean:
	@echo "Cleaning..."
	rm -rf LazyShell.out
	@echo "Done."

run:
	@echo "Starting lazy shell..."
	./LazyShell.out