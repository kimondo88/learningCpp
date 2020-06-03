#include <iostream>
#include <string>

using std::cout;
using std::string;
using std::cin;

string askText(string prompt);

int askNumber(string prompt);

void tellStory(string name, string noun, int number, string bodyPart, string verb);

int main()
{

cout << "Welcome to mad lib. \n\n";

cout << "Answer the following questions to help create story.\n";

string name = askText("Please enter a name: ");

string noun = askText("Please enter a plural noun: ");

string bodyPart = askText("Please enter a body part: ");

string verb = askText("Please enter a verb: ");

int number = askNumber("Please enter a number: ");

tellStory(name, noun, number, bodyPart, verb);

return 0; 

}

string askText(string prompt)
{

string text;

cout << prompt;

getline(cin, text);

return text;

}

int askNumber(string prompt)
{

int num;

cout << prompt;

cin >> num;

return num;


}

void tellStory(string name, string noun, int number, string bodyPart, string verb)
{

cout << "\nHere is your story.\n";

cout << "The famous explorer " << name << " had nearly given up life-long quest to find\n";

cout << "The Lost city of " << noun << " when one day, the ";

cout << noun << " found the explorer.\n";

cout << "Surrounded by " << number << " " << noun ;

cout << ", a tear came to " << name << "s ";

cout << bodyPart << ".\n";

cout << "After all this time, the quest was finally over.\n";

cout << "And then, the " << noun <<"\n";

cout << "promptly devoured " << name << ".";

cout << "\nThe Moral of the story? Be careful what you " << verb << "for.";

}