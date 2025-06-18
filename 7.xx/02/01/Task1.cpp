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