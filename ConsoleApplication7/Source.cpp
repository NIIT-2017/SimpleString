#include <cstring>
#include <iostream>
using namespace std;

class String
{
private:
	char *buf;
	size_t len;
	String(size_t);
public:	
	String(const String&);
	String(String&&);
	String(const char* =nullptr);	
	~String();
	String& operator=(const String&);
	String& operator=(String&&);
	String  operator+(const String&);
	char&   operator[](size_t);
	bool    operator==(const String&);
	bool    operator!=(const String&);
	char*   operator()(char*);
	size_t  operator()(int);
	operator char* ();
	char *get() const;

};

String::String(size_t len) 
{
	this->len = len;
	buf = new char[len];
	*buf = 0;
	//cout << "c " << this << endl;
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
		strcpy(buf, s.buf);
	}
	return *this;
}
String String::operator+(const String& s)
{
	String result(len + s.len + 1);
	strcpy(result.buf, buf);
	strcat(result.buf, s.buf);
	return result;
}
char&  String::operator[](size_t i)
{
	return buf[i];
}
bool    String::operator==(const String& s)
{
	return (bool)!strcmp(buf, s.buf);
}
bool    String::operator!=(const String& s)
{
	return !(*this == s);
}
char*   String::operator()(char*)
{
	return buf;
}
size_t   String::operator()(int)
{
	return len;
}
String::operator char* ()
{
	return buf;
}
String::~String()
{
	delete[]buf;
	//cout <<"d "<< this << endl;
}

char* String::get() const
{
	return buf;
}

void print(String &s)
{
	cout << s.get() << endl;
}

ostream& operator<< (ostream& out, const String& s)
{
	return out << s.get();
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
	print(a + b);
	cout << a[(size_t)0] << endl;
	char *p = a("");
	size_t len = a(0);
	cout << p << " "<<len<< endl;
	cout << (char*)b << endl;

	cout << a << endl;
	return 0;
}