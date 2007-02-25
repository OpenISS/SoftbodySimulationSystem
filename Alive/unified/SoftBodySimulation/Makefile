CC       = g++
CPPFLAGS = -g # -Wall -Wmissing-declarations -Wmissing-prototypes -ansi -pedantic
LIBS     = -L/encs/lib/ -lglut -lGL -lGLU -lGL -L/usr/X11R6/lib -lXmu -lXext -lXt -lXi -lX11
TARGET   = softbody
INCLUDE  = -I/encs/include/GL -I../gfx -I../common

OBJECTS  := \
	common/Object.o \
	common/Object1D.o \
	common/Object2D.o \
	common/Object3D.o \
	common/Vector.o \
	common/Spring.o \
	common/Particle.o \
	common/Face.o \
	simulation/ViewSpace.o \
	simulation/Simulation.o \
	simulation/EulerIntegrator.o \
	simulation/Integrator.o \
	simulation/MidpointIntegrator.o \
	simulation/RungeKutta4Integrator.o

.SUFFIXES: .cpp

.cpp.o:
	$(CC) -c $(CPPFLAGS) $(INCLUDE) -o $@ $<


all: $(TARGET)

$(TARGET):
	make -C common all
	make -C simulation all
	$(CC) $(LIBS) $(OBJECTS) -o $(TARGET)

clean:
	make -C common $@
	make -C simulation $@
	-rm -rf $(TARGET) *.pch *.ilk *.opt *.plg *.ncb Debug Release *.o

