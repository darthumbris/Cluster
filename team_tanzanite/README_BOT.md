# Go team Tanzanite

Team Tanzanite presents: a demonstration of the bot interface for Cluster, written in C.

# Steps to make:

	Quick guide:
	1.	brew install glfw
	2.	make files
	3.	make MAIN=sample_bot.c
	4.	cp cluster bot
	5.	make fclean bots
	6.	mkfifo p1_in p1_out p2_in p2_out (all required for bot gameplay)
	7.	./bot p1_out p1_in &
	8.	disown $!
	9.	./bot p2_out p2_in &
	10.	disown $!
	11.	./cluster
	12.	???
	13.	Profit!
