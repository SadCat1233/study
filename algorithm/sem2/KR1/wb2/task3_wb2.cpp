#include <iostream>
#include <string>
#include <vector>

using namespace std;

struct Contact {
    string name;
    vector<string> phones;

    Contact(const string& name) : name(name) {};
};

struct Node {
    Contact* contact;
    Node* left;
    Node* right;

    Node(Contact* c) : contact(c), left(nullptr), right(nullptr) {};
};


class PhoneBook {
private:
    Node* root;

    Node* addPhone(Node*& node, Contact* contact) {
        if (node == nullptr) return new Node(contact);
        if (contact->name < node->contact->name) {
            addPhone(node->left, contact);
        } else if (contact->name > node->contact->name) {
            addPhone(node->right, contact);
        } else {
            for (const auto& phone : contact->phones) {
                if (find(node->contact->phones.begin(), node->contact->phones.end(), phone) == node->contact->phones.end()) {
                    node->contact->phones.push_back(phone);
                }
            }
            delete contact;
        }
        return node;
    }

    Node* search(Node* node, const string& name) {
        if (node == nullptr || node->contact->name == name) return node;

        if (name < node->contact->name) {
            return search(node->left, name);
        }
        return search(node->right, name);
    }

    Node* remove(Node*& node, const string& name) {
        if (node == nullptr) return node;

        if (name < node->contact->name) {
            node = remove(node->left, name);
        } else if (name > node->contact->name) {
            node = remove(node->right, name);
        } else {
            if (node->left == nullptr && node->right == nullptr) {
                delete node->contact;
                delete node;
                return nullptr;
            } else if (node->left == nullptr) {
                Node* temp = node->right;
                delete node->contact;
                delete node;
                return temp;
            } else if (node->right == nullptr) {
                Node* temp = node->left;
                delete node->contact;
                delete node;
                return temp;
            }
            Node* temp = findMax(node->left);
            node->contact->name = temp->contact->name;
            node->contact->phones = temp->contact->phones;
            node->left = remove(node->left, temp->contact->name);
        }
        return root;
    }

    Node* findMax(Node* node) {
        while (node->right != nullptr) {
            node = node->right;
        }
        return node;
    }

    void ascendingOutput(Node* node) {
        if (node == nullptr) return;

        ascendingOutput(node->left);

        cout << "Имя: " << node->contact->name << endl;
        cout << "Телефоны: ";
        for (size_t i = 0; i < node->contact->phones.size(); i++) {
            cout << node->contact->phones[i];
            if (i < node->contact->phones.size() - 1) {
                cout << ", ";
            }
        }
        cout << endl << "-------------------" << endl;
        
        ascendingOutput(node->right);
    }

    void deleteTree(Node* node) {
        if (node == nullptr) return;

        deleteTree(node->left);
        deleteTree(node->right);
        delete node->contact;
        delete node;
    }

public:
    PhoneBook() : root(nullptr) {};

    ~PhoneBook() {
        deleteTree(root);
    }

    void addContact(const string& name, const string& phone) {
        Contact* contact = new Contact(name);
        contact->name = name;
        contact->phones.push_back(phone);
        root = addPhone(root, contact);
    }

    void findContact(const string& name) {
        Node* node = search(root, name);

        if (node == nullptr) {
            cout << "Контакт с именем " << name << " не найден" << endl;
        } else {
            cout << "Найден контакт:" << endl;
            cout << "Имя контакта: " << name << endl;
            cout << "Телефоны: ";
            for (size_t i = 0; i < node->contact->phones.size(); i++) {
                cout << node->contact->phones[i];
                if (i < node->contact->phones.size() - 1) {
                    cout << ", ";
                }
            }
            cout << endl;
        }
    }

    void deleteContact(const string& name) {
        Node* node = search(root, name);
        if (node == nullptr) {
            cout << "Контакт с именем " << name << "не найден" << endl;
        } else {
            root = remove(root, name);
            cout << "Контакт с именем " << name << " удалён" << endl;
        }
    }

    void deletePhone(const string& name, const string& phone) {
        Node* node = search(root, name);

        if (node == nullptr) {
            cout << "Контакт с именем " << name << "не найден" << endl;
            return;
        }  

        vector<string>& curPhones = node->contact->phones;
        auto it = find(curPhones.begin(), curPhones.end(), phone);

        if (it == curPhones.end()) {
            cout << "Телефон: " << phone << " не найден у контакта: " << name << "." << endl;
            return;
        }
        curPhones.erase(it);
        cout << "Телефон: " << phone << " удален у контакта: " << name << "." << endl;

        if (curPhones.empty()) {
            root = remove(root, name);
            cout << "У контакта не осталось телефонов. Контакт удален." << endl;
        }
    }

    void displayAll() {
        if (root == nullptr) {
            cout << "Телефонная книга пустая." << endl;
        } else {
            cout << "==== Все контакты ====" << endl;
            ascendingOutput(root);
        }
    }
};

void displayMenu() {
    cout << "\n=== ТЕЛЕФОННАЯ КНИГА ===" << endl;
    cout << "1. Добавить контакт" << endl;
    cout << "2. Найти контакт по имени" << endl;
    cout << "3. Удалить контакт" << endl;
    cout << "4. Удалить телефон у контакта" << endl;
    cout << "5. Показать все контакты" << endl;
    cout << "0. Выход" << endl;
    cout << "Выберите действие: ";
}

int main() {
    PhoneBook phonebook;
    int choice;
    string name, phone;
    do {
        displayMenu();
        cin >> choice;
        cin.ignore();

        switch (choice) {
            case 1: {
                cout << "Введите имя: ";
                getline(cin, name);
                cout << "Введите телефон: ";
                getline(cin, phone);
                phonebook.addContact(name, phone);
                cout << "Контакт добавлен!" << endl;
                break;
            }
            case 2: {
                cout << "Введите имя для поиска: ";
                getline(cin, name);
                phonebook.findContact(name);
                break;
            }
            case 3: {
                cout << "Введите имя для удаления: ";
                getline(cin, name);
                phonebook.deleteContact(name);
                break;
            }
            case 4: {
                cout << "Введите имя: ";
                getline(cin, name);
                cout << "Введите телефон для удаления: ";
                getline(cin, phone);
                phonebook.deletePhone(name, phone);
                break;
            }
            case 5: {
                phonebook.displayAll();
                break;
            }
            case 0: {
                cout << "Выход из программы." << endl;
                break;
            }
            default: {
                cout << "Неверный выбор. Попробуйте снова." << endl;
                break;
            }
        }
    } while (choice != 0);

    return 0;
}