# **Linked Lists to Simulate a Simple Blockchain**

This project demonstrates how to simulate a simple blockchain using linked lists in C. The blockchain includes basic functionalities such as block creation, mining, validation, and saving/loading to a binary ledger file.

---

## **Table of Contents**
1. [Project Overview](#project-overview)
2. [Features](#features)
3. [Project Structure](#project-structure)
4. [Setup and Installation](#setup-and-installation)
5. [How to Run the Code](#how-to-run-the-code)
6. [Dependencies](#dependencies)
7. [Contributing](#contributing)

---

## **Project Overview**

This project implements a simple blockchain using linked lists in C. Each block in the blockchain contains:
- **Index**: The position of the block in the chain.
- **Timestamp**: The time when the block was created.
- **Data**: The information stored in the block.
- **Hash**: A unique hash calculated from the block's data, nonce, and the previous block's hash.
- **Previous Hash**: The hash of the previous block in the chain.
- **Nonce**: A value used during the mining process to find a valid hash.

The project also includes functionality to save the blockchain to a binary file and load it back into memory.

---

## **Features**

- **Block Creation**: Create new blocks with a unique index, timestamp, and data.
- **Mining**: Simulate the mining process by finding a valid hash for a block.
- **Validation**: Validate the integrity of the blockchain by checking the links between blocks.
- **Display**: Display the entire blockchain with details of each block.

---

