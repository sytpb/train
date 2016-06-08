
#include <fstream>

class FileOp
{
	enum SAVE_TYPE{TYPE_TXT,TYPE_CSV,TYPE_DB};		/*FOR EXTENSION*/
public:
	FileOp(std::string name);
	bool FileOpen();
	std::string GetDataType();
	bool  ReadLine(std::string&);
	virtual void Write2File(SAVE_TYPE type,const std::string name,const char* context);
	virtual ~FileOp(){/*CLOSE FILE*/};
private:
	std::string	 _fname;
	std::fstream _ff;
	char _buffer[128];
};

