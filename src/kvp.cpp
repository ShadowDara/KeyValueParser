// KeyValue Parser Implementation

#include <kvp.hpp>


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
		for (size_t i = 0; i < line.size(); i++)
		{
			if (line[i] == '=')
			{
				useBuffer1 = false;
			}
			else if (useBuffer1)
			{
				buffer1 += line[i];
			}
			else
			{
				buffer2 += line[i];
			}
		}

		result[buffer1] = buffer1.empty() ? "" : buffer2;
	}

	return result;
}
