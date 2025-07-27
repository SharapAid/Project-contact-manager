<h1 align="center">📇 Terminal Contact Manager</h1>

<p align="center">
  <img src="https://media.giphy.com/media/3oKIPwoeGErMmaI43C/giphy.gif" width="250" alt="Terminal Magic"/>
</p>

<p align="center"><b>Manage your contacts from the terminal with sleek C++ power, featuring embedded SQLite3 for persistent storage.</b></p>

---

## 🚀 Getting Started

### 🔧 Requirements
- C++17 or higher
- g++ or compatible compiler
- SQLite3 development library

---

### 🛠️ Build & Run

```bash
g++ -std=c++17 application.cpp contact.cpp contactmanager.cpp databasemanager.cpp -lsqlite3 -o ContactApp
./ContactApp
```
---

### 🧩 Features

Option	Functionality
- 0	 - Exit
- 1	 - Add a new contact
- 2	 - Display all contacts
- 3	 - Search contact by ID
- 4	 - Edit contact information
- 5	 - Delete contact

---

✔️ Contacts are saved automatically to a SQLite3 database.

---

### 📸 Sample Interaction
```bash
___________________MENU_______________
What do you want to do?
0 - Exit
1 - Add new contact
2 - Show all contacts
3 - Find contact
4 - Change contact
5 - Delete contact
```

⬇️
```
Enter name of contact: Alice
Enter cogname of contact: Johnson
Enter number of contact: 123456789
Enter email of contact: alice@example.com
```
---

### 💡 Future Enhancements

- [ ] Sort and filter contacts

- [ ] Export to JSON/CSV

- [ ] GUI interface using Qt or SFML

- [ ] Dark-mode terminal themes with pixel-art banners 😎

---

### 👩‍💻 Created By

SharapAid — C++ enthusiast and pixel-powered problem solver 🔗 GitHub SharapAid

---

<p align="center">🛸 Powered by caffeine, compiled in chaos.</p>
