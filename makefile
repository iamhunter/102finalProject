RAYOBJS = main.o camera.o list.o  model.o material.o object.o plane.o \
          parser.o  vector.o pixel.o image.o raytrace.o sphere.o light.o \
          triangle.o fplane.o\
#         pplane.o tplane.o light.o sphere.o  tplane.o\
#         revsurf.o texplane.o texture.o \
#         spotlight.o tplane.o ellipse.o  cylinder.o \

INCLUDE = ray.h rayhdrs.h rayfuns.h vector.h pixel.h

CFLAGS = 
 -DAA_SAMPLES=1
# -DDBG_PIX -DDBG_HIT -DDBG_DRGB
# -DDBG_PIX -DDBG_DRGB
# -DSOFT_SHADOWS


ray: $(RAYOBJS)
	g++ -Wall -o ray -g -pg $(RAYOBJS) -lm

$(RAYOBJS): $(INCLUDE) makefile

.c.o: $<
	-g++ -c -Wall $(CFLAGS) -c -g $<  2> $(@:.o=.err)
	cat $*.err

.cpp.o: $<
	-g++ -c -Wall $(CFLAGS) -c -g $<  2> $(@:.o=.err)
	cat $*.err

clean:
	rm *.o *.err