// Код к заданию
#include <fstream>

class Printable
{
public:
    virtual ~Printable() = default;

    virtual std::string printAsHTML() const = 0;
    virtual std::string printAsText() const = 0;
    virtual std::string printAsJSON() const = 0;
};

class Data : public Printable
{
public:
    enum class Format
    {
        kText,
        kHTML,
        kJSON
    };

    Data(std::string data, Format format)
        : data_(std::move(data)), format_(format) {}

    std::string printAsHTML() const override
    {
        if (format_ != Format::kHTML) {
            throw std::runtime_error("Invalid format!");
        }
        return "<html>" + data_ + "<html/>";
    }
    std::string printAsText() const override
    {
        if (format_ != Format::kText) {
            throw std::runtime_error("Invalid format!");
        }
        return data_;
    }
    std::string printAsJSON() const override
    {
        if (format_ != Format::kJSON) {
            throw std::runtime_error("Invalid format!");
        }
        return "{ \"data\": \"" + data_ + "\"}";
    }

private:
    std::string data_;
    Format format_;
};

void saveTo(std::ofstream &file, const Printable& printable, Data::Format format)
{
    switch (format)
    {
    case Data::Format::kText:
        file << printable.printAsText();
        break;
    case Data::Format::kJSON:
        file << printable.printAsJSON();
        break;
    case Data::Format::kHTML:
        file << printable.printAsHTML();
        break;
    }
}

void saveToAsHTML(std::ofstream &file, const Printable& printable) {
    saveTo(file, printable, Data::Format::kHTML);
}

void saveToAsJSON(std::ofstream &file, const Printable& printable) {
    saveTo(file, printable, Data::Format::kJSON);
}

void saveToAsText(std::ofstream &file, const Printable& printable) {
    saveTo(file, printable, Data::Format::kText);
}

/*
Задание 1
В приведённом выше коде есть нарушения некоторых принципов SOLID.

Ваша задача найти и перечислить нарушенные принципы и указать, в чём именно состоит нарушение.


В коде нарушены три принципа SOLID:

подстановки Барбары Лисков
Принцип подстановки в том, что дочерний класс должен иметь возможность заменить родительский класс, при этом не вызывая никаких ошибок.
В данном случае родительтский и дочерний класс сильно рознятся, и поэтому подстановка будет реализована с ошибками.


открытости/закрытости
Принцип заключается в том, что класс должен быть открыт для расширения и закрыт для изменений.
В данном случае появление нового типа текста приведет к изменению класса, что недопустимо.

разделения интерфейса
В данном случае все классы - наследники базового класса будут иметь в своем арсенале методы, которыми они не будут пользоваться, но обязаны иметь их реализацию.
Нужно исключить лишние методы из классов-потомков, чтобы не нарушать принцип.
*/