#include "cluster.h"
#include "move.h"

int	main(int argc, char **argv)
{
	t_boards	*boards;
	char		**board;
	char		*raw;

	boards = initialize();
	board = boards->board_a;
	real_visualize_text(board);
	raw = boardstate_to_raw(board, TOTAL_COLUMNS * 2);
	printf("boardstate: <%s>\n", raw);
	board = boardstate_from_raw(raw, TOTAL_COLUMNS, TOTAL_COLUMNS);
	real_visualize_text(board);
	return (0);
}