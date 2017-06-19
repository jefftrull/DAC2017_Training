// Examples of the use of smart pointers to describe ownership
// Author: Jeff Trull <edaskel@att.net>

#include <algorithm>

#include "smart_pointers.h"

Instance::Instance(std::string const & name,
                   std::shared_ptr<const Cell> cell,
                   std::weak_ptr<Design> parent)
    : name_(name), cell_(std::move(cell)), parent_(parent) {}

std::shared_ptr<Design>
Instance::parent() const {
    return std::shared_ptr<Design>(parent_);
}

std::string const&
Instance::name() const {
    return name_;
}

std::shared_ptr<Instance>
Design::addInstance(std::shared_ptr<const Cell> cell, std::string name) {
    instances_.emplace_back(std::make_shared<Instance>(std::move(name), cell, shared_from_this()));
    return instances_.back();
}

void
Design::removeInstance(std::string const& name) {
    // apply the erase-remove idiom for instances with the given name
    instances_.erase(std::remove_if(instances_.begin(),
                                    instances_.end(),
                                    [&](auto inst) { return inst->name() == name; }),
                     instances_.end());
}

