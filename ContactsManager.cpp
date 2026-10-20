#include "ContactsManager.h"
#include <fstream>
#include <iostream>

// ─── Id Initialization ───────────────────────────────────────────────────────────────────
int ContactsManager::nextId = 0;

// ─── Constructor ───────────────────────────────────────────────────────────────────
ContactsManager::ContactsManager() : deletedContacts(0) { loadFromFile(); }

// ─── Create - Get Contact ───────────────────────────────────────────────────────────────────
Contact *ContactsManager::addContact(const int id)
{
    contacts.push_back(std::make_unique<Contact>(id));

    return contacts.back().get();
}

Contact *ContactsManager::getContact(const int index) const
{
    if (index >= 0 && index < (int)contacts.size())
        return contacts[index].get();

    return nullptr;
}

// ─── Increment and Return Id Counter Value ───────────────────────────────────────────────────────────────────
int ContactsManager::getNextId() { return nextId++; }

// ─── Owned Contacts Counter ───────────────────────────────────────────────────────────────────
int ContactsManager::getCount() const { return (int)contacts.size(); }
int ContactsManager::getRemainingContactCount() const { return (int)contacts.size() - deletedContacts; }

// ─── Owned Contacts Deletion ───────────────────────────────────────────────────────────────────
bool ContactsManager::isDeletedContact(const int index) const
{
    if (index >= 0 && index < (int)contacts.size())
        return contacts[index]->isDeletedContact();

    return false;
}
void ContactsManager::deleteContact(Contact *c)
{
    if (!c)
        return;

    c->deleteContact();
    deletedContacts++;
}

// ─── Owned Contacts Restoration ───────────────────────────────────────────────────────────────────
void ContactsManager::restoreContact(const int index)
{
    if (index >= 0 && index < (int)contacts.size())
        if (contacts[index]->isDeletedContact())
        {
            contacts[index]->restoreContact();
            deletedContacts--;
        }
}

// ─── Search ───────────────────────────────────────────────────────────────────
std::vector<int> ContactsManager::search(const std::string &term) const
{
    std::vector<int> results;

    if (!term.empty())
        for (size_t i = 0; i < contacts.size(); i++)
            if (!contacts[i]->isDeletedContact())
                if (toLower(contacts[i]->getName()).find(toLower(term)) != std::string::npos)
                    results.push_back(i);

    return results;
}

// ─── Search Helper Function ───────────────────────────────────────────────────────────────────
std::string ContactsManager::toLower(std::string str) const
{
    for (char &c : str)
        c = tolower(c);

    return str;
}

// ─── File Control ───────────────────────────────────────────────────────────────────
void ContactsManager::saveToFile() const
{
    std::ofstream file("contacts.txt");

    if (!file.is_open())
    {
        std::cout << "Error: Could not save contacts!" << std::endl;
        return;
    }

    file << (getRemainingContactCount() > 0 ? nextId : 0) << "\n";

    file << (int)contacts.size() - deletedContacts << "\n";

    for (size_t i = 0; i < contacts.size(); i++)
    {
        if (contacts[i]->isDeletedContact())
            continue;

        file << contacts[i]->getId() << "\n";

        file << contacts[i]->getName() << "\n";

        file << contacts[i]->getRemainingPhonesCount() << "\n";

        for (int j = 0; j < contacts[i]->getPhonesCount(); j++)
        {
            if (contacts[i]->isDeletedPhone(j))
                continue;

            file << contacts[i]->getPhone(j) << "\n";
        }

        file << contacts[i]->getRemainingEmailsCount() << "\n";

        for (int j = 0; j < contacts[i]->getEmailsCount(); j++)
        {
            if (contacts[i]->isDeletedEmail(j))
                continue;

            file << contacts[i]->getEmail(j) << "\n";
        }

        file << contacts[i]->getRemainingAddressesCount() << "\n";

        for (int j = 0; j < contacts[i]->getAddressesCount(); j++)
        {
            if (contacts[i]->isDeletedAddress(j))
                continue;

            file << contacts[i]->getAddress(j) << "\n";
        }
    }

    if ((int)contacts.size() > 0)
        std::cout << "Your contact" << ((int)contacts.size() > 1 ? "s have " : " has ") << "been saved successfully" << std::endl;

    file.close();
}

void ContactsManager::loadFromFile()
{
    std::ifstream file("contacts.txt");

    if (!file.is_open())
        return;

    file >> nextId;
    file.ignore();

    int total;
    file >> total;
    file.ignore();

    for (int i = 0; i < total; i++)
    {
        int id;
        file >> id;
        file.ignore();

        Contact *c = addContact(id);

        std::string name;
        std::getline(file, name);
        c->setName(name);

        int phones;
        file >> phones;
        file.ignore();

        for (int j = 0; j < phones; j++)
        {
            std::string phone;
            std::getline(file, phone);

            c->addPhone(phone);
        }

        int emails;
        file >> emails;
        file.ignore();

        for (int j = 0; j < emails; j++)
        {
            std::string email;
            std::getline(file, email);

            c->addEmail(email);
        }

        int addresses;
        file >> addresses;
        file.ignore();

        for (int j = 0; j < addresses; j++)
        {
            std::string address;
            std::getline(file, address);

            c->addAddress(address);
        }
    }

    file.close();
}
// ─── Destructor ───────────────────────────────────────────────────────────────────
ContactsManager::~ContactsManager() { saveToFile(); }