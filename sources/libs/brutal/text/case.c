#include <brutal/log/assert.h>
#include <brutal/parse/scan.h>
#include <brutal/text/case.h>
#include <ctype.h>

Buffer case_to_default(Str str, Alloc *alloc)
{
    Buffer buf;
    buffer_init(&buf, str.len, alloc);
    buffer_write(&buf, str.buffer, str.len);
    return buf;
}

Buffer case_to_camel(Str str, Alloc *alloc)
{
    Buffer buf = case_to_pascal(str, alloc);

    if (buf.used == 0)
    {
        return buf;
    }

    buf.data[0] = tolower(buf.data[0]);

    return buf;
}

Buffer case_to_capital(Str str, Alloc *alloc)
{
    Buffer buf = case_to_no(str, alloc);

    for (size_t i = 0; i < buf.used; i++)
    {
        if (i == 0 || buf.data[i - 1] == ' ')
        {
            buf.data[i] = toupper(buf.data[i]);
        }
    }

    return buf;
}

Buffer case_to_constant(Str str, Alloc *alloc)
{
    Buffer buf = case_to_no(str, alloc);

    for (size_t i = 0; i < buf.used; i++)
    {
        if (buf.data[i] == ' ')
        {
            buf.data[i] = '_';
        }
        else
        {
            buf.data[i] = toupper(buf.data[i]);
        }
    }

    return buf;
}

Buffer case_to_dot(Str str, Alloc *alloc)
{
    Buffer buf = case_to_no(str, alloc);

    for (size_t i = 0; i < buf.used; i++)
    {
        if (buf.data[i] == ' ')
        {
            buf.data[i] = '.';
        }
    }

    return buf;
}

Buffer case_to_header(Str str, Alloc *alloc)
{
    Buffer buf = case_to_no(str, alloc);

    for (size_t i = 0; i < buf.used; i++)
    {
        if (buf.data[i] == ' ')
        {
            buf.data[i] = '-';
        }
        else if (i == 0 || buf.data[i - 1] == '-')
        {
            buf.data[i] = toupper(buf.data[i]);
        }
    }

    return buf;
}

static int is_sep(int c)
{
    return isblank(c) || c == '.' || c == '_' || c == '/' || c == '-';
}

Buffer case_to_no(Str str, Alloc *alloc)
{
    Buffer buf;
    buffer_init(&buf, str.len, alloc);

    Scan scan;
    scan_init(&scan, str);

    scan_eat(&scan, isblank);

    while (!scan_ended(&scan))
    {
        char c = scan_curr(&scan);

        if (is_sep(c))
        {
            scan_eat(&scan, is_sep);

            if (!scan_ended(&scan))
            {
                buffer_putc(&buf, ' ');
            }
        }
        else
        {
            if (islower(scan_peek(&scan, -1)) && isupper(scan_curr(&scan)))
            {
                buffer_putc(&buf, ' ');
            }

            buffer_putc(&buf, tolower(scan_curr(&scan)));

            scan_next(&scan);
        }
    }

    return buf;
}

Buffer case_to_param(Str str, Alloc *alloc)
{
    Buffer buf = case_to_no(str, alloc);

    for (size_t i = 0; i < buf.used; i++)
    {
        if (buf.data[i] == ' ')
        {
            buf.data[i] = '-';
        }
    }

    return buf;
}

Buffer case_to_pascal(Str str, Alloc *alloc)
{
    Buffer nocase = case_to_no(str, alloc);

    if (nocase.used == 0)
    {
        return nocase;
    }

    Buffer buf;
    buffer_init(&buf, nocase.used, alloc);

    for (size_t i = 0; i < nocase.used; i++)
    {
        if (i == 0 || nocase.data[i - 1] == ' ')
        {
            buffer_putc(&buf, toupper(nocase.data[i]));
        }
        else if (nocase.data[i] != ' ')
        {
            buffer_putc(&buf, nocase.data[i]);
        }
    }

    buffer_deinit(&nocase);
    return buf;
}

Buffer case_to_path(Str str, Alloc *alloc)
{
    Buffer buf = case_to_no(str, alloc);

    for (size_t i = 0; i < buf.used; i++)
    {
        if (buf.data[i] == ' ')
        {
            buf.data[i] = '/';
        }
    }

    return buf;
}

Buffer case_to_sentence(Str str, Alloc *alloc)
{
    Buffer buf = case_to_no(str, alloc);

    if (buf.used == 0)
    {
        return buf;
    }

    buf.data[0] = toupper(buf.data[0]);

    return buf;
}

Buffer case_to_snake(Str str, Alloc *alloc)
{
    Buffer buf = case_to_no(str, alloc);

    for (size_t i = 0; i < buf.used; i++)
    {
        if (buf.data[i] == ' ')
        {
            buf.data[i] = '_';
        }
    }

    return buf;
}

Buffer case_to_title(Str str, Alloc *alloc)
{
    return case_to_capital(str, alloc);
}

Buffer case_to_swap(Str str, Alloc *alloc)
{
    Buffer buf;
    buffer_init(&buf, str.len, alloc);

    for (size_t i = 0; i < str.len; i++)
    {
        char c = str.buffer[i];

        if (isupper(c))
        {
            buffer_putc(&buf, tolower(c));
        }
        else
        {
            buffer_putc(&buf, toupper(c));
        }
    }

    return buf;
}

Buffer case_to_lower(Str str, Alloc *alloc)
{
    Buffer buf;
    buffer_init(&buf, str.len, alloc);

    for (size_t i = 0; i < str.len; i++)
    {
        char c = str.buffer[i];
        buffer_putc(&buf, tolower(c));
    }

    return buf;
}

Buffer case_to_lower_first(Str str, Alloc *alloc)
{
    Buffer buf;
    buffer_init(&buf, str.len, alloc);

    if (str.len == 0)
    {
        return buf;
    }

    buffer_write(&buf, str.buffer, str.len);
    buf.data[0] = tolower(buf.data[0]);

    return buf;
}

Buffer case_to_upper(Str str, Alloc *alloc)
{
    Buffer buf;
    buffer_init(&buf, str.len, alloc);

    for (size_t i = 0; i < str.len; i++)
    {
        char c = str.buffer[i];
        buffer_putc(&buf, toupper(c));
    }

    return buf;
}

Buffer case_to_upper_first(Str str, Alloc *alloc)
{
    Buffer buf;
    buffer_init(&buf, str.len, alloc);

    if (str.len == 0)
    {
        return buf;
    }

    buffer_write(&buf, str.buffer, str.len);
    buf.data[0] = toupper(buf.data[0]);

    return buf;
}

Buffer case_to_sponge(Str str, Alloc *alloc)
{
    Buffer buf;
    buffer_init(&buf, str.len, alloc);

    for (size_t i = 0; i < str.len; i++)
    {
        char c = str.buffer[i];
        buffer_putc(&buf, i % 2 ? tolower(c) : toupper(c));
    }

    return buf;
}

Buffer case_change(Case c, Str str, Alloc *alloc)
{
    switch (c)
    {
    case CASE_DEFAULT:
        return case_to_default(str, alloc);

    case CASE_CAMEL:
        return case_to_camel(str, alloc);

    case CASE_CAPITAL:
        return case_to_capital(str, alloc);

    case CASE_CONSTANT:
        return case_to_constant(str, alloc);

    case CASE_DOT:
        return case_to_dot(str, alloc);

    case CASE_HEADER:
        return case_to_header(str, alloc);

    case CASE_NO:
        return case_to_no(str, alloc);

    case CASE_PARAM:
        return case_to_param(str, alloc);

    case CASE_PASCAL:
        return case_to_pascal(str, alloc);

    case CASE_PATH:
        return case_to_path(str, alloc);

    case CASE_SENTENCE:
        return case_to_sentence(str, alloc);

    case CASE_SNAKE:
        return case_to_snake(str, alloc);

    case CASE_TITLE:
        return case_to_title(str, alloc);

    case CASE_SWAP:
        return case_to_swap(str, alloc);

    case CASE_LOWER:
        return case_to_lower(str, alloc);

    case CASE_LOWER_FIRST:
        return case_to_lower_first(str, alloc);

    case CASE_UPPER:
        return case_to_upper(str, alloc);

    case CASE_UPPER_FIRST:
        return case_to_upper_first(str, alloc);

    case CASE_SPONGE:
        return case_to_sponge(str, alloc);

    default:
        assert_unreachable();
    }
}
