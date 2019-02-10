OBJECTS = 

all: $(OBJECTS)
	node-gyp configure
	node-gyp build
	node index.js

distclean: clean

clean:
	rm -f $(OBJECTS)
	rm -rf ./build

