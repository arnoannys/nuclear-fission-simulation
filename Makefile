#Makefile voor opdracht
# Arno Annys 
# arno.annys@student.uantwerpen.be
#


COMPILER = g++ -Wall
LIBDIR = `root-config --glibs --cflags`

#aanroepen met make all
all : main1 main2 neutron isotoop kern bol cilinder plot


main1: main1.cpp neutron isotoop kern bol cilinder plot
	$(COMPILER)  -o $@ main1.cpp neutron.o isotoop.o bol.o cilinder.o kern.o plot.o $(LIBDIR) 
main2: main2.cpp neutron isotoop kern bol cilinder plot
	$(COMPILER)  -o $@ main2.cpp neutron.o isotoop.o bol.o cilinder.o kern.o plot.o $(LIBDIR)  
bol: bol.cpp 
	$(COMPILER)  -c bol.cpp  $(LIBDIR)  
cilinder: cilinder.cpp 
	$(COMPILER)  -c cilinder.cpp  $(LIBDIR) 
neutron: neutron.cpp
	$(COMPILER)  -c neutron.cpp $(LIBDIR)  #soort van lib gebruikt door executable
kern: kern.cpp 
	$(COMPILER)  -c kern.cpp  $(LIBDIR) 
isotoop: isotoop.cpp
	$(COMPILER)  -c isotoop.cpp $(LIBDIR)  
plot:plot.cpp
	$(COMPILER)  -c plot.cpp $(LIBDIR)  


#aanroepen met make clean
clean:
	rm -f main1     
	rm -f main2
	rm -f neutron
	rm -f isotoop
	rm -f kern
	rm -f bol
	rm -f cilinder