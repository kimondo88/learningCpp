#include <iostream>

using std::cout;

void func();

int main()

{
int var = 5;

cout << "in main() var is: " << var << "\n\n";

func();

cout << "Back in main() var is: " << var << "\n\n";

    {

    cout << "in main() in a new scope var is: " << var << "\n\n";

    cout << "Creating the new var in new scope.\n";

    int var = 10;

    cout << "in main() in a new scope var is: " << var << "\n\n";

    }

cout << " at the end of main() var created in new scope no longer exists.\n";

cout << "at end of main() var is: " << var << "\n\n";

return 0;

}

void func()

{

int var = -5;

cout << "In func() var is: " << var << "\n";

}