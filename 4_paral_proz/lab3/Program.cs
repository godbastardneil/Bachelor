using System;
using System.Collections.Generic;
using System.Threading;


namespace lab3
{
    class Program
    {
        static List<int> resheto_eratosfena(int start, int end)
        {
            List<int> pc = new List<int>();

            if (start < 2) { start = 2; }
            if (end == start) { return new List<int>() {start}; }
            if (end < start) { start -= end; end += start; start = end - start; }
            
            for (int i=2; i<=end; ++i) { pc.Add(i); }

            for (int i=0; i < pc.Count; ++i)
            {
                for (int j=2; j<pc.Count; ++j) { pc.Remove(pc[i] * j); }
            }
            for (int j=2; j<start; ++j) { pc.Remove(j); }

            return pc;
        }


        static void prov_na_razloh(List<int> pc, int start, int end, bool[] checks)
        {
            for (int i=start; i<=end; ++i)
            {
                bool tmp = true;
                for (int j=0; j<pc.Count && tmp; ++j)
                {
                    if (i%pc[j] == 0) { tmp = false; }
                }
                if (!tmp) { checks[i] = tmp; }
            }
        }
        static List<int> prov_na_razloh(List<int> pc, int start, int end)
        {
            List<int> res = new List<int>();

            for (int i=start; i<=end; ++i)
            {
                bool tmp = true;
                for (int j=0; j<pc.Count && tmp; ++j)
                {
                    if (i%pc[j] == 0) { tmp = false; }
                }
                if (tmp) { res.Add(i); }
            }

            return res;
        }


        static List<int> mod_resheto_eratosfena(int n)
        {
            int sqrt_n = (int)Math.Ceiling(Math.Sqrt(n));

            List<int> pc = resheto_eratosfena(2, sqrt_n);
            pc.AddRange( prov_na_razloh(pc, sqrt_n, n) );

            return pc;
        }
        
        static List<int> par1_resheto_eratosfena(int n, int m)
        {
            int sqrt_n = (int)Math.Ceiling(Math.Sqrt(n));

            List<int> pc = resheto_eratosfena(2, sqrt_n);
            
            Thread [] thrs =
                new Thread [m];
            List<int> [] lists =
                new List<int> [m];
            bool[] checks = new bool[n+1];
            for (int i=0; i<sqrt_n; ++i) { checks[i] = false; }
            for (int i=sqrt_n; i<=n; ++i) { checks[i] = true; }
            
            int nn = (n - sqrt_n)/m;
            for (int i=0; i<m; ++i)
            {
                thrs[i] = new Thread((object state) =>
                {
                    object[] arr = state as object[];
                    prov_na_razloh(pc, (int)arr[0], (int)arr[1], checks);
                });

                int N = sqrt_n+(i+1)*nn;
                thrs[i].Start(new object[] { sqrt_n+i*nn, ((n-N) == 1) ? N+1 : N });
            }
            foreach(Thread t in thrs) { t.Join(); }

            for (int i=sqrt_n+1; i<=n; ++i) { if (checks[i]) { pc.Add(i); } }

            return pc;
        }
        
        static List<int> par2_resheto_eratosfena(int n, int m)
        {
            int sqrt_n = (int)Math.Ceiling(Math.Sqrt(n));

            List<int> pc = resheto_eratosfena(2, sqrt_n);
            
            Thread [] thrs =
                new Thread [m];
                
            bool[] checks = new bool[n+1];
            for (int i=0; i<sqrt_n; ++i) { checks[i] = false; }
            for (int i=sqrt_n; i<=n; ++i) { checks[i] = true; }
            
            int nn = pc.Count/m;
            for (int i=0; i<m; ++i)
            {
                thrs[i] = new Thread((object state) =>
                {
                    object[] arr = state as object[];
                    prov_na_razloh(pc.GetRange((int)arr[0], (int)arr[1]), sqrt_n, n, checks);
                });

                thrs[i].Start(new object[] { i*nn, nn });
            }
            foreach(Thread t in thrs) { t.Join(); }

            for (int i=sqrt_n+1; i<=n; ++i) { if (checks[i]) { pc.Add(i); } }

            return pc;
        }

        static List<int> par3_resheto_eratosfena(int n, int m)
        {
            int sqrt_n = (int)Math.Ceiling(Math.Sqrt(n));
            List<int> pc = resheto_eratosfena(2, sqrt_n);

            bool[] checks = new bool[n+1];
            for (int i=0; i<sqrt_n; ++i) { checks[i] = false; }
            for (int i=sqrt_n; i<=n; ++i) { checks[i] = true; }

            ManualResetEvent [] events =  
                new ManualResetEvent [m];

            int nn = (n - sqrt_n)/m;
            for (int i=0; i<m; ++i)
            {
                events[i] = new ManualResetEvent(false);
                int N = sqrt_n+(i+1)*nn;
                ThreadPool.QueueUserWorkItem(new WaitCallback((object state) => {
                                                object[] arr = state as object[];
                                                
                                                prov_na_razloh(pc, (int)arr[0], (int)arr[1], checks);
                                                ((ManualResetEvent)arr[2]).Set();
                                            }),
                                            new object[] { sqrt_n+i*nn, ((n-N) == 1) ? N+1 : N, events[i] });
            }
            WaitHandle.WaitAll(events);

            for (int i=sqrt_n+1; i<=n; ++i) { if (checks[i]) { pc.Add(i); } }

            return pc;
        }

        static List<int> par4_resheto_eratosfena(int n, int m)
        {
            int sqrt_n = (int)Math.Ceiling(Math.Sqrt(n));

            List<int> pc = resheto_eratosfena(2, sqrt_n);
            
            Thread [] thrs =
                new Thread [m];
                
            bool[] checks = new bool[n+1];
            for (int i=0; i<sqrt_n; ++i) { checks[i] = false; }
            for (int i=sqrt_n; i<=n; ++i) { checks[i] = true; }
            
            int tmp = 0;
            for (int i=0; i<m; ++i)
            {
                thrs[i] = new Thread(() =>
                {
                    while (tmp < pc.Count)
                    {
                        ++tmp;
                        prov_na_razloh(pc.GetRange(tmp-1, 1), sqrt_n, n, checks);
                    }
                });

                thrs[i].Start();
            }
            foreach(Thread t in thrs) { t.Join(); }

            for (int i=sqrt_n+1; i<=n; ++i) { if (checks[i]) { pc.Add(i); } }

            return pc;
        }


        static void Main(string[] args)
        {
            int n = 100000;
            int m = 10;
            Console.WriteLine($"Диапазон {n}, Потоков {m}");
            DateTime t1, t2;
            TimeSpan [] t = new TimeSpan [6];


                t1 = DateTime.Now;
                resheto_eratosfena(2, n);
                t2 = DateTime.Now;
                t[0] = (t2-t1);

                t1 = DateTime.Now;
                mod_resheto_eratosfena(n);
                t2 = DateTime.Now;
                t[1] = (t2-t1);

                t1 = DateTime.Now;
                par1_resheto_eratosfena(n, m);
                t2 = DateTime.Now;
                t[2] = (t2-t1);

                t1 = DateTime.Now;
                par2_resheto_eratosfena(n, m);
                t2 = DateTime.Now;
                t[3] = (t2-t1);

                t1 = DateTime.Now;
                par3_resheto_eratosfena(n, m);
                t2 = DateTime.Now;
                t[4] = (t2-t1);

                t1 = DateTime.Now;
                par4_resheto_eratosfena(n, m);
                t2 = DateTime.Now;
                t[5] = (t2-t1);


            for (int i=0; i<9; ++i)
            {
                t1 = DateTime.Now;
                resheto_eratosfena(2, n);
                t2 = DateTime.Now;
                t[0] += (t2-t1);

                t1 = DateTime.Now;
                mod_resheto_eratosfena(n);
                t2 = DateTime.Now;
                t[1] += (t2-t1);

                t1 = DateTime.Now;
                par1_resheto_eratosfena(n, m);
                t2 = DateTime.Now;
                t[2] += (t2-t1);

                t1 = DateTime.Now;
                par2_resheto_eratosfena(n, m);
                t2 = DateTime.Now;
                t[3] += (t2-t1);

                t1 = DateTime.Now;
                par3_resheto_eratosfena(n, m);
                t2 = DateTime.Now;
                t[4] += (t2-t1);

                t1 = DateTime.Now;
                par4_resheto_eratosfena(n, m);
                t2 = DateTime.Now;
                t[5] += (t2-t1);
            }

            for (int i=0; i<6; ++i)
            {
                Console.WriteLine($"{i} - " + t[i]/10);
            }
        }
    }
}
