#pragma once
extern const char* lib_name;

bool isStartWith(string str, const char* check);
bool isEqual(char* s1, const char* s2);
bool isEqual(string s1, const char* check);
bool isEqual(string s1, string s2);
bool isContain(string str, string check);
void trimStr(string& str);
bool isASCII(const string& s);
