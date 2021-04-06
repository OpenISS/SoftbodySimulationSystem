CC       = g++
CPPFLAGS = -g # -Wall -Wmissing-declarations -Wmissing-prototypes -ansi -pedantic
LIBS     = -L/encs/lib/ -lglut -lGL -lGLU -lGL -L/usr/X11R6/lib -lXmu -lXext -lXt -lXi -lX11
TARGET   = softbody
INCLUDE  = -I/encs/include/GL -I../include

OBJECTS  := Particle.o Vector.o Spring.o Face.o Object.o Object1D.o Object2D.o Object3D.o

.SUFFIXES: .cpp

.cpp.o:
	$(CC) -c $(CPPFLAGS) $(INCLUDE) -o $@ $<


all: $(OBJECTS)

$(TARGET): $(OBJECTS)
	$(CC) $(LIBS) $(OBJECTS) -o $(TARGET)

Vector.o: Vector.cpp ../include/Vector.h
Spring.o: Spring.cpp ../include/Spring.h
Face.o: Face.cpp ../include/Face.h
Object1D.o: Object1D.cpp ../include/Object1D.h
Object2D.o: Object2D.cpp ../include/Object2D.h
Object3D.o: Object3D.cpp ../include/Object3D.h
Object.o: Object.cpp ../include/Object.h
Particle.o: Particle.cpp ../include/Particle.h


clean:
	-rm -rf $(TARGET) *.pch *.ilk *.opt *.plg *.ncb Debug Release *.o

