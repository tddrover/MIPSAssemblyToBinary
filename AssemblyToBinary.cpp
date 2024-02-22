#include <iostream>
#include <cstdlib>
#include <fstream>
#include <iomanip>
#include <string>
#include <algorithm>
#include <bitset>
#include <sstream>




//Tyler Drover
//CS-250 Project




using namespace std;

int searchFileReg(string words[],int i);
int searchFileFun(string words[],int i);
string twosComplement(int num, int size);

int main()
{
	string filename, filename2, line;

	ifstream fp;
	ifstream fp2;
	ofstream out("outputProject.txt");
	int i=0;
	int count=0;
	string words[100];

	int fun, rs, rt, rd, constant;
	string op, off, shampt, funct, label, off2, shampt2;
	int num, size;
	string fun2, rs2, rt2, rd2, constant2,place;

	cout<<"Enter the MIPS file name: ";
	cin>> filename;

//	filename="mips.asm";
	fp.open(filename);
	while(getline(fp, line)){            //reads the mips file and puts every word into a string array
		size_t comment_pos = line.find('#');

		if(comment_pos != string::npos)
			line=line.substr(0, comment_pos);

		for(char c: line) {
			if(c == ','|| c == ' '  || c== '(' || c == ')'){
				if(!words[count].empty() && words[count][0] != ' ')
					count++;
			}else if(c!= '\t'){
				words[count]+=c;
			//	cout<<words[count]<<endl;
			}
		}
		if(!words[count].empty() && words[count][0] != ' ')
			count++;
	}

	for(int i=0; i< count; i++){         //searches the string array for functions
	//	cout<<words[i]<<endl;
		if(words[i]=="add"||words[i]=="sub"||words[i]=="slt"||words[i]=="and"||words[i]=="or"){
			fun=searchFileFun(words,i);
			rd=searchFileReg(words, i+1);
			rs=searchFileReg(words, i+2);
			rt=searchFileReg(words, i+3);

			fun2=twosComplement(fun, 6);
			rd2 =twosComplement(rd, 5);
			rs2 =twosComplement(rs, 5);
			rt2 =twosComplement(rt, 5);
			op = twosComplement(0, 6);
			shampt = twosComplement(0, 5);
			out<<op<<rs2<<rt2<<rd2<<shampt<<fun2<<endl;
			
			cout<<"Function: "<<words[i]<<"   Registers: "<<words[i+1]<<"  "<<words[i+2]<<"   "<<words[i+3]<<endl;
	
		}
		else if(words[i]=="lw" || words[i]=="sw"){
			fun=searchFileFun(words,i);
			rt=searchFileReg(words, i+1);
			off=words[i+2];
			rs=searchFileReg(words, i+3);
			if(rs==-1){
				rs2=twosComplement(0, 5);
				place="$zero";
			}
			else
				rs2 =twosComplement(rs, 5);

			fun2=twosComplement(fun, 6);
			rt2 =twosComplement(rt, 5);
			off2=twosComplement(stoi(off), 16);
			out<<fun2<<rs2<<rt2<<off2<<endl;

			cout<<"Function: "<<words[i]<<"  Registers: "<<words[i+1]<<"   "<<place<<"  Offset: "<<words[i+2]<<endl;
		}
		else if(words[i]=="sll" || words[i]=="srl"){
			fun=searchFileFun(words,i);
			rd=searchFileReg(words, i+1);
			rt=searchFileReg(words, i+2);
			shampt=words[i+3];

			fun2=twosComplement(fun, 6);
			rs2 =twosComplement(0, 5);
			rd2 =twosComplement(rd, 5);
			rt2 =twosComplement(rt, 5);
			op =twosComplement(0, 6);
			shampt2=twosComplement(stoi(shampt), 5);
			out<<op<<rs2<<rt2<<rd2<<shampt2<<fun2<<endl;

			cout<<"Function: "<<words[i]<<" Registers: "<<words[i+1]<<"   "<<words[i+2]<<" Shift: "<<words[i+3]<<endl;
		}
		else if(words[i]=="bne" || words[i]=="beq"){   //last one
			fun=searchFileFun(words,i);
			rs=searchFileReg(words, i+1);
			rt=searchFileReg(words, i+2);
			label=words[i+3];

			fun2=twosComplement(fun, 6);
			rs2 =twosComplement(rs, 5);
			rt2 =twosComplement(rt, 5);
			op =twosComplement(stoi(label), 16);
			out<<fun2<<rs2<<rt2<<op<<endl;

			cout<<"Function: "<<words[i]<<"  Registers "<<words[i+1]<<"   "<<words[i+2]<<"  Label: "<<words[i+3]<<endl;
		}
		else if(words[i]=="la"){
			fun=searchFileFun(words, i);
			rd=searchFileReg(words, i+1);
			label=words[i+2];

			fun2=twosComplement(fun, 6);
			rs2 =twosComplement(0, 5);
			rd2 =twosComplement(rd, 5);
			op=twosComplement(stoi(label), 16);
			out<<fun2<<rs2<<rd2<<op<<endl;

			cout<<"Function: "<<words[i]<<" Registers: "<<words[i+1]<<"  Label: "<<words[i+2]<<endl;
		}
		else if(words[i]=="j"){  
			fun=searchFileFun(words, i);
			label=words[i+1];

			fun2=twosComplement(fun, 6);
			op=twosComplement(stoi(label), 26);
			out<<fun2<<op<<endl;

			cout<<"Function: "<<words[i]<<"  Label: "<<words[i+1]<<endl;
		}
		else if(words[i]=="li"){  
			fun=searchFileFun(words, i);;
			rd=searchFileReg(words, i+1);
			constant=stoi(words[i+2]);

			fun2=twosComplement(fun, 6);
			rd2 =twosComplement(rd, 5);
			rs2 =twosComplement(0, 5);
			op =twosComplement(constant, 16);
			out<<fun2<<rs2<<rd2<<op<<endl;

			cout<<"Function: "<<words[i]<<"  Register: "<<words[i+1]<<"  Value: "<<words[i+2]<<endl;
		}
		else if(words[i]=="addi"){
			fun=searchFileFun(words,i);
			rd=searchFileReg(words, i+1);
			rs=searchFileReg(words, i+2);
			constant=stoi(words[i+3]);

			fun2=twosComplement(fun, 6);
			rd2 =twosComplement(rd, 5);
			rs2 =twosComplement(rs, 5);
			op  =twosComplement(constant, 16);
			out<<fun2<<rs2<<rd2<<op<<endl;

			cout<<"Function: "<<words[i]<<"  Registers: "<<words[i+1]<<"    "<<words[i+2]<<"  Value: "<<words[i+3]<<endl;

		}
		else if(words[i]=="move"){ 
			fun=searchFileFun(words, i);
			rd=searchFileReg(words, i+1); 
			rs=searchFileReg(words, i+2); 

			fun2=twosComplement(fun, 6);
			rd2 =twosComplement(rd, 5);
			rs2 =twosComplement(rs, 5);
			rt2 =twosComplement(0, 5);
			op  =twosComplement(0, 6);
			shampt2=twosComplement(0, 5);
			out<<op<<rt2<<rs2<<rd2<<shampt2<<fun2<<endl;

			cout<<"Function: "<<words[i]<<"  Registers: "<<words[i+1]<<"    "<<words[i+2]<<endl;
		}
		else if(words[i]=="syscall"){
			fun=searchFileFun(words,i);	
			fun2=twosComplement(fun, 6);
			op  =twosComplement(0, 26);
			out<<op<<fun2<<endl;
			cout<<"Function: "<<words[i]<<endl;
		}
	}
	return 0;

}

int searchFileReg(string words[],int i){  //reads the Registers file and returns the value assigned to each
	ifstream fp2;
	string filename2;
	string name;
	int value;
	filename2="mips_registers.txt";
	fp2.open(filename2);

	while(fp2>>name){
		fp2>>value;
		if(words[i]==name){
			return value;
		}

	}
	return -1;
}
int searchFileFun(string words[],int i){     //reads the Function file and returns the value assigned to each
	ifstream fp2;
	string filename2;
	string name;
	int value;
	filename2="mips_funct.txt";
	fp2.open(filename2);

	while(fp2>>name){
		fp2>>value;
		if(words[i]==name){
			return value;
		}

	}
	return -1;
}
string twosComplement(int num, int size){    //turns every value into binary

	string binary="";

	if(num>=0){    //positive numbers
		for(int i = size-1; i>=0; i--){
			binary +=((num>>i) & 1) ? '1' : '0';
		}
	}
	else{    //inverts the bits
		num=abs(num);
		int inverted = ~num;
		for(int i= size-1; i >= 0; i--){
			binary += ((inverted >> i) & 1) ? '1' : '0';	
		
		}    //adds 1
		bool carry = true;
		for(int i = size -1; i>=0; i--){
			if(binary[i]== '1' && carry){
				binary[i]='0';
			}
			else if(binary[i]=='0' && carry){
				binary[i]='1';
				carry = false;
			}
		}
	}
	return binary;
}
