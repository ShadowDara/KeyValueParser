// KeyValueParser.hpp
// 

/*
// USAGE INFO

// IN HPP File:
#include "kvp.hpp"

// In CPP File:
#define KVP_IMPLEMENTATION
#include "kvp.hpp"

*/

// LICENSE:

/*
MIT License

Copyright (c) 2026 ShadowDara

Permission is hereby granted, free of charge, to any person obtaining a copy
of this software and associated documentation files (the "Software"), to deal
in the Software without restriction, including without limitation the rights
to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
copies of the Software, and to permit persons to whom the Software is
furnished to do so, subject to the following conditions:

The above copyright notice and this permission notice shall be included in all
copies or substantial portions of the Software.

THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
SOFTWARE.
*/

// 
// Version 1.1.0
// 
// New Features in 1.1.0
// - append entry
// - overwrite entry
// - delete entry
// - check for double entries (if a key already exists,
//   it will be overwritten, but the user will be informed
//   about it in the console) but only while parsing, not while
//   appending or overwriting.
// 
// Version 1.0.0
// - Initial Release
//
//
// DO NOT REMOVE THIS ANOTATION !
//
// Key Value Parser by Shadowdara
// https://github.com/ShadowDara
// 
// This is a simple Key Value Parser that can be
// used to parse key - value pairs from a string.
//
// 
// Example Usage:
// 
// val1 = Hallo
//
// val2 = Wordl
//
// # Hallo
// # This is a comment
// 
// 
// USAGE INFO
// 
// - only use 'parse_kvp2', the other one is deprecated and
// will be removed in the future.
// - The File must be loaded externally and the whole content
// will be passed as a string to the function, the function will
// parse the string and return a unordered_map with the key-value pairs.
//
//
// INFOS
// 
// KeyValueParser has comments with which lines which
// start with '#' will be ignored.
//
// Only Reading is possible, writing is not implemented yet.
//
// PROJECT LINK!
// https://github.com/ShadowDara/KeyValueParser
//
// 
// License: MIT License Shadowdara 2026
//
//


#pragma once

#pragma region Header Implementation

#ifndef KVP_HPP
#define KVP_HPP


#include <string>
#include <unordered_map>
#include <cassert>
#include <fstream>
#include <sstream>
#include <iostream>


namespace KeyValueParser
{
	// Function to parse key-value pairs from a string.
	// The input string is expected to have the format:
	// val1=val2
	// File must be ending with a newline character,
	// otherwise the last key-value pair will not be parsed.
	std::unordered_map<std::string, std::string>
		parse_kvp(const std::string& input);

	// Newer KeyValueParser Function
	// allowes Comments and Empty Lines and
	// does not require a newline at the end of the file.
	std::unordered_map<std::string, std::string>
		parse_kvp2(const std::string& input);

	// Function to append a key-value pair to the unordered_map.
	// INFO: If the key already exists, it WONT be overwritten.
	std::unordered_map<std::string, std::string>
		append_entry(
			const std::string& entryname,
			const std::string& entryvalue,
			const std::unordered_map<std::string, std::string>& kvp
		);

	// Function to append a key-value pair to the unordered_map.
	std::string append_entry(
		const std::string& entryname,
		const std::string& entryvalue,
		const std::string& input
	);

	// Function to overwrite a key-value pair in the unordered_map.
	// INFO: If the key does not exist, it will be NOT added to the unordered_map.
	std::unordered_map<std::string, std::string>
		overwrite_entry(
			const std::string& entryname,
			const std::string& entryvalue,
			const std::unordered_map<std::string, std::string>& kvp
		);

	// Function to overwrite a key-value pair in the unordered_map.
	std::string overwrite_entry(
		const std::string& entryname,
		const std::string& entryvalue,
		const std::string& input
	);

	// Function to delete a key-value pair from the unordered_map.
	// INFO: If the key does not exist, the unordered_map will
	// be returned unchanged and an error message will be printed to the console.
	std::unordered_map<std::string, std::string>
		delete_entry(
			const std::string& entryname,
			const std::unordered_map<std::string, std::string>& kvp
		);

	// Function to delete a key-value pair from the unordered_map.
	std::string delete_entry(
		const std::string& entryname,
		const std::string& input
	);
}


#endif // KVP_HPP

#pragma endregion

#pragma region Source Implementation

#ifdef KVP_IMPLEMENTATION

// KeyValue Parser Implementation

#include "kvp.hpp"

#pragma region Parser Implementation

// Function to parse key-value pairs from a string.
// The input string is expected to have the format:
std::unordered_map<std::string, std::string>
KeyValueParser::parse_kvp(const std::string& input)
{
	// Will disappear in a Export,
	// but for now it is here to prevent usage of the old function.
	assert(false && "This function is deprecated, use parse_kvp2 !!");

	bool useBuffer1 = true;

	std::string buffer1;
	std::string buffer2;

	std::unordered_map<std::string, std::string> result;

	for (size_t i = 0; i < input.size(); i++)
	{
		if (input[i] == '=')
		{
			useBuffer1 = !useBuffer1;
		}
		else if (input[i] == '\n')
		{
			useBuffer1 = !useBuffer1;
			if (buffer1.empty() || buffer2.empty())
			{
				continue;
			}
			result[buffer1] = buffer2;
			buffer1.clear();
			buffer2.clear();

		}
		else if (useBuffer1)
		{
			buffer1 += input[i];
		}
		else
		{
			buffer2 += input[i];
		}
	}

	return result;
}


// Newer KeyValueParser Function
std::unordered_map<std::string, std::string>
KeyValueParser::parse_kvp2(const std::string& input)
{
	std::stringstream ss(input);
	std::string line;

	std::unordered_map<std::string, std::string> result;

	// Iterate per Line
	while (std::getline(ss, line)) {
		// Empty lines
		if (line.empty())
		{
			continue;
		}

		// Lines without '=' will be ignored
		if (line.find('=') == std::string::npos)
		{
			continue;
		}

		// Comment Lines
		if (line.starts_with('#'))
		{
			continue;
		}

		bool useBuffer1 = true;

		std::string buffer1;
		std::string buffer2;

		// Interate per Character
		auto pos = line.find('=');
		buffer1 = line.substr(0, pos);
		buffer2 = line.substr(pos + 1);

		// Check for doublicates
		if (result.find(buffer1) != result.end()) {
			std::cerr << "Duplicate key found: " << buffer1
				<< " Value: " << buffer2 << "\n";
			// optionally throw or skip
		}
		else
		{
			result[buffer1] = buffer2;
		}
	}

	return result;
}

#pragma endregion

#pragma region Writer Implementation

// Add a new entry to the unordered_map
std::unordered_map<std::string, std::string>
KeyValueParser::append_entry(
	const std::string& entryname,
	const std::string& entryvalue,
	const std::unordered_map<std::string, std::string>& kvp
)
{
	std::unordered_map<std::string, std::string> result = kvp;

	// Check if the Entry already exists, if it does,
	// we will not add it again.
	if (result.find(entryname) != result.end()) {
		std::cerr << "Entry already exists!: " << entryname
			<< " Value: " << entryvalue << "\n";
		// optionally throw or skip
	}
	else
	{
		result[entryname] = entryvalue;
	}

	return result;
}

// Overwrite a key-value pair in the unordered_map
std::unordered_map<std::string, std::string>
KeyValueParser::overwrite_entry(
	const std::string& entryname,
	const std::string& entryvalue,
	const std::unordered_map<std::string, std::string>& kvp
)
{
	std::unordered_map<std::string, std::string> result = kvp;

	// Check if the entry exists, if it does, we will overwrite it,
	if (result.find(entryname) != result.end()) {
		result[entryname] = entryvalue;
	}
	else
	{
		std::cerr << "Entry does not exist! " << entryname << "\n";
	}

	return result;
}

// Delete a key-value pair from the unordered_map
std::unordered_map<std::string, std::string>
KeyValueParser::delete_entry(const std::string& entryname,
	const std::unordered_map<std::string, std::string>& kvp)
{
	std::unordered_map<std::string, std::string> result = kvp;

	// Check if the entry exists, if it does, we will delete it,
	if (result.find(entryname) != result.end()) {
		result.erase(entryname);
	}
	else
	{
		std::cerr << "Entry doesnt exist! : " << entryname << "\n";
	}

	return result;
}

#pragma endregion

#pragma region Source Writer Implementation

// Add a new Line to the Config
std::string KeyValueParser::append_entry(
	const std::string& entryname,
	const std::string& entryvalue,
	const std::string& input
)
{
	std::string line = entryname + "=" + entryvalue;
	return input + "\n" + line;
}

// Overwrite a key-value pair in the original config string.
// Keeps all comments and empty lines intact.
std::string KeyValueParser::overwrite_entry(
	const std::string& entryname,
	const std::string& entryvalue,
	const std::string& input
)
{
	std::stringstream ss(input);
	std::string line;
	std::string output;
	bool replaced = false;

	while (std::getline(ss, line)) {
		// Skip empty lines and comments
		if (line.empty() || line.starts_with('#')) {
			output += line + "\n";
			continue;
		}

		auto pos = line.find('=');
		if (pos != std::string::npos) {
			std::string key = line.substr(0, pos);
			if (key == entryname) {
				line = entryname + "=" + entryvalue;
				replaced = true;
			}
		}
		output += line + "\n";
	}

	// If the key was not found, append it at the end
	if (!replaced) {
		output += entryname + "=" + entryvalue + "\n";
	}

	return output;
}

// Delete a key-value pair from the original config string.
// Keeps all comments and empty lines intact.
std::string KeyValueParser::delete_entry(
	const std::string& entryname,
	const std::string& input
)
{
	std::stringstream ss(input);
	std::string line;
	std::string output;

	while (std::getline(ss, line)) {
		// Skip empty lines and comments
		if (line.empty() || line.starts_with('#')) {
			output += line + "\n";
			continue;
		}

		auto pos = line.find('=');
		if (pos != std::string::npos) {
			std::string key = line.substr(0, pos);
			if (key == entryname) {
				continue; // skip this line, effectively deleting it
			}
		}
		output += line + "\n";
	}

	return output;
}

#pragma endregion

// License: MIT License Shadowdara 2026
// End KVP Parser Implementation

// kvp.cpp

#endif // KVP_IMPLEMENTATION

#pragma endregion
