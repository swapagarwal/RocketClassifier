#ifndef PARSER_H
#define PARSER_H


class Parser
{
    public:
        Parser(string);
        string Getinput_str() { return input_str; }
    void Setinput_str(string val) {
        input_str = val;
    }
        vector<string> Getparsed_out() { return parsed_out; }
    protected:
    private:
        string input_str;
        vector<string> parsed_out;
};

#endif // PARSER_H
