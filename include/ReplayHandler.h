//
// Created by n on 29/10/2026.
//

#ifndef RAYLIB_STG_REPLAYHANDLER_H
#define RAYLIB_STG_REPLAYHANDLER_H
#include <cmath>
#include <cstdint>
#include <filesystem>
#include <fstream>
#include <iostream>
#include <string>

#include "InputHandler.h"

class ReplayHandler
{
private:
    static std::string currentReplayPath;
    static std::string replayPath;
    static u_int8_t lastInputs;
    static u_int16_t stepsWithoutChange;
    static std::vector<u_int16_t> currentReplayData;
private:
    static void appendCurrentReplayData(const u_int8_t _currentInputs)
    {
        u_int16_t newData = _currentInputs + stepsWithoutChange * 128;
        currentReplayData.emplace_back(newData);
    }

    static void writeToFile()
    {
        std::ofstream outf{currentReplayPath, std::ios::out};
        outf << "";
        outf.close();
        outf.open(currentReplayPath, std::ios::app);
        for (uint16_t newData : currentReplayData)
        {
            outf.write(reinterpret_cast<const char*>(&newData), sizeof(newData));
        }
        outf.close();
    }

    static void readFromFile(const uint16_t _replayIndex)
    {
        currentReplayData.clear();
        currentReplayPath = replayPath + std::to_string(_replayIndex);

        std::ifstream inf{replayPath + std::to_string(_replayIndex)};
        if (inf.fail())
        {
            inf.close();
            std::cerr << "Replay file could not be opened!" << std::endl;
            return;
        }
        std::cout << "File exists: " << replayPath << std::to_string(_replayIndex) << std::endl;
        const size_t dataPointCount = std::filesystem::file_size(currentReplayPath) / sizeof(u_int16_t);
        currentReplayData.resize(dataPointCount);
        std::cout << "Replay data point count: " << dataPointCount << std::endl;
        uint16_t readData = 0;
        std::string strInput{};

        while (true)
        {
            readData = inf.read(reinterpret_cast<char*>(&readData), sizeof(readData)).get();
            if (inf.eof())
                break;
            currentReplayData.emplace_back(readData);
        }
        std::cout << "Current replay data size: " << currentReplayData.size() << std::endl;
        //while (std::get())
          //  std::cout << strInput << '\n';
    }
    public:
    static void Init()
    {
        currentReplayData.clear();
        replayPath = "./userdata/replays/replay";
        u_int16_t i = -1;
        while (++i < UINT16_MAX)
        {
            std::ifstream inf{replayPath + std::to_string(i)};
            if (inf.fail())
            {
                inf.close();
                break;
            }
            std::cout << "File exists: " << replayPath << std::to_string(i) << std::endl;
            std::string strInput{};
            while (std::getline(inf, strInput))
                std::cout << strInput << '\n';
            std::cout << std::endl;
            inf.close();
        }
        std::string filePath = replayPath + std::to_string(i);
        std::ofstream outf{filePath, std::ios::out};
        // If we couldn't open the output file stream for writing
        if (!outf)
        {
            // Print an error and exit
            std::cerr << "Uh oh, " << filePath.c_str() << " could not be opened for writing!\n";
            outf.close();
        }
        currentReplayPath = filePath;
        outf.close();
        std::cout << "Current replay path: " << currentReplayPath << std::endl;
    }

    static void RecordStep()
    {
        if (IsKeyPressed(KEY_J))
            readFromFile(0);
        if (IsKeyPressed(KEY_L))
            writeToFile();
        const u_int8_t currentInputs =
            (InputHandler::CheckInputsDown(INPUT_LEFT)  << 0)  |
                (InputHandler::CheckInputsDown(INPUT_RIGHT)  << 1)  |
                    (InputHandler::CheckInputsDown(INPUT_UP)  << 2)  |
                        (InputHandler::CheckInputsDown(INPUT_DOWN)  << 3)  |
                            (InputHandler::CheckInputsDown(INPUT_FIRE)  << 4)  |
                                (InputHandler::CheckInputsDown(INPUT_FOCUS)  << 5)  |
                                    (InputHandler::CheckInputsDown(INPUT_HYPER)  << 6);
        if (currentInputs == lastInputs)
        {
            if (++stepsWithoutChange == 511)
                appendCurrentReplayData(currentInputs);
        }else
        {
            lastInputs = currentInputs;
            appendCurrentReplayData(currentInputs);
        }
    }

    static void FinishReplay()
    {
        writeToFile();
    }
};
#endif //RAYLIB_STG_REPLAYHANDLER_H