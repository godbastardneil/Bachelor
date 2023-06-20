using System;
using System.Collections.Generic;
using System.Threading;

namespace lab4
{
    class Program
    {
        static int t = 10; // количество повторов

        static int n = 100000; // количество сообщений
        static int size = 4; // длина сообщений
        static int m = 5; // количество потоков
        static int i = 0;

        static string buffer = "";
        static List<string> myMessages = new List<string>(m);

        static bool bEmpty = true, finish = false;
        static int usingResource = 0;
        static AutoResetEvent evEmpty = new AutoResetEvent(true), evFull = new AutoResetEvent(false);
        static SemaphoreSlim semReader = new SemaphoreSlim(1), semWriter = new SemaphoreSlim(1);

        delegate void writerWork(object state);
        delegate void readerWork(object state);


        static List<string> doWorks(writerWork writerlambda, readerWork readerlambda)
        {
            Thread [] writers = new Thread[m];
            for (int j=0; j<m; ++j)
            {
                writers[j] = new Thread((object state) => { writerlambda(state); });
                writers[j].Start( new string((char)('A'+j), size) );
            }

            Thread [] readers = new Thread[m];
            for (int j=0; j<m; ++j)
            {
                readers[j] = new Thread((object state) => { readerlambda(state); });
                readers[j].Start();
            }

            foreach(Thread wt in writers) { wt.Join(); }
            finish = true;
            evFull.Set();
            foreach(Thread rt in readers) { rt.Join(); }
            return myMessages;
        }

        static List<string> WithOutSync()
        {
            writerWork writerlambda = ((state) => {
                string tmp = (string)state;
                while (i < n)
                {
                    if (bEmpty)
                    {
                        buffer = tmp + (++i);
                        bEmpty = false;
                    }
                }
            });
            readerWork readerlambda = ((state) => {
                while (!finish)
                {
                    if (!bEmpty)
                    {
                        myMessages.Add(buffer);
                        bEmpty = true; 
                    }
                }
            });

            return doWorks(writerlambda, readerlambda);
        }
        static List<string> WithLocks()
        {
            writerWork writerlambda = ((state) => {
                string tmp = (string)state;
                while (i < n)
                {
                    lock("write")
                    {
                        if (bEmpty)
                        {
                            buffer = tmp + (++i);
                            bEmpty = false;
                        }
                    }
                }
            });
            readerWork readerlambda = ((state) => {
                while (!finish)   
                {
                    if (!bEmpty)
                    {
                        lock ("read")
                        {
                            if (!bEmpty)
                            {
                                myMessages.Add(buffer);
                                bEmpty = true;
                            }
                        }
                    }
                }
            });

            return doWorks(writerlambda, readerlambda);
        }

        static List<string> WithEvents()
        {
            writerWork writerlambda = ((state) => {
                string tmp = (string)state;
                while(i < n)
                {
                    evEmpty.WaitOne();
                        buffer = tmp + (++i);
                    evFull.Set();
                }
            });
            readerWork readerlambda = ((state) => {
                while(true)
                {
                    evFull.WaitOne();
                        if(finish) { break; }
                        myMessages.Add(buffer);
                    evEmpty.Set();
                }
                evFull.Set();
            });
            
            return doWorks(writerlambda, readerlambda);
        }
        static List<string> WithSemaphores()
        {
            writerWork writerlambda = ((state) => {
                string tmp = (string)state;
                while(i < n)
                {
                    if(bEmpty)
                    {
                        semWriter.Wait();
                        if(bEmpty)
                        {  
                            buffer = tmp + (++i);
                            bEmpty = false;
                        }
                        semWriter.Release();
                    }
                }
            });
            readerWork readerlambda = ((state) => {
                while(!finish)
                {
                    if(!bEmpty)
                    {
                        semReader.Wait();
                        if(!bEmpty)
                        {
                            bEmpty = true;
                            myMessages.Add(buffer);
                        }
                        semReader.Release();
                    }
                }
            });
            
            return doWorks(writerlambda, readerlambda);
        }
        static List<string> WithInterlockeds()
        {
            writerWork writerlambda = ((state) => {
                string tmp = (string)state;
                while(i < n)
                {
                    if (bEmpty)
                    {
                        if (Interlocked.Exchange(ref usingResource, 1) == 0)
                        {
                            if(bEmpty)
                            {  
                                bEmpty = false;
                                buffer = tmp + (++i);
                            }
                            Interlocked.Exchange(ref usingResource, 0);
                        }
                    }
                }
            });
            readerWork readerlambda = ((state) => {
                while (!finish)
                {
                    if (!bEmpty)
                    {
                        if (Interlocked.Exchange(ref usingResource, 1) == 0)
                        {
                            if (!bEmpty)
                            {
                                myMessages.Add(buffer);
                                bEmpty = true;
                            }
                            Interlocked.Exchange(ref usingResource, 0);
                        }
                    }
                }
            });
            
            return doWorks(writerlambda, readerlambda);
        }

        static void Main(string[] args)
        {
            DateTime t1, t2;
            
            t1 = DateTime.Now;
            for (int j=0; j<t; ++j)
            {
                //Console.WriteLine("Return - " + String.Join(',', WithOutSync())); // делаются не впопад, случайное количество, могут записаться одно и тоже сообщение несколько раз
                //WithOutSync();
                // примеры: 1) AAAA1,AAAA1,AAAA2,AAAA2,AAAA3,DDDD6,DDDD6,DDDD6,DDDD6; 2) DDDD1,DDDD1,DDDD1,DDDD2,DDDD3,DDDD46,DDDD46,DDDD46,DDDD46 3) DDDD4,DDDD4,DDDD4,DDDD4,DDDD4
                
                //Console.WriteLine("Return - " + String.Join(',', WithLocks())); // каждый раз новое сообщение и их индексы в порядке возростания, но сообщения одного писателя могут записаться несколько раз
                //WithLocks();
                // примеры: 1) AAA1,AAAA2,AAAA3,AAAA4,DDDD5; 2) AAAA1,AAAA2,BBBB3,BBBB4,DDDD5,CCCC6,AAAA7; 3) AAAA1,BBBB2,CCCC3,CCCC4,DDDD5
                
                //Console.WriteLine("Return - " + String.Join(',', WithEvents())); // каждый раз новое сообщение и их индексы в порядке возростания, но сообщения одного писателя могут записаться несколько раз
                //WithEvents();
                // примеры: 1) AAAA1,BBBB2,CCCC3,AAAA4,DDDD5,BBBB6,CCCC7; 2) CCCC1,BBBB2,AAAA3,DDDD4,CCCC5,BBBB6,AAAA7; 3) AAAA1,CCCC2,BBBB3,AAAA4,DDDD5,CCCC6

                //Console.WriteLine("Return - " + String.Join(',', WithSemaphores())); // зависает пустую строку в списов
                WithSemaphores();
                // примеры: 1) ,AAAA1,CCCC3,AAAA4,BBBB5,CCCC6; 2) ,AAAA1,AAAA3,AAAA4,AAAA4,BBBB6; 3) ,CCCC1,CCCC3,CCCC4
            
                //Console.WriteLine("Return - " + String.Join(',', WithInterlockeds())); // каждый раз новое сообщение и их индексы в порядке возростания, но сообщения одного писателя могут записаться несколько раз
                //WithInterlockeds();
                // примеры: 1) AAAA1,AAAA2,CCCC3,CCCC4; 2) AAAA1,DDDD2,AAAA3,BBBB4; 3) AAAA1,AAAA2,AAAA3,AAAA4
            }
            t2 = DateTime.Now;
            Console.WriteLine((t2-t1)/t);
        }
    }
}
