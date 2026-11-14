//
// Created by n on 29/10/2026.
//

#ifndef RAYLIB_STG_REPLAYHANDLER_H
#define RAYLIB_STG_REPLAYHANDLER_H
#include <cstdint>
#include <filesystem>
#include <fstream>
#include <iostream>
#include <string>
#include <sys/stat.h>
#include <ctime>

#include "GlobalVariables.h"
#include "InputHandler.h"

class ReplayHandler
{
private:
    static std::string currentReplayPath;
    static std::string replayPath;
    static uint8_t lastInputs;
    static int32_t stepsWithoutChange;
    static std::vector<uint16_t> currentReplayData;
    static bool isReadingFromFile;
    static size_t currentReplayDatumIndex;
    static std::vector<std::string> replayFilePaths;
private:
    static void appendCurrentReplayData(const uint8_t _currentInputs)
    {
        uint16_t newData = _currentInputs + (stepsWithoutChange << 7);
        currentReplayData.emplace_back(newData);
        stepsWithoutChange = 0;
    }

public:
    static void WriteToFile()
    {
        time_t timestamp = time(nullptr);
        tm datetime = *localtime(&timestamp);
        char dateTimeChar[50];
        strftime(dateTimeChar, 50, "%Y-%m-%d_%H-%M-%S", &datetime);
        std::stringstream ss;
        ss << "./userdata/replays/" << dateTimeChar << ".sceshreplay";
        currentReplayPath = ss.str();
        std::ifstream nameTestFile{currentReplayPath};
        if (nameTestFile)
            for (uint32_t i = 0; i < UINT32_MAX; i++)
            {
                nameTestFile.close();
                nameTestFile.clear();
                std::stringstream ss2;
                ss2 << "./userdata/replays/" << dateTimeChar << "_" << std::to_string(i) << ".sceshreplay";
                currentReplayPath = ss2.str();
                nameTestFile.open(currentReplayPath);
                if (!nameTestFile)
                    break;
            }
        std::ofstream outf{currentReplayPath, std::ios::out};
        outf << "";
        outf.close();
        outf.open(currentReplayPath, std::ios::app);
        //const uint8_t firstStepsWithoutChange = currentReplayData[0] >> 7;
        //std::cout << "First step without change: " << static_cast<int>(firstStepsWithoutChange) << std::endl;
        //if (false && firstStepsWithoutChange > 0)
        //    currentReplayData[0] = currentReplayData[0] - (1 << 7);
        for (uint16_t newData : currentReplayData)
        {
            outf.write(reinterpret_cast<const char*>(&newData), sizeof(newData));
        }
        std::cout << "Replay written! Data points: " << currentReplayData.size() << std::endl;

        outf.close();
    }
    static void ReadFromFile(const uint16_t _replayIndex) {
        currentReplayDatumIndex = 0;
        currentReplayData.clear();
        if (replayFilePaths.empty()) {
            currentReplayData.emplace_back(128);
            std::cout << "There are no replay files!" << std::endl;
        } else {
            const auto tempReplayPath = replayFilePaths.at(_replayIndex);
            currentReplayPath = tempReplayPath;
            std::cout << "Replay path: " << tempReplayPath << std::endl;

            std::ifstream inf{tempReplayPath};
            if (inf.fail()) {
                inf.close();
                currentReplayData.emplace_back(128);
                std::cerr << "Replay file could not be opened!" << std::endl;
                return;
            }
            isReadingFromFile = true;
            std::cout << "File exists: " << tempReplayPath << std::endl;
            const size_t dataPointCount = std::filesystem::file_size(tempReplayPath) / sizeof(uint16_t);
            currentReplayData.resize(dataPointCount + 1);
            std::cout << "Replay data point count: " << dataPointCount << std::endl;
            uint16_t readData = 0;
            std::string strInput{};
            size_t i = 0;
            while (true) {
                if (inf.eof())
                    break;
                std::ifstream::char_type thing;
                inf.read(&thing, 1);
                if (inf.eof())
                    break;
                auto low = static_cast<uint8_t>(thing);
                inf.read(&thing, 1);
                if (inf.eof())
                    break;
                auto high = static_cast<uint8_t>(thing);

                readData = (low) | (high << 8);
                //readData = low * 2 + high;
                //uint8_t low = inf.read(reinterpret_cast<std::istream::char_type *>(&low), 1).get();
                //uint8_t high = inf.read(reinterpret_cast<std::istream::char_type *>(&low), 1).get();
                //readData = low | (high << 8);
                //readData = inf.read(reinterpret_cast<char*>(&readData), sizeof(readData)).get();
                if (inf.eof())
                    break;
                currentReplayData[i] = readData;
                i++;
            }
            inf.close();
        }
        readStep();
        std::cout << "Current replay data size: " << currentReplayData.size() << std::endl;
        //while (std::get())
        //  std::cout << strInput << '\n';
        currentReplayData.emplace_back(128);
        for (auto data: currentReplayData) {
            unsigned int input = (data) % 128;
            unsigned int length = (data >> 7);
            std::cout << "Input: " <<
                    "Left: " << (input & 1) << " Right: " << (input >> 1 & 1) << " Up: " << (input >> 2 & 1) <<
                    " Length: " << length << std::endl;
        }
    }
    static void RestartReplay() {
        currentReplayDatumIndex = 0;
        stepsWithoutChange = 0;
        readStep();
    }

private:
    static void recordStep()
    {
        if (isReadingFromFile)
            return;

        const uint8_t currentInputs = (InputHandler::CheckInputsDown(INPUT_LEFT) << 0) |
            (InputHandler::CheckInputsDown(INPUT_RIGHT) << 1) |
            (InputHandler::CheckInputsDown(INPUT_UP) << 2) |
            (InputHandler::CheckInputsDown(INPUT_DOWN) << 3) |
            (InputHandler::CheckInputsDown(INPUT_FOCUS) << 4) |
            (InputHandler::CheckInputsDown(INPUT_HYPER) << 5) |
            (InputHandler::CheckInputsDown(INPUT_FIRE) << 6);
        GlobalVariables::SetCurrentReplayInputs(currentInputs);
        if (currentInputs != lastInputs || stepsWithoutChange == 511)
        {
            appendCurrentReplayData(lastInputs);
            lastInputs = currentInputs;
        }
        stepsWithoutChange++;
    }

    static void readStep() {
        ///TODO!!
        if (stepsWithoutChange-- <= 1 && currentReplayDatumIndex < currentReplayData.size()) {
            GlobalVariables::SetCurrentReplayInputs(currentReplayData.at(currentReplayDatumIndex));
            stepsWithoutChange = (currentReplayData.at(currentReplayDatumIndex) >> 7);
            currentReplayDatumIndex++;
        }
    }
public:
    static void FindReplayFiles()
    {
        // This structure would distinguish a file from a
        // directory
        struct stat sb;
        std::vector<std::string> returnVector{};
        // Looping until all the items of the directory are
        // exhausted
        for (const auto& entry : std::filesystem::directory_iterator(replayPath)) {

            // Converting the path to const char * in the
            // subsequent lines
            std::string outfilename_str = entry.path().string();
            const char* path = outfilename_str.c_str();

            // Testing whether the path points to a
            // non-directory or not If it does, displays path
            if (stat(path, &sb) == 0 && !(sb.st_mode & S_IFDIR))
            {
                if (outfilename_str.substr(outfilename_str.length() - 12) != ".sceshreplay")
                    continue;
                std ::cout << path << std::endl;
                returnVector.emplace_back(outfilename_str);
            }
        }
        replayFilePaths = returnVector;
    }

    static void StopReadingFromFile() {
        isReadingFromFile = false;
        Init();
    }
    static void Init()
    {
        if (!isReadingFromFile) {
            currentReplayData.clear();
            stepsWithoutChange = 0;
        } else {
            RestartReplay();
        }
        std::filesystem::create_directory("./userdata/replays");
        replayPath = "./userdata/replays/";
        FindReplayFiles();
        /*std::ofstream outf{filePath, std::ios::out};
        // If we couldn't open the output file stream for writing
        if (!outf)
        {
            // Print an error and exit
            std::cerr << "Uh oh, " << filePath.c_str() << " could not be opened for writing!\n";
            outf.close();
        }
        outf.close();*/
    }

    static void DoStep() {
        if (!isReadingFromFile)
            recordStep();
        else
            readStep();
    }


    static void FinishReplay()
    {
        WriteToFile();
    }

    static std::vector<std::string> *GetReplayFilePaths() {
    return &replayFilePaths;
    };

    static bool GetIsReadingFromFile() {
        return isReadingFromFile;
    }
};
#endif //RAYLIB_STG_REPLAYHANDLER_H