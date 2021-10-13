#########################################
# Students involve: (Name, account, Red ID)
#	Kotaro Ueoka, cssc1947, (RedID 821442616)
#	Liliana Guerrero, cssc1948, (RedID 821798582)
#	Marie Duffy, cssc1949, (RedID 821505237)
#	Kyle McLain Kane, cssc1950, (RedID 820003555)
# Class: CS 530, Spring 2020
# Assignment information: Assignment #2, XE Disassembler
# Filename: Makefile
#########################################

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
	
#################[EOF: Makefile]########
