all:
	$(MAKE) -C src

clean:
	rm -f test1

# Builder will call this to install the application before running.
install:
	echo "Installing is not supported"

# Builder uses this target to run your application.
run:
	./test1
