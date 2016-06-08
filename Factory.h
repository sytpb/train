#pragma once

#include<iostream>
#include<iostream>
#include<algorithm>


#define DECLARE1(r,a) function<r(a)> r##_##a;
#define DECLARE2(r,a,b) function<r(a,b)> r##_##a##_##b;

#define SET_FUNCTION1(r,a) \
void Set_##r##_##a(function<r(a)> x) \
{ \
	r##_##a = x; \
} 

#define SET_FUNCTION2(r,a,b) \
void Set_##r##_##a##_##b(function<r(a,b)> x) \
{ \
	r##_##a##_##b = x; \
}

#define GET_FUNCTION1(r,a) \
auto Get_##r##_##a()->function<r(a)> \
{ \
	return r##_##a; \
}

#define GET_FUNCTION2(r,a,b) \
auto Get_##r##_##a##_##b()->function<r(a,b)> \
{ \
	return r##_##a##_##b; \
}

#define SET_FUNCTER1(o,r,a,x) o.r##_##a = x
#define SET_FUNCTER2(o,r,a,b,x)  o.r##_##a##_##b = x

#define GET_FUNCTER1(o,r,a)  o.r##_##a
#define GET_FUNCTER2(o,r,a,b)  o.r##_##a##_##b


using namespace std;

class AdFactory
{
public:
	DECLARE1(int,string)
	DECLARE1(string,string)
	DECLARE1(double,string)
	
	/*ADD MORE*/

	DECLARE2(int,int,int)
	DECLARE2(string,string,string)
	DECLARE2(double,double,double)
	
	/*ADD MORE*/
	
	SET_FUNCTION1(int,string)
	SET_FUNCTION1(string,string)
	SET_FUNCTION1(double,string)

	SET_FUNCTION2(int,int,int)
	SET_FUNCTION2(string,string,string)
	SET_FUNCTION2(double,double,double)

};

