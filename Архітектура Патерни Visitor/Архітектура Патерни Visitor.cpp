#include <iostream>
#include <windows.h>
using namespace std;

// Абстракція для елементів (документів)
class Document {
public:
    virtual void accept(class Visitor* visitor) = 0;
    virtual ~Document() = default;
};

// Відвідувач
class Visitor {
public:
    virtual void visit(class TextDocument* text) = 0;
    virtual void visit(class ImageDocument* image) = 0;
    virtual ~Visitor() = default;
};

// Конкретний елемент: текстовий документ
class TextDocument : public Document {
public:
    void accept(Visitor* visitor) override {
        visitor->visit(this);
    }

    void print() {
        cout << "Це текстовий документ." << endl;
    }
};

// Конкретний елемент: зображення
class ImageDocument : public Document {
public:
    void accept(Visitor* visitor) override {
        visitor->visit(this);
    }

    void print() {
        cout << "Це зображення." << endl;
    }
};

// Конкретний відвідувач: для обчислення вартості друку
class PrintCostVisitor : public Visitor {
public:
    void visit(TextDocument* text) override {
        cout << "Вартість друку текстового документа: 1 грн." << endl;
    }

    void visit(ImageDocument* image) override {
        cout << "Вартість друку зображення: 5 грн." << endl;
    }
};

// Об'єктна структура: колекція документів
class DocumentCollection {
private:
    Document* documents[2];
public:
    DocumentCollection() {
        documents[0] = new TextDocument();
        documents[1] = new ImageDocument();
    }

    void accept(Visitor* visitor) {
        for (int i = 0; i < 2; ++i) {
            documents[i]->accept(visitor);
        }
    }

    ~DocumentCollection() {
        delete documents[0];
        delete documents[1];
    }
};

int main() {

    SetConsoleCP(1251);
    SetConsoleOutputCP(1251);

    // Створюємо відвідувача для обчислення вартості друку
    PrintCostVisitor* costVisitor = new PrintCostVisitor();

    // Створюємо колекцію документів
    DocumentCollection collection;

    // Додаємо операцію для всіх документів у колекції
    collection.accept(costVisitor);

    delete costVisitor;


}
