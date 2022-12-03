#include <iostream>
#include "./Array.cpp"

const int ch_MAX = 26;
std::string RandomString(int ch)
{
    char alpha[ch_MAX] = { 'a', 'b', 'c', 'd', 'e', 'f', 'g',
                          'h', 'i', 'j', 'k', 'l', 'm', 'n',
                          'o', 'p', 'q', 'r', 's', 't', 'u',
                          'v', 'w', 'x', 'y', 'z' };
    std::string result = "";
    for (int i = 0; i < ch; i++)
        result = result + alpha[rand() % ch_MAX];

    return result;
}

int main(int argc, char* argv[])
{
    Array<std::string> a;
    for (int i = 0; i < 10; ++i) 
    {
        a.Insert(RandomString(10+i));
        std::cout << a[i] << std::endl;
    }


    //std::cout << '\n' << a.Size() << '\n' << '\n';
   
    //a.Insert(9, 2);
    //a.Insert(10, 2);
    a.Remove(3);
    //a.Remove(0);
    std::cout << "----------------\n";
    for (auto it = a.Iterator(); it.HasNext(); it.Next())
        std::cout << it.Get() << std::endl;
    std::cout << "----------------";
    //std::cout << a.Size() << std::endl << a[0] << a.Insert(a.Size() - 1, 2) << a.Size() << std::endl << std::endl;
    //for (int i = 0; i < a.Size(); ++i)
    //    a[i] *= 2;
    ////std::cout << a.Size() << std::endl << a[0] << a.Insert(a.Size() - 1, 2) << a.Size();
    //for (auto it = a.Iterator(); it.HasNext(); it.Next())
    //    std::cout << it.Get() << std::endl;
    //std::cout << '\n';

    //for (auto it = a.ReverseIterator(); it.HasNext(); it.Next())
    //    std::cout << it.Get() << std::endl;
}
