#include"stringclass.h"
//默认构造函数+转换构造函数
String::String(const char * c)
{
	size = strlen(c);
	str = new char[size + 1];
	if (str == NULL)
		Error("String : overlow!");
	strcpy(str, c);
}
//COPY构造函数    (构造的时候传递一个相同的类型的对象或引用)
String::String(const String &s)
{
	size = s.size;
	str = new char(size + 1);
	if (str == NULL)
		Error("String overlow");
	strcpy(str, s.str);
}
//成员赋值函数    转换赋值运算符
//类串=C串
String& String:: operator =(const char* c)
{
	int len = strlen(c);
	if (len != size)
	{
		delete []str;
		str = new char[len + 1];
		if (str == NULL)
			Error("String:overlow");
		size = len;
	}
	strcpy(str, c);//先把容器的大小确定 然后再将其赋值进去
}
//类串 = C串
String& String::operator = (const String& s)
{
	if (size != s.size)
	{
		delete[]str;
		str = new char[s.size + 1];
		if (str == NULL)
			Error("String : overlow");
		size = s.size;
	}
	strcpy(str, s.str);
	return *this;
}

//成员转换函数  返回的是char*的内容,这个成员转换函数只能转换成一个标准类型
String:: operator char*()const
{
	char * c = new char[size + 1];
	if (c == NULL)
		Error("C : Overlow");
	strcpy(c, str);
	return c;
}
//串连接  类串+类串
String String::operator+(const String& s) const
{
	//实现的方式的是新建一个对象 在这个对象里面将其加起来
	String w;
	int len = s.size + size;
	delete[]str;
	w.str = new char[len + 1];
	if (w.str == NULL)
		Error("operator+ : overflow");
	strcpy(w.str, str);
	strcat(w.str, s.str);//先COPY  再连接
	w.size = len;
	return w;
	//由于返回的是一个新的对象  所以这个新的对象不能是直接返回引用
}
//串的连接和C串的连接
String String::operator+(const char * c)const
{
	String w;
	int len = strlen(c) + size;
	delete[]str;
	w.str = new char[len + 1];
	if (w.str == NULL)
		Error("operator++ : overlow");
	strcpy(w.str, str);
	strcat(w.str, c);
	w.size = len;
	return w;
}

//c串和类传的连接
//涉及到左元的使用   成员运算符重载函数必须要有左元来调用   也就是说左元必须使用类对象
//定义的时候不可以加上friend的关键字
String operator + (const char*c, const String &s)
{
	String w;
	delete w.str;
	int len = strlen(c) + s.size;
	w.str = new char[len + 1];
	if (w.str == NULL)
		w.Error("operator + :overlow");
	strcpy(w.str, c);
	strcat(w.str, s.str);

	return w;
}

//关系运算符重载
bool String::operator ==(const String&cs)const//类串和类串
{
	return (strcmp(str, cs.str) == 0);
}

bool String::operator ==(const char * c)const//类串和C串
{
	return (strcmp(str, c) == 0);
}
bool operator == (const String & s, const char * c)
{
	return (strcmp(c, s.str) == 0);
}
