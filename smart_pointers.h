// Examples of the use of smart pointers to describe ownership
// Author: Jeff Trull <edaskel@att.net>

#include <vector>
#include <memory>

class Design;
class Instance;
class Cell;

std::vector<std::unique_ptr<Cell>>
readCells(std::string const & fileName);

class Library {

    std::shared_ptr<Cell> findCell(std::string const& cellName);

private:
    std::vector<std::shared_ptr<Cell>> cells_;

};

class Instance {
public:
    Instance(std::string const & name,
             std::shared_ptr<const Cell> cell,
             std::weak_ptr<Design> parent);

    std::shared_ptr<Design> parent() const;
    
    std::string const & name() const;

private:
    std::string name_;
    std::shared_ptr<const Cell> cell_;
    std::weak_ptr<Design> parent_;    // it might get deleted
};

class Design : public std::enable_shared_from_this<Design> {

public:
    std::shared_ptr<Instance> addInstance(std::shared_ptr<const Cell> cell, std::string name);

    void removeInstance(std::string const& name);

private:
    std::vector<std::shared_ptr<Instance>> instances_;
};
