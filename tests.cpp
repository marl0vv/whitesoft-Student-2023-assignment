#define CATCH_CONFIG_MAIN

#include <catch2/catch_test_macros.hpp>

#include "main.cpp"

TEST_CASE("Input is not zero")
{
    REQUIRE(getDataCurl("https://raw.githubusercontent.com/thewhitesoft/student-2023-assignment/main/data.json").size() != 0);
    REQUIRE(getDataCurl("https://raw.githubusercontent.com/thewhitesoft/student-2023-assignment/main/replacement.json").size() != 0);
}

TEST_CASE("All permutations are correct")
{
    json correctDataInput = getDataFile("..//resultCorrect.json");
    
    json j_inputData = json::parse(getDataCurl("https://raw.githubusercontent.com/thewhitesoft/student-2023-assignment/main/data.json"));
    json j_replacements = json::parse(getDataCurl("https://raw.githubusercontent.com/thewhitesoft/student-2023-assignment/main/replacement.json")); 
    json fileOutput = dataPermutation(j_inputData, j_replacements);

    REQUIRE(correctDataInput == fileOutput);
}

TEST_CASE("Delete string when source is null")
{
    json j_replacements = 
    {
        {
            {"replacement", "Emptry... or NOT!"},
            {"source", nullptr}
        }
    };

    json j_inputData=
    {
        "Emptry... or NOT!"
    };
    json expectedResult = json::array();

    json fileOutput = dataPermutation(j_inputData, j_replacements);
    
    REQUIRE(fileOutput == expectedResult);
}

TEST_CASE("Correct permutations")
{
    json j_replacements = 
    {
        {
            {"replacement", "Ha-haaa, hacked you"},
            {"source", "I doubted if I should ever come back"}
        },
        {
            {"replacement", "parentheses - that is a smart word"},
            {"source", "the better claim"}
        }
    };

    json j_inputData=
    {
        "Ha-haaa, hacked you",
        "parentheses - that is a smart word"
    };

    json fileOutput = dataPermutation(j_inputData, j_replacements);
    json expectedResult =
    {
        "I doubted if I should ever come back",
        "the better claim"
    };

    REQUIRE(fileOutput == expectedResult);
}

TEST_CASE("Use last source if replacement repeats more than once")
{
    json j_replacements = 
    {
        {
            {"replacement", "Skooby-dooby-doooo"},
            {"source", "knowing how way leads on"}
        },
        {
            {"replacement", "Skooby-dooby-doooo"},
            {"source", "knowing how way"}
        }
    };

    json j_inputData=
    {
        "Skooby-dooby-doooo",
    };

    json fileOutput = dataPermutation(j_inputData, j_replacements);
    json expectedResult =
    {
        "knowing how way",
    };

    REQUIRE(fileOutput == expectedResult);
}

TEST_CASE("two replacement substring in one initial string")
{
     json j_replacements = 
    {
        {
            {"replacement", "Skooby-dooby-doooo"},
            {"source", "knowing how way"}
        },
        {
            {"replacement", "1"},
            {"source", "l"}
        }
    };

    json j_inputData=
    {
        "Yet Skooby-dooby-doooo 1eads on to way,",
    };

    json fileOutput = dataPermutation(j_inputData, j_replacements);
    json expectedResult =
    {
        "Yet knowing how way leads on to way,"
    };

    REQUIRE(fileOutput == expectedResult);
}

TEST_CASE("same replacement appears several times")
{
     json j_replacements = 
    {
        {
            {"replacement", "1"},
            {"source", "l"}
        }
    };

    json j_inputData=
    {
        "And 1ooked down one as far as I cou1d",
    };

    json fileOutput = dataPermutation(j_inputData, j_replacements);
    json expectedResult =
    {
        "And looked down one as far as I could"
    };

    REQUIRE(fileOutput == expectedResult);
}