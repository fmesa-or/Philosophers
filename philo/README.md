To see memory leaks use:

valgrind ./program_name

Flags:
	--leak-check=full						->To see details of leaked memory
	--leak-check=full --show-leak-kinds=all -> To see all leaks and where
	--log-fd=1								->??????
	--track-origins=yes						->To see where unitialised values come
	--show-leaks-kinds=all					->??????
	--supressions=supressions.supp			->??????
	--trace-children=yes					->traces the children process and shows


Also use:

lldb

For correction:
valgrind --leak-check=full --show-leak-kinds=all ./philo ...
