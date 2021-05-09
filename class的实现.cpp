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

String String::SubStr(const int& id, const int & num)const
{
	//先进行判断  
	int len = size;
	int left = len - id,i;
	if (id < 0 || id>len - 1)
		Error("id is illegal");
	if (num<0 || num>left)
		Error("num is illegal");
	//步骤1
	String w;
	delete []w.str;
	w.str = new char[num + 1];
	if (w.str == NULL)
		Error("Substr overlow");
	w.size = num;//
	//步骤2
	char * p = str + id;//指针的运算
	char * p1 = w.str;//暂时是指向新串的起点
	for (int i = 0; i < num; i++)//执行的次数
		*p1++ = *p++;//这个优先级要搞清楚
	*p1 = '\0';//自动填充到/0
	
	return w;
}
//指定位置的插入函数
String & String::Insert(int id, const String&s)
{
	char *p, *p1, *buf;
	int len = size;//原串的长度
	int len1 = s.size;//新串的长度
	int left = len - id;			//需要移动的数字的长度
	int i;
	//检验
	if (id<0 || id>s.size)
		Error("Insert overlow");
	buf = str;//保存原串的字符串
	/*在这里难道可以不delete  而直接创建吗*/
	str = new char[len + len1 + 1];
	if (str == NULL)
		Error("overlow");
	strcpy(str, buf);//把原串直接放在了新的str里面
	delete []buf;
	//步骤2
	p = str + len;
	p1 = p + len;
	for (i = 1; i < left + 1; ++i)
	{
		*p1-- = *p--;		//这一句要看清楚
	}
	p = str + id;		//指向原串插入的位置
	p1 = s.str;
	while (*p1 != '\0')//从p1开始表示结束
		*p++ = *p1++;
	size = len + len1;
	return *this;
}
//重写一遍插入函数    这个自己写的不知道正确与否  等都写完了之后再来全部改正
/*String & String::Insert(int id, const String & s)
{
	char *p, *p1 ,*buf;//p和p1是工作指针
	int len = size;
	int len1 = s.size;
	int left = size - id;//需要移动的数组的长度
	//开始判断这个id是否正常
	if (id<0 || id>size)
		Error("id : Overlow");
	buf = str;
	str = new char[len + len1 + 1];
	if (str == NULL)
		Error("str : Overlow");
	strcpy(str, buf);//对这个新的数组进行一个赋值
	delete []buf;
	//开始移动这个数组
	int i = 0;//用于次数的排序
	p = str + len;
	p1 = p + len1;
	for (int i = 0; i < left; i++)
	{
		*p1 = *p;
		p--;
		p1--;
	}
	p1 = s.str;
	for (i = 0; i < len1; i++)
	{
		*p = *p1;
		p++;
		p1++;
	}

	size = len + len1;
	return *this;
}*/
/*子串函数删除的原理是先将整个字符数组分成三段，即前中后，用后段覆盖中段，并且在
完成覆盖之后手动阻止（添加\0），于是在重新创建一个动态数组，于是，再相互COPY过去就好了*/
//子串删除函数
String& String::Erase(int id, int num)
{
	char *p, *q, *buf;
	int len = size;
	int left = len - id;
	if (id<0 || id>len - 1)
		Error("id is illegal");
	if (num <= 0 || num > left)
		Error("num is illegal");
	//步骤一
	p = str + id;
	q = str + id + num;
	while (*q != '\0')
		* p++ = *q++;		//用后段来覆盖掉中段
	*p = '\0';//用‘\0’手动封装
	//步骤二
	buf = str;
	//步骤三
	len = strlen(buf);
	str = new char[len + 1];
	if (str == NULL)
		Error("overlow");
	strcpy(str, buf);
	size = len;
	delete[]buf;
	return *this;
}

//下表运算符重载
char & String::operator[](int id)
{
	if (id<0 || id>size)
		Error("id : overlow");
	return *(str + id);
}
const char & String::operator[](int id)const
{
	if (id<0 || id>size)
		Error("id : overlow");
	return *(str + id);
}
//字符查找函数
int String::Find_First_Of(char ch, int id)const//清楚这个后置const的意义  就是在这个函数里面我不会改变函数的值
{
	int i = id;
	char * p;
	if (id<0 || id>size - 1)
		Error("id : overlow");
	p = str + id;
//第一种查找方法：
	while (*p = '\0')
	{
		if (*p == ch)
			break;
		else
		{
			++i;
			p++;				//不等于的话  就要都加了  不仅下表即  指针必然也要加
		}
	}
	return *p == '\0' ? -1 : i;			//这种判断其实也是很常见的  可以一下子减少好几行 何乐而不为
	//第二种查找方法
/*	while (*p == ch||*p =='\0') 
	{
		i++;
		p++
	}
	return *p == '\0' ? -1 : i;
	*/
}
int String::Find_First_Of(const String& s, int id)const
{
	int i = id;
	char * p;
	if (id<0 || id>size - 1)
		Error("id : overlow");
	p = str + id;
	//第一种查找方法：
	while (*p = '\0')
	{
		if (*p == ch)
			break;
		else
		{
			++i;
			p++;				//不等于的话  就要都加了  不仅下表即  指针必然也要加
		}
	}
	return *p == '\0' ? -1 : i;			//这种判断其实也是很常见的  可以一下子减少好几行 何乐而不为
	//第二种查找方法
/*	while (*p == ch||*p =='\0')
	{
		i++;
		p++
	}
	return *p == '\0' ? -1 : i;
	*/
}
//关于输入和输出函数
istream & operator<<(istream & input, String & s)
{
	char buf[256];//作为一个缓冲区
	input >> buf;
	s = buf;//运用COPY构造函数
	return input;
}

ostream & operator>>(ostream & output, String & s)
{
	output << s.str;
	return output;
}

//读取含空格的字符串的函数
int String::ReadString(istream&input, char delimiter)
{
	char buf[256];
	int token = -1;
	if (input.getline(buf, 256, delimiter))
	{
		*this = buf;
		token = size;
	}
	return token;
}
