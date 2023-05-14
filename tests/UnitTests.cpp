#include "gtest/gtest.h"

#include "../src/TapeImpl.h"
#include "../src/TapeImpl.cpp"
#include "../src/TapeGenerator.h"
#include "../src/TapeGenerator.cpp"

TEST(Tape, readFullTape_test1) {
    std::string fileName("../../tests/testDataFiles/input.txt");
    std::ofstream outputFile(fileName);
    std::vector<int> elements = {-8, 9, -16, 23269, 35, 46, 908, -876, 9065, -87};

    for (int i = 0; i < elements.size() - 1; ++i) {
        outputFile << elements[i] << ' ';
    }
    outputFile << elements[elements.size() - 1];
    outputFile.close();

    TapeSorter::TapeImpl tapeImpl(fileName);
    TapeSorter::Tape &tape = tapeImpl;

    GTEST_ASSERT_EQ(tape.readFullTape(), elements);
}

TEST(Tape, readTape_test1) {
    std::string fileName("../../tests/testDataFiles/input.txt");
    std::ofstream outputFile(fileName);
    std::vector<int> elements = {-8, 9, -16, 23269, 35};

    for (int i = 0; i < elements.size() - 1; ++i) {
        outputFile << elements[i] << ' ';
    }
    outputFile << elements[elements.size() - 1];
    outputFile.close();

    TapeSorter::TapeImpl tapeImpl(fileName);
    TapeSorter::Tape &tape = tapeImpl;

    GTEST_ASSERT_EQ(tape.readTape(5), elements);
}

TEST(Tape, readFirstElemTape_test1) {
    std::string fileName("../../tests/testDataFiles/input.txt");
    std::ofstream outputFile(fileName);
    int elem = -8;

    outputFile << elem;
    outputFile.close();

    TapeSorter::TapeImpl tapeImpl(fileName);
    TapeSorter::Tape &tape = tapeImpl;

    GTEST_ASSERT_EQ(tape.readFirstElemTape(), elem);
}

TEST(Tape, writeTape_test1) {
    std::string fileName("../../tests/testDataFiles/output.txt");

    std::vector<int> elements = {1, 2, 3, 4, 5, 6, 7, 8, 9};

    TapeSorter::TapeImpl tapeImpl(fileName);
    TapeSorter::Tape &tape = tapeImpl;

    tape.writeTape(elements);

    GTEST_ASSERT_EQ(tape.readFullTape(), elements);

    std::ifstream file(fileName);
    if (file.is_open()) {
        std::string expectedString("1 2 3 4 5 6 7 8 9");
        std::string resultString;
        while (true) {
            char c = file.get();
            if (file.eof()) {
                break;
            }
            resultString += c;
        }

        GTEST_ASSERT_EQ(resultString, expectedString);
    } else {
        std::cerr << "Unable to open the file: " << fileName << std::endl;
        GTEST_FAIL();
    }
}


TEST(TapeGenerator, writeTape_test1) {
    std::string fileName("../../tests/testDataFiles/input.txt");
    int countElements = 100;
    int leftBorder = -1000;
    int rightBorder = 1000;
    TapeSorter::TapeGenerator::generateTape(fileName, countElements, leftBorder, rightBorder);

    TapeSorter::TapeImpl tapeImpl(fileName);
    TapeSorter::Tape &tape = tapeImpl;

    std::vector<int> elements = tape.readFullTape();
    GTEST_ASSERT_EQ(elements.size(), countElements);
    GTEST_ASSERT_GE(*std::min_element(elements.begin(), elements.end()), leftBorder);
    GTEST_ASSERT_LE(*std::max_element(elements.begin(), elements.end()), rightBorder);
}



int main(int argc, char** argv) {
    testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}