using System;

using System.Threading;
using System.Threading.Tasks;

using System.Diagnostics;
using System.Collections.Generic;

namespace lab2
{
    class Program
    {
        public static void init_vec(double[] vec, int N)
        {
            for (int i=0; i<N; ++i) { vec[i] = i; }
        }
        public static void out_vec(double[] vec, int N)
        {
            for (int i=0; i<N; ++i) { Console.Write($"{vec[i]} "); }
            Console.WriteLine();
        }
        public static void calc_vec(double[] vec, int S, int N, int M, int K)
        {
            for (int i=S; i<N; i += M)
            {
                for (int j=0; j<K; ++j) { vec[i] = Math.Pow(vec[i], 1.789); }
            }
        }
        /*static void Main(string[] args)
        {
            Console.WriteLine("1 Задание");
            const int N = 100000;
            const int K = 100;
            double [] vec =  
                new double [N];
            init_vec(vec, N);

            DateTime t1 = DateTime.Now;


            calc_vec(vec, 0, N, 1, K);


            DateTime t2 = DateTime.Now; 
            Console.WriteLine("Общее - " + (t2-t1).ToString());
        }*/
        /*static void Main(string[] args)
        {
            Console.WriteLine("2 Задание");
            const int N = 100000;
            const int K = 100;
            const int M = 10;
            double [] vec =  
                new double [N];
            init_vec(vec, N);
            
            Thread [] thrs =  
                new Thread [M];

            DateTime t1 = DateTime.Now;
            
            int n = N/M;
            for (int i=0; i<M; ++i)
            {
                thrs[i] = new Thread((object state) => { object[] array = state as object[]; calc_vec(vec, (int)array[0], (int)array[1], 1, (int)array[2]); });

                int N_ = (i+1)*n;
                thrs[i].Start(new object[] { i*n, ((N - N_) == 1) ? N_+1 : N_, K });
            }
            foreach(Thread t in thrs) { t.Join(); }


            DateTime t2 = DateTime.Now; 
            Console.WriteLine("Общее - " + (t2-t1).ToString());
        }*/
        /*static void Main(string[] args)
        {
            Console.WriteLine("5 Задание");
            const int N = 100000;
            //const int K = 1;
            const int M = 10;
            double [] vec =  
                new double [N];
            init_vec(vec, N);
            
            Thread [] thrs =  
                new Thread [M];

            DateTime t1 = DateTime.Now;
            
            int n = N/M;
            for (int i=0; i<M; ++i)
            {
                thrs[i] = new Thread((object state) => { object[] array = state as object[]; calc_vec(vec, (int)array[0], (int)array[1], 1, (int)array[2]); });

                int N_ = (i+1)*n;
                thrs[i].Start(new object[] { i*n, ((N - N_) == 1) ? N_+1 : N_, N_ });
            }
            foreach(Thread t in thrs) { t.Join(); }


            DateTime t2 = DateTime.Now; 
            Console.WriteLine("Общее - " + (t2-t1).ToString());
        }*/
        static void Main(string[] args)
        {
            Console.WriteLine("6 Задание");
            const int N = 100000;
            //const int K = 1;
            const int M = 10;
            double [] vec =  
                new double [N];
            init_vec(vec, N);
            
            Thread [] thrs =  
                new Thread [M];

            DateTime t1 = DateTime.Now;
            
            int n = N/M;
            for (int i=0; i<M; ++i)
            {
                thrs[i] = new Thread((object state) => { object[] array = state as object[]; calc_vec(vec, (int)array[0], (int)array[1], (int)array[2], (int)array[3]); });

                thrs[i].Start(new object[] { i, N, M, (i+1)*n });
            }
            foreach(Thread t in thrs) { t.Join(); }


            DateTime t2 = DateTime.Now; 
            Console.WriteLine("Общее - " + (t2-t1).ToString());
        }
    }
}
