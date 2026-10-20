#include "Address.h"

// ─── Constructor ───────────────────────────────────────────────────────────────────
Address::Address(const std::string &address) : address(address), deleted(false) {}

// ─── Setter - Getter ───────────────────────────────────────────────────────────────────
void Address::setAddress(const std::string &address) { this->address = address; }
std::string Address::getAddress() const { return address; }

// ─── Deleting ───────────────────────────────────────────────────────────────────
bool Address::isDeletedAddress() const { return deleted; }
void Address::deleteAddress() { deleted = true; }

// ─── Restoring ───────────────────────────────────────────────────────────────────
void Address::restoreAddress() { deleted = false; }