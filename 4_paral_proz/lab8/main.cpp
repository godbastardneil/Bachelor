#include <fcntl.h>

#include <string>
#include <sys/stat.h>
#include <unistd.h>
#include <iostream>

using namespace std;

int fwrite(const string& fname, const string& str)
{
    int fd;

    (void)umask(0);

    if((fd = open(fname.c_str(), O_WRONLY | O_CREAT, 0666)) < 0)
    {
        cout << ("write - Can\'t open file\n");
        return -1;
    }

    int size = write(fd, str.c_str(), str.size());

    if(size != str.size())
    {
        cout << ("write - Can\'t write all string\n");
        return -1;
    }

    if(close(fd) < 0)
    {
        cout << ("write - Can\'t close file\n");
        return -1;
    }
    return 0;
}
int fread(const string& fname, string& str)
{
    int fd;

    if((fd = open(fname.c_str(), O_RDONLY)) < 0)
    {
        cout << ("read - Can\'t open file\n");
        return -1;
    }

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
        cout << ("read - Can\'t write all string\n");
        return -1;
    }

    if(close(fd) < 0)
    {
        cout << ("read - Can\'t close file\n");
        return -1;
    }

    return 0;
}


int main()
{
    string fname = "myfile.txt";
    string str = "Hello, gays!!";
    string out;

    if (fwrite(fname, str) == -1) { return -1; }
    if (fread(fname, out) == -1) { return -1; }

    cout << out << endl;

    return 0;
}
