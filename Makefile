# Autori: Vojtěch Jurka (xjurka08), Dávid Špavor (xspavo00)
# Makefile pre automatizaciu prekladu
#*******************
build: 
	cd src; \
	make	

run:
	cd src; \
	./mqtt-project

pack: *
	zip -r 1-xjurka08-xspavo00.zip *

clean: 
	rm -rf doc/*
	cd src; \
	make clean


doxygen: 
	doxygen src/Doxyfile
