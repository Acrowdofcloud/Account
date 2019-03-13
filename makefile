executable: Account.cpp
	@g++ $< -o $@ -pedantic-errors -std=c++11

run:
	@./executable

clean:
	@rm executable
	
