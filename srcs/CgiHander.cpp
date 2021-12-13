#ifndef _CGIHENDLER_H_
#define _CGIHENDLER_H_

class CgiHandler
{
private:
    static const char   *env;
    static const char   *argv;
public:
    CgiHandler(const char *file);
    ~CgiHandler();
};

#endif