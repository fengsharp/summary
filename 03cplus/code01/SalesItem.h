#ifndef SALES_ITEM_H_
#define SALES_ITEM_H_

#include <iostream>
#include <string>

class SalesItem
{
    friend std::istream &operator>>(std::istream &, SalesItem &);
    friend std::ostream &operator<<(std::ostream &, const SalesItem &);
    friend bool operator<(const SalesItem &, const SalesItem &);
    friend bool operator==(const SalesItem &, const SalesItem &);

public:
    SalesItem() = default;
    SalesItem(const std::string &book)
        : bookNo(book)
    {
    }
    SalesItem(std::istream &is)
    {
        is >> *this;
    }
public:
    SalesItem &operator+=(const SalesItem&);
    std::string isbn() const {
        return bookNo;
    }
    double avg_price() const;
private:
    std::string bookNo;
    unsigned int unitsSold = 0;
    double revenue = 0.0;
};

inline bool compareIsbn(const SalesItem &lhs, const SalesItem &rhs)
{
    return lhs.isbn() == rhs.isbn();
}

SalesItem operator+(const SalesItem&, const SalesItem&);
inline bool operator==(const SalesItem &lhs, const SalesItem &rhs)
{
    return lhs.unitsSold == rhs.unitsSold 
        && lhs.revenue == rhs.revenue
        && lhs.isbn() == rhs.isbn();
}

inline bool operator!=(const SalesItem &lhs, const SalesItem &rhs)
{
    return !(lhs == rhs);
}

SalesItem& SalesItem::operator+=(const SalesItem& rhs)
{
    this->unitsSold += rhs.unitsSold;
    this->revenue += rhs.revenue;
    return *this;
}

SalesItem operator+(const SalesItem& lhs, const SalesItem& rhs)
{
    SalesItem ret(lhs);
    ret += rhs;
    return ret;
}

std::istream& operator>>(std::istream& in, SalesItem& s)
{
    double price;
    in >> s.bookNo >> s.unitsSold >> price;
    if (in)
    {
        s.revenue = s.unitsSold * price;
    }
    else
    {
        s = SalesItem();
    }
    return in;
}

std::ostream& operator<<(std::ostream& out, const SalesItem& s)
{
    out << s.isbn() << " " << s.unitsSold << " "
        << s.revenue << " " << s.avg_price();
    return out;
}

double SalesItem::avg_price() const
{
    if (this->unitsSold)
    {
        return this->revenue / this->unitsSold;
    }
    else
    {
        return 0.0;
    }
}

#endif