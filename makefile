drawing: line.c
	gcc line.c -o drawing

run: drawing
	./drawing
	display image.ppm	

clean:
	rm *~ *.ppm
