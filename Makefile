# Push the gh-pagesd www directory to Github Pages

gh-pages:
	rm -rf gh-pages
	mkdir gh-pages
	cp hardware/bottom-label-de.svg gh-pages/
	cp hardware/bottom-label-pcb-de.svg gh-pages/
	(cd hardware; $(MAKE) frame.stl frame-pcb.stl)
	cp hardware/frame.stl gh-pages/
	cp hardware/frame-pcb.stl gh-pages/
	cp hardware/top-plate.dxf gh-pages/
	cp hardware/top-plate-pcb.dxf gh-pages/
	cp hardware/pcb-top-plate/plot_files/pcb-top-plate.zip gh-pages/
	-cp hardware/pcb-top-plate/plot_files/pcb-top-plate.pdf gh-pages/
	-cp hardware/pcb-top-plate/plot_files/pcb-top-plate-brd.svg gh-pages/
	cp hardware/pcb-main/plot_files/pcb-main.zip gh-pages/
	-cp hardware/pcb-main/plot_files/pcb-main.pdf gh-pages/
	-cp hardware/pcb-main/plot_files/pcb-main-brd.svg gh-pages/
	cp hardware/bottom-plate.dxf gh-pages/
	cp hardware/bottom-plate-pcb.dxf gh-pages/
	(cd firmware; $(MAKE) program)
	cp firmware/iso50_lufa.hex gh-pages/iso50-lufa.hex
	(cd firmware-pcb; $(MAKE) program)
	cp firmware-pcb/iso50_lufa.hex gh-pages/iso50-lufa-pcb.hex
	echo '<h3>Generated files for project <a href="https://github.com/trebb/iso50">ISO50</a></h3>' > gh-pages/index.html
	ls gh-pages | \
		grep -v index.html | \
		sed -e 's/^\(.*\)$$/<a href="\1">\1<\/a><br>/' >> gh-pages/index.html

publish: gh-pages
	(cd gh-pages; \
	git init; \
	git add ./; \
	git commit -a -m "gh-pages pseudo commit"; \
	git push git@github.com:trebb/iso50.git +master:gh-pages)

clean:
	rm -rf gh-pages
