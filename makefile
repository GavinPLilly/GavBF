gavbf: gavbf.cpp
	g++ gavbf.cpp -o gavbf

run-hello-world: gavbf.cpp
	@./gavbf helloworld.bf

.PHONY: clean
clean:
	rm -f gavbf
