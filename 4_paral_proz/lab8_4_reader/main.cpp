#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>

#include <string>
#include <iostream>

using namespace std;

int main()
{
    const string fname = "../aaa.fifo";

    umask(0);

    int fd = open(fname.c_str(), O_RDONLY);
    if(fd == -1)
    {
        cout << "Can't open FIFO for reading" << endl;
        return -1;
    }

    string str;
    char tmp[1];
    int size;

    size = read(fd, tmp, 1);
    while (size > 0)
    {
        str += tmp[0];
        size = read(fd, tmp, 1);
    }

    if(size == -1)
    {
        cout << "Can't read string" << endl;
        return -1;
    }

    cout << str << endl;

    close(fd);

    return 0;
}
