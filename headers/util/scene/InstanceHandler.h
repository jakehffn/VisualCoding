#include <vector>
#include <unordered_map>

#include "Instance.h"

class InstanceHandler {
public:
    InstanceHandler();

private:

    std::unordered_map<GLuint, std::vector<Instance*>> Instances;
};