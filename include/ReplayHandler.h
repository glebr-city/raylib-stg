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

#include "GlobalVariables.h"
#include "InputHandler.h"

class ReplayHandler
{
private:
    static std::string currentReplayPath;
    static std::string replayPath;
    static u_int8_t lastInputs;
    static u_int16_t stepsWithoutChange;
    static std::vector<u_int16_t> currentReplayData;
    static bool DEBUG_readingFromFile;
    static size_t currentReplayDatumIndex;
private:
    static void appendCurrentReplayData(const u_int8_t _currentInputs)
    {
        u_int16_t newData = _currentInputs + (stepsWithoutChange << 7);
        currentReplayData.emplace_back(newData);
        stepsWithoutChange = 0;
    }

    static void writeToFile()
    {
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
            uint DEBUG_input = (newData) % 128;
            uint DEBUG_length = (newData >> 7);
            outf.write(reinterpret_cast<const char*>(&newData), sizeof(newData));
        }

        outf.close();
    }
public:

    static void ReadFromFile(const uint16_t _replayIndex)
    {
        currentReplayDatumIndex = 0;
        currentReplayData.clear();
        currentReplayPath = replayPath + std::to_string(_replayIndex);

        std::ifstream inf{replayPath + std::to_string(_replayIndex)};
        if (inf.fail())
        {
            inf.close();
            std::cerr << "Replay file could not be opened!" << std::endl;
            return;
        }
        DEBUG_readingFromFile = true;
        std::cout << "File exists: " << replayPath << std::to_string(_replayIndex) << std::endl;
        const size_t dataPointCount = std::filesystem::file_size(currentReplayPath) / sizeof(u_int16_t);
        currentReplayData.resize(dataPointCount);
        std::cout << "Replay data point count: " << dataPointCount << std::endl;
        uint16_t readData = 0;
        std::string strInput{};
        size_t i = 0;
        while (true)
        {
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
        readStep();
        std::cout << "Current replay data size: " << currentReplayData.size() << std::endl;
        //while (std::get())
          //  std::cout << strInput << '\n';
        for (auto data: currentReplayData) {
            uint input = (data) % 128;
            uint length = (data >> 7);
            std::cout << "Input: " <<
                "Left: "<< (input&1) << " Right: " << (input>>1&1) << " Up: " << (input>>2&1) << " Length: " << length << std::endl;
        }
    }

private:
    static void recordStep() {
        if (DEBUG_readingFromFile)
            return;
        if (IsKeyPressed(KEY_J))
        {
            ReadFromFile(0);
        }
        else if (IsKeyPressed(KEY_L))
            writeToFile();
        else {
            const uint8_t currentInputs = (InputHandler::CheckInputsDown(INPUT_LEFT)  << 0)  |
                    (InputHandler::CheckInputsDown(INPUT_RIGHT)  << 1)  |
                        (InputHandler::CheckInputsDown(INPUT_UP)  << 2)  |
                            (InputHandler::CheckInputsDown(INPUT_DOWN)  << 3)  |
                                (InputHandler::CheckInputsDown(INPUT_FOCUS)  << 4)  |
                                    (InputHandler::CheckInputsDown(INPUT_HYPER)  << 5)  |
                                        (InputHandler::CheckInputsDown(INPUT_FIRE)  << 6);
            GlobalVariables::SetCurrentReplayInputs(currentInputs);
            if (currentInputs != lastInputs || stepsWithoutChange == 511)
            {
                appendCurrentReplayData(lastInputs);
                lastInputs = currentInputs;
            }
            stepsWithoutChange++;
        }
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
    static void Init()
    {
        DEBUG_readingFromFile = false;
        currentReplayData.clear();
        stepsWithoutChange = 0;
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
        const std::string filePath = replayPath + std::to_string(i);
        /*std::ofstream outf{filePath, std::ios::out};
        // If we couldn't open the output file stream for writing
        if (!outf)
        {
            // Print an error and exit
            std::cerr << "Uh oh, " << filePath.c_str() << " could not be opened for writing!\n";
            outf.close();
        }
        outf.close();*/
        currentReplayPath = filePath;
        std::cout << "Current replay path: " << currentReplayPath << std::endl;
        //readFromFile(0);
    }

    static void DoStep() {
        if (!DEBUG_readingFromFile)
            recordStep();
        else
            readStep();
    }


    static void FinishReplay()
    {
        writeToFile();
    }
};
#endif //RAYLIB_STG_REPLAYHANDLER_H