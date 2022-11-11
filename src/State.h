#include <string>

class State
{
    public:
        State(std::string name)
        {
            _name = name;
        }

        std::string GetName()
        {
            return _name;
        }

    private:
        std::string _name;
};