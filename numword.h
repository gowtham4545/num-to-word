#ifndef _NUMWORD_H
#define _NUMWORD_H

#include <string>
#include <string_view>
#include <memory>

namespace numword
{
    using std::string;
    using std::string_view;
    using lnum = uint64_t;
    using buf_str = std::unique_ptr<string>;
    constexpr const char *_version{"2024.03.22"};

    constexpr lnum maxnum = 999'999'999'999'999'999;

    constexpr int zero_i{0};
    constexpr int five_i{5};
    constexpr lnum zero{0};
    constexpr lnum ten{10};
    constexpr lnum twenty{20};
    constexpr lnum hundred{100};
    constexpr lnum thousand{1000};

    constexpr string_view errnum{"error"};

    constexpr string_view _singles [] {
        "zero", "one", "two", "three", "four", "five", "six", "seven", "eight", "nine"
    };

    constexpr string_view _teens [] {
        "ten", "eleven", "twleve", "thirteen", "fourteen", "fifteen", "sixteen", "seventeen", "eighteen", "nineteen"
    };

    constexpr string_view _tens [] {
        errnum, errnum, "twenty", "thirty", "forty", "fifty", "sixty", "seventy", "eighty", "ninety"
    };

    constexpr string_view _hundred = "hundred";

    constexpr string_view _powers [] {
        errnum, "thousand", "million", "billion", "trillion", "quadrillion"
    };

    constexpr char _hyphen{'-'};
    constexpr char _space{' '};

    class word {
        buf_str _buf {std::make_unique<string>(string{})};
        lnum _num{};
        bool _hyphen_flag{false};

        void clearbuf();
        size_t bufsize();
        void appendbuf(const string& s);
        void appendbuf(const string_view& s);
        void appendbuf(const char c);
        void appendspace();
        lnum pow_i(const lnum n,lnum p);
    
    public:
        word(const lnum& num=0) : _num(num){}
        word(const word& num) : _num(num._num){}
        const char* version() { return _version; }
        void setnum(const lnum& num) { _num=num; }
        lnum getnum() const { return _num; }
        lnum operator = (const lnum& num);
        const string& words();
        const string& words(const lnum& num);
        const string & operator () (const lnum& num) { return words(num); }
    };
}

#endif