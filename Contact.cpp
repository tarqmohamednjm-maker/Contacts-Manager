#include "Contact.h"
#include <iostream>

// ─── Constructor ───────────────────────────────────────────────────────────────────
Contact::Contact(const int id, const std::string &name)
{
    this->id = id;
    this->deleted = false;
    this->name = name;
    deletedPhonesCount = 0;
    deletedEmailsCount = 0;
    deletedAddressesCount = 0;
}

// ─── Self Setter - Getter ───────────────────────────────────────────────────────────────────
void Contact::setName(const std::string &name) { this->name = name; }
int Contact::getId() const { return id; }
std::string Contact::getName() const { return name; }

// ─── Owned Objects Creators ───────────────────────────────────────────────────────────────────
void Contact::addPhone(const std::string &number) { phones.push_back(std::make_unique<Phone>(number)); }
void Contact::addEmail(const std::string &email) { emails.push_back(std::make_unique<Email>(email)); }
void Contact::addAddress(const std::string &address) { addresses.push_back(std::make_unique<Address>(address)); }

// ─── Owned Objects Setters ───────────────────────────────────────────────────────────────────
void Contact::setPhone(const std::string &number, const int index)
{
    if (index >= 0 && index < (int)phones.size())
        phones[index]->setNumber(number);
}

void Contact::setEmail(const std::string &email, const int index)
{
    if (index >= 0 && index < (int)emails.size())
        emails[index]->setEmail(email);
}

void Contact::setAddress(const std::string &address, const int index)
{
    if (index >= 0 && index < (int)addresses.size())
        addresses[index]->setAddress(address);
}

// ─── Owned Objects Counters ───────────────────────────────────────────────────────────────────
int Contact::getPhonesCount() const { return (int)phones.size(); }
int Contact::getEmailsCount() const { return (int)emails.size(); }
int Contact::getAddressesCount() const { return (int)addresses.size(); }
int Contact::getRemainingPhonesCount() const { return (int)phones.size() - deletedPhonesCount; }
int Contact::getRemainingEmailsCount() const { return (int)emails.size() - deletedEmailsCount; }
int Contact::getRemainingAddressesCount() const { return (int)addresses.size() - deletedAddressesCount; }

// ─── Owned Objects Getters ───────────────────────────────────────────────────────────────────
std::string Contact::getPhone(const int index) const
{
    if (index >= 0 && index < (int)phones.size())
        return phones[index]->getNumber();
    return "";
}

std::string Contact::getEmail(const int index) const
{
    if (index >= 0 && index < (int)emails.size())
        return emails[index]->getEmail();
    return "";
}

std::string Contact::getAddress(const int index) const
{
    if (index >= 0 && index < (int)addresses.size())
        return addresses[index]->getAddress();
    return "";
}

// ─── Self Deletion ───────────────────────────────────────────────────────────────────
bool Contact::isDeletedContact() const { return deleted; }
void Contact::deleteContact() { deleted = true; }

// ─── Owned Objects Deletion ───────────────────────────────────────────────────────────────────
bool Contact::isDeletedPhone(const int index) const
{
    if (index >= 0 && index < (int)phones.size())
        return phones[index]->isDeletedPhone();
    return false;
}
bool Contact::isDeletedEmail(const int index) const
{
    if (index >= 0 && index < (int)emails.size())
        return emails[index]->isDeletedEmail();
    return false;
}
bool Contact::isDeletedAddress(const int index) const
{
    if (index >= 0 && index < (int)addresses.size())
        return addresses[index]->isDeletedAddress();
    return false;
}
void Contact::deletePhone(const int index)
{
    if (index >= 0 && index < (int)phones.size() && ((int)phones.size() - deletedPhonesCount) > 1)
    {
        if (!isDeletedPhone(index))
        {
            phones[index]->deletePhone();
            deletedPhonesCount++;
        }
    }
}

void Contact::deleteEmail(const int index)
{
    if (index >= 0 && index < (int)emails.size() && ((int)emails.size() - deletedEmailsCount) > 0)
    {
        if (!isDeletedEmail(index))
        {
            emails[index]->deleteEmail();
            deletedEmailsCount++;
        }
    }
}

void Contact::deleteAddress(const int index)
{
    if (index >= 0 && index < (int)addresses.size() && ((int)addresses.size() - deletedAddressesCount) > 0)
    {
        if (!isDeletedAddress(index))
        {
            addresses[index]->deleteAddress();
            deletedAddressesCount++;
        }
    }
}

// ─── Self Restoration ───────────────────────────────────────────────────────────────────
void Contact::restoreContact() { deleted = false; }

// ─── Owned Objects Restoration ───────────────────────────────────────────────────────────────────
void Contact::restorePhone(const int index)
{
    if (index >= 0 && index < (int)phones.size())
    {
        if (phones[index]->isDeletedPhone())
        {
            phones[index]->restorePhone();
            deletedPhonesCount--;
        }
    }
}
void Contact::restoreEmail(const int index)
{
    if (index >= 0 && index < (int)emails.size())
    {
        if (emails[index]->isDeletedEmail())
        {
            emails[index]->restoreEmail();
            deletedEmailsCount--;
        }
    }
}
void Contact::restoreAddress(const int index)
{
    if (index >= 0 && index < (int)addresses.size())
    {
        if (addresses[index]->isDeletedAddress())
        {
            addresses[index]->restoreAddress();
            deletedAddressesCount--;
        }
    }
}

// ─── Display Info ───────────────────────────────────────────────────────────────────
void Contact::displayInfo() const
{
    // ─── Seperator───────────────────────────────────────────────────────────────────
    std::cout << "----------------------------------------" << std::endl;

    // ─── Name Printing ───────────────────────────────────────────────────────────────────
    std::cout << "Name: " << name << std::endl;

    // ─── Phones Printing ───────────────────────────────────────────────────────────────────
    if ((int)phones.size() > 1)
        std::cout << "--------------------\nPhones\n--------------------" << std::endl;

    int printingCounter = 1;

    for (size_t i = 0; i < phones.size(); i++)
    {
        if (phones[i]->isDeletedPhone())
            continue;

        std::cout << "Phone";

        if ((int)phones.size() > 1)
            std::cout << " (" << printingCounter++ << ")";

        std::cout << ": " << getPhone(i) << std::endl;
    }

    // ─── Emails Printing ───────────────────────────────────────────────────────────────────
    if ((int)emails.size() > 1)
        std::cout << "--------------------\nEmails\n--------------------" << std::endl;

    printingCounter = 1;

    for (size_t i = 0; i < emails.size(); i++)
    {
        if (emails[i]->isDeletedEmail())
            continue;

        std::cout << "Email";

        if ((int)emails.size() > 1)
            std::cout << " (" << printingCounter++ << ")";

        std::cout << ": " << getEmail(i) << std::endl;
    }

    // ─── Addresses Printing ───────────────────────────────────────────────────────────────────
    if ((int)addresses.size() > 1)
        std::cout << "--------------------\nAddresses\n--------------------" << std::endl;

    printingCounter = 1;

    for (size_t i = 0; i < addresses.size(); i++)
    {
        if (addresses[i]->isDeletedAddress())
            continue;

        std::cout << "Address";

        if ((int)addresses.size() > 1)
            std::cout << " (" << printingCounter++ << ")";

        std::cout << ": " << getAddress(i) << std::endl;
    }

    // ─── Seperator ───────────────────────────────────────────────────────────────────
    std::cout << "----------------------------------------" << std::endl;
}