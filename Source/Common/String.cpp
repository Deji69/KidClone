#include <Source/pch.h>
#include "String.h"
#include <cctype>

namespace KidClone {

auto ltrim(string_view subj, const string& str)->string_view
{
	auto p = subj.find_first_not_of(str);
	if (p == string::npos) return "";
	return subj.substr(p);
}

auto rtrim(string_view subj, const string& str)->string_view
{
	auto p = subj.find_last_not_of(str);
	if (p != string::npos)
		return subj.substr(0, p + 1);
	return "";
}

auto ltrimmed(string_view subj, const string& str)->string
{
	return string(ltrim(subj, str));
}

auto rtrimmed(string_view subj, const string& str)->string
{
	return string(rtrim(subj, str));
}

auto trim(string_view subj, const string& str)->string_view
{
	return rtrim(ltrim(subj));
}

auto trimmed(string_view subj, const string& str)->string
{
	return string(trim(subj, str));
}

auto stringToLower(string str)->string
{
	std::transform(str.begin(), str.end(), str.begin(), [](char c) {
		return static_cast<char>(std::tolower(c));
	});
	return str;
}

auto stringToUpper(string str)->string
{
	std::transform(str.begin(), str.end(), str.begin(), [](char c) {
		return static_cast<char>(std::toupper(c));
	});
	return str;
}

auto stringReplace(string& subj, const string& find, const string& repl)->string&
{
	if (!subj.empty() && !find.empty()) {
		size_t pos = 0;
		while ((pos = subj.find(find, pos)) != string::npos) {
			subj.replace(pos, find.length(), repl);
			pos += repl.length();
		}
	}
	return subj;
}

auto stringReplaced(string subj, const string& find, const string& repl)->string
{
	return stringReplace(subj, find, repl);
}

auto stringBeginsWith(string_view s, char c)->bool
{
	return !s.empty() && s.front() == c;
}

auto stringBeginsWith(string_view s, const string& v)->bool
{
	if (v.empty()) return s.empty();
	if (s.size() >= v.size()) {
		return s.compare(0, v.size(), v) == 0;
	}
	return false;
}

auto stringEndsWith(string_view s, char c)->bool
{
	return !s.empty() && s.back() == c;
}

auto stringEndsWith(string_view s, const string& v)->bool
{
	if (v.empty()) return true;
	if (s.size() >= v.size()) {
		return s.compare(s.size() - v.size(), v.size(), v) == 0;
	}
	return false;
}

#ifdef _WIN32
auto toWideChar(const char* str)->wstring
{
	auto n = MultiByteToWideChar(CP_UTF8, 0, str, -1, nullptr, 0);
	wstring out;
	out.resize(n);
	MultiByteToWideChar(CP_UTF8, 0, str, -1, &out[0], n);
	return out;
}

auto toMultiByte(const wchar_t* str)->string
{
	auto n = WideCharToMultiByte(CP_UTF8, 0, str, -1, nullptr, 0, nullptr, nullptr);
	string out;
	out.resize(n);
	WideCharToMultiByte(CP_UTF8, 0, str, -1, &out[0], n, NULL, nullptr);
	while (out.size() && out.back() == '\0')
		out.pop_back();
	return out;
}

auto toWideChar(const string& str)->wstring
{
	auto n = MultiByteToWideChar(CP_UTF8, 0, str.c_str(), static_cast<int>(str.size()), nullptr, 0);
	wstring out;
	out.resize(n);
	MultiByteToWideChar(CP_UTF8, 0, str.c_str(), static_cast<int>(str.size()), &out[0], n);
	return out;
}

auto toMultiByte(const wstring& str)->string
{
	auto n = WideCharToMultiByte(CP_UTF8, 0, str.c_str(), static_cast<int>(str.size()), nullptr, 0, nullptr, nullptr);
	string out;
	out.resize(n);
	WideCharToMultiByte(CP_UTF8, 0, str.c_str(), static_cast<int>(str.size()), &out[0], n, NULL, nullptr);
	while (out.size() && out.back() == '\0')
		out.pop_back();
	return out;
}
#else // ifdef _WIN32
static wchar_t wchar_buffer[5000];
static char char_buffer[5000];

inline auto toWideChar(const char* str)->wstring {
	auto n = mbstowcs(wchar_buffer, str, sizeof(wchar_buffer));
	wstring out;
	out.resize(n);
	mbstowcs(&out[0], str, n);
	return out;
}

inline auto toMultiByte(const wchar_t* str)->string {
	auto n = wcstombs(char_buffer, str, sizeof(char_buffer));
	string out;
	out.resize(n);
	wcstombs(&out[0], str, n);
	return out;
}

inline auto toWideChar(const string& str)->wstring {
	auto n = mbstowcs(wchar_buffer, str.c_str(), sizeof(char_buffer));
	wstring out;
	out.resize(n);
	mbstowcs(&out[0], str.c_str(), str.size());
	return out;
}

inline auto toMultiByte(const wstring& str)->string {
	auto n = wcstombs(char_buffer, str.c_str(), str.size());
	string out;
	out.resize(n);
	wcstombs(&out[0], str.c_str(), str.size());
	return out;
}
#endif // ifdef _WIN32 else

} // namespace KidClone
