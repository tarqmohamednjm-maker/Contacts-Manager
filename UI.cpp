#include "UI.h"
#include <iostream>
#include <regex>
// ─── enums ─────────────────────────────────────────────────────────────
enum dataType
{
    CONTACT,
    PHONE,
    EMAIL,
    ADDRESS,
    NAME
};
enum menuChoice
{
    MAINMENU,
    UPDATEMENU,
    ADDTOCONTACTMENU,
    RESTOREMENU
};

// ─── Run Code ─────────────────────────────────────────────────────────────
void UI::run()
{
    int option;

    std::cout << "Welcome to Phone Contacts Manager!" << std::endl;

    do
    {
        menuChoice(option, 7, MAINMENU);

        switch (option)
        {
        case 1:
            std::cout << std::endl;
            promptAddContact();
            break;
        case 2:
            std::cout << std::endl;
            promptDisplayAll();
            break;
        case 3:
            std::cout << std::endl;
            promptSearch();
            break;
        case 4:
            std::cout << std::endl;
            promptUpdate();
            break;
        case 5:
            std::cout << std::endl;
            promptCount();
            break;
        case 6:
            std::cout << std::endl;
            promptDeleteContact();
            break;
        case 7:
            std::cout << std::endl;
            promptRestoreContact();
            break;
        default:
            break;
        }
    } while (option != 0);

    std::cout << std::endl
              << "Thank you for using my Phone Contact Manager." << std::endl;
}

// ─── Menus ─────────────────────────────────────────────────────────────
void UI::mainMenu() const
{
    std::cout << std::endl;
    std::cout << "=== PHONE CONTACTS MANAGER ===" << std::endl;
    std::cout << "1. Add new Contact" << std::endl;
    std::cout << "2. Display All Contacts" << std::endl;
    std::cout << "3. Search in Contacts" << std::endl;
    std::cout << "4. Update a Contact" << std::endl;
    std::cout << "5. Show Contacts Count" << std::endl;
    std::cout << "6. Delete a Contact" << std::endl;
    std::cout << "7. Restore a Contact" << std::endl;
    std::cout << "0. Exit" << std::endl;
    std::cout << "===============================" << std::endl;
    std::cout << "Enter your choice: ";
}
void UI::updateMenu() const
{
    std::cout << std::endl;
    std::cout << "========= Update Menu =========" << std::endl;
    std::cout << "1. Edit Contact current Details" << std::endl;
    std::cout << "2. Add new Entries to Contact (Phones - Emails - Addresses)" << std::endl;
    std::cout << "3. Restore deleted Entries" << std::endl;
    std::cout << "0. Return to Main Menu" << std::endl;
    std::cout << "===============================" << std::endl;
    std::cout << "Enter your choice: ";
}
void UI::addtoContactMenu() const
{
    std::cout << std::endl;
    std::cout << "===== Add to Contact Menu =====" << std::endl;
    std::cout << "1. Add new Phone(s)" << std::endl;
    std::cout << "2. Add new Email(s)" << std::endl;
    std::cout << "3. Add new Address(es)" << std::endl;
    std::cout << "0. Return to Update Menu" << std::endl;
    std::cout << "===============================" << std::endl;
    std::cout << "Enter your choice: ";
}
void UI::restoreMenu() const
{
    std::cout << std::endl;
    std::cout << "=== Restore Menu ===" << std::endl;
    std::cout << "1. Restore deleted Phone(s)" << std::endl;
    std::cout << "2. Restore deleted Email(s)" << std::endl;
    std::cout << "3. Restore deleted Address(es)" << std::endl;
    std::cout << "0. Return to Update Menu" << std::endl;
    std::cout << "===============================" << std::endl;
    std::cout << "Enter your choice: ";
}

// ─── Main Menu Prompts ─────────────────────────────────────────────────────────────
void UI::promptAddContact()
{
    std::cout << "=== Add New Contact ===" << std::endl;

    Contact *c = cm.addContact(ContactsManager::getNextId());

    if (!c)
        return;

    inputName(c);
    inputPhones(c);
    inputEmails(c);
    inputAddresses(c);

    std::cout << "Contact added successfully!" << std::endl;
}
void UI::promptSearch() const
{
    if (!cm.getRemainingContactCount())
    {
        std::cout << "No contacts yet!" << std::endl;
        return;
    }

    std::string term;
    std::cout << "Enter search term: ";
    if (!getline(std::cin, term))
    {
        std::cout << "\nInput stream closed. Exiting program." << std::endl;
        exit(0);
    }

    std::vector<int> results = cm.search(term);

    if (results.empty())
        std::cout << "No matches were found." << std::endl;

    else
    {
        std::cout << "Found " << results.size() << " contact(s):" << std::endl;

        for (int idx : results)
            cm.getContact(idx)->displayInfo();
    }
}
void UI::promptUpdate()
{
    if (!cm.getRemainingContactCount())
    {
        std::cout << "No contacts yet!" << std::endl;
        return;
    }

    Contact *c = lookupContact();

    if (!c)
        return;

    c->displayInfo();

    int option;

    do
    {
        menuChoice(option, 3, UPDATEMENU);

        switch (option)
        {
        case 1:
            std::cout << std::endl;
            promptEditContact(c);
            break;
        case 2:
            std::cout << std::endl;
            promptAddtoContact(c);
            break;
        case 3:
            std::cout << std::endl;
            promptRestoreDeletes(c);
            break;
        default:
            return;
            break;
        }
    } while (option != 0);
}
void UI::promptDisplayAll() const
{
    if (!cm.getRemainingContactCount())
    {
        std::cout << "No contacts yet!" << std::endl;
        return;
    }

    std::cout << "=== All Contacts (" << cm.getRemainingContactCount() << ") ===" << std::endl;

    for (int i = 0; i < cm.getCount(); i++)
    {
        if (!cm.isDeletedContact(i))
            cm.getContact(i)->displayInfo();
    }
}
void UI::promptCount() const
{
    std::cout << "You have (" << cm.getRemainingContactCount() << ") contact(s) saved." << std::endl;
}
void UI::promptDeleteContact()
{
    if (!cm.getRemainingContactCount())
    {
        std::cout << "No contacts to delete!" << std::endl;
        return;
    }

    Contact *c = lookupContact();

    if (!c)
        return;

    c->displayInfo();

    deleteContact(c);
}
void UI::promptRestoreContact()
{
    if (cm.getCount() == cm.getRemainingContactCount())
    {
        std::cout << "No deleted contacts to restore." << std::endl;
        return;
    }

    restoreContact();
}

// ─── Update Menu Prompts ──────────────────────────────────────────────────────────────────
void UI::promptEditContact(Contact *c)
{
    if (!c)
        return;

    editContact(c);
}
void UI::promptAddtoContact(Contact *c)
{
    if (!c)
        return;

    int option;
    do
    {

        menuChoice(option, 3, ADDTOCONTACTMENU);

        switch (option)
        {
        case 1:
            std::cout << std::endl;
            addPhones(c);
            break;
        case 2:
            std::cout << std::endl;
            addEmails(c);
            break;
        case 3:
            std::cout << std::endl;
            addAddresses(c);
            break;
        default:
            break;
        }
    } while (option != 0);
}
void UI::promptRestoreDeletes(Contact *c)
{
    int option;

    do
    {
        menuChoice(option, 3, RESTOREMENU);

        switch (option)
        {
        case 1:
            std::cout << std::endl;
            promptRestorePhone(c);
            break;
        case 2:
            std::cout << std::endl;
            promptRestoreEmail(c);
            break;
        case 3:
            std::cout << std::endl;
            promptRestoreAddress(c);
            break;
        default:
            break;
        }
    } while (option != 0);
}

// ─── Restore Menu Prompts ──────────────────────────────────────────────────────────────────
void UI::promptRestorePhone(Contact *c)
{
    if (!c)
        return;

    restorePhone(c);
}
void UI::promptRestoreEmail(Contact *c)
{
    if (!c)
        return;

    restoreEmail(c);
}
void UI::promptRestoreAddress(Contact *c)
{
    if (!c)
        return;

    restoreAddress(c);
}

// ─── Contact field input ─────────────────────────────────────────────────────────────
void UI::inputName(Contact *c)
{
    std::string name;
    bool isDuplicate;

    do
    {
        isDuplicate = false;

        std::cout << "Enter name: ";
        if (!getline(std::cin, name))
        {
            std::cout << "\nInput stream closed. Exiting program." << std::endl;
            exit(0);
        }

        if (name.empty())
        {
            std::cout << "Name field is required!" << std::endl;
            continue;
        }

        if (Duplicate(name, NAME, nullptr))
        {
            std::cout << "Theres another Contact saved with the same Name!" << std::endl;
            isDuplicate = true;
        }
    } while (name.empty() || isDuplicate);

    c->setName(name);
}
void UI::inputPhones(Contact *c)
{
    int entriesCount;

    int allowedSize = 5 - c->getRemainingPhonesCount();

    entriesCountInput(entriesCount, allowedSize, PHONE);

    int totalEntriesCount = entriesCount + c->getRemainingPhonesCount();

    std::string num;
    bool isDuplicate;
    bool isValid;
    int printingCounter = 1;

    for (int i = 0; i < totalEntriesCount; i++)
    {
        bool overwrite = false;
        if (c->getPhonesCount() >= i + 1) // Already Created
        {
            if (allowedSize + c->getPhonesCount() <= 5) // Don`t overwrite unless needed
                continue;
            if (!c->isDeletedPhone(i)) // Don`t overwrite unless deleted
                continue;
            if (c->isDeletedPhone(i))
            { // phones.deleted = false; deletedPhones --;
                c->restorePhone(i);
                overwrite = true;
            }
        }

        do
        {
            isDuplicate = false;
            isValid = true;

            std::cout << "Enter phone";

            if (entriesCount > 1)
                std::cout << " (" << printingCounter << ")";

            std::cout << " number: ";

            if (!getline(std::cin, num))
            {
                std::cout << "\nInput stream closed. Exiting program." << std::endl;
                exit(0);
            }

            if (!validNumber(num))
            {
                std::cout << "Invalid number! Please re-enter." << std::endl;
                isValid = false;
                continue;
            }

            if (Duplicate(num, PHONE, c))
            {
                std::cout << "This number is already saved to the contact!" << std::endl;
                isDuplicate = true;
            }
        } while (!isValid || isDuplicate);

        printingCounter++;

        if (overwrite)
        {
            c->setPhone(num, i);
            continue;
        }

        c->addPhone(num);
    }
}
void UI::inputEmails(Contact *c)
{
    int entriesCount;

    int allowedSize = 5 - c->getRemainingEmailsCount();

    entriesCountInput(entriesCount, allowedSize, EMAIL);

    int totalEntriesCount = entriesCount + c->getRemainingEmailsCount();

    std::string email;
    bool isDuplicate;
    bool isValid;
    int printingCounter = 1;

    for (int i = 0; i < totalEntriesCount; i++)
    {
        bool overwrite = false;

        if (c->getEmailsCount() >= i + 1) // Already Created
        {
            if (allowedSize + c->getEmailsCount() <= 5) // Don`t overwrite unless needed
                continue;

            if (!c->isDeletedEmail(i)) // Don`t overwrite unless deleted
                continue;

            if (c->isDeletedEmail(i))
            { // emails.deleted = false; deletedEmails --;
                c->restoreEmail(i);
                overwrite = true;
            }
        }

        do
        {
            isDuplicate = false;
            isValid = true;

            std::cout << "Enter email";

            if (entriesCount > 1)
                std::cout << " (" << printingCounter << ")";

            std::cout << " address: ";

            if (!getline(std::cin, email))
            {
                std::cout << "\nInput stream closed. Exiting program." << std::endl;
                exit(0);
            }

            if (!validEmail(email))
            {
                std::cout << "Wrong email address! Please re-enter." << std::endl;
                isValid = false;
                continue;
            }

            if (Duplicate(email, EMAIL, c))
            {
                std::cout << "This email is already saved to the contact!" << std::endl;
                isDuplicate = true;
            }
        } while (!isValid || isDuplicate);

        printingCounter++;

        if (overwrite)
        {
            c->setEmail(email, i);
            continue;
        }

        c->addEmail(email);
    }
}
void UI::inputAddresses(Contact *c)
{
    int entriesCount;

    int allowedSize = 5 - c->getRemainingAddressesCount();

    entriesCountInput(entriesCount, allowedSize, ADDRESS);

    int totalEntriesCount = entriesCount + c->getRemainingAddressesCount();

    std::string address;
    bool isDuplicate;
    int printingCounter = 1;

    for (int i = 0; i < totalEntriesCount; i++)
    {
        bool overwrite = false;

        if (c->getAddressesCount() >= i + 1) // Already Created
        {
            if (allowedSize + c->getAddressesCount() <= 5) // Don`t overwrite unless needed
                continue;

            if (!c->isDeletedAddress(i)) // Don`t overwrite unless deleted
                continue;

            if (c->isDeletedAddress(i))
            { // addresses.deleted = false; deletedAddress --;
                c->restoreAddress(i);
                overwrite = true;
            }
        }

        do
        {
            isDuplicate = false;
            std::cout << "Enter address";

            if (entriesCount > 1)
                std::cout << " (" << printingCounter << ")";

            std::cout << " location: ";

            if (!getline(std::cin, address))
            {
                std::cout << "\nInput stream closed. Exiting program." << std::endl;
                exit(0);
            }

            if (address.empty())
            {
                std::cout << "Invalid address! Please re-enter." << std::endl;
                continue;
            }

            if (Duplicate(address, ADDRESS, c))
            {
                std::cout << "This address is already saved to the contact!" << std::endl;
                isDuplicate = true;
            }
        } while (address.empty() || isDuplicate);

        printingCounter++;

        if (overwrite)
        {
            c->setAddress(address, i);
            continue;
        }

        c->addAddress(address);
    }
}

// ─── Lookup Contact ─────────────────────────────────────────────────────────────
Contact *UI::lookupContact()
{
    std::string term;

    std::cout << "Enter name of contact: ";

    if (!getline(std::cin, term))
    {
        std::cout << "\nInput stream closed. Exiting program." << std::endl;
        exit(0);
    }

    std::vector<int> results = cm.search(term);

    if (results.empty())
    {
        std::cout << "No matches were found." << std::endl;
        return nullptr;
    }

    if ((int)results.size() > 1)
    {
        std::cout << "Found multiple matches:" << std::endl
                  << std::endl;

        for (int idx : results)
        {
            std::cout << "Contact index (" << idx << "):" << std::endl;
            cm.getContact(idx)->displayInfo();
        }

        std::string input;
        static const std::regex pattern(R"(^(-1|[0-9]{1,8})$)");
        int chosenIndex;

        while (true)
        {
            std::cout << "Enter the Index of the contact from the list above to modify, or -1 to abort: ";

            if (!getline(std::cin, input))
            {
                std::cout << "\nInput stream closed. Exiting program." << std::endl;
                exit(0);
            }

            if (std::regex_match(input, pattern))
            {
                chosenIndex = stoi(input);

                if (chosenIndex == -1)
                    return nullptr;

                for (int idx : results)
                    if (idx == chosenIndex)
                        return cm.getContact(idx);

                std::cout << "Invalid Index! Please re-enter." << std::endl;
            }
            else
                std::cout << "Wrong input! Please re-Enter." << std::endl;
        }
    }
    return cm.getContact(results[0]);
}

// ─── Editing Contact ─────────────────────────────────────────────────────────────
void UI::editContact(Contact *c)
{
    std::cout << "Current contact details:" << std::endl;

    c->displayInfo();

    std::cout << "Enter new details (press enter to keep current) or -1 to delete (except name):" << std::endl;

    editName(c);
    editPhones(c);
    editEmails(c);
    editAddresses(c);

    std::cout << "Contact updated successfully!" << std::endl;
}
void UI::editName(Contact *c)
{
    std::string name;
    bool isDuplicate;

    do
    {
        isDuplicate = false;

        std::cout << "New name [" << c->getName() << "]: ";

        if (!getline(std::cin, name))
        {
            std::cout << "\nInput stream closed. Exiting program." << std::endl;
            exit(0);
        }

        if (name.empty())
            break;

        if (cm.toLower(name) != cm.toLower(c->getName()) && Duplicate(name, NAME, nullptr))
        {
            std::cout << "The name already exists in another contact!" << std::endl;
            isDuplicate = true;
        }
    } while (isDuplicate);

    if (!name.empty())
        c->setName(name);
}
void UI::editPhones(Contact *c)
{
    std::string num;
    bool isDuplicate;
    bool isValid;
    int printingCounter = 1;
    int entries = c->getRemainingPhonesCount();

    for (int i = 0; i < c->getPhonesCount(); i++)
    {
        if (c->isDeletedPhone(i))
            continue;

        do
        {
            isDuplicate = false;
            isValid = true;

            std::cout << "New phone";

            if (entries > 1)
                std::cout << " (" << printingCounter << ")";

            std::cout << " [" << c->getPhone(i) << "]: ";

            if (!getline(std::cin, num))
            {
                std::cout << "\nInput stream closed. Exiting program." << std::endl;
                exit(0);
            }

            if (num.empty())
                break;

            if (num == "-1")
            {
                if (c->getRemainingPhonesCount() <= 1)
                {
                    std::cout << "Cannot delete: Contact must have at least 1 phone number!" << std::endl;
                    continue;
                }

                else
                {
                    c->deletePhone(i);
                    break;
                }
            }

            if (!validNumber(num))
            {
                std::cout << "Invalid number! Please re-Enter." << std::endl;
                isValid = false;
                continue;
            }

            if (num != c->getPhone(i) && Duplicate(num, PHONE, c))
            {
                std::cout << "This number is already saved to the contact!" << std::endl;
                isDuplicate = true;
            }
        } while (!isValid || isDuplicate);

        if (num != "-1")
        {
            printingCounter++;

            if (!num.empty())
                c->setPhone(num, i);
        }
    }
}
void UI::editEmails(Contact *c)
{
    std::string email;
    bool isDuplicate;
    bool isValid;
    int printingCounter = 1;
    int entries = c->getRemainingEmailsCount();

    for (int i = 0; i < c->getEmailsCount(); i++)
    {
        if (c->isDeletedEmail(i))
            continue;

        do
        {
            isDuplicate = false;
            isValid = true;

            std::cout << "New email";

            if (entries > 1)
                std::cout << " (" << printingCounter << ")";

            std::cout << " [" << c->getEmail(i) << "]: ";

            if (!getline(std::cin, email))
            {
                std::cout << "\nInput stream closed. Exiting program." << std::endl;
                exit(0);
            }

            if (email.empty())
                break;

            if (email == "-1")
            {
                c->deleteEmail(i);
                break;
            }

            if (!validEmail(email))
            {
                std::cout << "Invalid email! Please re-Enter." << std::endl;
                isValid = false;
                continue;
            }

            if (cm.toLower(email) != cm.toLower(c->getEmail(i)) && Duplicate(email, EMAIL, c))
            {
                std::cout << "This email is already saved to the contact!" << std::endl;
                isDuplicate = true;
            }
        } while (!isValid || isDuplicate);

        if (email != "-1")
        {
            printingCounter++;

            if (!email.empty())
                c->setEmail(email, i);
        }
    }
}
void UI::editAddresses(Contact *c)
{
    std::string address;
    bool isDuplicate;
    int printingCounter = 1;
    int entries = c->getRemainingAddressesCount();

    for (int i = 0; i < c->getAddressesCount(); i++)
    {
        if (c->isDeletedAddress(i))
            continue;

        do
        {
            isDuplicate = false;

            std::cout << "New address";

            if (entries > 1)
                std::cout << " (" << printingCounter << ")";

            std::cout << " [" << c->getAddress(i) << "]: ";

            if (!getline(std::cin, address))
            {
                std::cout << "\nInput stream closed. Exiting program." << std::endl;
                exit(0);
            }

            if (address.empty())
                break;

            if (address == "-1")
            {
                c->deleteAddress(i);
                break;
            }

            if (cm.toLower(address) != cm.toLower(c->getAddress(i)) && Duplicate(address, ADDRESS, c))
            {
                std::cout << "This address is already saved to the contact!" << std::endl;
                isDuplicate = true;
            }
        } while (isDuplicate);

        if (address != "-1")
        {
            printingCounter++;

            if (!address.empty())
                c->setAddress(address, i);
        }
    }
}

// ─── Deleting ─────────────────────────────────────────────────────────────
void UI::deleteContact(Contact *c)
{
    if (validChoice())
        cm.deleteContact(c);
}
void UI::deletePhone(Contact *c, const int index)
{
    if (c->getRemainingPhonesCount() <= 1)
    {
        std::cout << "The contact must at least have 1 phone number!" << std::endl;
        return;
    }
    if (validChoice())
        c->deletePhone(index);
}
void UI::deleteEmail(Contact *c, const int index)
{
    if (validChoice())
        c->deleteEmail(index);
}
void UI::deleteAddress(Contact *c, const int index)
{
    if (validChoice())
        c->deleteAddress(index);
}

// ─── Adding to Contact ───────────────────────────────────────────────────────────────────
void UI::addPhones(Contact *c)
{
    if (c->getRemainingPhonesCount() >= 5)
        std::cout << "You have reached the limit! Delete some numbers before adding new ones." << std::endl;
    else
    {
        std::cout << "Be aware that adding new numbers may overwrite deleted ones and make them unrestorable!" << std::endl;
        if (validChoice())
            inputPhones(c);
    }
}
void UI::addEmails(Contact *c)
{
    if (c->getRemainingEmailsCount() >= 5)
        std::cout << "You have reached the limit! Delete some emails before adding new ones." << std::endl;
    else
    {
        std::cout << "Be aware that adding new emails may overwrite deleted ones and make them unrestorable!" << std::endl;
        if (validChoice())
            inputEmails(c);
    }
}
void UI::addAddresses(Contact *c)
{
    if (c->getRemainingAddressesCount() >= 5)
        std::cout << "You have reached the limit! Delete some addresses before adding new ones." << std::endl;
    else
    {
        std::cout << "Be aware that adding new addresses may overwrite deleted ones and make them unrestorable!" << std::endl;
        if (validChoice())
            inputAddresses(c);
    }
}

// ─── Restoring ───────────────────────────────────────────────────────────────────
void UI::restore(const std::vector<int> &indices, const int type, Contact *c)
{
    std::string dataType;
    switch (type)
    {
    case CONTACT:
        dataType = "contact";
        break;
    case PHONE:
        dataType = "number";
        break;
    case EMAIL:
        dataType = "email";
        break;
    case ADDRESS:
        dataType = "address";
        break;
    default:
        break;
    }

    std::string input;
    bool firstPrompt = true;
    int restoredCount = 0;
    std::vector<int> restoredIndices;

    static const std::regex pattern(R"(^[0-9]{1,8}$)");

    while (true)
    {
        if (restoredCount == (int)indices.size())
        {
            std::cout << "No more restorable deletes." << std::endl;
            return;
        }

        if (firstPrompt)
        {
            std::cout << "Enter the index of the " << dataType << " to restore, '*' for all, or -1 to abort: ";
            firstPrompt = false;
        }

        else
        {
            std::cout << "Enter another index, '*' or -1: ";
        }

        if (!getline(std::cin, input))
        {
            std::cout << "\nInput stream closed. Exiting program." << std::endl;
            exit(0);
        }

        if (input == "-1")
            break;

        else if (input == "*")
        {
            for (int idx : indices)
            {
                if (std::count(restoredIndices.begin(), restoredIndices.end(), idx))
                    continue;

                performRestoration(type, idx, c);
            }

            std::cout << "All deleted " << dataType << "s restored successfully!" << std::endl;
            return;
        }

        if (std::regex_match(input, pattern))
        {
            int value = std::stoi(input);

            if (std::count(restoredIndices.begin(), restoredIndices.end(), value))
            {
                std::cout << "This " << dataType << " is already restored!" << std::endl;
                continue;
            }

            if (std::count(indices.begin(), indices.end(), value))
            {
                performRestoration(type, value, c);

                std::cout << dataType << " at index " << value << " was restored." << std::endl;

                restoredIndices.push_back(value);
                restoredCount++;
                continue;
            }
        }
        std::cout << "Invalid input. Please enter a correct index." << std::endl;
    }
}
void UI::restoreContact()
{
    std::vector<int> indices;

    std::cout << "========== Deleted Contacts list ==========" << std::endl;

    for (int i = 0; i < cm.getCount(); i++)
    {
        if (cm.getContact(i)->isDeletedContact())
        {
            cm.getContact(i)->displayInfo();

            std::cout << "Contact index (" << i << ")" << std::endl
                      << std::endl;

            indices.push_back(i);
        }
    }

    if (indices.empty())
    {
        std::cout << "No deleted contacts to restore!" << std::endl;
        return;
    }

    restore(indices, CONTACT, nullptr);
}
void UI::restorePhone(Contact *c)
{
    std::vector<int> indices;

    std::cout << "========== Deleted Phones list ==========" << std::endl;

    for (int i = 0; i < c->getPhonesCount(); i++)
    {
        if (c->isDeletedPhone(i))
        {
            std::cout << "----------------------------------------------------------" << std::endl;
            std::cout << "Phone number: " << c->getPhone(i) << " with index (" << i << ")" << std::endl;
            std::cout << "----------------------------------------------------------" << std::endl;

            indices.push_back(i);
        }
    }

    if (indices.empty())
    {
        std::cout << "No deleted numbers to restore!" << std::endl;
        return;
    }

    restore(indices, PHONE, c);
}
void UI::restoreEmail(Contact *c)
{
    std::vector<int> indices;

    std::cout << "========== Deleted Emails list ==========" << std::endl;

    for (int i = 0; i < c->getEmailsCount(); i++)
    {
        if (c->isDeletedEmail(i))
        {
            std::cout << "----------------------------------------------------------" << std::endl;
            std::cout << "Email Address: " << c->getEmail(i) << " with index (" << i << ")" << std::endl;
            std::cout << "----------------------------------------------------------" << std::endl;

            indices.push_back(i);
        }
    }

    if (indices.empty())
    {
        std::cout << "No deleted emails to restore!" << std::endl;
        return;
    }

    restore(indices, EMAIL, c);
}
void UI::restoreAddress(Contact *c)
{
    std::vector<int> indices;
    std::cout << "========== Deleted Addresses list ==========" << std::endl;

    for (int i = 0; i < c->getAddressesCount(); i++)
    {
        if (c->isDeletedAddress(i))
        {
            std::cout << "----------------------------------------------------------" << std::endl;
            std::cout << "Address: " << c->getAddress(i) << " with index (" << i << ")" << std::endl;
            std::cout << "----------------------------------------------------------" << std::endl;

            indices.push_back(i);
        }
    }

    if (indices.empty())
    {
        std::cout << "No deleted addresses to restore!" << std::endl;
        return;
    }

    restore(indices, ADDRESS, c);
}
void UI::performRestoration(const int type, const int index, Contact *c)
{
    switch (type)
    {
    case CONTACT:
        cm.restoreContact(index);
        break;
    case PHONE:
        c->restorePhone(index);
        break;
    case EMAIL:
        c->restoreEmail(index);
        break;
    case ADDRESS:
        c->restoreAddress(index);
        break;
    }
}

// ─── Validators ─────────────────────────────────────────────────────────────
void UI::menuChoice(int &size, int allowedSize, const int type)
{
    std::string input;
    int minVal = 0;

    static const std::regex pattern(R"(^[0-9]{1,8}$)");

    while (true)
    {
        switch (type)
        {
        case MAINMENU:
            mainMenu();
            break;
        case UPDATEMENU:
            updateMenu();
            break;
        case ADDTOCONTACTMENU:
            addtoContactMenu();
            break;
        case RESTOREMENU:
            restoreMenu();
            break;
        default:
            break;
        }

        if (!getline(std::cin, input))
        {
            std::cout << "\nInput stream closed. Exiting program." << std::endl;
            exit(0);
        }

        if (std::regex_match(input, pattern))
        {
            size = stoi(input);

            if (size >= minVal && size <= allowedSize)
                return;
        }

        std::cout << "Wrong input! Please enter a number between "
                  << minVal << " and " << allowedSize << "." << std::endl;
    }
}
void UI::entriesCountInput(int &size, int allowedSize, const int type)
{
    std::string input;
    int minVal = (type == PHONE) ? 1 : 0;

    static const std::regex pattern(R"(^[0-9]{1,8}$)");

    while (true)
    {
        switch (type)
        {
        case PHONE:
            std::cout << "Enter the number of phones (1-" << allowedSize << "): ";
            break;
        case EMAIL:
            std::cout << "Enter the number of emails (0-" << allowedSize << "): ";
            break;
        case ADDRESS:
            std::cout << "Enter the number of addresses (0-" << allowedSize << "): ";
            break;
        default:
            break;
        }

        if (!getline(std::cin, input))
        {
            std::cout << "\nInput stream closed. Exiting program." << std::endl;
            exit(0);
        }

        if (std::regex_match(input, pattern))
        {
            size = stoi(input);
            if (size >= minVal && size <= allowedSize)
                return;
        }

        std::cout << "Wrong input! Please enter a number between "
                  << minVal << " and " << allowedSize << "." << std::endl;
    }
}
bool UI::validNumber(const std::string &number) const
{
    return Phone::isValidNumber(number);
}
bool UI::validEmail(const std::string &email) const
{
    return Email::isValidEmail(email);
}
bool UI::Duplicate(const std::string &input, const int type, Contact *c) const
{
    switch (type)
    {
    case PHONE:
        for (size_t i = 0; i < c->getPhonesCount(); i++)
        {
            if (c->isDeletedPhone(i))
                continue;
            if (c->getPhone(i) == input)
                return true;
        }
        break;
    case EMAIL:
        for (size_t i = 0; i < c->getEmailsCount(); i++)
        {
            if (c->isDeletedEmail(i))
                continue;
            if (cm.toLower(c->getEmail(i)) == cm.toLower(input))
                return true;
        }
        break;
    case ADDRESS:
        for (size_t i = 0; i < c->getAddressesCount(); i++)
        {
            if (c->isDeletedAddress(i))
                continue;
            if (cm.toLower(c->getAddress(i)) == cm.toLower(input))
                return true;
        }
        break;
    case NAME:
        for (size_t i = 0; i < cm.getCount(); i++)
        {
            if (cm.isDeletedContact(i))
                continue;
            if (cm.toLower(cm.getContact(i)->getName()) == cm.toLower(input))
                return true;
        }
        break;
    default:
        break;
    }
    return false;
}
bool UI::validChoice()
{
    std::string input;

    static const std::regex pattern(R"(^[yYnN]$)");

    while (true)
    {
        std::cout << "Are you sure you want to proceed? (y/n): ";

        if (!getline(std::cin, input))
        {
            std::cout << "\nInput stream closed. Exiting program." << std::endl;
            exit(0);
        }

        if (std::regex_match(input, pattern))
        {
            char ans = tolower(input[0]);
            return (ans == 'y');
        }

        std::cout << "Wrong input! Please re-Enter." << std::endl;
    }
}