#include <sstream>
#include <vector>
#include <algorithm>
#include <fstream>

#include <curlpp/cURLpp.hpp>
#include <curlpp/Options.hpp>
#include <curlpp/Easy.hpp>
#include "json.hpp"

using json = nlohmann::json;

std::string getDataCurl(std::string url)
{
    curlpp::Cleanup cleaner;
    std::ostringstream os;
    os << curlpp::options::Url(std::string(url));
    return os.str();
}

nlohmann::json getDataFile(std::string fileName)
{
    using json = nlohmann::json;
    std::ifstream input(fileName);
    json correctDataInput = json::parse(input);
    
    return correctDataInput;
}

std::vector<std::string> dataPermutation(json inputData, json replacements)
{
    std::vector<std::string> output;
    for (auto const &source : inputData)
    {
        std::string result = source;
        for (auto it = replacements.rbegin(); it != replacements.rend(); ++it)
        {
            while (result.find(it->at("replacement")) != std::string::npos)
            {
                size_t index = result.find(it->at("replacement"));
                size_t len = (*it)["replacement"].get_ref<json::string_t &>().size();
                if (it->at("source") == nullptr)
                {
                    result.erase(index, len);
                    continue;
                }
                result.replace(index, len, it->at("source"));
            }           
        }
        if (result.size() > 0)
        {
            output.push_back(result);
        }
    }
    return output;
}

/*int main(int, char**) 
{
   using json = nlohmann::json;

    json j_inputData = json::parse(getDataCurl("https://raw.githubusercontent.com/thewhitesoft/student-2023-assignment/main/data.json"));
    json j_replacements = json::parse(getDataCurl("https://raw.githubusercontent.com/thewhitesoft/student-2023-assignment/main/replacement.json")); 
  
    json fileOutput = dataPermutation(j_inputData, j_replacements);

    std::ofstream file;
    file.open("./result.json", std::fstream::out);
    if (file.is_open())
    {
        file << fileOutput;
    }
    return EXIT_SUCCESS;
}*/
