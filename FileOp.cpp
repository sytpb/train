#include "FileOp.h"
#include <string.h>
#include "Factory.h"

FileOp::FileOp(string name)
{
	_fname = name;
	memset(_buffer,0,sizeof(_buffer));
}

bool FileOp::FileOpen()
{
	_ff.open(_fname, std::ios::in|std::ios::out);
	
	return _ff.is_open();
}

string FileOp::GetDataType()
{
	/*assert(_ff!= NULL)*/

	char buf[128]  = {0};
	string out;
	if(_ff.getline(buf, sizeof(buf)))
		out = buf;
	return out;
}

bool FileOp::ReadLine(string& str)
{
	if(_ff.getline(_buffer,sizeof(_buffer)))
	{
		str = _buffer;
		return true;
	}
	return false;
}

void FileOp::Write2File(SAVE_TYPE type,const string  name,const char* context)
{
	switch(type)
	{
		case SAVE_TYPE::TYPE_TXT:
			break;
		case SAVE_TYPE::TYPE_CSV:
			break;
			/*...*/	
		default:
			break;

	}
}


/*------------------------------------------------------------------------------------------*/
/*BELOEW AS CLIENT CODE*/


void Load_Default_Adapter(AdFactory& adp)
{
	function<string(string)> fun0 = [](string s){return s;};			/*sring TO string*/
	SET_FUNCTER1(adp,string,string,fun0);	
	
	function<int(string)> fun1 = [](string s){return stoi(s);};			/*sring TO Int*/
	SET_FUNCTER1(adp,int,string,fun1);	
	
	function<double(string)> fun2 = [](string s){return stod(s);};		/*string TO Double*/
	SET_FUNCTER1(adp,double,string,fun2);
	
	function<int(int,int)> fun3 = [](int n1,int n2){return n1-n2;};		/*COMPARE 'Int' with 'Int' */
	SET_FUNCTER2(adp,int,int,int,fun3);

	/*MORE .....*/
}



int main(int argc,char* argv[])
{

	if(argc < 3)
	{
		cout << "Pls input the source file!" << endl;
		return 0;
	}

	AdFactory adp;
	Load_Default_Adapter(adp);					/* LOAD DEAULT ADAPTERS */


	//FileOp txtFile("InputA1.txt");
	FileOp txtFile1(argv[1]);
	FileOp txtFile2(argv[2]);

	if(!txtFile1.FileOpen() || !txtFile2.FileOpen())
		return 0;

	string sType1 = txtFile1.GetDataType();
	string sType2 = txtFile2.GetDataType();

	string strLine;
	if(sType1.find("Int_Day") != string::npos && sType2.find("Int_Day") != string::npos)
	{
		cout << "INT" << endl;
		string str1,str2;
		auto Fun1 = GET_FUNCTER1(adp,int,string);
		auto Fun2 = GET_FUNCTER2(adp,int,int,int);
		while(txtFile1.ReadLine(str1) && txtFile2.ReadLine(str2))
		{
			try{
				cout << Fun2(Fun1(str1),Fun1(str2)) << endl;
			}
			catch(const std::invalid_argument& ia) {
				cout<< "Invalid argument!" << endl;
			}
		}

	}
	else if(sType1.find("Str_Word") != string::npos)
	{
		cout << "STR " << endl;
		string str;
		auto Fun1 = GET_FUNCTER1(adp,string,string);
		while(txtFile1.ReadLine(str))
		{
			cout << Fun1(str) << endl;

		}
	}
	else if(sType1.find("Double") != string::npos)
		  cout << "DOUBLE" << endl;




	/*MORE WORKS BY USER DEFINE.... */


	return 0;
}


/*TEST FOR DIFFERENT ADAPTER*/
void  test()
{
	AdFactory con;
	function<int(string)> fun1 = [](string s){return stoi(s);};
	SET_FUNCTER1(con,int,string,fun1);	
	
	function<double(string)> fun2 = [](string s){return stod(s);};
	SET_FUNCTER1(con,double,string,fun2);
	
	function<int(int,int)> fun3 = [](int n1,int n2){return n1-n2;};
	SET_FUNCTER2(con,int,int,int,fun3);

	
	auto Fun1 = GET_FUNCTER1(con,int,string);
	auto nn  = Fun1("9999");
	cout << nn << endl;

	auto Fun2 = GET_FUNCTER1(con,double,string);
	auto dd  = Fun2("3.1415927");
	cout << dd << endl;

	auto Fun3 = GET_FUNCTER2(con,int,int,int);
	auto ee  = Fun3(100,20);
	cout << ee << endl;
}
