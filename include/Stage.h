//
// Created by n on 19/08/2026.
//

#ifndef RAYLIB_STG_STAGE_H
#define RAYLIB_STG_STAGE_H
#include <vector>

class Stage
{
protected:
        const std::string_view name;
        const std::vector<PHASES> phaseList;
        const size_t phaseCount;
public:
        Stage(const std::string_view _name, const std::vector<PHASES>& _phaseList) : name(_name), phaseList(_phaseList),  phaseCount(phaseList.size()) {}

        [[nodiscard]] std::string_view GetName() const
        {
                return name;
        }

        [[nodiscard]] const std::vector<PHASES>& GetPhaseList() const
        {
                return phaseList;
        }

        [[nodiscard]] size_t GetPhaseCount() const
        {
                return phaseCount;
        }
};
#endif //RAYLIB_STG_STAGE_H