/*
Задание 1
В программу рендеринга HTML из лекции (раздел про паттерн «Декоратор») добавьте новые классы для декорирования текста.

class Paragraph: ...

auto text_block = new Paragraph(new Text());
text_block->render("Hello world");

>>> <p>Hello world</p>
class Reversed: ...

auto text_block = new Reversed(new Text());
text_block->render("Hello world");

>>> dlrow olleH
class Link: ...

auto text_block = new Link(new Text());
text_block->render("netology.ru", "Hello world");

>>> <a href=netology.ru>Hello world</a>
Обратите внимание

Сигнатура метода Link::render() не совпадает с сигнатурой оригинального метода.
Для разворота строки используйте функцию std::reverse cppreference.
*/

#include <string>
#include <iostream>
#include <algorithm>

class Text 
{
public:
    virtual void render(const std::string& data) const 
    {
        std::cout << data;
    }
};


class DecoratedText : public Text 
{
public:
    explicit DecoratedText(Text* text) : text_(text) {}
    Text* text_;
};

class ItalicText : public DecoratedText 
{
public:
    explicit ItalicText(Text* text) : DecoratedText(text) {}
    void render(const std::string& data)  const 
    {
        std::cout << "<i>";
        text_->render(data);
        std::cout << "</i>";
    }
};

class BoldText : public DecoratedText 
{
public:
    explicit BoldText(Text* text) : DecoratedText(text) {}
    void render(const std::string& data) const 
    {
        std::cout << "<b>";
        text_->render(data);
        std::cout << "</b>";
    }
};

class Paragraph: public DecoratedText
{
public:
    explicit Paragraph(Text* text) : DecoratedText(text) {}
    void render(const std::string& data) const
    {
        std::cout << "<p>";
        text_->render(data);
        std::cout << "</p>";
    }
};

class Reversed : public DecoratedText
{
public:
    explicit Reversed(Text* text) : DecoratedText(text) {}
    void render(const std::string& data) const
    {
        std::string copy(data);
        std::reverse(copy.begin(), copy.end());
        text_->render(copy);
    }
};

class Link : public DecoratedText
{
public:
    explicit Link(Text* text) : DecoratedText(text) {}
    void render(const std::string& link, const std::string& data) const
    {
        std::cout << "<a href = " << link << ">";
        text_->render(data);
        std::cout << "</a>";
    }
};

int main() 
{
    auto text_block = new Link(new Text());
    text_block->render("netology.ru", "Hello world");
}