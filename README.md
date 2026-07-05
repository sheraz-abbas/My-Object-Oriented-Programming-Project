# 💰 Kaun Banega Crorepati (KBC) - C++ Console Game

Welcome to the **Kaun Banega Crorepati (KBC)** console game! This is a text-based, object-oriented recreation of the iconic television quiz show. Built entirely in C++, this project simulates the high-stakes atmosphere of the hot seat, testing the player's general knowledge as they attempt to win the ultimate prize of 7 Crores.

## 🚀 Features

* **Classic KBC Gameplay:** 15 increasingly difficult questions leading up to the grand prize.
* **Object-Oriented Design:** Built using clean OOP principles (Classes for `Question`, `QuestionBank`, and `Scoreboard`).
* **The Lifelines:** Three classic lifelines are fully functional in the console terminal:
    * **50:50:** Dynamically removes two incorrect options.
    * **Audience Poll:** Generates randomized, weighted percentages favoring the correct answer based on difficulty.
    * **Phone a Friend:** Simulates a friend's response with varying accuracy levels.
* **Safe Zones:** Implemented "milestone" questions where your prize money is secured even if you answer a later question incorrectly.

---

## 🛠️ Concepts Demonstrated

* **Encapsulation & Modular Design:** Distinct logical units separating game state, question handling, and data scoring.
* **Global Configuration Management:** Clean global state management handled via a dedicated `globals.h`.
* **Data Management:** Dynamic vectors or custom arrays utilized to efficiently handle the question pool and randomizations.

---

## 🎮 How to Play / Compile

### Prerequisites
You need a C++ compiler installed on your system (such as GCC/G++ or MSVC).

### Step-by-Step Execution

1. **Clone the repository:**
   ```bash
   git clone [https://github.com/sheraz-abbas/My-Object-Oriented-Programming-Project.git](https://github.com/sheraz-abbas/My-Object-Oriented-Programming-Project.git)
   cd My-Object-Oriented-Programming-Project
