using System;

using System.Threading;
using System.Threading.Tasks;

namespace lab1
{
    class Program
    {
        /*static void Main(string[] args) {
            // создаем новый поток
            Thread myThread = new Thread(new ThreadStart(Count));
            myThread.Start(); // запускаем поток
    
            for (int i = 1; i < 9; i++)
            {
                Console.WriteLine("Главный поток:");
                Console.WriteLine(i * i);
                Thread.Sleep(300);
            }
            Console.ReadLine();
        }
        public static void Count() {
            for (int i = 1; i < 9; i++)
            {
                Console.WriteLine("Второй поток:");
                Console.WriteLine(i * i);
                Thread.Sleep(400);
            }
        }*/

        /*static void Main(string[] args) {
            int number = 4;
            // создаем новый поток
            Thread myThread = new Thread(new ParameterizedThreadStart(Count));
            myThread.Start(number); 
    
            for (int i = 1; i < 9; i++)
            {
                Console.WriteLine("Главный поток:");
                Console.WriteLine(i * i);
                Thread.Sleep(300);
            }
    
            Console.ReadLine();
        }
        public static void Count(object x) {
            for (int i = 1; i < 9; i++)
            {
                int n = (int)x;
    
                Console.WriteLine("Второй поток:");
                Console.WriteLine(i*n);
                Thread.Sleep(400);
            }
        }*/

        static void Main() {
            int nWorkerThreads;
            int nCompletionThreads;
            ThreadPool.GetMaxThreads(out nWorkerThreads, out nCompletionThreads);
            Console.WriteLine("Максимальное количество потоков: " + nWorkerThreads
                + "\nПотоков ввода-вывода доступно: " + nCompletionThreads);
            // Объявляем массив сигнальных сообщений
            ManualResetEvent [] events =  
                new ManualResetEvent [5]; 

            for (int i = 0; i < 5; i++)
            {
                events[i] = new ManualResetEvent(false);
                ThreadPool.QueueUserWorkItem(JobForAThread, events[i]);
            }
            WaitHandle.WaitAll(events);
        }
        static void JobForAThread(object state) {
            for (int i = 0; i < 3; i++)
            {
                Console.WriteLine("цикл {0}, выполнение внутри потока из пула {1}",
                    i, Thread.CurrentThread.ManagedThreadId);
                Thread.Sleep(50);
            }
            //ManualResetEvent ev = (ManualResetEvent)state;
            //ev.Set();
            ((ManualResetEvent)state).Set();
        }

        /*delegate int Operation(int x, int y);
        static void Main(string[] args) {
            Operation operation = (x, y) => x + y;
            Console.WriteLine(operation(10, 20));       // 30
            Console.WriteLine(operation(40, 20));       // 60
            Console.Read();
        }*/



        /*static void Main(string[] args) {
            Console.WriteLine("последовательно");
            DateTime t1 = DateTime.Now;

            for (int b=0; b<5; ++b) {
                double x = 12345.6789; 
                for (int i = 0; i < 10000; i++)
                {
                    for (int j = 0; j < 10000; j++) 
                    { 
                        x = Math.Sqrt(x);  	 	
                        x = x + 0.000000001; 
                        x = Math.Pow(x, 2); 
                    }
                }
                Console.WriteLine("A: " + (x).ToString());

                x = 12345.6789; 
                for (int i = 0; i < 10000; i++)
                {
                    for (int j = 0; j < 10000; j++) 
                    { 
                        x = Math.Sqrt(x);  	 	
                        x = x + 0.000000001; 
                        x = Math.Pow(x, 2); 
                    }
                }
                Console.WriteLine("B: " + (x).ToString());

                x = 12345.6789; 
                for (int i = 0; i < 10000; i++)
                {
                    for (int j = 0; j < 10000; j++) 
                    { 
                        x = Math.Sqrt(x);  	 	
                        x = x + 0.000000001; 
                        x = Math.Pow(x, 2); 
                    }
                }
                Console.WriteLine("C: " + (x).ToString());

                x = 12345.6789; 
                for (int i = 0; i < 10000; i++)
                {
                    for (int j = 0; j < 10000; j++) 
                    { 
                        x = Math.Sqrt(x);  	 	
                        x = x + 0.000000001; 
                        x = Math.Pow(x, 2); 
                    }
                }
                Console.WriteLine("D: " + (x).ToString());

                x = 12345.6789; 
                for (int i = 0; i < 10000; i++)
                {
                    for (int j = 0; j < 10000; j++) 
                    { 
                        x = Math.Sqrt(x);  	 	
                        x = x + 0.000000001; 
                        x = Math.Pow(x, 2); 
                    }
                }
                Console.WriteLine("E: " + (x).ToString());
            }


            DateTime t2 = DateTime.Now; 
            Console.WriteLine("Общее - " + (t2-t1).ToString());
        }*/

        /*static void Main(string[] args) {
            Console.WriteLine("параллельно с лямбдой");

            Action<char> lambda = ((state) => {
                                                double x = 12345.6789; 
                                                for (int i = 0; i < 10000; i++)
                                                {
                                                    for (int j = 0; j < 10000; j++) 
                                                    { 
                                                        x = Math.Sqrt(x);  	 	
                                                        x = x + 0.000000001; 
                                                        x = Math.Pow(x, 2); 
                                                    }
                                                }
                                                Console.WriteLine( (char)state + ": " + x.ToString() );
                                            });
            
            DateTime t1 = DateTime.Now;

            for (int b=0; b<5; ++b) {

                Thread thr1 = new Thread(() => lambda('A'));
                Thread thr2 = new Thread(() => lambda('B'));
                Thread thr3 = new Thread(() => lambda('C'));
                Thread thr4 = new Thread(() => lambda('D'));
                Thread thr5 = new Thread(() => lambda('E'));

                thr1.Start();
                thr2.Start();
                thr3.Start();
                thr4.Start();
                thr5.Start();

                // Дожидаемся завершения задач 
                thr1.Join();
                thr2.Join();
                thr3.Join();
                thr4.Join();
                thr5.Join();
            }

                DateTime t2 = DateTime.Now; 
                Console.WriteLine("Общее - " + (t2-t1).ToString());
        }*/

        /*static void Main(string[] args) {
            Console.WriteLine("параллельно с функцией");
            
            DateTime t1 = DateTime.Now;


            for (int b=0; b<5; ++b) {
                Thread thr1 = new Thread(new ParameterizedThreadStart(Func));
                Thread thr2 = new Thread(new ParameterizedThreadStart(Func));
                Thread thr3 = new Thread(new ParameterizedThreadStart(Func));
                Thread thr4 = new Thread(new ParameterizedThreadStart(Func));
                Thread thr5 = new Thread(new ParameterizedThreadStart(Func));

                thr1.Start('A');
                thr2.Start('B');
                thr3.Start('C');
                thr4.Start('D');
                thr5.Start('E');

                // Дожидаемся завершения задач 
                thr1.Join();
                thr2.Join();
                thr3.Join();
                thr4.Join();
                thr5.Join();
            }

            DateTime t2 = DateTime.Now; 
            Console.WriteLine("Общее - " + (t2-t1).ToString());
        }
        public static void Func(object state) {
            double x = 12345.6789; 
            for (int i = 0; i < 10000; i++)
            {
                for (int j = 0; j < 10000; j++) 
                { 
                    x = Math.Sqrt(x);  	 	
                    x = x + 0.000000001; 
                    x = Math.Pow(x, 2); 
                }
            }
            Console.WriteLine( (char)state + ": " + x.ToString() );
        }*/
        
        /*static void Main() {
            Console.WriteLine("параллельно с пулом");
            
            // Объявляем массив сигнальных сообщений
            ManualResetEvent [] events =  
                new ManualResetEvent [5];
            char [] ch =  
                new char [5]{'A', 'B', 'C', 'D', 'E'};

            Action<object> lambda = ((state) => {
                                                object[] array = state as object[];
                                                double x = 12345.6789; 
                                                for (int i = 0; i < 10000; i++)
                                                {
                                                    for (int j = 0; j < 10000; j++) 
                                                    { 
                                                        x = Math.Sqrt(x);  	 	
                                                        x = x + 0.000000001; 
                                                        x = Math.Pow(x, 2); 
                                                    }
                                                }
                                                Console.WriteLine( (char)array[0] + ": " + x.ToString() );
                                                ((ManualResetEvent)array[1]).Set();
                                            });

            DateTime t1 = DateTime.Now;

            for (int b=0; b<5; ++b) {
                for (int i = 0; i < 5; i++)
                {
                    events[i] = new ManualResetEvent(false);
                    ThreadPool.QueueUserWorkItem(new WaitCallback(lambda), new object[] { ch[i], events[i] });
                }
                WaitHandle.WaitAll(events);
            }

            DateTime t2 = DateTime.Now; 
            Console.WriteLine("Общее - " + (t2-t1).ToString());
        }*/

        /*static void Main(string[] args) {
            Console.WriteLine("приоритет - 5 потоков");

            DateTime t1 = DateTime.Now;

            Thread thr1 = new Thread(new ParameterizedThreadStart(Func));
            Thread thr2 = new Thread(new ParameterizedThreadStart(Func));
            Thread thr3 = new Thread(new ParameterizedThreadStart(Func));
            Thread thr4 = new Thread(new ParameterizedThreadStart(Func));
            Thread thr5 = new Thread(new ParameterizedThreadStart(Func));
            
            thr1.Priority = (ThreadPriority.Lowest);
            thr2.Priority = (ThreadPriority.BelowNormal);
            thr3.Priority = (ThreadPriority.Normal);
            thr4.Priority = (ThreadPriority.AboveNormal);
            thr5.Priority = (ThreadPriority.Highest);
            
            thr1.Start('A'); thr2.Start('B'); thr3.Start('C');
            thr4.Start('D'); thr5.Start('E');

            // Дожидаемся завершения задач 
            thr1.Join(); thr2.Join(); thr3.Join();
            thr4.Join(); thr5.Join();

            DateTime t2 = DateTime.Now; 
            Console.WriteLine("Общее - " + (t2-t1).ToString());
        }
        public static void Func(object state) {
            double x = 12345.6789;
            for (int i = 0; i < 10000; i++)
            {
                for (int j = 0; j < 10000; j++) 
                { 
                    x = Math.Sqrt(x);  	 	
                    x = x + 0.000000001; 
                    x = Math.Pow(x, 2); 
                }
            }
            Console.WriteLine( (char)state + ": " + x.ToString() );
        }*/
        
        /*static void Main(string[] args) {
            Console.WriteLine("приоритет - 4 потоков");

            DateTime t1 = DateTime.Now;

            Thread thr1 = new Thread(new ParameterizedThreadStart(Func));
            Thread thr2 = new Thread(new ParameterizedThreadStart(Func));
            Thread thr3 = new Thread(new ParameterizedThreadStart(Func));
            Thread thr4 = new Thread(new ParameterizedThreadStart(Func));
            
            thr1.Priority = (ThreadPriority.Lowest);
            thr2.Priority = (ThreadPriority.BelowNormal);
            thr3.Priority = (ThreadPriority.AboveNormal);
            thr4.Priority = (ThreadPriority.Highest);
            
            thr1.Start('A'); thr2.Start('B'); thr3.Start('C');
            thr4.Start('D');

            // Дожидаемся завершения задач 
            thr1.Join(); thr2.Join(); thr3.Join();
            thr4.Join();

            DateTime t2 = DateTime.Now; 
            Console.WriteLine("Общее - " + (t2-t1).ToString());
        }
        public static void Func(object state) {
            double x = 12345.6789;
            for (int i = 0; i < 10000; i++)
            {
                for (int j = 0; j < 10000; j++) 
                { 
                    x = Math.Sqrt(x);  	 	
                    x = x + 0.000000001; 
                    x = Math.Pow(x, 2); 
                }
            }
            Console.WriteLine( (char)state + ": " + x.ToString() );
        }*/
        
        /*static void Main(string[] args) {
            Console.WriteLine("приоритет - 3 потоков");

            DateTime t1 = DateTime.Now;

            Thread thr1 = new Thread(new ParameterizedThreadStart(Func));
            Thread thr2 = new Thread(new ParameterizedThreadStart(Func));
            Thread thr3 = new Thread(new ParameterizedThreadStart(Func));
            
            thr1.Priority = (ThreadPriority.Lowest);
            thr2.Priority = (ThreadPriority.BelowNormal);
            thr3.Priority = (ThreadPriority.Highest);
            
            thr1.Start('A'); thr2.Start('B'); thr3.Start('C');

            // Дожидаемся завершения задач 
            thr1.Join(); thr2.Join(); thr3.Join();

            DateTime t2 = DateTime.Now; 
            Console.WriteLine("Общее - " + (t2-t1).ToString());
        }
        public static void Func(object state) {
            double x = 12345.6789;
            for (int i = 0; i < 10000; i++)
            {
                for (int j = 0; j < 10000; j++) 
                { 
                    x = Math.Sqrt(x);  	 	
                    x = x + 0.000000001; 
                    x = Math.Pow(x, 2); 
                }
            }
            Console.WriteLine( (char)state + ": " + x.ToString() );
        }*/
    }
}
