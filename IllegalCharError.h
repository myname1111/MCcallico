#ifndef ILLEGALCHARERROR_H
#define ILLEGALCHARERROR_H

using namespace std;


class IllegalCharError {
    public:
        string error_details;
        IllegalCharError(string details);
        IllegalCharError(char details);
        IllegalCharError();
        string as_string();
    protected:

    private:
};

#endif // ILLEGALCHARERROR_H
