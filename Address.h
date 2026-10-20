#ifndef _ADDRESS_H_INCLUDED
#define _ADDRESS_H_INCLUDED
#include <string>

class Address
{
private:
    // Value
    std::string address;

    // State
    bool deleted;

public:
    // Constructor
    Address(const std::string & = "");

    // Setter - Getter
    void setAddress(const std::string &);
    std::string getAddress() const;

    // Deleting
    bool isDeletedAddress() const;
    void deleteAddress();

    // Restoring
    void restoreAddress();
};
#endif