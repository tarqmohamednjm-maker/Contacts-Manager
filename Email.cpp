#include "Email.h"
#include <regex>

// ─── Constructor ───────────────────────────────────────────────────────────────────
Email::Email(const std::string &email) : email(email), deleted(false) {}

// ─── Setter - Getter ───────────────────────────────────────────────────────────────────
void Email::setEmail(const std::string &email) { this->email = email; }
std::string Email::getEmail() const { return email; }

// ─── Validation ───────────────────────────────────────────────────────────────────
bool Email::isValidEmail(const std::string &email)
{
    // must start with a combination of (numbers - letters - digits - dot) then @ then letters then dot then letters
    static const std::regex pattern(R"(^[a-zA-Z0-9._%+-]+@[a-zA-Z0-9.-]+\.[a-zA-Z]{2,}$)");
    return (std::regex_match(email, pattern));
}

// ─── Deleting ───────────────────────────────────────────────────────────────────
void Email::deleteEmail() { deleted = true; }
bool Email::isDeletedEmail() const { return deleted; }

// ─── Restoring ───────────────────────────────────────────────────────────────────
void Email::restoreEmail() { deleted = false; }