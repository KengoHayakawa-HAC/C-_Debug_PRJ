#include "exercise.hpp"
#include <cstdio>
#include <utility>

namespace resource {
Resource::Resource(std::vector<int> data) : data_(std::move(data)) {}

Resource::Resource(const Resource& other) : data_(other.data_) {
    ++counts_.copies;
    std::puts("Resource(const Resource&) : COPY");
}

Resource::Resource(Resource&& other) noexcept : data_(std::move(other.data_)) {
    ++counts_.moves;
    std::puts("Resource(Resource&&) : MOVE");
}

const std::vector<int>& Resource::data() const {
    return data_;
}

void Resource::reset_counts() {
    counts_ = {};
}

Counts Resource::counts() {
    return counts_;
}

Resource transfer(const Resource& source) {
    return Resource(std::move(source));
}

TransferReport run_transfer(const std::vector<int>& input) {
    const Resource source(input);
    // Measurement covers construction of the destination Resource only.
    Resource::reset_counts();
    Resource destination = transfer(std::move(source));
    const Counts measured = Resource::counts();
    // Exporting the report is outside the measurement interval.
    return {measured, destination.data()};
}
}
