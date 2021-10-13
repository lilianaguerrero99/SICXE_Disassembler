Students involved:
- Kotaro Ueoka, cssc1947, (RedID 821442616)
- Liliana Guerrero, cssc1948, (RedID 821798582)
- Marie Duffy, cssc1949, (RedID 821505237)
- Kyle McLain Kane, cssc1950, (RedID 820003555)

CS530 Spring 2020

Program Assignment #2
XE DISASSEMBLER

README.txt

File manifest:
- README.txt
- formats.cpp
- formats.h
- opcodeTableBinary.cpp
- opcodeTableBinary.h
- openFiles.cpp
- openFiles.h
- printFiles.cpp
- printFiles.h
- Makefile

- sample1.obj
- sample1.sym
- sample2.obj
- sample2.sym

Instructions:
- Ensure that you have placed in the folder a appropriate .obj or .sym file with the same file name 
- First when you are in the correct file you type: make 
	- What this will do is it creates 4 .o files(formats.o, opcodeTableBinary.o, openFiles.o, and printFiles.o) using the files listed above, and importantly it creates a executable named dxe
- Now that you have your dxe, you want to: dxe <filename>
	- What this dxe does is using the files you have given it creates a .lis and a .sic file
	- NOTE: if you do not enter a valid name the program will not run (We have handled this error)
- Now that you you have the respective <filename>.lis and <filename>.sic you can open them up to see the results of the XE Dissasembler, (creating these files using your .obj and .sym files)

Compile Instructions:
	make 									(NOTE: has to be done in the file the code is in, and we compile using the g++ compiler)

Operating Instructions (In-order):
	make									(NOTE: This compiles our code)
	dxe <filename>								(NOTE: This creates a executable where we can enter the file name of the .sym and .obj to create a .lis and .sic)
	(from here you can open the newly created .sic and .lis files)
	make clean 								(NOTE: this will delete the dxe executable, all .sic files, all .lis files, and all .o files)		

Significant Design Choices:
- Makefile (when entering "make clean") we delete the dxe executable, all .sic files, all .lis files, and all .o files
- We chose to do the assignment in c++
- Our format 2,3 and 4 actually influence our registers
- We decided to give our opcode table its necessary binary code in 6 bits since the remaining 2 bits will always be 0
- We decided to use maps for the object code so we could create a key value pair to make readability easier
- We store our data in parallel vectors, while our final product is stored in a vector of vectors
- We decided to have a master format, that would direct the flow of the format calculations and it returns a vector of vectors
- We split our files into 4 different files based off what they do
- We split up the project into, open file, differentiate, calculate addresses, convert, opcode table, calculate, print (for testing), and wrtiting to files
- We handle literals in our differentiate
- We used maps to store things in a kev value pair such as registers to look up what value they are
- We used alot of stringstream to convert values into hex or binary
- We stored our values as strings once we were done with calculations to make the writing to file easier
- When reading in the files, we have the literals, header records, text records, and end records read into different functions
- We have a master format which is the function in charge for directing all of the formats

Extra Features:
- It can handle inproper file reading 
- We have split everything up logically to improve readability 
- We have a generic class to store the registers
- Using setw with our algorithm to create a proper amount of spacing

Known deficiencies or bugs:
- As of now, the code cannot handle when a literal actually shows up in the object code (ex: 'EOF')

Lessons Learned:
- Improved skills with reading in multiple files
- How to use vectors
- How to use maps
- Creating a generic class in c++
- The intricacies of Format 1, 2, 3, and 4
- How format 2 influences the registers
- How to calculate the PC, Base, and Index registers
- How memory, reserved or not influences the storage
- How to read object code and symbol tables
- How to write a format 4
- How to read/create new files based off output
- How to handle literals and what to do with them
- How the address in the .lis is calculated/works
- How to create a make file for multiple files
- How format 3 deals with base, PC, and indexed
- How to calculate the displacement for format 3 and 4
- How format 4 deals with indexed 
- How to effectively have group meetings
- How to set deadlines for memebers
- How to organize your project
- How to review and discuss others codes
- How to communicate better in a group setting

Explanation of process:
So for this project, we met multiple times a week to discuss how we would go about completing this project. From there we would create a minimum viable product that we would have to do which was copmpleted 3-4 weeks
before the deadline. We began by splitting up the program in its proper tasks that we had to accomplish to get to the finished product. We decided to have the project split by reading in the files, the opcode table,
the format calculations, and the reading out to files. In the Reading in the files, we decided we would error handle certain aspects of the files here, also we had read into multiple vectors the text records in order
to then feed that information into the format analyzer, which would split up the object code based off what format it is. Then from there we would feed that information into a binary converter, where we would store 
the binary converted hex into its own parallel vector. We did this in order to make the calculation process of which opcode that line is easier, (you can see this as our opcode table takes in 6 bits). From there we 
feed in all the necessary information into the formats.cpp where it would calculate what each opcode and information from the symbol table meant to better calculate our resulting .sic and .lis files. Also in this class 
we have our generic register class, so we can call and edit the contents of the individual registers to better modify our code. Also in this formats.cpp we have a master format, which would direct the object code to
the correct desination based off of the information from the format analyzer. An important design decision was made here, with the master format returning our final vector of vectors, which would then be sent to printFiles.cpp.
In our testing process we would use this printFiles.cpp as a testing zone where we would cout the calculated code, but now its intended purpose is to print out the resulting .lis and .sic files from the .obj and .sym
files we read into the openFiles.cpp.



