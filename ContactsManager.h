#ifndef _CONTACTSMANAGER_H_INCLUDED
#define _CONTACTSMANAGER_H_INCLUDED
#include "Contact.h"

class ContactsManager
{
private:
    // Id Counter
    static int nextId;

    // Deleted Contacts Counter
    int deletedContacts;

    // Owned Contacts Pointer
    std::vector<std::unique_ptr<Contact>> contacts;

public:
    // Constructor
    ContactsManager();

    // Increment and Return Id Counter Value
    static int getNextId();

    // Create - Get Contact
    Contact *addContact(const int);
    Contact *getContact(const int) const;

    // Owned Contacts Counter
    int getCount() const;
    int getRemainingContactCount() const;

    // Owned Contacts Deletion
    bool isDeletedContact(const int) const;
    void deleteContact(Contact *);

    // Owned Contacts Restoration
    void restoreContact(const int);

    // Search — returns indices of matches
    std::vector<int> search(const std::string &term) const;

    // Search Helper Function
    std::string toLower(std::string) const;

    // File Control
    void saveToFile() const;
    void loadFromFile();

    // Destructor
    ~ContactsManager();
};
#endif