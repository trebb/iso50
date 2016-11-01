all: bottom-label-de.pdf frame.stl bottom-label-pcb-de.pdf frame-pcb.dxf

%.pdf: %.svg
	inkscape --export-pdf $@ $<

%.stl: %.scad %.dxf
	openscad -o $@ $<

clean:
	rm -f *.pdf *.stl
