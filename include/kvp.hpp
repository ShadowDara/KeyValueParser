// KeyValueParser.hpp
// 
//
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
