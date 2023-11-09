#include <string>

struct State
{
    std::string diff;
    int diffLength;

    State() { }
    State(int diffLength, std::string diff)
    {
        this->diff = diff;
        this->diffLength = diffLength;
    }

    bool operator==(const State& otherState) const
    {
        return this->diff == otherState.diff && this->diffLength == otherState.diffLength;
    }

    struct HashFunction
    {
        size_t operator()(const State& state) const
        {
            return std::hash<std::string>()(state.diff) ^ (std::hash<int>()(state.diffLength) << 1);
        }
    };
};