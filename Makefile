CC=g++
coloring_book_make: main.cpp shade.cpp png_image.cpp lodepng.cpp
	$(CC) -o coloring_book.o main.cpp shade.cpp png_image.cpp lodepng.cpp -lglut -lGL -lGLU -lpng