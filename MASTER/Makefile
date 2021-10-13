CXX = g++
OBJS = formats.o openFiles.o printFiles.o opcodeTableBinary.o

dxe: $(OBJS)
	$(CXX) -o dxe $(OBJS)

openFiles.o: openFiles.cpp openFiles.h
	$(CXX) -c -std=c++11 openFiles.cpp

printFiles.o: printFiles.cpp printFiles.h openFiles.h formats.h
	$(CXX) -c -std=c++11 printFiles.cpp

formats.o: formats.cpp formats.h openFiles.h opcodeTableBinary.h
	$(CXX) -c -std=c++11 formats.cpp

opcodeTableBinary.o: opcodeTableBinary.cpp opcodeTableBinary.h
	$(CXX) -c -std=c++11 opcodeTableBinary.cpp

clean:
	rm -rf $(OBJS) dxe *.sic *.lis 
