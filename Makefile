CXX = g++

EXEC = main
CXXFLAGS = -g --std=c++17 -F /Library/Frameworks -MMD
LDFLAGS = -framework SDL2 -F /Library/Frameworks -I /Library/Frameworks/SDL2.framework/Headers
OBJECTS = main.o hittable_list.o camera.o material.o sphere.o ray.o vec3.o
DEPENDS = ${OBJECTS:.o=.d}

${EXEC}: ${OBJECTS}
	${CXX} ${CXXFLAGS} ${OBJECTS} ${LDFLAGS} -o ${EXEC}

-include {DEPENDS}

clean:
	rm ${OBJECTS} ${EXEC} ${DEPENDS}
