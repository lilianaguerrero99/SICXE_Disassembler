Please look at my comments on the code, I also have several helper functions that could be removed such as GetHexStringFromBinaryString
and GetBinaryStringFromHexString depending on our implementation. Also there are a few format 2 instructions I did not do such as;
COMPR, and SVC because I dont know how it affects the registers.

ALSO VERY IMPORTANT:
In SHIFTL AND SHIFTR
I am assuming that the n bits that we shift is the contents inside of r2, someone fact check me on this if wrong
Also when I do the SHIFTR it correctly shifts everything off but if it is a 0 hex val it will only print as 0 instead of 0000
