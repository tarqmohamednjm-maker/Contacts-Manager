#ifndef _PHONE_H_INCLUDED
#define _PHONE_H_INCLUDED
#include <string>

class Phone
{
private:
    // Value
    std::string number;

    // State
    bool deleted;

public:
    // Constructor
    Phone(const std::string & = "");

    // Setter - Getter
    void setNumber(const std::string &);
    std::string getNumber() const;

    // Validation
    static bool isValidNumber(const std::string &);

    // Deleting
    void deletePhone();
    bool isDeletedPhone() const;

    // Restoring
    void restorePhone();
};
#endif