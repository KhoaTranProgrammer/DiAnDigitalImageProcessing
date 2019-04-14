# Which compiler
CC = gcc
INCLUDE = ..\..\..\include
SOURCE = ..\..\..\source
MAIN = ..\..\..\app\SampleWS

objects = main.o DADIP_BMP.o DADIP_Convert.o DADIP_FileIO.o DADIP_Filter.o DADIP_Geometry.o DADIP_Histogram.o DADIP_ImageIO.o DADIP_Math.o DADIP_Overlay.o DADIP_Rotate.o DADIP_Utility.o DADIP_Warping.o

# Build application
SampleWS: $(objects)
	$(CC) -I$(INCLUDE) -o $@ $^

# Build DADIP library to objects
%.o: $(SOURCE)/%.c
	$(CC) -c -I$(INCLUDE) -o $@ $<

# Build main function to object
%.o: $(MAIN)/%.c
	$(CC) -c -I$(INCLUDE) -o $@ $<

# Remove application and objects	
clean:
	-rm SampleWS $(objects)
