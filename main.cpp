#include <sstream>
#include <vector>
#include <algorithm>
#include <fstream>

#include <curlpp/cURLpp.hpp>
#include <curlpp/Options.hpp>
#include <curlpp/Easy.hpp>
#include "json.hpp"

std::string get_data(std::string url)
{
    curlpp::Cleanup cleaner;
    std::ostringstream os;
    os << curlpp::options::Url(std::string(url));
    return os.str();
}

int main(int, char**) 
{
    using json = nlohmann::json;

    json j_inputData = json::parse(get_data("https://raw.githubusercontent.com/thewhitesoft/student-2023-assignment/main/data.json"));
    json j_replacements = json::parse(get_data("https://raw.githubusercontent.com/thewhitesoft/student-2023-assignment/main/replacement.json")); 
  

    std::vector<std::string> output;
    for (auto const &source : j_inputData)
    {
        std::string result = source;
        for (auto it = j_replacements.rbegin(); it != j_replacements.rend(); ++it)
        {
            bool exit = false;
            while (result.find(it->at("replacement")) != std::string::npos && !exit)
            {
                size_t index = result.find(it->at("replacement"));
                size_t len = (*it)["replacement"].get_ref<json::string_t &>().size();
                if (it->at("source") == nullptr)
                {
                    exit = true;
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
    json fileOutput = output;

    std::ofstream file;
    file.open("./result.json", std::fstream::out);
    if (file.is_open())
    {
        file << fileOutput;
    }
    return EXIT_SUCCESS;
}
