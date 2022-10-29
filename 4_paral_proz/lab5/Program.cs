using System;
using System.Collections.Generic;
using System.Diagnostics;
using System.IO;
using System.Threading;
/*
namespace lab5
{
    class Program
    {
        public static int CountVal; // Количество элементов, которые можно записать в буфер
        public static int CountRecorded = 0; // Количество элементов, которые записаны в буфер
        public static int CountReader; // Количество читателей
        public static int CountWriter; // Количество писателей
        public static bool f_filledBuf = false; // Флаг, который отслеживает заполнение буфера
        public static int bufferSize; // Размер буфера
        public static List<int> BufferList; // Буфер
        public static int W_bufIndex; // Индекс записанного в буфер элемента
        public static int R_bufIndex; // Индекс считанного из буфера элемента
        public static int CountReaderRead = 0; // Количество элементов, которые можно считать
        public static void Writers()
        {
            while (CountRecorded < CountVal)
            {
                lock ("")
                {
                    if (!f_filledBuf)
                    {
                        BufferList.Add(CountRecorded++);
                        W_bufIndex++;
                        if (W_bufIndex == bufferSize) W_bufIndex = 0;
                        f_filledBuf = (W_bufIndex == R_bufIndex);
                    }
                }
            }
        }
        public static void Readers()
        {
            while (CountReaderRead < CountVal)
            {
                lock ("")
                {
                    if (R_bufIndex != W_bufIndex || f_filledBuf)
                    {
                        ++CountReaderRead;
                        R_bufIndex++;
                        if (R_bufIndex == bufferSize) R_bufIndex = 0;
                        f_filledBuf = false;
                    }
                }
            }
        }
        static void Main(string[] args)
        {
            CountReader = 8;
            CountWriter = 8;
            bufferSize = 10000;
            CountVal   = 10000;
            BufferList = new List<int>(new int[bufferSize]);
            List<Thread> ThreadForRead = new List<Thread>();
            List<Thread> ThreadForWrite = new List<Thread>();
            Stopwatch sw = new Stopwatch();
            sw.Start();
            for (int i = 0; i < CountWriter; i++)
            {
                Thread writer = new Thread(new ThreadStart(Writers));
                writer.Start();
                ThreadForWrite.Add(writer);
            }
            for (int i = 0; i < CountReader; i++)
            {
                Thread reader = new Thread(new ThreadStart(Readers));
                reader.Start();
                ThreadForRead.Add(reader);
            }
            foreach (Thread thread in ThreadForWrite) thread.Join();
            foreach (Thread thread in ThreadForRead) thread.Join();
            sw.Stop();
            TimeSpan ts = sw.Elapsed;
            Console.WriteLine("Время - " + ts.TotalMilliseconds);
        }
    }
}
*/

namespace lab5
{
    class Program
    {
        public static int CountVal; // Количество элементов, которые можно записать в буфер
        public static int CountRecorded = 0; // Количество элементов, которые записаны в буфер
        public static int CountReader; // Количество читателей
        public static int CountWriter; // Количество писателей
        public static bool f_filledBuf = false; // Флаг, который отслеживает заполнение буфера
        public static List<int> BufferList; // Буфер
        public static int W_bufIndex; // Индекс записанного в буфер элемента
        public static int R_bufIndex; // Индекс считанного из буфера элемента
        public static int bufferSize; // Размер буфера
        public static int CountReaderRead = 0; // Количество элементов, которые можно считать
        public static int firstThread = 0;
        public static int secondThread = 0;
        public static void Writers()
        {
        while (CountRecorded < CountVal)
        {
            lock ("")
            {
                if (!f_filledBuf)
                {
                    BufferList.Add(CountRecorded++);
                    W_bufIndex++;
                    if (W_bufIndex == bufferSize) W_bufIndex = 0;
                    f_filledBuf = W_bufIndex == R_bufIndex;
                }
                }
            }
        }
        public static void Readers(object id)
        {
            while (CountReaderRead < CountVal)
            {
                lock ("")
                {
                    if (R_bufIndex != W_bufIndex || f_filledBuf)
                    {
                        if ((int)id == 0)
                        {
                            firstThread++;
                        } else { secondThread++; }
                        ++CountReaderRead;
                        R_bufIndex++;
                        if (R_bufIndex == bufferSize) R_bufIndex = 0;
                        f_filledBuf = false;
                    }
                }
            }
        }
        static void Main(string[] args)
        {
            CountVal = 1000000;
            bufferSize = 10000;
            CountReader = 2;
            CountWriter = 2;
            BufferList = new List<int>(new int[bufferSize]);
            List<Thread> ThreadForRead = new List<Thread>();
            List<Thread> ThreadForWrite = new List<Thread>()
            {
                new Thread(new ParameterizedThreadStart(Readers)),
                new Thread(new ParameterizedThreadStart(Readers))
            };
            Stopwatch sw = new Stopwatch();
            sw.Start();
            for (int i = 0; i < CountReader; i++)
            {
                Thread writer = new Thread(new ThreadStart(Writers));
                writer.Start();
                ThreadForRead.Add(writer);
            }
            ThreadForWrite[0].Priority = ThreadPriority.Highest;
            ThreadForWrite[1].Priority = ThreadPriority.Lowest;
            ThreadForWrite[0].Start(0);
            ThreadForWrite[1].Start(1);
            foreach (Thread thread in ThreadForWrite) thread.Join();
            foreach (Thread thread in ThreadForRead) thread.Join();
            sw.Stop();
            TimeSpan ts = sw.Elapsed;
            Console.WriteLine("Считал первый поток - " + firstThread);
            Console.WriteLine("Считал второй поток - " + secondThread);
            Console.WriteLine("Время выполнения - " + ts.TotalMilliseconds);
        }
    }
}