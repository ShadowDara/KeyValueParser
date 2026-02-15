// KeyValueParser.cpp: Definiert den Einstiegspunkt für die Anwendung.
//

#include <kvp.hpp>
#include <fstream>
#include <iostream>

using namespace std;

int main(int argc, char* argv[])
{
	cout << "KeyValueParser." << "\n";

    std::ifstream file{ "C:/Users/schueler/source/repos/KeyValueParser/config.txt" };
    if (!file) {
        std::cerr << "Datei konnte nicht geöffnet werden\n";
        return 1;
    }

    std::string content(
        (std::istreambuf_iterator<char>(file)), std::istreambuf_iterator<char>()
    );

	//auto result = KeyValueParser::parse_kvp(content);
    auto result = KeyValueParser::parse_kvp2(content);

    for (const auto& pair : result) {
        std::cout << pair.first << " -> " << pair.second << "\n";
    }

	return 0;
}
