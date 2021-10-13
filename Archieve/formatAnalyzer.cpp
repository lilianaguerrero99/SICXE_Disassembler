#include <iostream>
#include <string>
#include <vector>
#include <bitset>
#include <sstream>


using namespace std;

//Assuming no SIC format 1 commands
//Format 1 (First char should be c or f )
//Format 2 (First char should be 9,a, or b)
//Format 4 (3rd char should be a 1 or 9 for extended bit)
//Format 3 (Default if all cases fall through)
vector<string> getFormatArray(vector<string> vectorToSort){
    int lengthOfVectorInElements = vectorToSort.size();                                 //Gets the length of the vector
    string variable = "";                                                               //Initializing the string that we will be chopping up

    for(int i = 0; i < lengthOfVectorInElements; i++)                                   //For loop to append multiple elements to a single string
        variable.append(vectorToSort[i]);
    
    int stringLength = variable.length();                                               //Gets the length of the string we will be chopping up
    vector<string> v;                                                                   //This is the vector declaration to return our sorted vector
    int i = 0;
    
    while(i < stringLength){
        //Format 1 check case (1 byte)
        if(variable.at(i) == 'c' || variable.at(i) == 'f'){
            v.push_back(variable.substr(i, 2));
            i += 2;
        }

        //Format 2 check case (2 bytes)
        if(variable.at(i) == '9' || variable.at(i) == 'a' || variable.at(i) == 'b'){
            v.push_back(variable.substr(i, 4));
            i += 4;
        }

        //Format 4 check case   (4 bytes)
        if(variable.at(i+2) == '1' || variable.at(i+2) == '9'){
            v.push_back(variable.substr(i, 8));
            i += 8;
        }

        //Format 3 default  (3 bytes)
        else{          
            v.push_back(variable.substr(i, 6));
            i += 6;
        }       
    }

    return v;
}

vector<string> getBinaryValues(vector<string> vectorToBinary){
    vector <string> buff;                                                               //Creating a vector to store converted values   
    for(int i = 0; i < vectorToBinary.size(); i++){                                     //Looping through the vectors elements
        string store = "";                                                              //Reseting the store string/initializing the store string
        for(int j = 0; j < vectorToBinary[i].length(); j++){                            //Looping through each character in that element
            if(vectorToBinary[i].at(j) == '0')                                          //These if statements act as cases and they append the result to store that will go into its prospective element
                store.append("0000");
            if(vectorToBinary[i].at(j) == '1')
                store.append("0001");
            if(vectorToBinary[i].at(j) == '2')
                store.append("0010");
            if(vectorToBinary[i].at(j) == '3')
                store.append("0011");
            if(vectorToBinary[i].at(j) == '4')
                store.append("0100");
            if(vectorToBinary[i].at(j) == '5')
                store.append("0101");
            if(vectorToBinary[i].at(j) == '6')
                store.append("0110");
            if(vectorToBinary[i].at(j) == '7')
                store.append("0111");
            if(vectorToBinary[i].at(j) == '8')
                store.append("1000");
            if(vectorToBinary[i].at(j) == '9')
                store.append("1001");
            if(vectorToBinary[i].at(j) == 'A')
                store.append("1010");
            if(vectorToBinary[i].at(j) == 'B')
                store.append("1011");
            if(vectorToBinary[i].at(j) == 'C')
                store.append("1100");
            if(vectorToBinary[i].at(j) == 'D')
                store.append("1101");
            if(vectorToBinary[i].at(j) == 'E')
                store.append("1110");
            if(vectorToBinary[i].at(j) == 'F')
                store.append("1111");

            if(j == vectorToBinary[i].length() - 1)                                     //Stores the converted values into buffer once the element is
                buff.push_back(store);  
        }       
    }
    return buff;                                                                        //Returns a vector of our stored binary values
}


int main(){
    //REMOVE ME POST
    string test = "0500000320033F691017911BA0131BC0002F200A3B2FF40F102F014F0000";                             
    string test1 = "0500000320033F691017911BA0131BC0002F200A3B2FF40F102F014F0000";
    vector<string> testVector;
    testVector.push_back(test);
    testVector.push_back(test1);

    vector<string> sorted = getFormatArray(testVector);                                 //Stores the sorted format array
    vector<string> binaryValuesSorted = getBinaryValues(sorted);                        //Stores the binary converted sorted format array
    for(int i = 0; i< binaryValuesSorted.size(); i++)
        cout<<sorted[i] << " : " << binaryValuesSorted[i]<<endl;
    return 0;
}