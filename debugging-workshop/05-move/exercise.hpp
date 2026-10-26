#pragma once
#include <vector>

namespace resource {
struct Counts {
    int copies = 0;
    int moves = 0;
};

class Resource {
public:
    explicit Resource(std::vector<int> data);
    Resource(const Resource& other);
    Resource(Resource&& other) noexcept;
    const std::vector<int>& data() const;
    static void reset_counts();
    static Counts counts();
private:
    std::vector<int> data_;
    inline static Counts counts_{};
};

struct TransferReport {
    Counts operations;
    std::vector<int> data;
};

Resource transfer(const Resource& source);
TransferReport run_transfer(const std::vector<int>& input);
}
