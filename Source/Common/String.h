#pragma once
#include <string>
#include <algorithm>

namespace KidClone {

using std::string;
using std::wstring;
using std::string_view;

auto toWideChar(const char*)->wstring;
auto toWideChar(const string&)->wstring;
auto toMultiByte(const wchar_t*)->string;
auto toMultiByte(const wstring&)->string;

auto ltrim(string_view subj, const string& str = " \t\n\r")->string_view;
auto rtrim(string_view subj, const string& str = " \t\n\r")->string_view;
auto trim(string_view subj, const string& str = " \t\n\r")->string_view;
auto ltrimmed(string_view subj, const string& str = " \t\n\r")->string;
auto rtrimmed(string_view subj, const string& str = " \t\n\r")->string;
auto trimmed(string_view subj, const string& str = " \t\n\r")->string;

auto stringToLower(string str)->string;
auto stringToUpper(string str)->string;

auto stringReplace(string& subj, const string& find, const string& repl)->string&;
auto stringReplaced(string subj, const string& find, const string& repl)->string;

auto stringBeginsWith(string_view s, char c)->bool;
auto stringBeginsWith(string_view s, const string& v)->bool;
auto stringEndsWith(string_view s, char c)->bool;
auto stringEndsWith(string_view s, const string& v)->bool;

} // namespace KidClone
