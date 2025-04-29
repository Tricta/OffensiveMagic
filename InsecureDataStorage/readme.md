# Insecure Data Storage

This is an Insecure Data Storage Proof-of-Concept (PoC) designed to exemplify how an attacker could remotely steal files from an app’s internal storage using a Magisk module.

## Potential Targets
- Apps storing sensitive data in plain text or unprotected formats
- Session or login tokens saved in internal storage
- Cached API responses, configuration files, or SQLite databases

## Why It Matters
Mobile apps often assume internal storage is secure. This PoC highlights how improper data storage practices combined with device compromise (e.g., via Magisk) can lead to serious data leaks.