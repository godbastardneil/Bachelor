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
    int fd;
    if((fd = open(fname.c_str(), O_WRONLY | O_CREAT, 0666)) < 0)
    {
        cout << "Can't create FIFO" << endl;
        return -1;
    }

    string str = "hi from lab8_4_writer";
    auto size = write(fd, str.c_str(), str.size());

    if(size != str.size())
    {
        cout << "Can't write all string to FIFO" << endl;
        return -1;
    }

    close(fd);

    return 0;
}
