# Implementation of "How To Color in Coloring Book"
In this project, done for credit towards IS F311 (Computer Graphics), we implement a flood fill algorithm that can be used to shade areas that are defined by their boundaries. We implement the paper by Henry Lieberman. The group members in this project are: 

1. Prasoon Baghel
2. Shreya Manish Jambavalikar
3. Rohit Dwivedula

## The Algorithm
The algorithm is implemented in the `shade.cpp` file, and these are the relevant functions that you should be looking at: 

- `lookforSTurns`
- `lookforUTurns`
- `shadeHorizontally`
- `shade_vertically`
- `shade`

All of these functions are implementations of the psuedocode that is given in the paper (which has also been submtted in the zip file). This is a broad explanation of how the algorithm works: 

1. When a user clicks any point on the canvas, a function call is made to `shade` with the arguments to the function being: (i) the point or location the user clicked and (ii) the target colour that needs to be filled. 
2. The shading algorithm explained in this paper tries to access elements row by row since that is more efficient (elements in the same row are stored continuously in memory and will require lesser memory accesses to work). The algorithm works row-by-row. Firstly, it traverses from the selected point rightwards till it encounters the boundary. Then it repeats the same thing, leftwards. After this, it creates an object of type `HorizontalLine` that stores the y coordinate of the horizontal line, and x-coordinates of both ends. Once this line is detected, all the pixels in that line are shaded in the target colour. 
3. When shading concave or weirdly shaped areas, simple algorithms that just go shading row-by-row might not work. This paper proposes to solve this problem by keeping track of things called `s turns` and `u turns`. Let us say you shaded one row entirely. Next, you select a pixel that is one row above (or below) the current row. There we identify all the horizontal lines that need to be shaded (using the same method as described above). Let us say we shaded 5 pixels in a row (row 1), and all five pixels in the row just above it (row 2) aren't boundary points - that means that we need to shade them. Since these are not the boundary points, there may be more points two rows above (row 3) which also need to be shaded. So, we mark the line in row 2 as an `agenda`, which means, something that needs to be shaded. Now let us say in row 2, there are some points which need to be shaded, that are NOT immediately above a point that has been shaded in row 1 - this is called a `u turn`, since we need to go back down and shade these points as well. The functions `lookforUTurns` and `lookforSTurns` search for these kind of positions and mark them as agendas. 
4. To keep track of these turns, the algorithm works by maintaining something called an `agenda` list. An `agenda` is an object that has three elements: a horizontal line, a direction, and the color. Our implementation of the algorithm has two agenda lists, one for the places where you need to go up and another for places where you need to go down. Since each agenda represents an area that has not been shaded yet, we must continue shading as long as the agenda list is not empty. While shading one agenda, one or more new agendas may get added to the list. This is basically what is happening in the `while` loop in the `shade` function. In that loop, we first try to complete all the agendas that ask us to search upwards and then complete all agendas that need to be searched downwards - while searching downwards, encountering a `u turn` would mean that an agenda where we need to search up is added to the list again. The loop alternates between trying to empty the `agendaListUP` and `agendaListDOWN` until both lists are empty.
5. When both lists are empty, shading is successfully done. Images for examples of S-turns and U-turns are available in the attached PDF paper to this directory. 

# Instructions to Run

1. A `Makefile` has been configured for this program, which was written in C++ using OpenGL. Run `make` to create executable binaries. 
2. Run the created `.obj`/`.o` file. Example images that you can colour with colours from the palette are present in the `pngs` directory. 
3. HTML Documentation of the code and explanation of the algorithm is available in the `html` directory. Doxygen has been used to document parts of the code and the setup file for that can be found in `.doxygen-config`. To generate HTML and LaTeX files, run `doxygen .doxygen-config` on any system that has `doxygen` installed. 