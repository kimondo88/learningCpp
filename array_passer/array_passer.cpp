#include <iostream>

using std::cout;
using std::endl;

void increase(int* const array, const int NUM_ELEMENTS);

void display(const int* const array, const int NUM_ELEMENTS);

int main()
{

    cout << "Creating the array of high scores.\n\n";

    const int NUM_SCORES = 3;
    int highScores[NUM_SCORES] = {5000, 3500, 2700};

    cout << "Displaying scores using array name as constant pointer.\n";

    cout << *highScores << endl;

    cout << *(highScores + 1) << endl;

    cout << *(highScores + 2 ) << "\n\n";

    cout << "Increasing scores by passing the array as constant pointer.\n\n";

    increase(highScores, NUM_SCORES);

    cout << "Displaying scores by passing array as constant pointer to a constant. \n";

    display(highScores, NUM_SCORES);

    return 0;

}

void increase(int* const array, const int NUM_ELEMENTS)
{

    for(int i = 0; i < NUM_ELEMENTS; ++i)
    {

        array[i] += 500;

    }

}

void display(const int* const array, const int NUM_ELEMENTS)
{

    for(int i = 0; i < NUM_ELEMENTS; ++i)
    {

        cout << array[i] << endl;

    }

}