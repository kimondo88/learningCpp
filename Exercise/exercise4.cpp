#include <iostream>
#include <string>

using std::cout;
using std::string;

string* varSize(string* const prompt);

string askPrompt(string prompt);

int main()
{

    string prompt = askPrompt("The string");
    string* pSize = varSize(&prompt);
    string* pRepeat = pSize;
    cout << (*pRepeat).size();
    return 0;

}

string* varSize(string* const prompt)
{

    return prompt;

}

string askPrompt(string prompt)
{

    return prompt;

}