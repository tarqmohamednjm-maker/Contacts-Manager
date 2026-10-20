#include "Phone.h"
#include <regex>

// ─── Constructor ───────────────────────────────────────────────────────────────────
Phone::Phone(const std::string &number) : number(number), deleted(false) {}

// ─── Setter - Getter ───────────────────────────────────────────────────────────────────
void Phone::setNumber(const std::string &number) { this->number = number; }
std::string Phone::getNumber() const { return number; }

// ─── Validation ───────────────────────────────────────────────────────────────────
bool Phone::isValidNumber(const std::string &number)
{
    // must start with +201 or 01 then 0 or 1 or 2 or 5 then 8 digits for total of 11 or 13 digits
    static const std::regex pattern(R"(^(\+201|01)[0125]\d{8}$)");
    return std::regex_match(number, pattern);
}

// ─── Deleting ───────────────────────────────────────────────────────────────────
void Phone::deletePhone() { deleted = true; }
bool Phone::isDeletedPhone() const { return deleted; }

// ─── Restoring ───────────────────────────────────────────────────────────────────
void Phone::restorePhone() { deleted = false; }