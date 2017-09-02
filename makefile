all: libglmnet.a

OPT = -O3

libglmnet.a: GLMnet.o
	ar rcs libglmnet.a GLMnet.o

#libglmnet.a: glmnet5.o
#	ar rcs libglmnet.a glmnet5.o

glmnet5.o: glmnet5.f90
	gfortran $(OPT) -c -fPIC -Wall -Wextra -ggdb glmnet5.f90

GLMnet.o: GLMnet.f
	gfortran $(OPT) -c -fPIC -Wall -Wextra -ggdb GLMnet.f

.PHONY: clean

clean:
	rm -rfv *.o *.a

