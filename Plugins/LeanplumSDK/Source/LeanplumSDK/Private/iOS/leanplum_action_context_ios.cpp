//
//  leanplum_action_context_ios.cpp
//  Leanplum-SDK
//
//  Created by Milos Jakovljevic.
//  Copyright © 2021 Leanplum, Inc. All rights reserved.
//

#if PLATFORM_IOS

#include "action_context.h"

struct ios_private_data : public private_data
{

}

action_context::action_context()
{
	data = new ios_private_data();
}

action_context::~action_context()
{
	delete data;
}

std::string action_context::get_message_id() const
{
	return "";
}

void action_context::track(const std::string& name, double value, std::unordered_map<std::string, std::string> params)
{
	// do nothing
}

void action_context::track_message_event(const std::string& name, double value, const std::string& info, const std::unordered_map<std::string, std::string>& params)
{
	// do nothing
}

void action_context::run_action_named(const std::string& name)
{
	// do nothing
}

void action_context::run_tracked_action_named(const std::string& name)
{
	// do nothing
}

std::string action_context::get_string_named(const std::string& name)
{
	return "";
}
bool action_context::get_bool_named(const std::string& name)
{
	return false;
}

template<typename T>
std::vector<T> action_context::get_vector_named(const std::string& name)
{
	return std::vector<T>();
}

template<typename T>
std::unordered_map<std::string, T> action_context::get_map_named(const std::string& name)
{
	return std::unordered_map<std::string, T>();
}

template<typename T>
T action_context::get_number_named(const std::string& name)
{
	return T();
}

// specializations for supported types
template std::vector<int> action_context::get_vector_named(const std::string&);
template std::vector<long> action_context::get_vector_named(const std::string&);
template std::vector<double> action_context::get_vector_named(const std::string&);
template std::vector<float> action_context::get_vector_named(const std::string&);
template std::vector<std::string> action_context::get_vector_named(const std::string&);

template std::unordered_map<std::string, int> action_context::get_map_named(const std::string&);
template std::unordered_map<std::string, std::string> action_context::get_map_named(const std::string&);

template int action_context::get_number_named(const std::string&);
template char action_context::get_number_named(const std::string&);
template long action_context::get_number_named(const std::string&);
template double action_context::get_number_named(const std::string&);
template float action_context::get_number_named(const std::string&);

#endif // PLATFORM_IOS