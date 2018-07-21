#include <cstring>
#include <iostream>
using namespace std;

class String
{
private:
	char *buf;
	size_t len = 100;
	size_t maxlen = 2 * len;
	String(size_t);
public:	
	String(const String&);
	String(String&&);
	String(const char* =nullptr);	
	~String();
	String& operator=(const String&);
	String& operator=(String&&);
	char *get() const;
	size_t getMaxLen() const;
};
size_t String::getMaxLen() const
{
	return maxlen;
}
String::String(size_t len) :maxlen(0)
{
	this->len = len;
	buf = new char[len];
	*buf = 0;
	cout << "c " << this << endl;
}

String::String(const char * str) :String(strlen(str) + 1)
{
	strcpy(buf, str);
}
String::String(const String& s) : String(s.len)
{
	strcpy(buf, s.buf);
}
String::String(String && s)
{
	buf = s.buf;
	len = s.len;
	maxlen = s.maxlen;
	s.buf = nullptr;
	s.len = 0;
}
String& String::operator=(String&& s)
{
	if (this != &s)
	{
		delete[]buf;
		buf = s.buf;
		len = s.len;
		maxlen = s.maxlen;
		s.buf = nullptr;
		s.len = 0;
	}
	return *this;
}

String& String::operator=(const String& s)
{
	if (this != &s)
	{
		delete[] buf;
		len = s.len;
		buf = new char[len];
		maxlen = s.maxlen;
		strcpy(buf, s.buf);
	}
	return *this;
}

String::~String()
{
	delete[]buf;
	cout <<"d "<< this << endl;
}

char* String::get() const
{
	return buf;
}

void print(String &s)
{
	cout << s.get() << endl;
}

int main()
{
	String a("abc");
	//String b{ a };
	String b{ "qwerty" };

	String t{ move(a) };
	a = move(b);
	b = move(t);

	print(a);
	print(b);
	cout << a.getMaxLen() << endl;
	return 0;
}