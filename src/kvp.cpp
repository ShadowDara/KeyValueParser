// KeyValue Parser Implementation

#include <kvp.hpp>

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
		std::cerr << "Entry already exists!: " << entryname << "\n";
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
