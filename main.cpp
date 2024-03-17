#include <algorithm>
#include <iostream>
#include <string>
#include <fstream>
#include <vector>
#include <cmath>

class node {
public:
  std::string data;
  node *next;
};

class linkedList {
  node *front;

public:
  int getLetVal(char ch) {
    return tolower(ch) - 'a';
  }

  long nameToNumber(const std::string &name) {
    long num = 0;
    for (int i = 0; i < 3; ++i) {
      num *= 26;
      if (i < name.length()) {
        num += getLetVal(name[i]);
      }
    }
    return num;
  }


  linkedList() : front(nullptr) {
  }

  node *makeNode(const std::string &n) {
    node *t = new node;
    t->data = n;
    t->next = nullptr;
    return t;
  }

  void showList() {
    node *current = front;
    while (current != nullptr) {
      std::cout << current->data << " ";
      current = current->next;
    }
    std::cout << std::endl;
  }

  node *findSpot(const std::string &n) {
    node *curr = front;
    node *prev = nullptr;
    while (curr != nullptr && nameToNumber(curr->data) < nameToNumber(n)) {
      prev = curr;
      curr = curr->next;
    }
    return prev;
  }

  void insertSorted(const std::string &n) {
    node *newNode = makeNode(n);
    if (front == nullptr || nameToNumber(n) < nameToNumber(front->data)) {
      newNode->next = front;
      front = newNode;
    } else {
      node *prev = findSpot(n);
      if (prev != nullptr) {
        newNode->next = prev->next;
        prev->next = newNode;
      }
    }
  }

  void deleteNode(const std::string &n) {
    if (front == nullptr) return;

    if (nameToNumber(front->data) == nameToNumber(n)) {
      node *temp = front;
      front = front->next;
      delete temp;
      return;
    }

    node *prev = nullptr;
    node *curr = front;
    while (curr != nullptr && nameToNumber(curr->data) != nameToNumber(n)) {
      prev = curr;
      curr = curr->next;
    }

    if (curr == nullptr) {
      std::cout << "Node not found." << std::endl;
      return;
    }

    prev->next = curr->next;
    delete curr;
  }

  void readFile() {
    std::string fileName;
    std::cout << "Enter file name: ";
    std::cin >> fileName;
    std::ifstream file(fileName);
    std::string name;
    if (file.is_open()) {
      while (getline(file, name)) {
        insertSorted(name);
      }
      file.close();
    } else {
      std::cout << "Unable to open file: " << fileName << std::endl;
    }
  }

  void printNamesStartingWith(char letter) {
    if (front == nullptr) {
      std::cout << "The list is empty." << std::endl;
      return;
    }

    node *current = front;
    bool found = false;
    while (current != nullptr) {
      if (tolower(current->data[0]) == tolower(letter)) {
        std::cout << current->data << std::endl;
        found = true;
      }
      current = current->next;
    }

    if (!found) {
      std::cout << "No names starting with '" << letter << "' found." << std::endl;
    }
  }

  int getLength() {
    int count = 0;
    node *current = front;
    while (current != nullptr) {
      count++;
      current = current->next;
    }
    return count;
  }
};

int main() {
  linkedList myList;
  std::string value;
  char startingLetter;
  int choice = 0;

  myList.readFile();

  do {
    std::cout << "\nMenu:\n"
        << "1. Show List\n"
        << "2. Insert a Node Sorted\n"
        << "3. Delete a Node\n"
        << "4. Get Length of the List\n"
        << "5. Print Names Starting With a Letter\n"
        << "6. Exit\n"
        << "Enter your choice: ";
    std::cin >> choice;
    switch (choice) {
      case 1:
        myList.showList();
        break;

      case 2:
        std::cout << "Enter the value of the new node: ";
        std::cin >> value;
        myList.insertSorted(value);
        std::cout << "Node inserted.\n";
        break;

      case 3:
        std::cout << "Enter the value of the node to delete: ";
        std::cin >> value;
        myList.deleteNode(value);
        std::cout << "Node deleted.\n";
        break;

      case 4:
        std::cout << "Length of the list: " << myList.getLength() << std::endl;
        break;

      case 5:
        std::cout << "Enter the starting letter of the names you want to print: ";
        std::cin >> startingLetter;
        myList.printNamesStartingWith(startingLetter);
        break;

      case 6:
        std::cout << "Exiting program.\n";
        break;

      default:
        std::cout << "Invalid choice. Please try again.\n";
    }
  } while (choice != 6);

  return 0;
}
