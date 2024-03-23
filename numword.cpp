#include "numword.h"

namespace numword
{

    lnum word::operator=(const lnum &num)
    {
        setnum(num);
        return getnum();
    }

    const string &word::words()
    {
        return words(_num);
    }

    const string &word::words(const lnum &num)
    {
        lnum n{num};
        clearbuf();

        if (n > maxnum)
        {
            appendbuf(errnum);
            return *_buf;
        }

        if (n == 0)
        {
            appendbuf(_singles[n]);
            return *_buf;
        }

        // powers of 1000
        if (n >= thousand)
        {
            for (auto i = five_i; i > zero_i; --i)
            {
                lnum power{pow_i(thousand, i)};
                lnum _n{(n - (n % power)) / power};
                if (_n)
                {
                    int index = i;
                    word _nw{_n};
                    appendbuf(_nw.words());
                    appendbuf(_powers[index]);
                    n -= _n * power;
                }
            }
        }

        // hundreds
        if (n >= hundred && n < thousand)
        {
            lnum _n{(n - (n % hundred)) / hundred};
            word _nw{_n};
            appendbuf(_nw.words());
            appendbuf(_hundred);
            n -= _n * hundred;
        }

        // tens
        if (n >= twenty && n < hundred)
        {
            lnum _n{(n - (n % ten)) / ten};
            appendbuf(_teens[_n]);
            n -= _n * ten;
            _hyphen_flag = true;
        }

        // teens
        if (n >= ten && n < twenty)
        {
            appendbuf(_teens[n - ten]);
            n = zero;
        }

        // singles
        if (n > zero && n < ten)
        {
            appendbuf(_singles[n]);
        }

        return *_buf;
    }

    void word::clearbuf()
    {
        *_buf = string{};
    }

    size_t word::bufsize()
    {
        return _buf->size();
    }

    void word::appendbuf(const string &s)
    {
        appendspace();
        _buf->append(s);
    }

    void word::appendbuf(const string_view &s)
    {
        appendspace();
        _buf->append(s.data());
    }

    void word::appendbuf(const char c)
    {
        _buf->append(1, c);
    }

    void word::appendspace()
    {
        if (bufsize())
        {
            appendbuf(_hyphen_flag ? _hyphen : _space);
            _hyphen_flag = false;
        }
    }

    lnum word::pow_i(const lnum n, lnum p)
    {
        lnum out{n};
        while (--p)
            out *= n;
        return out;
    }
}
