#include "gtest/gtest.h"

#include "../src/TapeImpl.h"
#include "../src/TapeImpl.cpp"
#include "../src/TapeGenerator.h"
#include "../src/TapeGenerator.cpp"
#include "../src/TapeExceptions.h"
#include "../src/TapeExceptions.cpp"
#include "../src/TapeSorter.h"
#include "../src/TapeSorter.cpp"

TEST(Tape, readFull_test1) {
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

    GTEST_ASSERT_EQ(tape.readFull(), elements);
}

TEST(Tape, readFull_test2) {
    std::string fileName("../../tests/testDataFiles/input.txt");
    std::ofstream outputFile(fileName);
    std::vector<int> elements = {0, 1, 2, 3, 4, 5, 6, 7, 8, 9};

    for (int i = 0; i < elements.size() - 1; ++i) {
        outputFile << elements[i] << ' ';
    }
    outputFile << elements[elements.size() - 1];
    outputFile.close();

    TapeSorter::TapeImpl tapeImpl(fileName);
    TapeSorter::Tape &tape = tapeImpl;

    GTEST_ASSERT_EQ(tape.readFull(), elements);
}

TEST(Tape, readFull_test3) {
    std::string fileName("../../tests/testDataFiles/input.txt");
    std::ofstream outputFile(fileName);
    outputFile.clear();
    outputFile.close();

    TapeSorter::TapeImpl tapeImpl(fileName);
    TapeSorter::Tape &tape = tapeImpl;

    EXPECT_THROW(tape.readFull(), TapeSorter::EmptyTapeException);
}

TEST(Tape, read_test1) {
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

    GTEST_ASSERT_EQ(tape.read(5), elements);
}

TEST(Tape, read_test2) {
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
    std::vector<int> eraseElements = {-8, 9, -16};
    GTEST_ASSERT_EQ(tape.read(3), eraseElements);
}

TEST(Tape, read_test3) {
    std::string fileName("../../tests/testDataFiles/input.txt");
    std::ofstream outputFile(fileName);
    outputFile.clear();
    outputFile.close();

    TapeSorter::TapeImpl tapeImpl(fileName);
    TapeSorter::Tape &tape = tapeImpl;
    EXPECT_THROW(tape.read(3), TapeSorter::EmptyTapeException);
}

TEST(Tape, readFirstElement_test1) {
    std::string fileName("../../tests/testDataFiles/input.txt");
    std::ofstream outputFile(fileName);
    int elem = -8;

    outputFile << elem;
    outputFile.close();

    TapeSorter::TapeImpl tapeImpl(fileName);
    TapeSorter::Tape &tape = tapeImpl;

    GTEST_ASSERT_EQ(tape.readFirstElement(), elem);
}

TEST(Tape, readFirstElement_test2) {
    std::string fileName("../../tests/testDataFiles/input.txt");
    std::ofstream outputFile(fileName);
    outputFile.clear();
    outputFile.close();

    TapeSorter::TapeImpl tapeImpl(fileName);
    TapeSorter::Tape &tape = tapeImpl;

    EXPECT_THROW(tape.readFirstElement(), TapeSorter::EmptyTapeException);
}

TEST(Tape, writeElements_test1) {
    std::string fileName("../../tests/testDataFiles/output.txt");

    std::vector<int> elements = {1, 2, 3, 4, 5, 6, 7, 8, 9};

    TapeSorter::TapeImpl tapeImpl(fileName);
    TapeSorter::Tape &tape = tapeImpl;

    tape.writeElements(elements);

    GTEST_ASSERT_EQ(tape.readFull(), elements);

    std::ifstream file(fileName);
    if (file.is_open()) {
        std::string expectedString("1 2 3 4 5 6 7 8 9");
        std::string resultString;
        while (true) {
            char c = static_cast<char>(file.get());
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

TEST(Tape, writeElements_test2) {
    std::string fileName("../../tests/testDataFiles/output.txt");

    std::vector<int> elements = {};

    TapeSorter::TapeImpl tapeImpl(fileName);
    TapeSorter::Tape &tape = tapeImpl;

    EXPECT_THROW(tape.writeElements(elements), TapeSorter::EmptyTapeException);
}


TEST(Tape, eraseFirstElement_test1) {
    std::string fileName("../../tests/testDataFiles/output.txt");
    std::ofstream outputFile(fileName);
    std::vector<int> elements = {-8, 9, -16, 23269, 35};

    for (int i = 0; i < elements.size() - 1; ++i) {
        outputFile << elements[i] << ' ';
    }
    outputFile << elements[elements.size() - 1];
    outputFile.close();

    TapeSorter::TapeImpl tapeImpl(fileName);
    TapeSorter::Tape &tape = tapeImpl;

    tape.eraseFirstElement();
    std::vector<int> elementsAfterErase = tape.readFull();
    std::vector<int> expected = {9, -16, 23269, 35};
    GTEST_ASSERT_EQ(elementsAfterErase, expected);
}

TEST(Tape, eraseFirstElement_test2) {
    std::string fileName("../../tests/testDataFiles/output.txt");
    std::ofstream outputFile(fileName);
    int element = -8;

    outputFile << element;
    outputFile.close();

    TapeSorter::TapeImpl tapeImpl(fileName);
    TapeSorter::Tape &tape = tapeImpl;

    EXPECT_THROW(tape.eraseFirstElement(), TapeSorter::EmptyTapeException);
}

TEST(Tape, eraseFirstElement_test3) {
    std::string fileName("../../tests/testDataFiles/output.txt");
    std::ofstream outputFile(fileName);

    outputFile.clear();
    outputFile.close();

    TapeSorter::TapeImpl tapeImpl(fileName);
    TapeSorter::Tape &tape = tapeImpl;

    EXPECT_THROW(tape.eraseFirstElement(), TapeSorter::EmptyTapeException);
}


TEST(TapeGenerator, generateTape_test1) {
    std::string fileName("../../tests/testDataFiles/input.txt");
    int countElements = 100;
    int leftBorder = -1000;
    int rightBorder = 1000;
    TapeSorter::TapeGenerator::generateTape(fileName, countElements, leftBorder, rightBorder);

    TapeSorter::TapeImpl tapeImpl(fileName);
    TapeSorter::Tape &tape = tapeImpl;

    std::vector<int> elements = tape.readFull();
    GTEST_ASSERT_EQ(elements.size(), countElements);
    GTEST_ASSERT_GE(*std::min_element(elements.begin(), elements.end()), leftBorder);
    GTEST_ASSERT_LE(*std::max_element(elements.begin(), elements.end()), rightBorder);
}


TEST(TapeSorter, Sorting_test1) {
    std::string inputFileName("../../tests/testDataFiles/input.txt");
    std::string ouputFileName("../../tests/testDataFiles/output.txt");
    std::vector<int> disorderedElements = {3, 5, 9, 6, 8, 0, 7, 4, 2, 10, 1};

    TapeSorter::TapeImpl tapeImplOriginal(inputFileName);
    TapeSorter::Tape &tapeOriginal = tapeImplOriginal;
    tapeOriginal.writeElements(disorderedElements);

    TapeSorter::TapeImpl tapeImplResult(ouputFileName);
    TapeSorter::Tape &tapeResult = tapeImplResult;

    TapeSorter::TapeSorter tapeSorter;
    std::string outputTempTapeFilesName("../../tests/testDataFiles/");
    int countElementsInTempTape = 2;
    tapeSorter.sort(tapeOriginal, tapeResult, outputTempTapeFilesName, countElementsInTempTape);

    std::sort(disorderedElements.begin(), disorderedElements.end());
    std::vector<int> orderedElements = disorderedElements;


    GTEST_ASSERT_EQ(tapeResult.readFull(), orderedElements);
}

TEST(TapeSorter, Sorting_test2) {
    std::string inputFileName("../../tests/testDataFiles/input.txt");
    std::string ouputFileName("../../tests/testDataFiles/output.txt");
    int countElements = 1000;
    int leftBorder = -1000;
    int rightBorder = 1000;

    for (int i = 0; i < 5; ++i) {
        TapeSorter::TapeGenerator::generateTape(inputFileName, countElements * (i + 1), leftBorder * (i + 1),
                                                rightBorder * (i + 1));

        TapeSorter::TapeImpl tapeImplOriginal(inputFileName);
        TapeSorter::Tape &tapeOriginal = tapeImplOriginal;
        std::vector<int> disorderedElements = tapeOriginal.readFull();

        TapeSorter::TapeImpl tapeImplResult(ouputFileName);
        TapeSorter::Tape &tapeResult = tapeImplResult;

        TapeSorter::TapeSorter tapeSorter;
        std::string outputTempTapeFilesName("../../tests/testDataFiles/");
        int countElementsInTempTape = 10;
        tapeSorter.sort(tapeOriginal, tapeResult, outputTempTapeFilesName, countElementsInTempTape);

        std::sort(disorderedElements.begin(), disorderedElements.end());
        std::vector<int> orderedElements = disorderedElements;

        GTEST_ASSERT_EQ(tapeResult.readFull(), orderedElements);
    }
}


int main(int argc, char **argv) {
    testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}