CC       = g++
CPPFLAGS = -g # -Wall -Wmissing-declarations -Wmissing-prototypes -ansi -pedantic
LIBS     = -L/encs/lib/ -lglut -lGL -lGLU -lGL -L/usr/X11R6/lib -lXmu -lXext -lXt -lXi -lX11
TARGET   = softbody
INCLUDE  = -I/encs/include/GL -I../include

OBJECTS  := EulerIntegrator.o Integrator.o MidpointIntegrator.o RungeKutta4Integrator.o ViewSpace.o Simulation.o

.SUFFIXES: .cpp

.cpp.o:
	$(CC) -c $(CPPFLAGS) $(INCLUDE) -o $@ $<


all: $(OBJECTS)

Simulation.o: Simulation.cpp ../include/Simulation.h
ViewSpace.o: ViewSpace.cpp ../include/ViewSpace.h
EulerIntegrator.o: EulerIntegrator.cpp ../include/EulerIntegrator.h
Integrator.o: Integrator.cpp ../include/Integrator.h
MidpointIntegrator.o: MidpointIntegrator.cpp ../include/MidpointIntegrator.h
RungeKutta4Integrator.o: RungeKutta4Integrator.cpp ../include/RungeKutta4Integrator.h

clean:
	-rm -rf $(TARGET) *.pch *.ilk *.opt *.plg *.ncb Debug Release *.o

