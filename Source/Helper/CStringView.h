#pragma once
#include <string_view>
#include <variant>

namespace KidClone {

using std::string;
using std::variant;
using std::string_view;

class CStringView {
public:
	CStringView(const string& str) : m_var(str.c_str())
	{ }
	CStringView(const char* cstr) : m_var(cstr)
	{ }
	CStringView(string_view sv) {
		if (sv.empty()) {
			m_var = "";
		}
		else {
			if (!sv.data()[sv.size()])
				m_var = sv.data();
			else
				m_var = string(sv);
		}
	}
	CStringView(CStringView&&) = delete;
	CStringView(const CStringView&) = delete;
	auto operator=(CStringView&&)->CStringView& = delete;
	auto operator=(const CStringView&)->CStringView& = delete;

	inline auto data() const {
		return std::holds_alternative<string>(m_var) ? std::get<string>(m_var).c_str() : std::get<const char*>(m_var);
	}

	inline operator const char*() const {
		return data();
	}

private:
	variant<const char*, string> m_var;
};

} // namespace KidClone
