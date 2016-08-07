all: bottom-label-de.pdf frame.stl

%.pdf: %.svg
	inkscape --export-pdf $@ $<

%.stl: %.scad %.dxf
	openscad -o $@ $<

clean:
	rm -f *.pdf *.stl
