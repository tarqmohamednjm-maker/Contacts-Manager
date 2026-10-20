#ifndef _EMAIL_H_INCLUDED
#define _EMAIL_H_INCLUDED
#include <string>

class Email
{
private:
    // Value
    std::string email;

    // State
    bool deleted;

public:
    // Constructor
    Email(const std::string & = "");

    // Setter - Getter
    void setEmail(const std::string &);
    std::string getEmail() const;

    // Validation
    static bool isValidEmail(const std::string &);

    // Deleting
    bool isDeletedEmail() const;
    void deleteEmail();

    // Restoring
    void restoreEmail();
};
#endif