flags = -Wall -Wextra -Werror
name = -o ../build
files = cipher.c dop.c logger.c
make: clear clean cipher
open: 
	../build/graph
clear:
	clear
clean:
	rm -rf *.o ../build/cipher
cipher:
	gcc $(flags) $(files) $(name)/cipher
check:
	clang-format -i *.c
	cppcheck —enable=all —suppress=missingIncludeSystem *.c
	leaks -atExit -- ../build/cipher
push:
	git switch develop
	rm -rf *.o
	cp ../materials/linters/.clang-format .
	clang-format -i *.h *.c
	git add .
	git commit -m "pushed with make"
	git push origin develop
test: clear
	gcc $(files) -o ../build/cipher
logging_cipher:
	gcc $(flags) $(files) $(name)/logging_cipher