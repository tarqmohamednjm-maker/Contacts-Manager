#ifndef _CONTACT_H_INCLUDED
#define _CONTACT_H_INCLUDED
#include <vector>
#include <memory>
#include "Phone.h"
#include "Email.h"
#include "Address.h"

class Contact
{
private:
    // Unique id
    int id;

    // State
    bool deleted;

    // Deletes count
    int deletedPhonesCount;
    int deletedEmailsCount;
    int deletedAddressesCount;

    // Name
    std::string name;

    // Pointers of Owned Objects
    std::vector<std::unique_ptr<Phone>> phones;
    std::vector<std::unique_ptr<Email>> emails;
    std::vector<std::unique_ptr<Address>> addresses;

public:
    // Constructor
    Contact(const int, const std::string & = "");

    // Self Setter - Getter
    void setName(const std::string &);
    int getId() const;
    std::string getName() const;

    // Owned Objects Creators
    void addPhone(const std::string &);
    void addEmail(const std::string &);
    void addAddress(const std::string &);

    // Owned Objects Setters
    void setPhone(const std::string &, const int);
    void setEmail(const std::string &, const int);
    void setAddress(const std::string &, const int);

    // Owned Objects Counters
    int getPhonesCount() const;
    int getEmailsCount() const;
    int getAddressesCount() const;
    int getRemainingPhonesCount() const;
    int getRemainingEmailsCount() const;
    int getRemainingAddressesCount() const;

    // Owned Objects Getters
    std::string getPhone(const int) const;
    std::string getEmail(const int) const;
    std::string getAddress(const int) const;

    // Self Deletion
    bool isDeletedContact() const;
    void deleteContact();

    // Owned Objects Deletion
    bool isDeletedPhone(const int) const;
    bool isDeletedEmail(const int) const;
    bool isDeletedAddress(const int) const;
    void deletePhone(const int);
    void deleteEmail(const int);
    void deleteAddress(const int);

    // Self Restoration
    void restoreContact();

    // Owned Objects Restoration
    void restorePhone(const int);
    void restoreEmail(const int);
    void restoreAddress(const int);

    // Display Info
    void displayInfo() const;
};
#endif