CC = g++
CFLAGC =  -Wall -Werror -Wextra  -std=c++17 -lgtest -lgtest_main -lpthread --coverage


all: test

# for linux: -lcheck -lpthread -pthread -lrt -lm -lsubunit
test: clean
	$(CC) $(CFLAGC)  model/*.cc controller/*.cc test/*.cc -o tests
	./tests

gcov_report: clean test
	./tests
	lcov -t "tests" -o tests.info -c -d . 
	genhtml -o report tests.info
	open report/index.html

install:
	make clean
	mkdir build
	cd build&&qmake ../view/calc.pro&&make&&mv calc.app ../calc.app
	cd build&&rm -rf *.*&&rm -rf Makefile&&rm -rf .qmake.stash
	rm -rf view/calc.pro.user
	rm -rf build

uninstall:
	rm -rf calc.app

dvi:
	open dvi.txt

dist:
	rm -rf Archive_SmartCalc_v2.0/
	mkdir Archive_SmartCalc_v2.0/
	mkdir Archive_SmartCalc_v2.0/src
	mv calc.app Archive_SmartCalc_v2.0/src/
	tar cvzf Archive_SmartCalc_v2.0.tgz Archive_SmartCalc_v2.0/
	rm -rf Archive_SmartCalc_v2.0/

clean:
	rm -rf *.{a,o,dSYM,out}
	rm -rf $(EXECUTABLE)
	rm -rf gcov_report
	rm -rf report
	rm -rf CPPLINT.cfg
	rm -rf *.gcda
	rm -rf *.gcno
	rm -rf *.info
	rm -rf Archive_SmartCalc_v2.0 
	rm -rf *tgz
	rm -rf tests
	rm -rf calc.app

rebuild: clean all

linter:
		cp ../materials/linters/.clang-format ..
		clang-format -i test/*.cc controller/*.cc controller/*.h model/*.cc model/*.h view/*.h view/*.cpp
		rm -rf ../.clang-format

leak:
		CK_FORK=no leaks --atExit -- ./tests
style:
		cp ../materials/linters/.clang-format ..
		clang-format -n test/*.cc controller/*.cc controller/*.h model/*.cc model/*.h view/*.h view/*.cpp
		rm -rf ../.clang-format