OPENGLLIB= -lGL
GLEWLIB= -lGLEW
GLFWLIB = -lglfw
LIBS=$(OPENGLLIB) $(GLEWLIB) $(GLFWLIB)
LDFLAGS=-L/usr/local/lib 
CPPFLAGS=-I/usr/local/include -std=c++11

BIN1=asssigment_O1
SRCS1=main.cpp gl_framework.cpp shader_util.cpp object.cpp
INCLUDES= gl_framework.hpp object.hpp shader_util.hpp

all: $(BIN1) pen.raw bat.raw headPhone.raw

$(BIN1): $(SRCS1) $(INCLUDES)
	g++ $(CPPFLAGS) $(SRCS1) -o $(BIN1) $(LDFLAGS) $(LIBS)

pen.raw: pen.cpp
	g++ -std=c++11 pen.cpp -o pen
	./pen

bat.raw: bat.cpp
	g++ -std=c++11 bat.cpp -o bat
	./bat

headPhone.raw: headPhone.cpp
	g++ -std=c++11 headPhone.cpp -o headPhone
	./headPhone

clean:
	rm -f *~ *.o $(BIN1) $(BIN2) *.raw pen bat headPhone
