#pragma once

namespace ft
{
	template<bool B, class T = void>
	struct enable_if
	{};

	template<class T>
	struct enable_if<true, T>
	{
		typedef T type;
	};

	template<class Type, Type Value>
	struct integral_constant
	{
		static const Type value = Value;
		typedef Type value_type;
		typedef integral_constant type;

		operator value_type() const throw()
		{
			return value;
		}
	};

	typedef integral_constant<bool, true> true_type;
	typedef integral_constant<bool, false> false_type;

	template<class>
	struct _void_t { typedef void type; };

	template<class T>
	struct is_abstract : public integral_constant<bool, __is_abstract(T)> {};

	template<class T1, class T2>
	struct is_convertible : public integral_constant<bool, __is_convertible_to(T1, T2) && !is_abstract<T2>::value> {};

	template<class T>
	struct is_integral : public integral_constant<bool, __is_integral(T)> {};

	template<class T>
	struct remove_const { typedef T type; };
	template<class T>
	struct remove_const<const T> { typedef T type; };

	template<class T>
	struct remove_volatile { typedef T type; };
	template<class T>
	struct remove_volatile<volatile T> { typedef T type; };

	template<class T>
	struct remove_cv { typedef typename remove_volatile<typename remove_const<T>::type>::type type; };
}
