#include <iostream>
#include <thread>


void hello()
{
    std::cout << " Hello " << std::endl;
}

void world()
{
    std::cout << " World. " << std::endl;
}

int main()
{
    // TODO: call with two new threads
    hello();
    world();

    // TODO: join the threads with the main thread


    return 0;
}
