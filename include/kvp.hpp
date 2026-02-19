// KeyValueParser.hpp
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


#include <string>
#include <unordered_map>
#include <cassert>
#include <fstream>
#include <sstream>


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
}
