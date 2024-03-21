#include <algorithm>
#include <iostream>
#include <string>
#include <fstream>
#include <vector>
#include <cmath>

class node {
public:
  std::string data;
  node *next{};
};

class linkedList {
  node *front;
  node *index[26]{};

public:
  int getLetVal(char ch) {
    return tolower(ch) - 'a';
  }

  long nameToNumber(const std::string &name) {
    long num = 0;
    int len = std::min(3, static_cast<int>(name.length()));
    for (int i = 0; i < len; ++i) {
      num += getLetVal(name[i]) * std::pow(26, 2 - i);
    }
    return num;
  }

  linkedList() : front(nullptr) {
    for (auto &i: index) i = nullptr;
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
    int letterIndex = tolower(n[0]) - 'a';

    if (front == nullptr || nameToNumber(n) < nameToNumber(front->data)) {
      newNode->next = front;
      front = newNode;
      if (index[letterIndex] == nullptr || index[letterIndex]->data > n) {
        index[letterIndex] = newNode;
      }
    } else {
      node *prev = findSpot(n);
      newNode->next = prev->next;
      prev->next = newNode;
      if (index[letterIndex] == nullptr || index[letterIndex]->data > n) {
        index[letterIndex] = newNode;
      }
    }
  }

  void deleteNode(const std::string &n) {
    if (front == nullptr) return;

    int letterIndex = tolower(n[0]) - 'a';


    if (nameToNumber(front->data) == nameToNumber(n)) {
      node *temp = front;
      front = front->next;
      // Update index if the deleted node was the first of its letter
      if (index[letterIndex] == temp) {
        index[letterIndex] = (front != nullptr && tolower(front->data[0]) == letterIndex + 'a') ? front : nullptr;
      }
      delete temp;
    } else {
      node *prev = nullptr;
      node *curr = front;
      while (curr != nullptr && nameToNumber(curr->data) != nameToNumber(n)) {
        prev = curr;
        curr = curr->next;
      }

      if (curr == nullptr) {
        std::cout << "Not Found!" << std::endl;
        return;
      }


      if (index[letterIndex] == curr) {
        index[letterIndex] = (curr->next != nullptr && tolower(curr->next->data[0]) == letterIndex + 'a')
                               ? curr->next
                               : nullptr;
      }

      // Delete the node
      prev->next = curr->next;
      delete curr;
    }
  }


  void readFile() {
    std::string fileName;
    std::cout << "Enter file name (eg \"names.txt\"): ";
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
    letter = tolower(letter);
    int letterIndex = letter - 'a';

    if (index[letterIndex] == nullptr) {
      std::cout << "No names starting with '" << letter << "' found." << std::endl;
      return;
    }
    node *curr = index[letterIndex];

    while (curr != nullptr && tolower(curr->data[0]) == letter) {
      std::cout << curr->data << " ";
      curr = curr->next;
    }
    std::cout << std::endl;
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
