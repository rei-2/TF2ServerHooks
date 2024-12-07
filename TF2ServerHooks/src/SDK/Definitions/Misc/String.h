#pragma once

#define NULL_STRING			castable_string_t()
#define STRING( string_t_obj )	(string_t_obj).ToCStr()
#define MAKE_STRING( c_str )	castable_string_t( c_str )
#define IDENT_STRINGS( s1, s2 )	*((void **)&(s1)) == *((void **)&(s2))

struct string_t
{
public:
	bool operator!() const { return (pszValue == 0); }
	bool operator==(const string_t& rhs) const { return (pszValue == rhs.pszValue); }
	bool operator!=(const string_t& rhs) const { return (pszValue != rhs.pszValue); }
	bool operator<(const string_t& rhs) const { return ((void*)pszValue < (void*)rhs.pszValue); }

	const char* ToCStr() const { return (pszValue) ? pszValue : ""; }

protected:
	const char* pszValue;
};