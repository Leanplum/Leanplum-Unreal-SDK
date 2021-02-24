//
//  action_args.h
//  Leanplum-SDK
//
//  Created by Milos Jakovljevic.
//  Copyright © 2021 Leanplum, Inc. All rights reserved.
//

#ifndef action_args_h
#define action_args_h

#include <string>
#include <vector>
#include <map>
#include <unordered_map>

// std::map type check
template <class T>
struct is_map
{
	static constexpr bool value = false;
};

// unordered_map type check
template <class T>
struct is_unordered_map
{
	static constexpr bool value = false;
};

template<class Key, class Value>
struct is_map<std::map<Key, Value>>
{
	static constexpr bool value = true;
};

template<typename Key, typename Value>
struct is_unordered_map<std::unordered_map<Key, Value>>
{
	static constexpr bool value = true;
};

struct action_arg
{
	std::string name;
	std::string data;
	std::string kind;

	action_arg(const std::string& arg_name, const std::string& value, const std::string& value_kind)
	{
		name = arg_name;
		data = value;
		kind = value_kind;
	}
};

class action_args
{
public:
	action_args()
	{

	}

	template<typename T>
	action_args* with(const std::string& name, T value)
	{
		if (std::is_same<T, int>::value ||
			std::is_same<T, long>::value ||
			std::is_same<T, short>::value ||
			std::is_same<T, char>::value)
		{
			args.push_back(action_arg{ name, std::to_string(value), "integer" });
		}
		else if (std::is_same<T, float>::value ||
				 std::is_same<T, double>::value)
		{
			args.push_back(action_arg{ name, std::to_string(value), "float" });
		}
		else if (std::is_same<T, std::string>::value)
		{
			args.push_back(action_arg{ name, value, "string" });
		}
		else if (std::is_same<T, bool>::value)
		{
			args.push_back(action_arg{ name, std::to_string(value), "bool" });
		}
		// todo: vector and map

		return this;
	}

	action_args* with_color(const std::string& name, int value)
	{
		const auto kind = "color";
		args.push_back(action_arg{name, std::to_string(value), kind});
		return this;
	}

	action_args* with_action(const std::string& name, const std::string& value)
	{
		const auto kind = "action";
		args.push_back(action_arg{ name, value, kind });
		return this;
	}

	const std::vector<action_arg>& get_values() const
	{
		return args;
	}

private:
	std::vector<action_arg> args;
};

#endif /* action_args_h */