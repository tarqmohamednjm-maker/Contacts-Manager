#ifndef _UI_H_INCLUDED
#define _UI_H_INCLUDED
#include <string>
#include "ContactsManager.h"
#include "Contact.h"
#include "Phone.h"
#include "Email.h"

class UI
{
private:
    // Contact Manager Object
    ContactsManager cm;

    // Menus
    void mainMenu() const;
    void updateMenu() const;
    void addtoContactMenu() const;
    void restoreMenu() const;

    // Main Menu Prompts
    void promptAddContact();
    void promptSearch() const;
    void promptUpdate();
    void promptDisplayAll() const;
    void promptCount() const;
    void promptDeleteContact();
    void promptRestoreContact();

    // Update Menu Prompts
    void promptEditContact(Contact *);
    void promptAddtoContact(Contact *);
    void promptRestoreDeletes(Contact *);

    // Restore Menu Prompts
    void promptRestorePhone(Contact *);
    void promptRestoreEmail(Contact *);
    void promptRestoreAddress(Contact *);

    // Contact field input
    void inputName(Contact *);
    void inputPhones(Contact *);
    void inputEmails(Contact *);
    void inputAddresses(Contact *);

    // Lookup Contact
    Contact *lookupContact();

    // Editing Contact
    void editContact(Contact *);
    void editName(Contact *);
    void editPhones(Contact *);
    void editEmails(Contact *);
    void editAddresses(Contact *);

    // Deleting
    void deleteContact(Contact *);
    void deletePhone(Contact *, const int);
    void deleteEmail(Contact *, const int);
    void deleteAddress(Contact *, const int);

    // Adding to Contact
    void addPhones(Contact *);
    void addEmails(Contact *);
    void addAddresses(Contact *);

    // Restoring deletaions
    void restore(const std::vector<int> &, const int, Contact *);
    void performRestoration(const int, const int, Contact *);
    void restoreContact();
    void restorePhone(Contact *);
    void restoreEmail(Contact *);
    void restoreAddress(Contact *);

    // Validators
    void menuChoice(int &, int, const int);
    void entriesCountInput(int &, int, const int);
    bool validNumber(const std::string &) const;
    bool validEmail(const std::string &) const;
    bool Duplicate(const std::string &, const int, Contact *) const;
    bool validChoice();

public:
    void run();
};
#endif