# Go team Tanzanite

Team Tanzanite presents: Cluster.

From the award winning board-game designers: The Deckhands.

# Steps to make:

	Quick guide:
	1. brew install glfw
	2. make files
	3. make (run "make bots" to enable preliminary bot support. Requires some dup2/fork/exec magic that we haven't yet implemented)
	4. mkfifo p1_in p1_out p2_in p2_out (for I/O. p1_out and p2_out aren't required for human player mode)
	5. run ./cluster

	Using different main:
	1. Put your .c file in main/
	2. make re MAIN=<YOUR_FILE.c> (you don't need to include the path)
	3. run!


# math for hexagons
	From Column number to TOP coordinates:
		column -= g_options.board_width - 2
		y = min(column + (SIDE * 2 - 2), SIDE * 2 - 2) 
		x = min(-column + (SIDE * 2 - 2), SIDE * 2 - 2)

	
