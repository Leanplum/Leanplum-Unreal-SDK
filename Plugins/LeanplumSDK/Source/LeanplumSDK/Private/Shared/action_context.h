//
//  action_context.h
//  Leanplum-SDK
//
//  Created by Milos Jakovljevic.
//  Copyright © 2021 Leanplum, Inc. All rights reserved.
//

#ifndef action_context_h
#define action_context_h

#include <string>
#include <unordered_map>
#include <vector>
#include "macros.h"

class action_context
{
public:
	action_context();
	~action_context();

	std::string get_message_id() const;

	void track(const std::string& name, double value, std::unordered_map<std::string, std::string> params);
	void track_message_event(const std::string& name, double value, const std::string& info, const std::unordered_map<std::string, std::string>& params);
	
	void run_action_named(const std::string& name);
	void run_tracked_action_named(const std::string& name);

	std::string get_string_named(const std::string& name);
	bool get_bool_named(const std::string& name);

	template<typename T>
	std::vector<T> get_vector_named(const std::string& name);

	template<typename T>
	std::unordered_map<std::string, T> get_map_named(const std::string& name);
	
	template<typename T>
	T get_number_named(const std::string& name);
private:
	private_data* data = nullptr;
};

#endif /* action_context_h */